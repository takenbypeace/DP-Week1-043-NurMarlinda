# DP-Week2-043-NurMarlinda



##### Step 1 — Write the Core Loop

Game saya adalah game roguelike poker yang terinspirasi dari Balatro. Core loop permainannya adalah :

1. **Player draws and plays cards :** Sistem memberikan 5 kartu kepada pemain, lalu pemain memilih kartu mana saja yang akan dimainkan untuk membentuk kombo.
2. **System evaluates score :** Sistem (melalui HandEvaluator) mengevaluasi nama kombo, menghitung chips dan multiplier dari kartu tersebut, lalu mengecek apakah total skornya berhasil menembus target ronde.
3. **Reward or penalty is given :** Jika target skor tercapai, pemain mendapatkan hadiah uang (contohnya $15). Jika skor tidak mencapai target, permainan langsung dihentikan (Game Over).
4. **Game state updates :** Kartu di tangan pemain dibersihkan. Jika pemain menang dan belum mencapai ronde terakhir, pemain akan masuk ke Shop Phase untuk membeli upgrade. Setelah itu, angka ronde bertambah.
5. **Repeat :** Siklus ini berulang terus sampai pemain berhasil menyelesaikan 3 ronde atau kalah di tengah jalan.



##### Step 2 — Identify the Invariants

**1. Which steps in your loop must NEVER change order?**

* Fase pembagian kartu dan pemilihan kartu oleh pemain (PlayHand).
* Fase evaluasi kombo dan penghitungan skor (CalculateScore).
* Fase pengecekan kondisi menang/kalah dan pemberian reward uang.
* Fase masuk ke toko (EnterShop).



**2. Which components must always exist for the game to function?**

* Player (untuk menyimpan uang, state, dan kartu di tangan).
* Deck (untuk memberikan input berupa kartu).
* HandEvaluator (untuk menentukan jenis kombo).
* ScoringSystem (untuk menghitung chips dan multiplier).
* RunSession (sebagai pengontrol round game).



**3. What would break if the order changes?**

Jika urutan di atas diubah, logika game akan hancur dan menjadi tidak masuk akal. Contohnya :

* Jika sistem menghitung skor (Evaluasi) sebelum pemain memilih kartu, maka HandEvaluator akan mengalami error atau menghasilkan skor 0 karena belum ada kartu yang diinputkan.
* Jika fase Toko diletakkan sebelum fase Evaluasi \& Reward, maka pemain tidak akan bisa berbelanja menggunakan uang hadiah dari ronde yang baru saja mereka menangkan (uangnya belum diberikan).



##### Step 3 — Identify Mutable Elements

1. **Target Score**

Target skor untuk setiap ronde (misalnya Ronde 1 butuh 10 skor, Ronde 2 butuh 100) bisa dinaikkan atau diturunkan. Ini mutable karena hanya mengubah angka batas kemenangan, tidak mengubah urutan kapan skor itu dicek.



**2. Scoring Formula \& Modifiers**

Rumus perhitungan skor atau efek dari kartu modifier bisa diganti atau diseimbangkan ulang. Ini mutable karena proses perhitungannya tetap terjadi di dalam fase Evaluasi, apa pun rumusnya.



**3. Reward Amount**

Jumlah uang yang diberikan ketika pemain berhasil mencapai target (saat ini $15) bisa diubah menjadi acak atau disesuaikan dengan sisa jumlah kartu di tangan. Ini mutable karena hanya mengubah besaran nilai variabel uang, bukan mengubah kapan hadiah itu diberikan.



Ketiga hal di atas bersifat mutabel karena hanya mempengaruhi nilai angka dan tingkat kesulitan game, tanpa mengubah urutan core loop.



##### Step 4 — Implement a C++ Core Loop Skeleton

Berikut adalah skeleton OOP minimal saya yang mencerminkan loop invarian.



File structure :

|Player.h<br />Player.cpp<br />ScoringSystem.h<br />ScoringSystem.cpp<br />RunSession.h<br />RunSession.cpp<br />main.cpp|
|-|



**Player.h**

|#pragma once<br />#include "modifiers/IModifier.h"<br />#include <vector><br />#include "Card.h"<br /><br />class Player {<br />private:<br />  std::vector<IModifier\*> activeModifiers;<br />  int money = 10;<br />  std::vector<Card> hand;<br /><br />public:<br />  void AddModifier(IModifier\* newModifier);<br />  std::vector<IModifier\*> GetModifiers();<br /><br />  int GetMoney();             <br />  void AddMoney(int amount);   <br />  bool SpendMoney(int amount); <br /><br />  void ReceiveCard(Card c); <br />  void ShowHand();          <br />  Card PlayCard(int index); <br />  std::vector<Card> PlayCards(std::vector<int> indices);<br />  void ClearHand();         <br />};|
|-|



