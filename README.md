# LED Control with ESP8266

## Overview

This project implements a program on the ESP8266 microcontroller to control WS2812B LED strips. The ESP8266 hosts a server that accepts data via a REST API, allowing users to set lighting modes, colors, and transition effects between colors. The code is primarily written in C++ with some functional programming elements to facilitate easy extension of functionality.

## Features

- **Receiving REST Requests**: The server receives REST API requests to control the LED strip.
- **Setting Lighting Modes**: Configure various lighting modes, including setting solid colors or dynamic effects.
- **Color Transitions**: Manage color transitions with different effects.
- **Removing Modes or Colors**: Capability to remove specific lighting modes or colors, including handling the associated transition effects.

## Technologies Used

- **Microcontroller**: ESP8266
- **Programming Language**: C++
- **LED Type**: WS2812B
- **Communication Protocol**: REST API

