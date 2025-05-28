#pragma once
#include <iostream>
#include <string>
#include <cctype>
#include "user.h"

class InputHandler {
public:
    void fillUser(User& user) {
        std::string input;

        std::cout << "������� ���: ";
        std::getline(std::cin, user.name);

        std::cout << "������� ��� (M/F): ";
        std::getline(std::cin, input);
        if (!input.empty()) user.gender = input[0];

        std::cout << "������� ��� (� ��): ";
        std::getline(std::cin, input);
        user.weight = std::stod(input);

        std::cout << "������� ���� (� ��): ";
        std::getline(std::cin, input);
        user.height = std::stod(input);

        std::cout << "������� �������: ";
        std::getline(std::cin, input);
        user.age = std::stoi(input);

        std::cout << "�������� ������� ���������� (0-4):\n";
        std::cout << "0. �������������\n1. ������ ����������\n2. ���������\n3. ��������\n4. ����� ��������\n";
        std::getline(std::cin, input);
        user.activityIndex = std::stoi(input);
    }

    std::string askFormulaType() {
        std::string choice;
        std::cout << "\n�������� ������� ������� BMR:\n";
        std::cout << "1. mifflin � ��������-��� �����\n";
        std::cout << "2. harris � �������-���������\n";
        std::cout << "3. katch � �����-�������\n";
        std::cout << "������� �������� ��� �����: ";
        std::getline(std::cin, choice);

        for (char& c : choice) c = std::tolower(c);

        if (choice == "1" || choice == "mifflin") return "mifflin";
        if (choice == "2" || choice == "harris") return "harris";
        if (choice == "3" || choice == "katch") return "katch";

        return "invalid";
    }

    void askLeanMass(User& user) {
        std::string input;
        std::cout << "������� ���� �������� ����� (� ��): ";
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
        std::cout << "\n������, " << user.name << "!\n";
        std::cout << "���� �������� ����� �������: " << calories << " ����\n";
    }
};
