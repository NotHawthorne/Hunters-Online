g++ -Iincludes -lpthread -lsqlite3 src/Aura.cpp src/Item.cpp src/Server.cpp src/Player.cpp src/main.cpp -g -fsanitize=address -o server
