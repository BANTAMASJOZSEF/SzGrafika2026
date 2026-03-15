# Helikopter Szimulátor: Erdőtűz (Számítógép Grafika Féléves Feladat)

**Név:** Bán Tamás József

**Neptun kód:** QTMKZZ

**Gyakorlati Óra:** Csüt 12-14

## 1. A feladat koncepciója
A projekt egy 3D-s helikopter szimulátor, amelyben a játékos egy tűzoltó/kutató helikoptert irányít egy sűrű, részben lángoló erdő felett. A program célja a térbeli mozgás, a dinamikus megvilágítás, valamint az interaktív és veszélyes környezet bemutatása. A kamera folyamatosan követi a járművet (Third-person view).

## 2. Tervezett plusz funkciók
1. **Részecskerendszerek (Tűz és füst):** Az égő erdő hatásának eléréséhez a fák körül dinamikus tűz- és füsteffektek jelennek meg.
2. **Dinamikus Árnyék:** Valós idejű árnyékvetés a helikopterre és a fákra a fényforrás (Nap) pozíciója alapján.
3. **Köd:** Dinamikusan, futásidőben változtatható sűrűségű ködhatás, amely a füstös, rossz látási viszonyokat szimulálja.
4. **Ütközésvizsgálat (Bounding-box):** A helikopter fizikai kiterjedéssel rendelkezik, így nem repülhet át indokolatlanul a fákon, és nem mehet a talajszint alá.
5. **Térkép:** A képernyő bal alsó sarkában jelzi a helikopter helyzetét a pályán felülnézetből.
+ Plusz: Állítható sebesség, hogy a helikopter gyorsabban/lassabban mozogjon előre/hátra & fel/le (WASD & QE)

## 3. Fordítás és Futtatás
A program C nyelven, OpenGL és GLUT könyvtárak felhasználásával készült. A forráskód a `make` parancs kiadásával lefordítható.
