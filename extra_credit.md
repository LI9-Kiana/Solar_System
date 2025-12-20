# CS 3251: Intermediate Software Design
## Programming Assignment 6

## Optional Extra Credit (Up to 55pts)

Below are three separate extra credit objectives.  If you fully complete the mandatory portions of the assignment (i.e. the core assignment) with a grade of 90% or greater you are eligible to receive extra credit.

You may complete none, some, or all of the extra credit.  Each of the three objectives will be evaluated separately.  You will receive either full credit or no credit on each individual objective - there is no partial credit within any one objective.

### Comets & Asteroids (20pts)

The vast majority of objects in our solar system are neither planets nor stars.  Add two new types of Objects to help make our Solar System more realistic.  Duplicate the `solar_system.json` file as `extended_solar_system.json` - you will add to it below.

1. Asteroid Class
   1. Must have a mass of less than 1e+21 (throw `std::logic_error` if not)
   2. Add ObjectFactory support for Asteroids
      1. Add factory methods for the [five largest asteroids](https://en.wikipedia.org/wiki/List_of_exceptional_asteroids)
      2. Add the five largest asteroids to the extended_solar_system.json file, and enhance the `Parser` class to create Asteroids as appropriate (based on mass)
2. Comet Class
   1. Must have a composition data element.  Comet constructor must validate that the string value is one of the following: "ice", "dust", "rock"
   2. Add ObjectFactory support for the following ["Great Comets"](https://en.wikipedia.org/wiki/Great_comet#List_of_great_comets):
      1. [Halley's](https://en.wikipedia.org/wiki/Halley%27s_Comet)
      2. [Hale-Bopp](https://en.wikipedia.org/wiki/Comet_Hale–Bopp)
   3. Add these two comets to the extended_solar_system.json file, and enhance the `Parser` class to create Comets as appropriate (based on the presence of a "composition" field)
3. Testing
   1. Create a new testing file `extended_solar_system.cpp`.  Pattern it after one of the existing testing files.  You will need to add this file to `tests/CmakeLists.txt`.  This new test should utilize the JSON you built in parts 1 & 2 above.
   2. Write at least four tests each for the Asteroid and Comet classes.  Ensure a solar system full of Stars, Planets, Asteroids and Comets can be constructed, simulated, visited, and cleaned up.
   
**Notes:**

While the necessary data for each Asteroid and Comet should be readily available in the linked wiki articles, some manual calculation of initial position and velocity is acceptable.

**How Evaluated:**

* Graders will review your code manually to ensure an appropriate response
* Graders will run the modified `extended_solar_system.cpp` test to ensure expected Asteroids and Comets are present

### Better Automated Tests (10pts)

Full coverage tests of the Universe, Star, Planet, Object classes.  Add a new file for each in the tests subdirectory (add these files to `tests/CMakeLists.txt`)

1. Universe Class
   1. Robust tests of the Universe class in isolation - i.e. test the class' methods individually.  You do not need to write more large tests like EarthYear
   2. Make sure that the first object in the Universe can only be a Star (throw `std::logic_error` in `Universe::addObject` if not)
   3. Make sure that all objects in the Universe have unique names (throw `std::logic_error` in `Universe::addObject` if not)
   4. Do not allow zero or negative mass (throw `std::logic_error` in `Universe::addObject` if not)
2. Object Class
   1. Write at least three good tests to validate the behavior of the `Object::getForce` method
   2. Write tests that test all the other methods in this class
3. Star and Planet Classes
   1. Write tests that validate the parts of these classes that differ from each other and from their Object base-class 

**How Evaluated:**

* Graders will review your code manually to ensure tests are well written and thorough.

### Visualization (20+5pts)

I would like a simple visualization of any Universe - let's use [ASCII art](https://en.wikipedia.org/wiki/ASCII_art)!  Write a new visitor that can be called at any time and will print an ASCII visualization of the state of the universe.

Below is an example visualization for the Sun and Earth with the Earth about 1/8 of its orbit around the Sun.  I have put in (but commented out) calls to the visualizer in both the `EarthYear` and `SolarSystem` tests.  Uncomment these to put the visualizer to work.

```text
****************************************************************
*                                                              *
*                                                              *
*                                                              *
*                                                              *
*                                                              *
*                        E                                     *
*                                                              *
*                             S                                *
*                                                              *
*                                                              *
*                                                              *
*                                                              *
*                                                              *
*                                                              *
****************************************************************
```

#### Files to be created/modified (at a minimum):

* `include/visitors/visualizer.h`
* `src/visitors/visualizer.h`
* `src/visitors/CMakelists.txt`
* `tests/earth_year.cpp`
* `tests/solar_system.cpp`
* Additional files as necessary

#### Extra Credit Grading & Criteria

* The visualization should work at any point in time - i.e. do not assume it will always be called at the end of one of the long tests
* The visualization should work for any number of stars and planets (1-9)
* The visualization scale and planet placement should be as accurate as possible - the star is always at the center
* Keep the visualization size to 64x16
* Colors are not necessary, but +5 additional points can be earned if each star & planet (and asteroid and comet if Objective 1 is completed) is a different color
* Use the first letter of the object as its placeholder.  If two objects have the same letter (Mercury and Mars) then use the first unique letter in their name

** How Evaluated:**

* Graders will review your code manually to ensure an appropriate response
* Graders will expect your automated tests for `earth_year` and `solar_system` to visualize the state of the Universe at the of the test.  They will compare what is printed to the expected output.  