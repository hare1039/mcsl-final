Hi, 我們是 22 組

---

<< 耳機架 >>

![logo](https://hare1039.nctu.me/imgs/headphone.png)
---

室友不在，想播音樂該怎麼辦？

---

按下調整輸出，選內建音響



    ...拔掉耳機線最快

---

耳機常常剛買沒多久，卻接頭接觸不良，而變成單聲道耳機？

---

為了避免耳機跟電腦插頭的磨損，我們希望做出一個附帶音響的耳機架

---

理想模型：

設計出一個耳機架，當耳機掛上去時，便轉為由音箱撥出聲音，

當一拿開時，便由耳機撥出。

---

如何實作?

音樂輸出的 devices，透過 stm32 使用 USB 或是 bluetooth 模組與電腦連線。

---

computer >> (USB, bluetooth) >> 

stm32 controls

    -> speakers
    -> headphone      
by button

---

Thank you
