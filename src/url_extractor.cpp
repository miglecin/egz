#include "url_extractor.h"
#include <fstream>
#include <regex>
#include <set>
#include <string>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <vector>

// Funkcija, skirta užkrauti TLD sąrašą iš failo
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

// Pagalbinė funkcija domeno etiketėms skaidyti
std::vector<std::string> split_domain(const std::string &domain) {
    std::vector<std::string> labels;
    size_t start = 0;
    size_t end = domain.find('.');
    while (end != std::string::npos) {
        labels.push_back(domain.substr(start, end - start));
        start = end + 1;
        end = domain.find('.', start);
    }
    labels.push_back(domain.substr(start));
    return labels;
}

// Pagrindinė funkcija URL adresams išgauti
void rasti_url_adresus(const std::string& ivestis_failas, const std::string& isvestis_failas, const std::set<std::string>& galimi_tld) {
    std::ifstream ivestis(ivestis_failas);
    if (!ivestis.is_open()) throw std::runtime_error("Nepavyko atidaryti įvesties failo.");

    std::ofstream isvestis(isvestis_failas);
    if (!isvestis.is_open()) throw std::runtime_error("Nepavyko atidaryti išvesties failo.");

    // Atnaujintas regex, fiksuojantis visą domeną
    std::regex url_regex(R"((https?:\/\/)?(www\.)?([a-zA-Z0-9\-]+\.[a-zA-Z0-9\-\.]+))", std::regex::icase);
    std::set<std::string> url_rinkinys;
    std::string eilute;

    while (std::getline(ivestis, eilute)) {
        std::sregex_iterator it(eilute.begin(), eilute.end(), url_regex);
        std::sregex_iterator end;

        while (it != end) {
            std::string pilnas_url = it->str();
            std::string domenas = (*it)[3];  // 3 grupė – domenas

            std::transform(domenas.begin(), domenas.end(), domenas.begin(), ::tolower);
            std::vector<std::string> labels = split_domain(domenas);

            // Tikriname visus galimus TLD variantus
            std::string current_suffix;
            bool valid_tld = false;
            for (auto label_it = labels.rbegin(); label_it != labels.rend(); ++label_it) {
                current_suffix = current_suffix.empty() ? *label_it : *label_it + "." + current_suffix;
                if (galimi_tld.count(current_suffix)) {
                    valid_tld = true;
                    break;
                }
            }

            if (valid_tld) {
                url_rinkinys.insert(pilnas_url);
            }

            ++it;
        }
    }

    for (const auto& url : url_rinkinys) {
        isvestis << url << "\n";
    }
}