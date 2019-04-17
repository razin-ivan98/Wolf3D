kill $(ps axu | grep play_back.sh | cut -d' '  -f 10) > /dev/null 2> /dev/null
kill $(ps axu | grep afplay | grep back.wav | cut -d' '  -f 10) > /dev/null 2> /dev/null