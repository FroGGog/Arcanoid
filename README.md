# Arcanoid
![Language (C++)](https://img.shields.io/badge/powered_by-C++-brightgreen.svg?style=flat-square) 

A classic arcanoid game made in C++ using sfml library.

## Controls

Use ~WASD~ to control player's panel. Catch bonuses to beat level.

Bonuses: 
- ![Screenshot](Screenshots/increaseLenght.png?raw=true "Lenght increase bonus")
Increases player's panel lenght
- ![Screenshot](Screenshots/multiplyBall.png?raw=true "Balls multiply")
Multiply count of all balls on screen by 2
- ![Screenshot](Screenshots/multiplyBall.png?raw=true "Speed up")
Speed up game x2 for few seconds

## Screenshots
![Screenshot](Screenshots/09.12.2024.png?raw=true "Start of game")
![Screenshot](Screenshots/09.12.2024(2).png?raw=true "Gameplay")

#### Must Have (dependencies)
- A valid C++ compiler - clang, gcc, msvc that supports c++17
- cmake >= v3.15

## Building

The CMAKE is set up to automatically download the dependencies and link against it. It will be done when configuring cmake.

```
git clone https://github.com/FroGGog/Arcanoid.git
cd Arcanoid
build .
```

Feel free to fork, fix the issues and contribute. Help is always welcome.