#include "Interfaces.h"
#include "Rules.h"
#include "RunSession.h"

int main()
{
  RandomInputGenerator myInputGen;
  SimpleScoringRule myScoringRule;
  BonusRewardRule myRewardRule;
  ShopSystem myShop;

  RunSession session(&myInputGen, &myScoringRule, &myRewardRule, &myShop);
  session.run();

  return 0;
}