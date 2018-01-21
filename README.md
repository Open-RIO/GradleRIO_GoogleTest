GradleRIO GoogleTest Example
===

This project demonstrates how to use GoogleTest with GradleRIO, in order to develop your code in a test-driven-development style fashion, or to test certain library code without the physical robot.

## Differences to a normal GradleRIO project
For starters, this project is a multi-project build. You'll find a description of each subproject down below.

A task `subclean` has been added to replace `clean` in `./gradlew clean build`. The reason for this is that we include the googletest source, which can take a while to compile on some machines (not very long, but noticeable). `subclean` only cleans the code that you've written (robot, subsystems) and _not_ the googletest source.

Instead of running `./gradlew build`, you may want to instead run `./gradlew assemble`, which will build but not test your code, if you know the code is in a failing state. Note that `./gradlew deploy` WILL NOT RUN TESTS. Use `./gradlew build deploy` instead.

## Project Structure
- `:` - Root Project
    - Includes the `googletest` component, for building the googletest framework. Also includes some other logic to make the subprojects behave.  
    - `:subsystems` - Subsystems Project
        - This is where your code for subsystems go. These are abstract, and don't depend on WPILib/other roborio-specific libs, but instead act as models of the systems. The testing framework is also included here. 
    - `:robot` - Robot Project
        - The actual code that goes onto your robot. Don't worry, this includes the `subsystems` project.