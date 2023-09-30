#include "animeFunctions.h"

int main(int argc, const char* argv[])
{
    vector<pair<string, string>> defaultVariables = GetDefaultVariables(CONF_FILE);
    string title, season, episode;
    bool episodeProvided = false;

    int status = ReadInput(title, season, episode, argc, argv);

    if (status == 1)
    {
        cout << "Wrong usage! Try -h or --help to open the usage menu." << endl;
        return 1;
    }
    else if(status == 2)
    {
        cout << "Unknown flag! Try -h or --help to see availabe flags." << endl;
        return 1;
    }

    if (title.length() == 0) title = GetTitle(defaultVariables);
    if (season.length() == 0) season = GetSeason(defaultVariables);
    if (episode.length() == 0) 
        episode = GetEpisode(defaultVariables);
    else 
        episodeProvided = true;

    if (ValidateVariables(title, season, episode) == true)
    {
        if (episodeProvided == false)
            NextEpisode(title, season, episode);

        WriteVariables(title, season, episode);
        WatchEpisode(title, season, episode);
    }
    else {
        cout << "Credentials not valid!" << endl;
        return 1;
    }

    return 0;
}