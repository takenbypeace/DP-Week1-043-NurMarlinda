#include <iostream>
#include <vector>
#include <string>

using namespace std;

// MUTABLE & SUPPORTING SYSTEMS
class Deck {
public:
    void DrawCards() { 
        cout << "[DECK] Mengocok dan membagikan kartu ke tangan pemain.\n"; 
    }
};

class Player {
public:
    void PlayHand() { 
        cout << "[PLAYER] Memilih dan memainkan kartu ke tengah meja.\n"; 
    }
    void AddMoney(int amount) { 
        cout << "[PLAYER] Menerima hadiah uang: $" << amount << ".\n"; 
    }
};

class HandEvaluator {
public:
    void EvaluateHand() { 
        cout << "[EVALUATOR] Mengevaluasi kombo kartu (Contoh: Flush).\n"; 
    }
};

class ScoringSystem {
public:
    int CalculateScore() {
        cout << "[SCORING] Menghitung total chips dan multiplier.\n";
        return 150; // Placeholder
    }
};

class ShopSystem {
public:
    void EnterShop() { 
        cout << "[SHOP] Memasuki toko untuk membeli upgrade (Joker/Tarot).\n"; 
    }
};

// INVARIANT STRUCTURE
class RunSession {
private:
    Deck deck;
    Player player;
    HandEvaluator evaluator;
    ScoringSystem scorer;
    ShopSystem shop;
    int currentRound;

public:
    RunSession() {
        currentRound = 1;
    }

    void StartRun() {
        cout << "=== MEMULAI RUN BALATRO ===\n";
        
        while (currentRound <= 3) {
            cout << "\n--- Ronde " << currentRound << " ---\n";

            // 1. Fase Pemain (Draw & Play)
            deck.DrawCards();
            player.PlayHand();

            // 2. Fase Evaluasi Sistem
            evaluator.EvaluateHand();
            int finalScore = scorer.CalculateScore();

            // 3. Fase Pengecekan Menang/Kalah & Reward
            int targetScore = 100 * currentRound; // Target skor yang makin susah
            if (finalScore >= targetScore) {
                cout << "[SISTEM] Target tercapai!\n";
                player.AddMoney(15);
                
                // 4. Fase Toko (Hanya jika belum ronde terakhir)
                if (currentRound < 3) {
                    shop.EnterShop();
                }
            } else {
                cout << "[SISTEM] Target gagal ditembus! GAME OVER.\n";
                break; // Hentikan permainan
            }

            // 5. Update State
            currentRound++;
        }
        
        cout << "\n=== RUN SELESAI ===\n";
    }
};

// MAIN FUNCTION
int main() {
    RunSession game;
    game.StartRun(); // Memulai core loop
    
    return 0;
}