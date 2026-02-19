#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>

//Structure to contain the course information 

struct course_information
{
    double course_mark;
    double course_module_tag;
    double course_year;
    std::string course_module_name;
};

//Structure to contain the calculated exam statistic's parameters

struct exam_statistics
{
    int course_sample_size;
    double mean;
    double standard_deviation;
    double standard_error;
    double range;
};

//Declare main menu prototype function

void main_menu(const std::vector<course_information>& courses);

//Function to read in file, state how many entries there are, organise, write into new file

std::vector<course_information> load_exam_statistics()
{
    //Read in a file and create arrays containing the file's parameters

    std::ifstream file("C:\\Users\\lexma\\projects\\assignment2\\course_marks.dat");
    std::string line;

    std::vector<course_information> courses;

    //While loop that reads in data

    while(std::getline(file,line))
    {
        {
            //Create a try catch, so if there is any errors, it skips and trys the next
            try
            {
                course_information gather_parameters;
                gather_parameters.course_mark = std::stod(line.substr(0,4));
                gather_parameters.course_module_tag = std::stod(line.substr(5,5));
                gather_parameters.course_year = std::stod(line.substr(5,1));
                gather_parameters.course_module_name = (line.substr(13));
                
                courses.push_back(gather_parameters);
            }catch(...){
            }
        }     
    }
    std::cout << "Successfully read in " << courses.size() << " exam records\n";
    return courses;
}

//----------Statistical calculation function----------//

exam_statistics exam_statistics_calculator(const std::vector<course_information>& courses)
{
    exam_statistics stats;
    //Identifies the samples course size
    stats.course_sample_size = courses.size();
    //Calculates the mean
    double mean_sum = 0 ;
    for(const auto& course : courses)
    {
        mean_sum += course.course_mark;
    }
    stats.mean = mean_sum / stats.course_sample_size;
    //Calculates the standard deviation
    double std_sum = 0;
    for(const auto& course : courses)
    {
        std_sum += std::pow(course.course_mark - stats.mean, 2);
    }
    stats.standard_deviation = pow( (1.0 / (stats.course_sample_size - 1)) * std_sum, (0.5));
    //Calculates the standard error
    stats.standard_error = stats.standard_deviation / std::pow(stats.course_sample_size, 0.5);
    //Calculates the range 
    std::vector<double> course_marks;
    for(const auto& course : courses)
    {
        course_marks.push_back(course.course_mark);
    }
    auto minmax = std::minmax_element(course_marks.begin(), course_marks.end());
    stats.range = *minmax.second - *minmax.first;
    return stats;
}

//----------Filtering functions----------//

//Filtering function that filter out a year upon users choice

std::vector<course_information> exam_statistics_filter_by_year(const std::vector<course_information>& courses, int year)
{
    std::vector<course_information> user_selected_course_year;
    for(const auto& course : courses)
    {
        if(course.course_year == year){
            user_selected_course_year.push_back(course);
        }
    }
    return user_selected_course_year;
}

//Filtering function that filters out the mathematical "(M)" courses upon user request

std::vector<course_information> exam_statistics_filter_mathematical_courses(const std::vector<course_information>& courses)
{
    std::vector<course_information> mathematical_courses;
    for(const auto& course : courses)
    {
        if(course.course_module_name.find("(M)") != std::string::npos)
        {
            mathematical_courses.push_back(course);
        }
    }
    return mathematical_courses;
}

//----------Display functions----------//

//Function to allow user to view all course information, or course information by year if selected

