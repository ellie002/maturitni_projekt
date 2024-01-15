# Samozavlažovací květináč

### Autor projektu: 
Eliška Káňová

### Popis projektu
Tento projekt obsahuje automatický zavlažovací systém, jehož hodnoty lze sledovat prostřednictvím aplikace. Projekt zahrnuje jak obvod na experimentálním panelu, tak návrh tištěného spoje. Projekt měří hodnotu senzoru hladiny vody, hodnotu senzoru vlhkosti půdy a provozuje systém v určeném časovém intervalu, přičemž se provádí funkce automatického zavlažování. Obvod používá LED diodu Neopixel s ultrafialovým zářením, senzor měření hladiny vody, senzor měření vlhkosti půdy MOSFET, který slouží jako spínač pro aktivaci motoru, a samozřejmě motor čerpadla na vodu.

### Cíle projektu

 - [x] Byla úspěšně implementována funkcionalita senzorů pro monitorování vlhkosti půdy a hladiny vody v nádrži. 

 - [x] Systém řídí zavlažování na základě naměřených hodnot. Pokud je zjištěna nedostatečná vlhkost půdy a zároveň dostatečná hladina vody v nádrži, spouští se čerpadlo pro zalití rostlin. 

 - [x] Úspěšně navázána komunikace s MQTT brokerem, což umožňuje odesílání dat o úrovni hladiny vody na platformu Home Assistant. 

 - [x] Byl zakomponován plošný spoj pro efektivní propojení a řízení všech komponent včetně senzorů, čerpadla a mikrokontroléru. 

 - [x] Bylo úspěšně provedeno fyzické zapojení hardwaru do 3D vytištěného modelu květináče, což přidává prvky estetiky a praktičnosti k celkovému provedení. 

### Konzultanti
 - Marcel Godovský
 - Petr Grussmann

---
