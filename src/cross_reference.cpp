#include "cross_reference.h"
#include "zodziu_skaiciavimas.h"
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <string>
#include <stdexcept>
#include <iostream>

void generuoti_kryzmine_nuoroda(const std::string& ivestis_failas, const std::string& isvestis_failas) {
    std::ifstream ivestis(ivestis_failas);
    if (!ivestis.is_open()) {
        throw std::runtime_error("Nepavyko atidaryti įvesties failo.");
    }

    std::ofstream isvestis(isvestis_failas);
    if (!isvestis.is_open()) {
        throw std::runtime_error("Nepavyko atidaryti išvesties failo.");
    }

    std::map<std::string, std::set<int>> zodziai_ir_eilutes;
    std::string eilute;
    int eil_nr = 1;

    while (std::getline(ivestis, eilute)) {
        std::istringstream iss(eilute);
        std::string zodis;
        while (iss >> zodis) {
            std::string isvalytas = isvalyti_zodi(zodis);
            if (!isvalytas.empty()) {
                zodziai_ir_eilutes[isvalytas].insert(eil_nr);
            }
        }
        eil_nr++;
    }

    for (const auto& pora : zodziai_ir_eilutes) {
        if (pora.second.size() > 1) {
            isvestis << pora.first << ": ";
            for (int linija : pora.second) {
                isvestis << linija << " ";
            }
            isvestis << "\n";
        }
    }
}
