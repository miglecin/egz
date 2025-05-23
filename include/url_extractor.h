#ifndef URL_EXTRACTOR_H
#define URL_EXTRACTOR_H

#include <string>
#include <set>

using std::string;

std::set<string> ikrauti_tld_sarasa(const string& failas);
void rasti_url_adresus(const string& ivestis_failas, const string& isvestis_failas, const std::set<string>& galimi_tld);

#endif // URL_EXTRACTOR_H
