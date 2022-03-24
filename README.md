# DSBA Introduction to Programming // Workshop 24
Spring semester 2021/22


Enums, bitwise operations, tests.


# Part 2. Tests

Study the structure of the test project, make sure you can run it.

Add a new file bitwise_test.cpp to the project. Implement EXPECT_EQ tests for tasks 1-3 from the previous workshop in this file.

1.  Task 1, getting bit at an index.
    1. Several checks for bits equal to 0 and 1. Use binary literals to define numbers for testing.
    2. Checks for indices 0 and 31 both for numbers where they should be 0 and where they should be 1.
2. Task 2, counting bits equal to 1 in a number.
    1. Checks for a number with 64 ones, 0 ones, some random numbers.
3. Task 3, output.
    1. Rewrite the function to output the number as a string instead of printing it. (If you haven’t finished this function during the last workshop, you may reverse a string instead of directly printing it in the reverse order).
    2. Check 1-2 random numbers.
    3. Check that numbers which have 1 as their first bit are outputted correctly.
    4. If you implemented the signed version of this task, check that it works with negative numbers, including ones which have 0 as their second bit.
