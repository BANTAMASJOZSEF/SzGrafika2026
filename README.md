# Helikopter Szimulátor: Erdőtűz (Számítógép Grafika Féléves Feladat)

**Név:** Bán Tamás József
**Neptun kód:** QTMKZZ
**Gyakorlati Óra:** Csütörtök 12-14

## 1. A feladat koncepciója
A projekt egy interaktív 3D-s helikopter szimulátor, ahol a játékos egy kutató-mentő helikoptert irányít egy dinamikusan generált erdős terület felett. A program központi eleme egy erdőtűz szimulációja, amely köré a grafikai és fizikai megoldások épülnek. A kamera folyamatosan követi a járművet (TPS nézet), biztosítva a folyamatos térérzékelést.

## 2. Technikai Megvalósítás és Megoldások

### Grafikai Motor és Ablakkezelés
A program **OpenGL** és **SDL2** könyvtárakat használ.

### Objektumkezelés és Geometria
- **Modellbetöltés**: A helikopter egyedi `.obj` fájlból töltődik be, a hozzá tartozó textúra pedig SDL2_image segítségével kerül a GPU memóriájába.
- **Procedurális fák**: A pálya 400 darab, véletlenszerűen generált fenyőfát tartalmaz. A fák elhelyezése inicializáláskor egy ütközésfigyelő algoritmussal történik, hogy elkerüljék az egymásba lógást és a pálya lefedését.
- **Magas betonfal**: Egy statikus akadály, amely a fizikai interakciók tesztelésére szolgál.

### Dinamikus Effektek (Plusz funkciók)
1. **Részecskerendszerek (Tűz és füst)**: A központi tűzfészek részecskékből áll, amelyek élettartama, mérete és átlátszósága (Alpha-blending) dinamikusan változik. A füst részecskék figyelembe veszik a szélhatást és a fal ütközéseit.
2. **Dinamikus Megvilágítás és Árnyék**: A program `GL_LIGHT0` fényforrást használ. Megvalósításra került egy **nappal/éjszaka ciklus**, ahol az 'I' és 'K' gombokkal állítható a fényerő. Ez nemcsak a modellek Diffuse és Ambient fényét, hanem a háttérszínt és a köd színét is módosítja.
3. **Fizikai szimuláció**:
    - **Ütközésvizsgálat**: Bounding-sphere és Bounding-box alapú ütközés a fákkal és a fallal.
    - **Visszapattanás**: A helikopter nagy sebességű ütközés esetén "biliárd-szerűen" pattan vissza a falról (beesési szög = visszaverődési szög logika alapján).
4. **2D HUD és Minimap**: A képernyőn egy fix, **1024x768-as virtuális felbontású** réteg található. Ez garantálja, hogy a Minimap, a sebességmérő (SPD) és a magasságmérő (ALT) bármilyen ablakfelbontás mellett olvasható maradjon.

## 3. Projektszerkezet
A forráskód a tanári kérésnek megfelelően logikai jegyzékekbe van szervezve:

- `src/`: A forrásfájlok (.c), mint a `main.c`, `app.c`, `scene.c`.
- `include/`: A fejlécfájlok (.h) dokumentált interfészekkel.
- `assets/`: A modelleket és textúrákat tartalmazó könyvtár.
- `Makefile`: A projekt fordítását automatizáló szkript.

## 4. Irányítás
- **W, S**: Előre / Hátra mozgatás
- **A, D**: Balra / Jobbra fordulás
- **Q, E**: Emelkedés / Süllyedés
- **I, K ( + , - )**: Fényerő növelése / csökkentése (Nappal/Éjszaka)
- **F1 vagy H**: Használati útmutató megjelenítése
- **ESC**: Kilépés