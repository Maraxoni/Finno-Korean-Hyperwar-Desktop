#pragma once

class City {
private:
    bool is_destroyed;
    bool is_upgraded;
    int farms;
    int mines;
    int reactors;
public:
    City(); // Constructor

    bool getIsDestroyed() const;
    void setIsDestroyed(bool value);

    bool getIsUpgraded() const;
    void setIsUpgraded(bool value);

    int getFarms() const;
    void setFarms(int value);

    int getMines() const;
    void setMines(int value);

    int getReactors() const;
    void setReactors(int value);
};
