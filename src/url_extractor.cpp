#include "url_extractor.h"
#include <fstream>
#include <regex>
#include <set>
#include <string>
#include <iostream>
#include <stdexcept>
#include <algorithm>

std::set<std::string> ikrauti_tld_sarasa(const std::string& failas) {
    std::set<std::string> tld_sarasas;
    std::ifstream tld_failas(failas);
    std::string eilute;

    while (std::getline(tld_failas, eilute)) {
        if (!eilute.empty() && eilute[0] != '#') {
            std::transform(eilute.begin(), eilute.end(), eilute.begin(), ::tolower);
            tld_sarasas.insert(eilute);
        }
    }

    return tld_sarasas;
}

void rasti_url_adresus(const std::string& ivestis_failas, const std::string& isvestis_failas, const std::set<std::string>& galimi_tld) {
    std::ifstream ivestis(ivestis_failas);
    if (!ivestis.is_open()) throw std::runtime_error("Nepavyko atidaryti įvesties failo.");

    std::ofstream isvestis(isvestis_failas);
    if (!isvestis.is_open()) throw std::runtime_error("Nepavyko atidaryti išvesties failo.");

    std::regex url_regex(R"((https?:\/\/)?(www\.)?([a-zA-Z0-9\-]+\.)+([a-z]{2,}))");
    std::set<std::string> url_rinkinys;
    std::string eilute;

    while (std::getline(ivestis, eilute)) {
        std::sregex_iterator it(eilute.begin(), eilute.end(), url_regex);
        std::sregex_iterator end;

        while (it != end) {
            std::string pilnas_url = it->str();
            std::string tld = (*it)[4];  // grupė 4 – tai TLD

            std::transform(tld.begin(), tld.end(), tld.begin(), ::tolower);
            if (galimi_tld.find(tld) != galimi_tld.end()) {
                url_rinkinys.insert(pilnas_url);
            }

            ++it;
        }
    }

    for (const auto& url : url_rinkinys) {
        isvestis << url << "\n";
    }
}
