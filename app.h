#pragma once
#include "user.h"
#include "input_output.h"
#include "settings.h"
#include "activity.h"
#include "bmr.h"

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

            break;
        }
    }
};
