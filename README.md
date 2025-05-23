 # egz

## Apie užduotį

Šio projekto tikslas – praktiškai išnagrinėti `std::string` ir asociatyvių C++ konteinerių (`std::map`, `std::set`) taikymą teksto analizėje.

##  Užduotys

### 1. Žodžių dažnio analizė
Iš pasirinko teksto nustatoma, kiek kartų pasikartoja kiekvienas žodis. Į rezultatą įtraukiami tik tie žodžiai, kurie pasikartoja **daugiau nei vieną kartą**. Skyrybos ženklai nėra laikomi žodžio dalimi.

 Naudojami konteineriai: `std::string`, `std::unordered_map`.

### 2. Kryžminė žodžių lentelė (cross-reference)
Sugeneruojama lentelė, kurioje nurodoma, **kuriose teksto eilutėse** (pagal numerį) kiekvienas daugiau nei vieną kartą pasikartojęs žodis buvo paminėtas.

 Naudojami konteineriai: `std::map<std::string, std::set<int>>`.

### 3. URL adresų paieška
Tekste automatiškai aptinkami URL adresai (pvz. `https://`, `www.` arba `vu.lt` formatu) ir išvedami į atskirą failą. Tikrinama, ar URL baigiasi tikru TLD pagal IANA sąrašą.

 Naudojami: `std::regex`, `std::set`, failų apdorojimas.

##  Įvestis
Tekstas turi būti pateiktas faile `tekstas.txt`. Failas `tlds.txt` turi būti parsisiųstas iš IANA (arba pateiktas rankiniu būdu) ir naudojamas tikrinti URL galūnėms.

##  Išvestis
- `dazniai.txt`: žodžių dažnis
- `kryzmine.txt`: žodžių vietos tekste (eilutės)
- `urlai.txt`: rasti URL adresai

##  Paleidimas
```bash
mkdir build
cd build
cmake ..
make
./main

