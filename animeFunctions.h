#ifndef ANIME_FUNCTIONS_H
#define ANIME_FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>

using namespace std;

extern const char* CONF_FILE;

vector<pair<string, string>> GetDefaultVariables(const char*);

string GetTitle(vector<pair<string, string>>);
string GetSeason(vector<pair<string, string>>);
string GetEpisode(vector<pair<string, string>>);

bool ValidateEpisode(string&, string&);
bool ValidateTitle(string);
bool ValidateVariables(string, string&, string&);

void Usage();

int WriteVariables(string, string, string);

void NextEpisode(string, string&, string&);
void TitanNextEpisode(string&, string&);

void WatchEpisode(string, string, string);

int ReadInput(string&, string&, string&, int, const char**);

#endif
