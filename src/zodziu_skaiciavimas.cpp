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
