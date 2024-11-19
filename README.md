## ELECTRICITY MOTORCYCLE

### List of contents

[I. Introduction](#Modau)

[II. Description](#ngonngumarkdown)
		
===========================

<a name="Modau"></a>
## I. Introduction

This program simulates an electric motorcycle's dashboard display and user interaction.
It provides a menu for the user to control various aspects of the motorcycle

<a name="ngonngumarkdown"></a>
## II. Desciption
There are some requirements

| Parameter                     | Requirement | 
|--------------                 |-------|
| Battery temperature           | Environment temperature -> random value |
| Battery level                 | Battery decrease after each cycle|  
| Fan mode                      | Turn on when battery temperature > 50 | 

Console at the beginning would be like that 

```sh
    ---/                    \---
    | /                      \ |
    |/                        \|
    ****ELECTRIC MOTORCYCLE****
    ----------------------------
    Battery temperature: ----
    Battery level: ----
    Turn signal: ----
    Fan mode: ----
    Speed: ----
    ----------------------------
    Start : OFF
```
Here's how you can interact with the program:
```sh
    1. Press '1' to start the motorcycle.
    2. Press '0' to turn off the motorcycle.
    3. Press 'K' to activate the left turn signal (equivalent to an left arrow).
    5. Press 'o' to turn off the turn signals.
    7. Press 'P' to decrease the motorcycle's speed (equivalent to an down arrow).
```
For example, start motorcycle and turn left
```sh
    ***
    **
    *

    ****ELECTRIC MOTORCYCLE****
    ----------------------------
    Battery temperature: 61
    Battery level: 7
    Turn signal: LEFT
    Fan mode: ON
    Speed: 50
    ----------------------------
    Start : ON
```


