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
Secondly, it was important to have trees because our goal is to have a forest. For this, we found some tree obj files and loaded them inside the program. From there, we were able to procedurally generate a random number of trees. In addition, we have two different tree objects that we are generating.
Since both the terrain and the trees are now being rendered, it was important that our next step focuses on assigning a texture to the objects. Texture allows for the objects to get a realistic look through binding useful and detailed textures. Our trees are assigned one texture to give a look that nature isn't how it should be. We used our creativity for the texture on trees by assigning a texture that would be bizzare for a tree. For our terrain, we wanted to take it a step further than just binding one texture. We are using three different textures for the terrain and blending pairs of them at different levels. This has been achieved by modifing our fragment shader to use three different 'sampler 2D' texture units. We then assign a texture to the according unit. With this, our objects now have a more life-like look that suits our theme.
Following textures, one of the requirements is that we shouldn't be able to go through objects. To complete this task, collisions were needed. Currently, this task is still in progress. At the moment, we tried checking the placement of the trees in our map to make sure that our camera won't reach that location. 
The next requirement to satisfy is that the world map should be generated as the user keeps traveling. Currently, this task is also in progress. 
Lastly, we wanted to enhance the experience of the user by adding some bonus features. There are three major features that we added. First, we added fog which adds the effect of uncertainty and mystery. The fog colour is black to not make its presence as obvious and to make the world appear to be coming out from darkness. Secondly, we added the ability to make the user go into "god" mode. In other words, this enables the "flight" superpower. Users begin by travelling slowly by walking on the ground, but with the press of key 'G', they can toggle their mode. In "god" mode, the travel speed increases and the users have the ability to travel above the world. In "human" mode, users can only travel by walking or by sprinting through holding shift. Lastly, we added the use of audio to simulate the theme and add the illusion that the user is in a real environment. Upon launch, an apocalypse theme song begins to play; every few minutes, either a dramatic sound effect or zombie sounds will be played. Lastly, power ups and power down sound effects are played for when the user toggles between "god" mode and "human" mode.

Note: for procedural generation, it is important that we define constraints. For ours, we made sure that hills would have a max height and that no hill can be generated on another hill. For the trees, we made sure that they are going to be generated on the terrain and that a tree can't be in the same location as another.

## What We Learned


## References