**Player.cpp**

|#include "Player.h"<br />#include <iostream><br />#include <algorithm><br /><br />void Player::AddModifier(IModifier\* newModifier)<br />{<br />  activeModifiers.push\_back(newModifier);<br />}<br /><br />std::vector<IModifier\*> Player::GetModifiers()<br />{<br />  return activeModifiers;<br />}<br /><br />int Player::GetMoney()<br />{<br />  return money;<br />}<br /><br />void Player::AddMoney(int amount)<br />{<br />  money = money + amount;<br />}<br /><br />bool Player::SpendMoney(int amount)<br />{<br />    if (money >= amount) {<br />    money = money - amount; <br />    return true;            <br />  }<br />  else {<br />    return false; <br />  }<br />}<br /><br />void Player::ReceiveCard(Card c)<br />{<br />  hand.push\_back(c);<br />}<br /><br />void Player::ShowHand()<br />{<br />  std::cout << "\\n--- Kartu di Tanganmu ---" << std::endl;<br />  for (int i = 0; i < hand.size(); i++) {<br />    std::cout << i + 1 << ". " << hand\[i].ToString() << " (Nilai: " << hand\[i].GetValue() << ")"<br />              << std::endl;<br />  }<br />}<br /><br />Card Player::PlayCard(int index)<br />{<br />  Card playedCard = hand\[index];    <br />  hand.erase(hand.begin() + index); <br />  return playedCard;                <br />}<br /><br />void Player::ClearHand()<br />{<br />  hand.clear();<br />}<br /><br />std::vector<Card> Player::PlayCards(std::vector<int> indices)<br />{<br />  std::vector<Card> playedCards;<br /><br />  std::sort(indices.begin(), indices.end(), std::greater<int>());<br /><br />  for (int index : indices) {<br />    if (index >= 0 \&\& index < hand.size()) {<br />      playedCards.push\_back(hand\[index]);<br />      hand.erase(hand.begin() + index); <br />    }<br />  }<br />  return playedCards;<br />}|
|-|



**ScoringSystem.h**

|#pragma once<br />#include "Player.h"<br /><br />class ScoringSystem {<br />public:<br />  int CalculateBaseScore(int baseScore, Player\& player);<br />};|
|-|



**ScoringSystem.cpp**

|#include "ScoringSystem.h"<br /><br />int ScoringSystem::CalculateBaseScore(int baseScore, Player\& player)<br />{<br />  int currentScore = baseScore;<br /><br />  std::vector<IModifier\*> tasPemain = player.GetModifiers();<br /><br />  for (IModifier\* mod : tasPemain) {<br />      currentScore = mod->ApplyModifier(currentScore);<br />  }<br />  return currentScore;<br />}|
|-|



**RunSession.h**

|#pragma once<br />#include <iostream><br />#include "ScoringSystem.h"<br />#include "ShopSystem.h"<br />#include "Player.h"<br />#include "Deck.h"<br />#include "HandEvaluator.h"<br /><br />class RunSession {<br />private:<br />  int currentRound;<br />  int totalScore;<br /><br />  Player player;<br />  ScoringSystem scoring;<br />  ShopSystem shop;<br />  Deck deck;<br /><br />public:<br />  RunSession();<br />  void StartRun();<br /><br />  std::vector<Card> PlayHand();<br /><br />  bool CalculateScore(int targetScore, std::vector<Card> playedCards);<br /><br />  void EnterShop();<br />  void EndRun();<br />  void RunLoop();<br />};|
|-|



**RunSession.cpp**

