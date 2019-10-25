#pragma once

#include <string>

#include "ECS.hpp"
#include "../Akuma/RNG/Dice.hpp"

struct CharacterSheet {
    std::string name = "";
    int level        = 1;
    int levelPoint   = 0;
    int exp          = 0;
    int HD           = 8;
    bool assignedHP  = false;
    int maxHP        = 0;
    int HP           = 1;
    int strength     = 10;
    int dexterity    = 10;
    int luck         = 10;
    int intelligence = 10;
    int vitality     = 10;
    int pointsLeft   = 10;
};

struct StatDescription {
    const std::string strength = "Increases damage and hit chance on strength weapons.";
    const std::string dexterity = "Increases sneak and hit on dex weapons.";
    const std::string luck = "Increases crit chance.";
    const std::string intelligence = "Does absolutely nothing, it would be ironic if you picked this.";
    const std::string vitality = "Increases health.";
};

class StatComponent : public Component {
  public:
    StatComponent();
    StatComponent(CharacterSheet newStat);
    ~StatComponent();
    void init();
    void update();
    void draw();

	auto takeDamage(int damage) -> void;
	auto setupEntity() -> void;
    auto getStrengthMod() -> int;
    auto getIntelligenceMod() -> int;
    auto getDexterityMod() -> int;
    auto getLuckMod() -> int;
    auto getVitalityMod() -> int;
    auto getStatSheet() -> CharacterSheet &;
    auto setStatSheet(CharacterSheet newStat) -> void;
    CharacterSheet stat;

  private:
    Dice diceroller;
    auto getMod(int checkStat) -> int;
};
