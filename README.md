# Hunters Online
---
![logo](https://github.com/NotHawthorne/cursewar/raw/master/screenshots/1.jpg "Screenshot")
---
## Description
Hunters Online is an `ncurses` based idle online MMORPG inspired heavily by the roguelike genre.
---
## Requirements
- libsqlite3-dev
- ncurses
- g++
---
## Howto
1. `git clone https://github.com/NotHawthorne/Hunters-Online.git ./hunters`
2. `cd hunters && make`
3. `./hunters`
4. Login with the desired username and password! The client is configured to connect to the main dedicated server by default.
---
## Known Issues
- You cannot CTRL+C to exit the login manager, requiring a `kill`.
- Resizing does not work correctly.
- The screen straight up becomes garbage sometimes. 
- Command parser is very barebones and wonky and will crash sometimes.
