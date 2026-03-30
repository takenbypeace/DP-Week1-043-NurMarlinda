#pragma once
#include <iostream>

using namespace std;

class IInputGenerator {
public:
  virtual ~IInputGenerator() = default;
  virtual int generateInput() = 0;
};

class IScoringRule {
public:
  virtual ~IScoringRule() = default;
  virtual int calculateScore(int input) = 0;
};

class IRewardRule {
public:
  virtual ~IRewardRule() = default;
  virtual int calculateReward(int baseScore) = 0;
};

class ShopSystem {
public:
  void showOffer()
  {
    cout << "[SHOP] offered: Bonus (+2) cost 2\n";
    cout << "[SHOP] skipped\n";
  }
};