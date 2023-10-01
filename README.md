# Anime-Viewer

Anime Browser Opener is a command-line tool that allows you to open a web browser to a specific episode and season of your favorite anime series, making it easier to continue watching where you left off. The credentials you provide are saved on a configuration file in /etc/anime/anime.conf so that you can use the command without flags and it will start the next episode in the series.

## Usage

anime -n "Titan" -s 1 -e 12  
anime --name "Titan" --season 2 --episode 1  
anime  

## Options

-n, --name: Specify the name of the anime series  
-s, --season: Specify the season or series season number  
-e, --episode: Specify the episode number  
-h, --help: Display usage information.  

# Configuration file

It should be located at /etc/anime/anime.conf. And the contents should look something like this:  

$animeTitle=Titan  
$animeSeason=1  
$animeEpisode=1  

The contents represent the default credentials if no input is provided. If there is no input for the episode the program uses the default credential and automatically goes to the next episode in the series.