void display_bulk_statistics(const std::vector<course_information>& courses)
{
    std::cout << "\nThis is the view course information section. ";
    std::cout << "\nWhat would you like to do today? ";
    std::cout << "\nOption 1 - View all course information.";
    std::cout << "\nOption 2 - View course information by year.";
    std::cout << "\nOption 3 - View mathematical courses.";
    std::cout << "\nOption 4 - Return to main menu.";
    std::cout << "\nPlease select an option 1-4: ";
    int display_bulk_statistics_option = 0;
    std::cin >> display_bulk_statistics_option;
    while(std::cin.fail() || display_bulk_statistics_option <= 0 || display_bulk_statistics_option > 4)
    {
    std::cout << "\nYou have entered an invalid input, please select an option 1-4:";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin >> display_bulk_statistics_option;
    }
    if(display_bulk_statistics_option == 1)
    {
        for(const auto& course : courses)
        {
            std::cout << "\nModule name : " << course.course_module_name << " Module module tag : " << course.course_module_tag << " Module mark : " << course.course_mark;
        }
        std::cout << "\n";
        display_bulk_statistics(courses);
    }else if (display_bulk_statistics_option == 2)
    {
        std::cout << "\nPlease enter a course year you would like to view: ";
        int year;
        std::cin >> year;
        while(std::cin.fail() || year <= 0 || year > 4 )
        {
            std::cout << "\nInvalid course year input, please enter a course between the years 1-4: ";
            std::cin >> year;
        }
        std::vector<course_information> user_selected_exam_year = exam_statistics_filter_by_year(courses, year);
        //Uses the filtering function to filter out a year, then passes the variable back to be printed
        std::cout << "\nIdentified " << user_selected_exam_year.size() << " courses in year " << year << "\n";
        for(const auto& course : user_selected_exam_year)
        {
            std::cout << "\nModule name : " << course.course_module_name << " Module module tag : " << course.course_module_tag << " Module mark : " << course.course_mark;
        }
        std::cout << "\n";
        display_bulk_statistics(courses);
    }else if (display_bulk_statistics_option == 3)
    {
        std::vector<course_information> mathematical_courses_information =  exam_statistics_filter_mathematical_courses(courses);
        std::cout << "\nIdentified " << mathematical_courses_information.size() << " Mathematical courses. ";
        for(const auto& course : mathematical_courses_information)
        {
            std::cout << "\nModule name : " << course.course_module_name << " Module module tag : " << course.course_module_tag << " Module mark : " << course.course_mark;
        }
        std::cout << "\n";
        display_bulk_statistics(courses);

    }else if (display_bulk_statistics_option == 4)
    {
        //Sends the user back to the main menu function
        main_menu(courses);
    }
}

//Function to allow user to view all exam statistics, or exam statistics by year if selected

void display_exam_statistics(const std::vector<course_information>& courses)
{
    std::cout << "\nView exam statistics section. ";
    std::cout << "\nWhat would you like to do today? ";
    std::cout << "\nOption 1 - View all exam statistics.";
    std::cout << "\nOption 2 - View exam statistics by year.";
    std::cout << "\nOption 3 - Return to main menu.";
    std::cout << "\nPlease select an option 1-3: ";
    int exam_statistics_menu_option = 0;
    std::cin >> exam_statistics_menu_option;
    while(std::cin.fail() || exam_statistics_menu_option <= 0 || exam_statistics_menu_option > 4)
    {
    std::cout << "\nYou have entered an invalid input, please select an option 1-4:";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin >> exam_statistics_menu_option;
    }
    if(exam_statistics_menu_option == 1)
    {
        for(const auto& course : courses)
        {
        }
        std::cout << "\n";
        display_exam_statistics(courses);
    }else if (exam_statistics_menu_option == 2)
    {
        std::cout << "\nPlease enter a course year you would like to view: ";
        int year;
        std::cin >> year;
        while(std::cin.fail() || year <= 0 || year > 4 )
        {
            std::cout << "\nInvalid course year input, please enter a course between the years 1-4: ";
            std::cin >> year;
        }
        std::vector<course_information> user_selected_exam_year = exam_statistics_filter_by_year(courses, year);
        //Uses the filtering function to filter out a year, then passes the variable back to be printed
        std::cout << "\nIdentified " << user_selected_exam_year.size() << " courses in year " << year << "\n";
        exam_statistics calculated_statistical_results = exam_statistics_calculator(user_selected_exam_year);
        std::cout << "\n";
        display_exam_statistics(courses);
    }else if (exam_statistics_menu_option == 3)
    {
        //Sends the user back to the main menu function
        main_menu(courses);
    }
}

//Main menu, containing and directing traffic to all other functions

void main_menu(const std::vector<course_information>& courses)
{
    std::cout << "\nWelcome to the course marks data program. ";
    std::cout << "\nWhat would you like to do today? ";
    std::cout << "\nOption 1 - View bulk course data.";
    std::cout << "\nOption 2 - View calculated exam statistics.";
    std::cout << "\nOption 3 - Exit course marks program.";
    std::cout << "\nPlease select an option 1-3: ";
    int main_menu_option = 0;
    std::cin >> main_menu_option;
    while(std::cin.fail() || main_menu_option <= 0 || main_menu_option > 4)
    {
    std::cout << "\nYou have entered an invalid input, please select an option 1-4:";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin >> main_menu_option;
    }
    if(main_menu_option == 1)
    {
        display_bulk_statistics(courses);
    }else if (main_menu_option == 2)
    {
        display_exam_statistics(courses);
    }else if (main_menu_option == 3)
    {
        std::cout << "\nThank you for using this program, have a lovely day.";
    }
}

//----------Main function, No touchy----------//

int main(){
    std::vector<course_information> courses = load_exam_statistics();
    main_menu(courses);
    //exam_statistics_calculator(courses);
    //user_interface(courses);

    return 0;
}