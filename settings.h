#pragma once

class Settings {
private:
    static Settings* instance;
    Settings(); // ��������� �����������

public:
    static Settings* getInstance();
    double getDefaultLeanMass() const;
};
