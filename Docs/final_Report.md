# Final Report
This document discusses our procedural forest generation project. It is divided in sections to explain why we chose our idea, what we used, and what we learned.

## Contributors
**Student** | **ID**
:---:| ---
Christopher McArthur | `40004257`
Daniel Privorotsky | `40002150`
Nicholas Gattuso | `40007087`

> For best viewing of this [document](https://github.com/prince-chrismc/Computer-Graphics-Project/blob/master/docs/final_Report.md), use the link provided.

### Project Goal
- We must implement a 'Procedurally Modeled' world; that means our world objects are randomly generated and placed relative to each other within a set of rules.

### Table of Contents
1. [Project Idea](#Project-Idea)
2. [Accomplishment](#Accomplishment)
3. [What We Leanred](#What-We-Learned)
4. [References](#References)

## Project Idea
The goal of the project is to create a procedural generating forest using OpenGL. Upon lauch, a map containing a terrain, trees, and any additional objects should be generated; the catch is that the objects will never spawn in the same location thus, creating a new world with every launch. Additionally, it is required that the user must not be able to travel through objects.
We chose a theme that is both original and interesting to create. The idea is to create a Post-Apocalyptic Forest Setting. This can be achieved through setting a certain tone in the colouring of our world, in the theme of music, and the style of objects.The following explains our theme in more details:

Long into the future, after a devastating event, life on Earth has become a challenging task. So what exactly happened? Late in the year 2219, an immense nuclear explosion radiated the world thus changing all that we know. Humans began getting infected and turning into zombie-like creatures while others were getting superhuman abilities, all became dark, and properties of nature completely switched. Remaining humans are trying to survive against the aggressive zombies-like creatures while adjusting to the newly distorted world. With no more light, humans created an artificial light source to help them keep some visibility of the world.

But, what is really going on in this world? We need you to observe what is going on, specifically with the nature, and let us know what your findings are. It's up to you now, the user, to scout and travel this world to see what has happened. However, we helped simplify your task by granting you with the abilities to fly and to keep zombies away. This means, that no zombie will bother you and whenever you want, you can activate your flight in order to travel across the world much easily.

The theme of our project interested us because it allowed us to be creative while keeping along the requirements of the project. It also allowed for us to try new things by playing around with the basic Computer Graphics knowledge. For example, we got to play around with the fog colour and position, with settings various textures on objects (in some cases, more than 1 texture) and, with the placement of our objects.

## Accomplishment
In the previous section, we discussed the requirements and the theme of the project. Knowing this, we were able to achieve certain task to create our world. This section will discuss the accomplishments that we've had in order to achieve our objectives.

To begin, a terrain is needed as a base of the world. However, on the terrain, we chose to procedurally generate hills of random size. This has been done by generating a grid and during the generation, the program decides how many hills to create and what size for each one. The hills are created by following a sin function; since the points are close to each other, we can generate enough points to simulate the smooth surface. 
Secondly, it was important to have trees because our goal is to have a forest. For this, we found some tree obj files and loaded them inside the program. From there, we were able to procedurally generate a random number of trees. In addition, we have two different tree objects. 

## What We Learned


## References



