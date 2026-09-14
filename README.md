# xiaozhi_kamerka
An MCP-based chatbot | Chatbot oparty na MCP
1. Wywalenie WakeNet: Całkowite usunięcie słowa wybudzającego na rzecz trybu bezpośredniego. Czyli po wcisnieciu przycisku.
   Usunac inicjalizację modelu AI WakeNet. W jej miejsce zdefiniowac przerwanie (ISR) na GPIO0, które wyzwala semafor we FreeRTOS budzący nasłuch audio.

2. Ekran: Obrót wyświetlacza ST7789V do pionu.
   Rotacja: Zmodyfikowac polecenie inicjalizujące ST7789V (rejestr 0x36 - Memory Data Access Control), aby wymusić układ pionowy (Portrait)

3. (Wentylator ze starego laptopa na 5v i z 4 przewodami) Wentylator PWM: Sterowanie obrotami w zależności od temperatury układu.
   Użyjemy sprzętowego kontrolera LEDC w ESP32-S3 do generowania sygnału PWM. Napisac funkcję, która czyta temperaturę rdzenia i płynnie steruje wypełnieniem PWM (0-100%)

4. Tryb Idle: Przejście w stan czuwania po 30 sekundach bezczynności ( wyswietlanie zegar + data + pogoda + miejsce).
   Dodac timer programowy, który po 30 sekundach braku interakcji wyzwoli zdarzenie dla interfejsu graficznego, przełączając ekran na zegar, date, pogodę oraz miasto.

5. Tapety: Dynamiczne/zmienne tła zamiast białego ekranu.
   LittleFS: Uruchomic montowanie partycji LittleFS, aby grafiki tła mogły być dynamicznie ładowane z pamięci układu, bez zawieszania głównej pętli.
   Wybiore i wysle naprzyklad 10 zdjec z mojego komputera do wgrania na LittleFS
   5a. zmienic emotikony (w tym celu zapoznaj sie z plikiem Xiaozhi_Emoticons_ustalenia.md)

6. Kamera OV5640: Programowe usypianie (Power Down), żeby sensor nie emitował ciepła, gdy nie robi zdjęć.
   Napisac funkcję używającą magistrali SCCB (I2C), która po zwolnieniu bufora ramki (kamera nie robi zdjęcia) wyśle rejestr 0x3008 z wartością 0x42, co usypia matrycę i odcina grzanie.

 7. trzeba dopisac aby w trybie spoczynku dla GPIO48 (WS2811) animację płynnego oddechu ("breathing") operującą na kanale PWM w kolorze pomarańczowym
