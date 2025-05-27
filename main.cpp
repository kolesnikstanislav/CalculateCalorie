#include <iostream>
#include <string>
#include <limits>
#include <sstream>
#include <cctype>

// --- Constants ---
class Constants {
public:
    static constexpr double activityFactors[5] = { 1.2, 1.375, 1.55, 1.725, 1.9 };
};
constexpr double Constants::activityFactors[5];

// --- Singleton Settings ---
class Settings {
private:
    static Settings* instance;
    Settings() {}

public:
    static Settings* getInstance() {
        if (!instance) {
            instance = new Settings();
        }
        return instance;
    }

    double getDefaultLeanMass() const { return 50.0; }
};
Settings* Settings::instance = nullptr;

// --- User Data ---
class User {
public:
    std::string name;
    char gender;
    double weight;
    double height;
    int age;
    int activityIndex;
    double leanMass;

    User() : gender('M'), weight(0), height(0), age(0), activityIndex(0), leanMass(0) {}
};

// --- Activity Level ---
class ActivityLevel {
public:
    static double getFactor(int index) {
        if (index >= 0 && index < 5)
            return Constants::activityFactors[index];
        return 1.0;
    }
};

// --- BMR Strategy ---
class BMRCalculator {
public:
    virtual double calculate(const User& user) = 0;
    virtual ~BMRCalculator() {}
};

class MifflinStJeorCalculator : public BMRCalculator {
public:
    double calculate(const User& user) override {
        if (user.gender == 'M' || user.gender == 'm')
            return 10 * user.weight + 6.25 * user.height - 5 * user.age + 5;
        else
            return 10 * user.weight + 6.25 * user.height - 5 * user.age - 161;
    }
};

class HarrisBenedictCalculator : public BMRCalculator {
public:
    double calculate(const User& user) override {
        if (user.gender == 'M' || user.gender == 'm')
            return 66.47 + 13.75 * user.weight + 5.003 * user.height - 6.755 * user.age;
        else
            return 655.1 + 9.563 * user.weight + 1.850 * user.height - 4.676 * user.age;
    }
};

class KatchMcArdleCalculator : public BMRCalculator {
public:
    double calculate(const User& user) override {
        return 370 + 21.6 * user.leanMass;
    }
};

// --- Factory Method ---
class BMRCalculatorFactory {
public:
    static BMRCalculator* createCalculator(const std::string& type) {
        if (type == "mifflin") return new MifflinStJeorCalculator();
        if (type == "harris")  return new HarrisBenedictCalculator();
        if (type == "katch")   return new KatchMcArdleCalculator();
        return nullptr;
    }
};

// --- Calorie Calculator ---
class CalorieCalculator {
    BMRCalculator* bmrCalculator;

public:
    CalorieCalculator(BMRCalculator* calculator) : bmrCalculator(calculator) {}

    double calculateTotal(const User& user) {
        double bmr = bmrCalculator->calculate(user);
        return bmr * ActivityLevel::getFactor(user.activityIndex);
    }
};

// --- Input Handler ---
class InputHandler {
public:
    void fillUser(User& user) {
        std::string input;

        std::cout << "Введите имя: ";
        std::getline(std::cin, user.name);

        std::cout << "Введите пол (M/F): ";
        std::getline(std::cin, input);
        if (!input.empty()) user.gender = input[0];

        std::cout << "Введите вес (в кг): ";
        std::getline(std::cin, input);
        user.weight = std::stod(input);

        std::cout << "Введите рост (в см): ";
        std::getline(std::cin, input);
        user.height = std::stod(input);

        std::cout << "Введите возраст: ";
        std::getline(std::cin, input);
        user.age = std::stoi(input);

        std::cout << "Выберите уровень активности (0-4):\n";
        std::cout << "0. Малоподвижный\n1. Легкая активность\n2. Умеренная\n3. Активный\n4. Очень активный\n";
        std::getline(std::cin, input);
        user.activityIndex = std::stoi(input);
    }

    std::string askFormulaType() {
        std::string choice;
        std::cout << "\nВыберите формулу расчета BMR:\n";
        std::cout << "1. mifflin — Миффлина-Сан Жеора\n";
        std::cout << "2. harris — Харриса-Бенедикта\n";
        std::cout << "3. katch — Катча-МкАрдла\n";
        std::cout << "Введите название или номер: ";
        std::getline(std::cin, choice);

        for (char& c : choice) c = std::tolower(c);

        if (choice == "1" || choice == "mifflin") return "mifflin";
        if (choice == "2" || choice == "harris") return "harris";
        if (choice == "3" || choice == "katch") return "katch";

        return "invalid";
    }

    void askLeanMass(User& user) {
        std::string input;
        std::cout << "Введите вашу мышечную массу (в кг): ";
        std::getline(std::cin, input);
        try {
            user.leanMass = std::stod(input);
        }
        catch (...) {
            user.leanMass = 0;
        }
    }
};

// --- Output Handler ---
class OutputHandler {
public:
    void printResult(const User& user, double calories) {
        std::cout << "\nПривет, " << user.name << "!\n";
        std::cout << "Ваша суточная норма калорий: " << calories << " ккал\n";
    }
};

// --- Validator ---
class Validator {
public:
    static bool validateUser(const User& user) {
        return (user.weight > 0 && user.height > 0 && user.age > 0 &&
            (user.gender == 'M' || user.gender == 'F' ||
                user.gender == 'm' || user.gender == 'f') &&
            user.activityIndex >= 0 && user.activityIndex < 5);
    }
};

// --- Main App Controller ---
class App {
    User user;
    InputHandler input;
    OutputHandler output;
    Validator validator;

public:
    void run() {
        while (true) {
            input.fillUser(user);

            if (!validator.validateUser(user)) {
                std::cout << "Ошибка: некорректные данные. Пожалуйста, введите корректные данные.\n\n";
                continue;
            }

            std::string formula;
            do {
                formula = input.askFormulaType();
                if (formula == "invalid") {
                    std::cout << "Ошибка: неизвестная формула. Пожалуйста, введите корректное название.\n\n";
                }
            } while (formula == "invalid");

            if (formula == "katch") {
                input.askLeanMass(user);
                if (user.leanMass <= 0) {
                    user.leanMass = Settings::getInstance()->getDefaultLeanMass();
                    std::cout << "(Используется значение по умолчанию для мышечной массы: "
                        << user.leanMass << " кг)\n";
                }
            }

            BMRCalculator* bmr = BMRCalculatorFactory::createCalculator(formula);
            if (!bmr) {
                std::cout << "Ошибка: невозможно создать калькулятор.\n";
                continue;
            }

            CalorieCalculator calculator(bmr);
            double totalCalories = calculator.calculateTotal(user);
            output.printResult(user, totalCalories);
            delete bmr;

            break; // завершить после успешного расчета
        }
    }
};

// --- Main ---
int main() {
    App app;
    app.run();
    return 0;
}
