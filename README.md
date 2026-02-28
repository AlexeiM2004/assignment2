# Assignment 2 - Course Marks Data

## Program Brief

Progrm processes and analyses course mark data from the file "course_marks.dat". Providing a menu interface allowing the user to;

- Load module information containing; mark, module tag, year and module name.
- View bulk course data with various sorting options; alphabetically, by year, by mark.
- Filter and display mathematical (M) courses.
- Compute and display statistics such as mean, standard deviation, and range.
- Filter and display courses by year (1-4).
- Handle file input errors gracefully by skipping error lines or closing if no input file is detected.

## Compilcation code

- g++-11 assignment2.cpp -o assignment-2.o -std=gnu++17
- Note: ensure the "course_marks.dat" file is in the same directory as the created executable.

## Program Structure

The code is split into 6 sections;

1. Structure functions
- Contains two structures, "course_information" and "exam_statistics". "course_information" holds all relevant details for each course entry such as mark, tag, year and name. "exam_statistics" contains the calculated statistical results such as sample size, mean, standard deviation, standard error and range.
2. File loading function
- Opens and reads the "course_marks.dat" file line by line.
- Implements a try-catch error handling to skip to the next line if an error is encountered using catch(...)
- Parses each line according to a fixed string length format, (course mark, course module tag and year, module name)
- Creates objects from the parsed data.
- Closes the file after analysing.
3. Statistical calculation function
- Takes a vector of the course information as an input
- Calculates a sample size from the input vector
- Calculates the mean, standard deviation, standard error and range then returns an "exam_statistics" structure containing the calculated values.
- Range calculated using std::minmax_element
4. Filtering functions
- Filters courses by year (1-4) based on the users input.
- Returns a vector containing the courses from that academic year.
- Mathematical courses filtered identifies the substring (M) and returns all courses containing it using std::string::find, returning a vector of mathematical courses.
5. Sorting functions
- Organises data according to different user inputs.
- Sorts alphabetically (a - z), by year (highest to lowest) and by mark (lowest to highest), utilising std::sort. 
6. Display functions
- Hierachial system of display functions that direct user traffic.
- Main menu is the primary hub allowing the user to transfer to 2 other sub-menus or exit the program.
- Bulk statistics function is a sub-menu for bulk data vieiwing, directing the user to view all course information, view course information by year, or view mathematical courses.
- Exam statistics function is a sub-menu to view computed statistical information, directing the user to view all exam statistics or view exam statistics by year.
- Each sub-menu allows the user to return to the main menu.

## Decleration of AI usage

AI tools were utilized in the coding process to;
- Debug and provide solutions to code errors.
- Provide feedback to code quality, and suggestions for improvement.

The core program logic, strutures and algorithms were developed independently by the student (11022726). With AI tools serving as an invaluable tool for debugging and review purposes.
