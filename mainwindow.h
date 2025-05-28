#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QStringList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onCalculateClicked();            // расчет суточной нормы калорий
    void onGoalChanged(const QString &);  // обработка цели (похудение и т.д.)
    void onMealCalculateClicked();        // расчет калорий по еде

private:
    Ui::MainWindow *ui;

    double getActivityFactor(int index);  // возвращает коэффициент активности

    // работа с таблицей продуктов
    QMap<QString, int> loadCaloriesFromFile(const QString &filePath);
    int calculateMealCalories(const QStringList &meals, const QMap<QString, int> &table);
};

#endif // MAINWINDOW_H
