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
