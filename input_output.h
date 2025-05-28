#pragma once
#include <iostream>
#include <string>
#include <cctype>
#include "user.h"

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

class OutputHandler {
public:
    void printResult(const User& user, double calories) {
        std::cout << "\nПривет, " << user.name << "!\n";
        std::cout << "Ваша суточная норма калорий: " << calories << " ккал\n";
    }
};