|#include "RunSession.h"<br />#include <iostream><br />#include <sstream><br />#include <string><br /><br />// Constructor: Menyiapkan nilai awal<br />RunSession::RunSession()<br />{<br />  currentRound = 1;<br />  totalScore = 0;<br />}<br /><br />void RunSession::StartRun()<br />{<br />  std::cout << "\\n=== Memulai Run Baru ===" << std::endl;<br />  std::cout << "Skor Awal: " << totalScore << std::endl;<br /><br />  // Siapkan 52 kartu dan kocok sebelum main<br />  deck.InitializeDeck();<br />  deck.Shuffle();<br />}<br /><br />void RunSession::RunLoop()<br />{<br />  StartRun();<br /><br />  while (currentRound <= 3) {<br />    std::cout << "\\n--- Memulai Ronde " << currentRound << " ---" << std::endl;<br /><br />    // 1. Tentukan target skor tiap ronde<br />    int targetScore = 0;<br />    if (currentRound == 1)<br />      targetScore = 10; <br />    else if (currentRound == 2)<br />      targetScore = 100; <br />    else if (currentRound == 3)<br />      targetScore = 1000;<br /><br />    std::cout << "Target Skor ronde ini: " << targetScore << std::endl;<br />    std::cout << "Uangmu saat ini: $" << player.GetMoney() << std::endl;<br /><br />    // --- FASE PEMBAGIAN KARTU ---<br />    // Tarik 5 kartu dari atas tumpukan dan berikan ke tangan pemain<br />    for (int i = 0; i < 5; i++) {<br />      player.ReceiveCard(deck.DrawCard());<br />    }<br /><br />    // Memilih kartu dan menyimpan nilai kartu yang dimainkan<br />    std::vector<Card> kartuYangDimainkan = PlayHand();<br /><br />    // 2. Minta juri menilai, apakah tembus target? (Sekarang pakai nilai kartu asli)<br />    bool isWin = CalculateScore(targetScore, kartuYangDimainkan);<br /><br />    // Bersihkan kartu dari tangan pemain untuk ronde berikutnya<br />    player.ClearHand();<br /><br />    // 3. Jika juri bilang kalah (false), hentikan permainan!<br />    if (isWin == false) {<br />      std::cout << "\\n=== GAME OVER ===" << std::endl;<br />      break; // Perintah 'break' akan langsung menghancurkan putaran 'while'<br />    }<br /><br />    // 4. Kalau menang dan belum ronde terakhir, silakan ke toko<br />    if (currentRound < 3) {<br />      EnterShop();<br />    }<br /><br />    currentRound++;<br />  }<br /><br />  EndRun();<br />}<br /><br />// ... (RunLoop biarkan sama, kita cuma ubah 2 fungsi di bawahnya)<br /><br />std::vector<Card> RunSession::PlayHand()<br />{<br />  player.ShowHand();<br /><br />  std::cout << "\\nPilih nomor kartu (pisahkan dengan spasi, maks 5). Contoh: 1 3 4\\n";<br />  std::cout << "Pilihanmu: ";<br /><br />  std::string input;<br />  // Bersihkan sisa tombol "Enter" dari input sebelumnya agar tidak error<br />  if (std::cin.peek() == '\\n')<br />    std::cin.ignore();<br />  std::getline(std::cin, input);<br /><br />  // Alat bantu untuk memecah teks "1 3 4" menjadi angka terpisah<br />  std::stringstream ss(input);<br />  std::vector<int> pilihan;<br />  int nomor;<br />  while (ss >> nomor) {<br />    pilihan.push\_back(nomor - 1); // Kurangi 1 karena komputer menghitung dari 0<br />  }<br /><br />  std::vector<Card> dimainkan = player.PlayCards(pilihan);<br /><br />  std::cout << "\\n>> Kamu memainkan " << dimainkan.size() << " kartu!" << std::endl;<br />  return dimainkan; // Kirim kumpulan kartu ini ke juri<br />}<br /><br />bool RunSession::CalculateScore(int targetScore, std::vector<Card> playedCards)<br />{<br />  // 1. Serahkan ke Juri untuk dinilai kombonya!<br />  HandInfo vonis = HandEvaluator::EvaluateHand(playedCards);<br /><br />  std::cout << "\\n=== HASIL JURI ===" << std::endl;<br />  std::cout << "Kombo: " << vonis.name << "!" << std::endl;<br /><br />  // 2. Hitung total Chips dari nilai asli kartu-kartu yang dimainkan<br />  int totalCardChips = 0;<br />  for (Card c : playedCards) {<br />    totalCardChips += c.GetValue();<br />  }<br /><br />  // 3. RUMUS BALATRO ASLI: (Chips Kombo + Chips Kartu) \* Mult Kombo<br />  int totalChips = vonis.chips + totalCardChips;<br />  int skorKombo = totalChips \* vonis.mult;<br /><br />  std::cout << "Hitungan: (" << vonis.chips << " Chips Kombo + " << totalCardChips<br />            << " Chips Kartu) x " << vonis.mult << " Mult\\n";<br /><br />  // 4. Masukkan skor ini ke sistem modifikator toko milikmu!<br />  int finalScore = scoring.CalculateBaseScore(skorKombo, player);<br />  totalScore = totalScore + finalScore;<br /><br />  // Tampilkan skor dan bandingkan dengan target<br />  std::cout << ">> Mendapatkan skor: " << finalScore << " / Target: " << targetScore << std::endl;<br />  std::cout << ">> Total Skor sekarang: " << totalScore << std::endl;<br /><br />  if (finalScore >= targetScore) {<br />    int hadiah = 15;<br />    player.AddMoney(hadiah);<br />    std::cout << ">> TARGET TERCAPAI! Kamu mendapat hadiah $" << hadiah << "\\n" << std::endl;<br />    return true;<br />  }<br />  else {<br />    std::cout << ">> TARGET GAGAL! Skormu tidak mencukupi.\\n" << std::endl;<br />    return false;<br />  }<br />}<br /><br />void RunSession::EnterShop()<br />{<br />  shop.EnterShop(player);<br />}<br /><br />void RunSession::EndRun()<br />{<br />  std::cout << "\\n=== Run Selesai ===" << std::endl;<br />  std::cout << "Skor Akhir: " << totalScore << std::endl;<br />}|
|-|



