#include <iostream>
#include <string>

using namespace std;

// Перечисление уровней активности
enum ActivityLevel {
    SEDENTARY = 1,     // Малоподвижный образ жизни
    LIGHT,             // Небольшая активность
    MODERATE,          // Умеренная активность
    ACTIVE,            // Активный образ жизни
    VERY_ACTIVE        // Очень активный
};

// Функция расчета базового обмена веществ по формуле Миффлина-Сан Жеора
double calculateBMR(char gender, double weight, double height, int age) {
    if (gender == 'M' || gender == 'm') {
        return 10 * weight + 6.25 * height - 5 * age + 5;
    }
    else {
        return 10 * weight + 6.25 * height - 5 * age - 161;
    }
}

// Функция для получения коэффициента активности
double getActivityFactor(ActivityLevel level) {
    switch (level) {
    case SEDENTARY: return 1.2;
    case LIGHT: return 1.375;
    case MODERATE: return 1.55;
    case ACTIVE: return 1.725;
    case VERY_ACTIVE: return 1.9;
    default: return 1.0;
    }
}

int main() {
    char gender;
    double weight, height;
    int age, activityChoice;

    cout << "Калькулятор калорий\n";
    cout << "Введите ваш пол (M/F): ";
    cin >> gender;
    cout << "Введите ваш вес (в кг): ";
    cin >> weight;
    cout << "Введите ваш рост (в см): ";
    cin >> height;
    cout << "Введите ваш возраст: ";
    cin >> age;

    cout << "\nВыберите уровень вашей активности:\n";
    cout << "1. Малоподвижный образ жизни\n";
    cout << "2. Легкая активность (спорт 1-3 раза в неделю)\n";
    cout << "3. Умеренная активность (спорт 3-5 раз в неделю)\n";
    cout << "4. Активный образ жизни (спорт 6-7 раз в неделю)\n";
    cout << "5. Очень активный (интенсивные тренировки или физическая работа)\n";
    cout << "Ваш выбор (1-5): ";
    cin >> activityChoice;

    ActivityLevel level = static_cast<ActivityLevel>(activityChoice);
    double bmr = calculateBMR(gender, weight, height, age);
    double totalCalories = bmr * getActivityFactor(level);

    cout << "\nВаша суточная норма калорий: " << totalCalories << " ккал" << endl;

    return 0;
}
