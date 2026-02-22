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

//----------Sorting functions----------//

//Sorting function to sort alphabetically if user requests

std::vector<course_information> sort_courses_alphabetically(const std::vector<course_information>& courses)
{
    std::vector<course_information> sorted_alphabetically = courses;
    std::sort(sorted_alphabetically.begin(), sorted_alphabetically.end(), [](const course_information& a,const course_information& b) {return a.course_module_name < b.course_module_name;});
    
    return sorted_alphabetically;
}

//Sorting function to sort by mark (highest to lowest) if user requests

std::vector<course_information> sort_courses_by_mark(const std::vector<course_information>& courses)
{
    std::vector<course_information> sorted_by_mark = courses;
    std::sort(sorted_by_mark.begin(), sorted_by_mark.end(), [](const course_information& a,const course_information& b) {return a.course_mark < b.course_mark;});
    
    return sorted_by_mark;
}

//Sorting function to sort by year (lowest to highest) if user requests

std::vector<course_information> sort_courses_by_year(const std::vector<course_information>& courses)
{
    std::vector<course_information> sorted_by_year = courses;
    std::sort(sorted_by_year.begin(), sorted_by_year.end(), [](const course_information& a,const course_information& b) {return b.course_year < a.course_year;});
    
    return sorted_by_year;
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
        std::cout << "\nPlease state how you would all course information sorted: ";
        std::cout << "\nOption 1 - View all course information as written from file.";
        std::cout << "\nOption 2 - View all course information alphabetically.";
        std::cout << "\nOption 3 - View all course information by mark (Lowest to Highest).";
        std::cout << "\nOption 4 - View all course information by year (Lowest to Highest).";
        std::cout << "\nPlease select an option 1-4: ";     
        int sort_option;
        std::cin >> sort_option;
        while(std::cin.fail() || sort_option <= 0 || sort_option > 4 )
        {
            std::cout << "\nInvalid sort type input, please enter an option between 1-4: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> sort_option;
        }
        if(sort_option == 1)
        {
            for(const auto& course : courses)
            {
                std::cout << "\nModule name : " << course.course_module_name << " Module module tag : " << course.course_module_tag << " Module mark : " << course.course_mark;
            }
            std::cout << "\n";
            display_bulk_statistics(courses);
        }else if(sort_option ==2)
        {
            std::vector<course_information> sorted_alphabetically = sort_courses_alphabetically(courses);
            for(const auto& course : sorted_alphabetically)
            {
                std::cout << "\nModule name : " << course.course_module_name << " Module module tag : " << course.course_module_tag << " Module mark : " << course.course_mark;
            }
            std::cout << "\n";
            display_bulk_statistics(courses);
        }else if(sort_option ==3)
        {
            std::vector<course_information> sorted_by_mark = sort_courses_by_mark(courses);
            for(const auto& course : sorted_by_mark)
            {
                std::cout << "\nModule name : " << course.course_module_name << " Module module tag : " << course.course_module_tag << " Module mark : " << course.course_mark;
            }
            std::cout << "\n";
            display_bulk_statistics(courses);
        }else if(sort_option == 4)
        {
            std::vector<course_information> sorted_by_year = sort_courses_by_year(courses);
            for(const auto& course : sorted_by_year)
            {
                std::cout << "\nModule name : " << course.course_module_name << " Module module tag : " << course.course_module_tag << " Module mark : " << course.course_mark;
            }
            std::cout << "\n";
            display_bulk_statistics(courses);
        }

    }else if (display_bulk_statistics_option == 2)
    {
        std::cout << "\nPlease enter a course year you would like to view: ";
        int year;
        std::cin >> year;
        while(std::cin.fail() || year <= 0 || year > 4 )
        {
            std::cout << "\nInvalid course year input, please enter a course between the years 1-4: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> year;
        }
        std::vector<course_information> user_selected_exam_year = exam_statistics_filter_by_year(courses, year);
        //Uses the filtering function to filter out a year, then passes the variable back to be printed
        std::cout << "\nIdentified " << user_selected_exam_year.size() << " courses in year " << year << "\n";
        //Prompts the user as to how they would like their information by year sorted
        std::cout << "\nPlease state how you would like course year [" << year << "] information sorted: ";
        std::cout << "\nOption 1 - View course year [" << year << "] information as written from file.";
        std::cout << "\nOption 2 - View course year [" << year << "] information alphabetically.";
        std::cout << "\nOption 3 - View course year [" << year << "] information by mark (Lowest to Highest).";
        std::cout << "\nPlease select an option 1-3: ";     
        int sort_option;
        std::cin >> sort_option;
        while(std::cin.fail() || sort_option <= 0 || sort_option > 3 )
        {
            std::cout << "\nInvalid sort type input, please enter an option between 1-3: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> sort_option;
        }
        if(sort_option == 1)
        {
            for(const auto& course : user_selected_exam_year)
            {
                std::cout << "\nModule name : " << course.course_module_name << " Module module tag : " << course.course_module_tag << " Module mark : " << course.course_mark;
            }
            std::cout << "\n";
            display_bulk_statistics(courses);
        }else if(sort_option ==2)
        {
            std::vector<course_information> sorted_alphabetically = sort_courses_alphabetically(user_selected_exam_year);
            for(const auto& course : sorted_alphabetically)
            {
                std::cout << "\nModule name : " << course.course_module_name << " Module module tag : " << course.course_module_tag << " Module mark : " << course.course_mark;
            }
            std::cout << "\n";
            display_bulk_statistics(courses);
        }else if(sort_option ==3)
        {
            std::vector<course_information> sorted_by_mark = sort_courses_by_mark(user_selected_exam_year);
            for(const auto& course : sorted_by_mark)
            {
                std::cout << "\nModule name : " << course.course_module_name << " Module module tag : " << course.course_module_tag << " Module mark : " << course.course_mark;
            }
            std::cout << "\n";
            display_bulk_statistics(courses);
        }
    }else if (display_bulk_statistics_option == 3)
    {
        std::vector<course_information> mathematical_courses_information =  exam_statistics_filter_mathematical_courses(courses);
        std::cout << "\nIdentified " << mathematical_courses_information.size() << " Mathematical courses. ";
        //Prompts the user as to how they would like their information by year sorted
        std::cout << "\nPlease state how you would the mathematical course information sorted: ";
        std::cout << "\nOption 1 - View mathematical course information as written from file.";
        std::cout << "\nOption 2 - View mathematical course information alphabetically.";
        std::cout << "\nOption 3 - View mathematical course information by mark (Lowest to Highest).";
        std::cout << "\nOption 4 - View mathematical course information by year (Lowest to Highest).";
        std::cout << "\nPlease select an option 1-4: ";     
        int sort_option;
        std::cin >> sort_option;
        while(std::cin.fail() || sort_option <= 0 || sort_option > 4 )
        {
            std::cout << "\nInvalid sort type input, please enter an option between 1-4: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> sort_option;
        }
        if(sort_option == 1)
        {
            for(const auto& course : mathematical_courses_information)
            {
                std::cout << "\nModule name : " << course.course_module_name << " Module module tag : " << course.course_module_tag << " Module mark : " << course.course_mark;
            }
            std::cout << "\n";
            display_bulk_statistics(courses);
        }else if(sort_option ==2)
        {
            std::vector<course_information> sorted_alphabetically = sort_courses_alphabetically(mathematical_courses_information);
            for(const auto& course : sorted_alphabetically)
            {
                std::cout << "\nModule name : " << course.course_module_name << " Module module tag : " << course.course_module_tag << " Module mark : " << course.course_mark;
            }
            std::cout << "\n";
            display_bulk_statistics(courses);
        }else if(sort_option ==3)
        {
            std::vector<course_information> sorted_by_mark = sort_courses_by_mark(mathematical_courses_information);
            for(const auto& course : sorted_by_mark)
            {
                std::cout << "\nModule name : " << course.course_module_name << " Module module tag : " << course.course_module_tag << " Module mark : " << course.course_mark;
            }
            std::cout << "\n";
            display_bulk_statistics(courses);
        }else if(sort_option == 4)
        {
            std::vector<course_information> sorted_by_year = sort_courses_by_year(courses);
            for(const auto& course : sorted_by_year)
            {
                std::cout << "\nModule name : " << course.course_module_name << " Module module tag : " << course.course_module_tag << " Module mark : " << course.course_mark;
            }
            std::cout << "\n";
            display_bulk_statistics(courses);
        }
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
        std::cout << "\nYou have entered an invalid input, please select an option 1-3;";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> exam_statistics_menu_option;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if(exam_statistics_menu_option == 1)
    {
        exam_statistics calculated_statistical_results = exam_statistics_calculator(courses);
        std::cout << "\nIdentified a total of [" << calculated_statistical_results.course_sample_size << "] overall.";
        std::cout << "\nOverall exam statistics were;";
        std::cout << "\nMean = " << calculated_statistical_results.mean;
        std::cout << "\nStandard Deviation = " << calculated_statistical_results.standard_deviation;
        std::cout << "\nStandard error = " << calculated_statistical_results.standard_error;
        std::cout << "\nRange = " << calculated_statistical_results.range;
        std::cout << "\n";
        std::cout << "\n";
        display_exam_statistics(courses);
    }else if (exam_statistics_menu_option == 2)
    {
        std::cout << "\nPlease enter a course year you would like to view 1-4: ";
        int year;
        std::cin >> year;
        while(std::cin.fail() || year <= 0 || year > 4 )
        {
            std::cout << "\nInvalid course year input, please enter a course between the years 1-4: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> year;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::vector<course_information> user_selected_exam_year = exam_statistics_filter_by_year(courses, year);
        //Uses the filtering function to filter out a year, then passes the variable back to be printed
        std::cout << "\nIdentified " << user_selected_exam_year.size() << " courses in year " << year << "\n";
        exam_statistics calculated_statistical_results = exam_statistics_calculator(user_selected_exam_year);
        std::cout << "\nStatistics for exam year [" << year << "] were;";
        std::cout << "\nMean = " << calculated_statistical_results.mean;
        std::cout << "\nStandard Deviation = " << calculated_statistical_results.standard_deviation;
        std::cout << "\nStandard error = " << calculated_statistical_results.standard_error;
        std::cout << "\nRange = " << calculated_statistical_results.range;
        std::cout << "\n";
        display_exam_statistics(courses);
    }else if (exam_statistics_menu_option == 3)
    {
        //Sends the user back to the main menu function
        main_menu(courses);
    }
}

//Main menu, directing traffic to all other functions and allowing the user to exit the program
 
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
    while(std::cin.fail() || main_menu_option <= 0 || main_menu_option > 3)
    {
        std::cout << "\nYou have entered an invalid input, please select an option 1-3:";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> main_menu_option;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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