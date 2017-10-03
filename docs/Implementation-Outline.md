# Implementation Outline
This document sets out to lay out the basic ideas for the project, set the timeline which we aim to follow, and raise questions for ourselves that we will have to discuss and finalize. We have put forth a set of milestones which we will need to achieve, which are planned in an agile workflow, in order to complete the project on time. Our end product strives to deliever a rich but mildly realistic environment that will be statisfying for the user.

> For best viewing of this [document](https://github.com/prince-chrismc/Computer-Graphics-Project/blob/master/docs/Implementation-Outline.md), use the link provided.

### Project Goal
- We must implement a 'Procedurally Modeled' world; that means our world objects are randomly generated and placed relative to each other within a set of rules.

### Table of Contents
1. [Basic Concepts](#Basic-Concepts)
2. [Questions](#Questions)
3. [Idea Explanation](#Idea-Explanation)
4. [Milestones](#Milestones)
4. [Examples](#Examples)

## Basic Concepts
- Theme: Post-Apocalyptic Forest Setting
- Elements:
  - Trees
  - Paths

## Questions
- What degree of variation do we want within our trees?
- What kinds of elements do we want?
- What density of trees?
- Do we want camera restrictions (beyond collision prevention)?

## Idea Explanation
We plan to create a forest representation that our user can walk through. However, instead of creating your traditional forest, we plan to be a bit creative by making an "post-apocolypse forest." In other words, we'll have some burnt, brown, and broken down trees instead of having all our world all beautiful, fully grown, and green. This idea will give a creative twist to the traditional design in addition to an exciting and thrilling walk through to the user. In addition, our world will include a sun that will create light and shadow. This will allow us to apply the various ways to colour an object and to create the effect that our world is real.

As the user moves through the terrain, new world objects will appear within various constraints that we will implement. The constraints are still to be decided, but they will make the objects fall in a certain area, be a certain size, and facing a specific direction. For example, if we generate a path, we have to make sure the path follows a direction and the trees will have to be generated outside of the path.

Our plan is to go through the project by milestones. The following [section](#Milestones) breaks down the timeline we will be aiming to complete our tasks along. In each milestone, we'll split the task equally among the four of us. The milestones are still needded to be broken down to the sub-tasks that we will be assigning to each other, however, when this is done, we'll be creating issues for each task to keep track of what needs to be done and what is completed.

## Milestones
**Deadline** | **Task**
:---: | ---
`week #6` | Generate a terrain
`week #7` | Explore terrain
`week #8` | Generate trees
`week #9` | Manipulate trees
`week #11` | Exploration with trees
`week #13` | Collision handling

## Examples
- [](https://github.com/oxaoo/forest)
- [](https://github.com/Aftnet/Terrain-Generator)
- [](http://algorithmicbotany.org/papers/TreeSketch.SBM2012.pdf)
