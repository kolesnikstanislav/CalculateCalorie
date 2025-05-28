#pragma once
#include "user.h"
#include "activity.h"

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

class BMRCalculatorFactory {
public:
    static BMRCalculator* createCalculator(const std::string& type) {
        if (type == "mifflin") return new MifflinStJeorCalculator();
        if (type == "harris")  return new HarrisBenedictCalculator();
        if (type == "katch")   return new KatchMcArdleCalculator();
        return nullptr;
    }
};

class CalorieCalculator {
    BMRCalculator* bmrCalculator;

public:
    CalorieCalculator(BMRCalculator* calculator) : bmrCalculator(calculator) {}

    double calculateTotal(const User& user) {
        double bmr = bmrCalculator->calculate(user);
        return bmr * ActivityLevel::getFactor(user.activityIndex);
    }
};
