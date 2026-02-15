#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>

//Structure to contain the information 

struct course_information
{
    double course_mark;
    double course_module_tag;
    double course_year;
    std::string course_module_name;
};

///Function to calculate mean, std, variance, maybe a skibidy graph

void exam_statistics_calculator()
{
    //Here we will calculate, mean, mode and range
    //Here we will calculate standard deviation & variance
    //Possibly plot a distribution of exam results
}

//Function to read in file, state how many entries there are, organise, write into new file

void placeholder_function_name_1()
{
    //Define constants

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
    //State how many entries it has read, (for loops)
    //Ask the user questions?
    //Should be able to filter by course year, and by course name
    std::cout << "Read in " << courses.size() << " Course records\n";
    for(int i=0; i < courses.size(); ++i)
    {
        std::cout << "\nCourse Mark " << courses[i].course_mark;
        std::cout << " Course Year " << courses[i].course_year;
        std::cout << " Course Tag " << courses[i].course_module_tag;
        std::cout << " Course Name " << courses[i].course_module_name;
    }
}

int main(){
    exam_statistics_calculator();
    placeholder_function_name_1();

    return 0;
}