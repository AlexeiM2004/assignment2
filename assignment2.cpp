#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>

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
    std::string data;

    std::vector<double> course_mark;
    std::vector<double> course_module_tag;
    std::vector<double> course_year;
    std::vector<std::string> course_module_name;

    //While loop that reads in data

    while(std::getline(file,data))
    {
        std::stringstream ss(data);
        std::string course_information;
        if(std::getline(ss,course_information, '\n'))
        {
            //Create a try catch, so if there is any errors, it skips and trys the next
            try
            {
                double mark = std::stod(course_information.substr(0,4));
                double tag = std::stod(course_information.substr(5,5));
                double year = std::stod(course_information.substr(5,1));
                std::string name = (course_information.substr(13));

                course_mark.push_back(mark);
                course_year.push_back(year);
                course_module_tag.push_back(tag);           
                course_module_name.push_back(name);
            }catch(...){
            }
        }     
    }
    std::cout << "Read in " << course_mark.size() << " Course marks\n";
    std::cout << "Read in " << course_module_tag.size() << " Course module tags\n";
    std::cout << "Read in " << course_module_name.size() << " Course module names\n"; 

    for( int i = 0; i < course_mark.size(); ++i)
    {
        std::cout << course_module_name[i] << "\n";
    }

    //State how many entries it has read, (for loops)
    //Ask the user questions?
    //Should be able to filter by course year, and by course name

}

int main(){
    exam_statistics_calculator();
    placeholder_function_name_1();

    return 0;
}