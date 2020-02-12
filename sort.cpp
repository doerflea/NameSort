#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

struct person{
   std::string first_name, last_name;
};

/* Compare names alphatebically by last name.
 * If last names match, then first names are compared
 * If first individual is alphabetically before the 2nd individual true is returned*/
bool comp (const struct person &p1, const struct person &p2){

   if(p1.last_name < p2.last_name){
      return true;
   }
   else if(p1.last_name == p2.last_name){
      if(p1.first_name < p2.first_name){
	 return true;
      }
   }
      return false;
}



int main(){

   std::ifstream file_input;
   std::ofstream file_output;

   std::string file_name;

   //Allow user to enter file name
   std::cout << "Enter file name to open (a sample file called names.txt is provided within directory). File: ";
   std::cin >> file_name;

   file_input.open(file_name.c_str());

   //Invalid files will be reprompted
   while(file_input.fail()){
      std::cout << std::endl << "An error occured while opening the file" << std::endl;
      std::cout << "Enter file name to open: ";
      std::cin >> file_name;
      file_input.open(file_name.c_str());
   }

   if(file_input.good()){

      std::vector<struct person>people;

      std::string str;

      /*Get each indiviual's first and last names. Assumptions:
      	  -names are given in a file formatted as first name then last name
	  -first and last names are seperated by a space
	  -each individual is on a seperate line*/

      while(getline(file_input,str)){ 
	 std::istringstream ss(str);
	 std::string fn,ln;
	 ss >> fn; //get first name
	 ss >> ln; //get last name
	 struct person p = {fn,ln}; //create person object
	 people.push_back(p); 
      }

      file_input.close();

      std::sort(people.begin(), people.end(),comp); //sort names alphabetically by last name

      //Output sorted names to new sorted_names.txt file
      file_output.open("sorted_names.txt");

      for(int i = 0; i < people.size(); i++){
         file_output << people[i].last_name << " " << people[i].first_name << std::endl;

      }
      file_output.close();

      std::cout << std::endl <<  "File sucessfully sorted. Sorted names file is located at sorted_names.txt" << std::endl;
   }
   return 0;
}
