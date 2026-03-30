#pragma once
#include "Interfaces.h"

class RunSession {
private:
  IInputGenerator* inputGen;
  IScoringRule* scoringRule;
  IRewardRule* rewardRule;
  ShopSystem* shop;
  int money;

public:
  RunSession(IInputGenerator* ig, IScoringRule* sr, IRewardRule* rr, ShopSystem* s)
  {
    inputGen = ig;
    scoringRule = sr;
    rewardRule = rr;
    shop = s;
    money = 0;
  }

  void run()
  {
    cout << "=== RUN START ===\n";
    for (int round = 1; round <= 3; round++) {
      cout << "Round " << round << "\n";

      int input = inputGen->generateInput();
      cout << "[PLAY] input generated: " << input << "\n";

      int score = scoringRule->calculateScore(input);
      cout << "[SCORE] base score: " << score << "\n";

      int reward = rewardRule->calculateReward(score);
      money += reward;
      cout << "[REWARD] gain: " << reward << " money: " << money << "\n";

      shop->showOffer();
    }
    cout << "=== RUN END ===\n";
    cout << "Final money: " << money << "\n";
  }
};