**main.cpp**

|#include "RunSession.h"<br />#include <iostream><br /><br />int main()<br />{<br />  RunSession gameSession;<br />  gameSession.RunLoop();<br /><br />  return 0;<br />}|
|-|



##### Final Reflection

**1. What is the invariant structure of your game?**

Struktur invariant (tetap) di dalam game saya adalah urutan eksekusi fase di dalam core loop yang dikendalikan oleh kelas RunSession. Urutan ini tidak boleh diubah-ubah, yaitu : 

* Fase pembagian kartu oleh Deck
* Fase pemilihan kartu olrh Player
* Fase evaluasi jenis kombo oleh HandEvaluator
* Fase penghitungan skor akhir oleh ScoringSystem
* Fase pengecekan kondisi menang/kalah dan pembagian hadian uang
* Fase toko (shop) untuk membeli upgrade.

Urutan ini adalah fondsasi Utama dari cara kerja permainan dari awal ronde hingga akhir ronde, posisinya sama sekali tidak boleh dipindahkan, ditukar, atau dihilangkan salah satunya.



**2. What parts are mutable?**

Bagian yang bersifat mutable (bisa diubah) adalah implementasi detail atau aturan spesifik di dalam masing-masing fase, yang tidak mempengaruih core loop. Contohnya adalah target score, scoring formula \& modifiers, dan reward amount. Kita bisa dengan bebas mengubah ketiga hal tersebut tanpa merusak urutan jalannya permainan di RunSession.


Sebagai contoh, batas nilai target score bisa dibuat semakin tinggi seiring berjalannya ronde untuk mengatur tingkat kesulitan. Semua perubahan ini bersifat modifikasi nilai dan data, sehingga aman dilakukan.



**3. If you wanted to add a new feature, which class would change?**

Jika saya ingin menambahkan fitur baru, misalnya modifier yang memberikan efek "skor ganda jika kartu yang dimainkan semuanya berwarna merah", saya hanya perlu membuat turunan class baru di system modifier (misalnya RedCardModifier). Saya tidak perlu menyentuh atau mengedit class RunSession dan class RunSession tidak perlu tau detail tentang aturan kartu merah tersebut.



Hal ini sesuai dengan prinsip desain arsitektur yang baik, di mana penambahan fitur atau perilaku mutable harus selalu dikembangkan di luar struktur utama (invariant). 



**4. If you changed the loop order, what would break?**

Jika urutan loop diubah, maka semua logika aliran data permainan akan runtuh dan akan sering mengalami bug atau crash. 



Sebagai contoh, jika fase perhitungan skor dipindah posisinya menjadi sbelum fase pemilihan kartu oleh pemain, maka system akan mencoba menghitung skor dari data kartu yang masih kosong karena pemain belum memilih apa-apa. Ini akan menghasilkan skor 0 atau menyebabkan program error.



Contoh lain adalah, jika fase toko diletakkan sebelum fase pemberian reward, pemain tidak akan bisa menggunakan uang yang seharusnya mereka dapatkan di ronde tersebut untuk membeli modifier. 



Oleh karena itu memisahkan struktur invariant dengan elemen mutable adalah langkah yang paling krusial. Karena hal ini memastikan stabilnya pondasi game agar tidak hancur meskipun kita terus menambah banyak jenis modifier, jenis kartu, atau fitur baru di masa depan.

