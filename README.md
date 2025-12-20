# CS 3251: Intermediate Software Design
## Programming Assignment 6


### Patterns Explored:

- [Singleton pattern](https://en.wikipedia.org/wiki/Singleton_pattern)
- [Visitor Pattern](https://en.wikipedia.org/wiki/Visitor_pattern)
- [Factory Pattern](https://en.wikipedia.org/wiki/Factory_pattern)


## Assignment Overview

Design patterns are essential in developing anything larger than a trivial program. This assignment requires you to start implementing the meaningful portions of a Gravitational Simulation project using a few simple patterns.

This assignment provides a number of header files and requires the implementation of the corresponding *.cpp files using appropriate patterns. A few basic physics principles are required to code the actual simulation.  While this may seem overwhelming at first glance, thanks to the Vector class, the actual math will be very easy to implement.

Do not change any of the header files. Please start early and ask questions as they arise. One of the tests simulates every second of the Earth’s journey around the sun for a year, the final binary may take up to a minute or two to execute. It is crucial that your approach to developing the application does not rely upon frequent executions.

#### Classes

* Universe – A class responsible for keeping track of all the objects in your simulation. Since no more than one such environment should exist, it makes sense to make this class a Singleton. For this assignment you are to assume that the first object registered with the Universe is a “sun” and it should not be affected by any forces.

* Object – The base class of the class hierarchy designed to outline the interface for objects to be used in the simulation. We can imagine that certain objects may be composed of other bodies so this class could eventually exhibit the Composite pattern. Correct handling of different types of objects requires this class provide an access point for a Visitor. Finally, to make all force applications appear simultaneously, a “snapshot” method will be available via the Prototype.

* Planet - A planet object that can orbit (i.e. move) in the Universe

* Star - An object that always sits at the center of a Universe

* ObjectFactory – An Abstract Factory implementation that provides an easy way of creating celestial Objects

* Visitor – A Visitor abstract base class will be defined as well as a concrete subclass, the PrintVisitor. The latter will be responsible for testing the Visitor/Iterator framework via simple print tests.  You will expand on this for the extra credit portion of the assignment.

#### Physics Concepts Required for this Assignment: 

* The Law of Universal Gravitation: the magnitude of the force due to gravity between two objects is equal to G times the mass of the first times the mass of the second divided by the square of the distance between the two. 

* The Second Law of Motion: the net force acting on an object is equal to its mass times its acceleration.

* The net force acting on upon an object is also equal to the sum of all the forces acting upon it.

* The acceleration of an object equals the change in its velocity divided by the corresponding change in time.

* The velocity of an object equals the change in its position divided by the corresponding change in time.

* Acceleration, force, position, and velocity are all vector quantities.


#### How to Get Started

1. Review the primer on [vector math](./docs/VectorMathTutorial.pdf).  This is important context for this assignment.
2. Start with the easier tests first - Gravitation, Inertia, Factory and Visitor. Once these are working as expected, then move on to the EarthYear and SolarSystem tests.
3. The overall simulation breaks time into small steps.  Look at the heart of the EarthYear and SolarSystem tests.  There is a loop that goes through an entire year, with a step size of 1 second (EarthYear) and 1 hour (SolarSystem).  Use the state information for each object in the Universe to calculate state for the next step - make sure to keep the state in the current step completely unchanged until you have fully calculated the state in the next step.
4. Start small.  Maybe try temporarily commenting out most of the test files.  Remember, you'll need to reload your Cmake if you change these files - and DO NOT commit these changes.
5. Comment out as much as needed throughout the code and focus on getting one test to pass.  Then slowly expand as your knowledge and confidence grows.  Again, make sure to only add/commit/push those changes you mean to.

#### Final Thoughts for the Base Assignment:

As always, do not change the CMakeList.txt or any of the build-related files unless explicitly directed to do so.  Concentrate all of your effort and changes into the *.cpp files in the ./src directory.  I have provided a solution to the Vector class - you should not need to change this.


## Optional Extra Credit

Extra credit opportunities for this assignment are detailed in `extra_credit.md`.  You are only eligible for extra credit points if you score a 90% or higher on the base portion of the assignment.  My suggestion would be to complete the base assignment with a high level of confidence before attempting any of the extra credit.


## Reminders

* Ensure that your name, vunetid, email address, and the honor code appear in the header comments of all files that you have altered.

* Do not commit changes to any of the project files!  Work only on those files specified above.  You must use the supplied `CMakeLists.txt` file as is.

* All students are required to abide by the CS 3251 coding standard, [available on the course web page](https://vuse-cs3251.github.io/style-guidelines/) and provided to you on the first day of class. Points will be deducted for not following the coding standard.

* For full credit, your program must compile with a recent version of `clang` or `gcc` and run successfully with the CI platform.
  * The CI build *will* fail if your code is not properly formatted. **This is by design.** If your code is compiling and running successfully, but the build is failing, then your build is most likely failing because your code is not passing the linter. This can be confirmed by checking if a command involving `linter` or `clang-format` in the CI build output log has an exit code of 1.

* Your program(s) should always have an exit code of 0.  A non-zero exit code (generally indicative of a segmentation fault or some other system error) is reason to worry and must be corrected for full points.

* When submitting the assignment, all files that are provided to you, plus your solution files have been submitted. All files necessary to compile and run your program must reside in the GitHub.com repository. 
