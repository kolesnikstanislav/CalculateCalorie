#pragma once

class Constants {
public:
    static constexpr double activityFactors[5] = { 1.2, 1.375, 1.55, 1.725, 1.9 };
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
