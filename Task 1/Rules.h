#pragma once
#include "Interfaces.h" 
#include <cstdlib>
#include <ctime>

class RandomInputGenerator : public IInputGenerator {
public:
  RandomInputGenerator() { srand(time(0)); }
  int generateInput() override { return (rand() % 10) + 1; }
};

class SimpleScoringRule : public IScoringRule {
public:
  int calculateScore(int input) override { return input; }
};

class BonusRewardRule : public IRewardRule {
public:
  int calculateReward(int baseScore) override { return baseScore + 2; }
};