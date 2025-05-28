#pragma once
#include <string>

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

class Validator {
public:
    static bool validateUser(const User& user) {
        return (user.weight > 0 && user.height > 0 && user.age > 0 &&
                (user.gender == 'M' || user.gender == 'F' ||
                 user.gender == 'm' || user.gender == 'f') &&
                user.activityIndex >= 0 && user.activityIndex < 5);
    }
};

class Settings {
private:
    static Settings* instance;
    Settings() {}

public:
    static Settings* getInstance() {
        if (!instance)
            instance = new Settings();
        return instance;
    }

    double getDefaultLeanMass() const { return 50.0; }
};
inline Settings* Settings::instance = nullptr;

class Constants {
public:
    static constexpr double activityFactors[5] = {1.2, 1.375, 1.55, 1.725, 1.9};
};
constexpr double Constants::activityFactors[5];

class ActivityLevel {
public:
    static double getFactor(int index) {
        if (index >= 0 && index < 5)
            return Constants::activityFactors[index];
        return 1.0;
    }
};
