#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>
#include <limits>

//Structure to contain the information 

struct course_information
{
    double course_mark;
    double course_module_tag;
    double course_year;
    std::string course_module_name;
};

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

double exam_statistics_calculator(const std::vector<course_information>& courses)
{
    return 0;
}

//----------Filtering functions----------//

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

//----------Display functions----------//

//Function to allow user to view all course information, or course information by year

void display_bulk_statistics(const std::vector<course_information>& courses)
{
    std::cout << "User is in the display bulk statistics function";
}

//Function to display all calculated year's course statistics

void display_all_course_statistics(const std::vector<course_information>& courses)
{
    std::cout << "User is in the display all course statistics function";
}

//Function to display a selected year's course statistics

void display_course_statistics_by_year(const std::vector<course_information>& courses)
{
    std::cout << "User is in the display course statistics by year function";
}

//Old function to be reworked into the code

void user_interface(const std::vector<course_information>& courses)
{
    //Asks the user what course year information they would like to view
    std::cout << "\nPlease enter a course year you would like to view: ";
    int year;
    std::cin >> year;
    while(year <= 0 || year > 4 )
    {
        std::cout << "\nInvalid course year input, please enter a course between the years 1-4: ";
        std::cin >> year;
    }
    
    //Call the exam filter by year function

    std::vector<course_information> user_selected_exam_year_information = exam_statistics_filter_by_year(courses, year);
    std::cout << "\nIdentified " << user_selected_exam_year_information.size() << " courses in year " << year << "\n";
    for(const auto& course : user_selected_exam_year_information)
    {
        std::cout << "\nModule name : " << course.course_module_name;
        std::cout << "\nModule module tag : " << course.course_module_tag;
        std::cout << "\nModule mark : " << course.course_mark;

    }

}

//Main menu, containing paths to all other functions

void main_menu(const std::vector<course_information>& courses)
{
    std::cout << "\nWelcome to the course marks data program.";
    std::cout << "\nWhat would you like to do today? ";
    std::cout << "\nOption 1 - View bulk course mark data.";
    std::cout << "\nOption 2 - View all year's exam statistics.";
    std::cout << "\nOption 3 - View a selected year's exam statistics.";
    std::cout << "\nOption 4 - Exit course marks data program.";
    std::cout << "\nPlease select an option 1-4: ";
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
        display_all_course_statistics(courses);
    }else if (main_menu_option == 3)
    {
        display_course_statistics_by_year(courses);
    }else if (main_menu_option == 4)
    {
        std::cout << "\nThank you for using this program, have a lovely day.";
        //Find a backdoor for the program to escape here
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