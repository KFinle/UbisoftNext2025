# Ubisoft NEXT 2025

This is my entry for Ubisoft Next 2025. The theme this year was "Minigoft". Entrants are given one weekend to create a small game using a provided API that handles input, game loops, and line rendering. Here is a link to a gameplay video of the project:  

[![Gameplay Video](https://img.youtube.com/vi/tIEpu_ZekJc/0.jpg)](https://www.youtube.com/watch?v=tIEpu_ZekJc)

## Gameplay Overview
In my game, your cursor is the golf club, and it is always active. The goal is to hit the ball into the green hole. 
Levels are randomly generated with increasing difficulty after each successfully completing each level. 


## Key Challenge
The biggest challenge I faced when working on this project was the implementation of the collision system. Because I wanted the cursor to always be active, this meant having to account for moments in between frames when the cursor overlaps with the ball. The solution I landed on was to add a 10-frame lockout after each hit to ensure the player can reposition their cursor without having the ball get stuck to it. 

