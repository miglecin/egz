#include "zodziu_skaiciavimas.h"
#include <fstream>
#include <unordered_map>
#include <iostream>
#include <cctype>
#include <stdexcept>
#include <locale>
#include <regex>

using std::string;

string isvalyti_zodi(const string& zodis) {
    return std::regex_replace(zodis, std::regex(R"([^[:alnum:]ąčęėįšųūžĄČĘĖĮŠŲŪŽ])"), "");
}
// Paprasta filtravimo funkcija, kuri leidžia UTF-8 ženklus
/*string isvalyti_zodi(const string& zodis) {
    
    string rezultatas;
    for (char raide : zodis) {
        // leidžiam ir lotyniškus simbolius, ir UTF-8 (kai > 0 arba rašytinis ženklas)
        if (std::isalnum((unsigned char)raide) || (unsigned char)raide > 127) {
            rezultatas += std::tolower((unsigned char)raide);
        }
    }
    return rezultatas;
}*/

void skaiciuoti_zodzius(const string& ivestis_failas, const string& isvestis_failas) {
    std::ifstream ivestis(ivestis_failas);
    if (!ivestis.is_open()) {
        throw std::runtime_error("Nepavyko atidaryti įvesties failo.");
    }

    std::ofstream isvestis(isvestis_failas);
    if (!isvestis.is_open()) {
        throw std::runtime_error("Nepavyko atidaryti išvesties failo.");
    }

    std::unordered_map<string, int> zodziu_kiekiai;
    string zodis;

    while (ivestis >> zodis) {
        string isvalytas = isvalyti_zodi(zodis);
        if (!isvalytas.empty()) {
            zodziu_kiekiai[isvalytas]++;
        }
    }

    for (const auto& pora : zodziu_kiekiai) {
        if (pora.second > 1) {
            isvestis << pora.first << ": " << pora.second << "\n";
        }
    }
}
