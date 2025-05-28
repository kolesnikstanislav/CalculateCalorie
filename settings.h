#pragma once

class Settings {
private:
    static Settings* instance;
    Settings(); // приватный конструктор

public:
    static Settings* getInstance();
    double getDefaultLeanMass() const;
};
