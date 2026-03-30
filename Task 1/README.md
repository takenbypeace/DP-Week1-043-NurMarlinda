##### 1\. What is the invariant structure in your program?



Invariant adalah struktur utama yang urutannya mutlak dan tidak boleh berubah. Di program ini, invariant nya adalah kelas RunSession. Dalam fungsi run(), urutannya selalu mulai dari generate input, menghitung base score, menghitung reward, update money, dan memunculkan shop selama 3 ronde. Urutan ini tidak boleh diubah maupun ditukar posisinya.



##### 2\. Which parts are mutable?



Bagian yang mutable adalah bagian sistem yang bisa dimodifikasi dengan aman tanpa merusak struktur utama. Di program ini, bagian ini adalah implementasi logika permainannya, yaitu turunan dari interface IInputGenerator (menentukan input, diubah jadi random), IScoringRule (menghitung skor dasar), dan IRewardRule (menghitung uang dari skor). 



Sebagai contoh, jika awalnya kita memakai SimpleInputGenerator, lalu bisa dengan mudah diubah menjadi RandomInputGenerator. Begitu juga dengan SimpleRewardRule diubah menjadi BonusRewardRule. Perubahan ini membuktikan bahwa kita bisa mengganti cara kerja dan kesulitan game dengan bebas tanpa menyentuh fondasi utamanya.



##### 3\. When you replaced the InputGenerator, why didn’t RunSession change?



Karena RunSession dirancang untuk hanya mengenali interface yaitu IInputGenerator. Selama objek tersebut memiliki fungsi generateInput(), maka RunSession tidak perlu diubah.



RunSession tidak tahu soal bagaimana angka acak dihitung secara spesifik. RunSession hanya tahu siapapun yang menjadi IInputGenerator pasti bisa memberikan angka acak saat diminta.



##### 4\. What would happen if scoring logic was placed inside RunSession?



Jika logika skor ditaruh di dalam RunSession, maka setiap kali ingin mengubah aturan skor, kita harus membongkar dan mengedit kode di dalam RunSession. Kalau kita taruh logika nya dalam RunSession, program nya jadi tidak fleksibel.



Selain tidak fleksibel, ini berisiko merusak invariant yang sudah tidak boleh diubah dan memicu bug.

