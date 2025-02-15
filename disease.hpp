#pragma once

class Disease {
    public:
        constexpr Disease(int days, float chance): duration{days}, infection_chance{chance} {}
        constexpr int get_duration() const {return duration;}
        constexpr float get_chance() const {return infection_chance;}

    private:
        int duration{};
        float infection_chance{};
};