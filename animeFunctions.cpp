#include "animeFunctions.h"

const char* CONF_FILE = "/etc/anime/anime.conf";

/*  *
    * Gets the variables from the configuration files.
    * @param - file The name of the file.
    * @return - A vector with key value pairs.
    */

vector<pair<string, string>> GetDefaultVariables(const char* file)
{
    vector<pair<string, string>> result;
    ifstream fin(file);
    
    if (!fin.is_open())
    {
        cerr << "Error: Unable to open the file!\n";
        return result;
    }

    string line;

    while (getline(fin, line)){
        if (line[0] == '$'){
            int start = 1;
            int end = line.find('=');
         
            string variable = line.substr(start, end - start);
            start = end + 1;
            string value = line.substr(start, line.length());

            result.push_back(make_pair(variable, value));
        }
    }

    fin.close();
    return result;
}

/*  *
    * Gets the title from the dictionary
    * @param - The dictionary.
    * @return - Title, string;
    */

string GetTitle(vector<pair<string, string>> defaultVariables)
{
    string title = "";
    for (pair<string, string> var : defaultVariables)
    {
        if (var.first.compare("animeTitle") == 0)
        {
            title = var.second;
        }
    }
    return title;
}

// same as GetTitle

string GetSeason(vector<pair<string, string>> defaultVariables)
{
    string season = "";
    for (pair<string, string> var : defaultVariables)
    {
        if (var.first.compare("animeSeason") == 0)
        {
            season = var.second;
        }
    }
    return season;
}

// same as GetTitle

string GetEpisode(vector<pair<string, string>> defaultVariables)
{
    string episode = "";
    for (pair<string, string> var : defaultVariables)
    {
        if (var.first.compare("animeEpisode") == 0)
        {
            episode = var.second;
        }
    }
    return episode;
}

/// VALIDATION FUNCTIONS ///

bool ValidateTitle(string title)
{
    if (title.compare("Titan") == 0)
        return true;
    else
        return false;
}


bool ValidateEpisode(string &season, string &episode)
{
    int s, e;
    try {
        s = stoi(season);
        e = stoi(episode);
        season = to_string(s);
        episode = to_string(e);
    } 
    catch (exception &err)
    {
        return false;
    }

    bool result;

    switch(s){
        case 1:
            result = (e >= 1 && e <= 25);
            break;
        case 2:
            result = (e >= 1 && e <= 12);
            break;
        case 3:
            result = (e >= 1 && e <= 12);
            break;
        case 4:
            result = (e >= 1 && e <= 16);
            break;
        default:
            result = false;
            break;
    }

    return result;
}

bool ValidateVariables(string title, string &season, string &episode)
{
    return ValidateTitle(title) && ValidateEpisode(season, episode);
}

// Display usage information.

void Usage()
{
    cout << "Description & Usage:\n\n"
        << "anime - opens a browser to the specified season and episode of the specified anime."
        << "The script also uses configuration variables to remember the last credentials (configuration file at: /etc/anime/anime.conf), "
        << "and you can use the command \"anime\" without flags and it will give you the next episode.\n\n"
        << "Flags:\n\n"
        << "-e, --episode num -> select the episode\n\n"
        << "-s, --season num -> select the season\n\n"
        << "-n, --name str -> select the anime\n\n"
        << "-h, --help -> to display usage menu\n\n"
        << "Example:\n\n"
        << "anime -n Titan -s 4 -e 12\n"
        << "anime --name Titan --season 4 --episode 12\n"
        << "anime (uses variables from /etc/anime/anime.conf)\n"
        << "anime -n Titan (uses configuration variables for episode and season)\n\n"
        << "Available animes:\n"
        << "Attack on Titan -> command value: -n Titan\n\n";

}

// Writes the variables to the configuration file

int WriteVariables(string title, string season, string episode)
{
    ofstream fout(CONF_FILE);
    if (!fout.is_open())
    {
        cout << "Unable to open output file!\n";
        return 1; 
    }
    fout << "$animeTitle=" << title << endl
        << "$animeSeason=" << season << endl
        << "$animeEpisode=" << episode << endl;
    fout.close();
    return 0;
}

// Goes to the next episode specifically for Attack on Titan

void TitanNextEpisode(string& season, string& episode)
{
    int e = stoi(episode), s = stoi(season);
    
    if (e == 12 && (s == 2 || s == 3))
        e = 1, s ++;
    else if (e == 16 && s == 4)
        s = 1, e = 1;
    else if (e == 25 && s == 1)
        e = 1, s ++;
    else
        e ++;
    
    episode = to_string(e);
    season = to_string(s);
}   

// Picks the anime, and calls the right function

void NextEpisode(string title, string& season, string& episode) 
{

    if (title == "Titan")
    {
        TitanNextEpisode(season, episode);
    }

}

// Creates an url for Attack on Titan

string TitanUrl(string season, string episode)
{
    string titanUrl = "https://ww4.gogoanime2.org/watch/shingeki-no-kyojin";
    if(season == "2")
        titanUrl += string("-season-2");
    else if (season == "3")
        titanUrl += string("-season-3");
    else if (season == "4")
        titanUrl += string("-the-final-season");
    
    titanUrl += string("/") + episode;
    
    return titanUrl;
}

// Opens the browser to the specific url of the episode

void WatchEpisode(string title, string season, string episode) 
{
    string url;
    if (title == "Titan")
        url = TitanUrl(season, episode);
    else
    {
        cout << "Cannot create URL!\n";
        return;
    }

    string command = string("xdg-open ") + url;

    system(command.c_str());

}


int ReadInput(string& title, string &season, string &episode, int argc, const char* argv[])
{

    if (argc % 2 != 1 || argc > 7)
    {
        Usage();
        return 1;
    }
    else 
    {
        for (int i = 1; i < argc; i += 2)
        {
            if (strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "--episode") == 0)
                episode = argv[i + 1];
            else if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--season") == 0)
                season = argv[i + 1];
            else if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "--name") == 0)
                title = argv[i + 1];
            else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
            {
                Usage(); 
                return 0;
            }
            else
                return 2;
        }
    }
    return 0;
}
