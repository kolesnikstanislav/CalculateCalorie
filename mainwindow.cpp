#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Активность
    ui->activityBox->addItems({
        "Малоподвижный",
        "Легкая активность",
        "Умеренная активность",
        "Активный образ жизни",
        "Очень активный"
    });

    // Формулы
    ui->formulaBox->addItems({
        "Mifflin-St Jeor",
        "Harris-Benedict",
        "Katch-McArdle"
    });

    // Цели
    ui->goalBox->addItems({
        "Похудение",
        "Поддержание",
        "Набор массы"
    });
    ui->goalBox->setCurrentIndex(1);

    // Сигналы
    connect(ui->goalBox, &QComboBox::currentTextChanged, this, &MainWindow::onGoalChanged);
    connect(ui->calculateButton, &QPushButton::clicked, this, &MainWindow::onCalculateClicked);
    connect(ui->mealCalcButton, &QPushButton::clicked, this, &MainWindow::onMealCalculateClicked);

    // Инициализация
    onGoalChanged(ui->goalBox->currentText());
}

MainWindow::~MainWindow() {
    delete ui;
}

double MainWindow::getActivityFactor(int index) {
    static const double factors[5] = {1.2, 1.375, 1.55, 1.725, 1.9};
    return (index >= 0 && index < 5) ? factors[index] : 1.0;
}

void MainWindow::onGoalChanged(const QString &goal) {
    if (goal == "Похудение") {
        ui->adjustSpin->setEnabled(true);
        ui->adjustSpin->setValue(-20);
    } else if (goal == "Поддержание") {
        ui->adjustSpin->setValue(0);
        ui->adjustSpin->setEnabled(false);
    } else if (goal == "Набор массы") {
        ui->adjustSpin->setEnabled(true);
        ui->adjustSpin->setValue(10);
    }
}

void MainWindow::onCalculateClicked() {
    QString genderStr = ui->genderBox->currentText();
    QString formula = ui->formulaBox->currentText();
    QString goal = ui->goalBox->currentText();
    int percent = ui->adjustSpin->value();

    bool ok1, ok2, ok3, ok4;
    double weight = ui->weightEdit->text().toDouble(&ok1);
    double height = ui->heightEdit->text().toDouble(&ok2);
    int age = ui->ageEdit->text().toInt(&ok3);
    double leanMass = ui->leanMassEdit->text().toDouble(&ok4);
    int activityIndex = ui->activityBox->currentIndex();

    if (!ok1 || !ok2 || !ok3 || (!ok4 && formula == "Katch-McArdle")) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, введите корректные данные.");
        return;
    }

    double bmr = 0;
    if (formula == "Mifflin-St Jeor") {
        bmr = (genderStr == "M")
        ? 10 * weight + 6.25 * height - 5 * age + 5
        : 10 * weight + 6.25 * height - 5 * age - 161;
    } else if (formula == "Harris-Benedict") {
        bmr = (genderStr == "M")
        ? 66.47 + 13.75 * weight + 5.003 * height - 6.755 * age
        : 655.1 + 9.563 * weight + 1.850 * height - 4.676 * age;
    } else if (formula == "Katch-McArdle") {
        if (leanMass <= 0) leanMass = 50.0;
        bmr = 370 + 21.6 * leanMass;
    }

    double totalCalories = bmr * getActivityFactor(activityIndex);

    if (goal == "Похудение") {
        totalCalories -= totalCalories * percent / 100.0;
    } else if (goal == "Набор массы") {
        totalCalories += totalCalories * percent / 100.0;
    }

    ui->resultLabel->setText("Суточная норма калорий: " +
                             QString::number(totalCalories, 'f', 1) + " ккал");
}

QMap<QString, int> MainWindow::loadCaloriesFromFile(const QString &filePath) {
    QMap<QString, int> table;
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            QStringList parts = line.split(':');
            if (parts.size() == 2) {
                QString food = parts[0].trimmed().toLower();
                int cal = parts[1].trimmed().toInt();
                table[food] = cal;
            }
        }
        file.close();
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл food_calories.txt");
    }
    return table;
}

int MainWindow::calculateMealCalories(const QStringList &meals, const QMap<QString, int> &table) {
    int total = 0;
    for (const QString &dish : meals) {
        QString clean = dish.trimmed().toLower();
        if (table.contains(clean)) {
            total += table[clean];
        }
    }
    return total;
}

void MainWindow::onMealCalculateClicked() {
    QString path = "food_calories.txt";  // 🔗 файл должен лежать рядом с .exe
    QMap<QString, int> table = loadCaloriesFromFile(path);

    QStringList breakfast = ui->breakfastEdit->toPlainText().split(',', Qt::SkipEmptyParts);
    QStringList lunch = ui->lunchEdit->toPlainText().split(',', Qt::SkipEmptyParts);
    QStringList snack = ui->snackEdit->toPlainText().split(',', Qt::SkipEmptyParts);
    QStringList dinner = ui->dinnerEdit->toPlainText().split(',', Qt::SkipEmptyParts);

    int total = 0;
    total += calculateMealCalories(breakfast, table);
    total += calculateMealCalories(lunch, table);
    total += calculateMealCalories(snack, table);
    total += calculateMealCalories(dinner, table);

    ui->foodResultLabel->setText("Калорийность еды за день: " +
                                 QString::number(total) + " ккал");
}
