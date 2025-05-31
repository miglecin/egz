#include "zodziu_skaiciavimas.h"
#include "cross_reference.h"
#include "url_extractor.h"
#include <iostream>
#include <exception>

int main() {
    int pasirinkimas;
    string ivestis = "tekstas.txt";
    string isvestis;

    do {
        std::cout << "1. Suskaičiuoti žodžių dažnius\n";
        std::cout << "2. Sugeneruoti kryžminę nuorodų lentelę\n";
        std::cout << "3. Ieskoti URL\n";
        std::cout << "0. Išeiti\n";
        std::cout << "Pasirinkite: ";
        std::cin >> pasirinkimas;

        try {
            switch (pasirinkimas) {
                case 1:
                    isvestis = "dazniai.txt";
                    skaiciuoti_zodzius(ivestis, isvestis);
                    std::cout << "Žodžių skaičiavimas baigtas. Rezultatai faile " << isvestis << "\n";
                    break;

                case 2:
                    isvestis = "kryzmine.txt";
                    generuoti_kryzmine_nuoroda(ivestis, isvestis);
                    std::cout << "Kryžminė lentelė sugeneruota. Rezultatai faile " << isvestis << "\n";
                    break;

                case 3: {
                    std::set<string> tldai = ikrauti_tld_sarasa("tlds.txt");
                    rasti_url_adresus("tekstas.txt", "urlai.txt", tldai);
                    std::cout << " URL'ai rasti. Rezultatai faile urlai.txt\n";
                    break;
                    }

                case 0:
                    std::cout << "Baigta.\n";
                    break;

                default:
                    std::cout << "Neteisingas pasirinkimas, bandykite dar kartą.\n";
                    break;
            }
        }
        catch (const std::exception& klaida) {
            std::cerr << "Klaida: " << klaida.what() << std::endl;
        }

    } while (pasirinkimas != 0);

    return 0;
}
