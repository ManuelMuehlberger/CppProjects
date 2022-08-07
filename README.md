# CppProjects
A showcase of some C++ projects I have made. 

1_FileManager
=============
An emulated filemanager that supports folders, creation and deletion of different types of files, sorting by various metrics and more. It works through a command-line-interface and keeps all generated files by reference only.

2_SandboxLogger
===============
a program which can monitor the creation, modification, and deletion of files within a specified location and record the observed changes into a log file. On execution there is both the monitor thread and a test-thread that "does stuff" in a specified sandbox directory. If the monitor finds a previous log file, it will just rename it to log.txt_old. This implementation relies heavily on filesystem library that is [identical](https://en.cppreference.com/w/cpp/filesystem) in both *boost*- and *std*-libraries.

3_TerrainGenerator_diamondsquare
================================
This was part of an assigment of an university course on computer graphics with the goal of random terrain generation. Both required and optional arguments can be specified through a command-line-interface. The program applies the Diamond-Square-algorithm for random heightmap-generation. From this heightmap, a map of the surface normals and a splatmap (Interpolation of a set of textures depending on factors like height or steepness) can be calculated. Because this project relies heavily on Vulcan-SDK and other potentionally proprietary libraries provided by the organising faculty, I can sadly only offer it in non-running fashion. But I hope it still serves its purpose as a means of demonstration.
4_recursiveTemplates
====================
A very small project which can recursively calculate fibonacci using *recursive templates*. It can also calculate the greatest common divisor or minimum common multiple of n numbers with *variadic templates* at *compile time*. Example usage can be found in `main.cpp`.

SolarLogger
===========
This is a project that can be found on my profile or [here](https://github.com/ManuelMuehlberger/SolarLogger). Its basic idea is to utilise a number of ESP8266s that each keep watch of  electricity-meter's S0-interface and send their logged eletricity usage to a central server (like a raspberry pi) via e.g. *MQTT*. This server can then calculate a variety of metrics with this data. Although progress has been slow the last few months (It is more of a joy-project to me) it has been a very educational experience in embedded software-development. 
