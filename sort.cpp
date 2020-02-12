#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <algorithm>

using namespace std;

struct person{
   string first_name, last_name;
};

/* Overload "<" operator to compare names alphatebically by last name.
 * If last names match, then first names are compared*/
bool operator < (const struct person &p1, const struct person &p2){
   if(p1.last_name == p2.last_name){
      if(p1.first_name < p2.first_name){
	 return true;
      }
   }
   else if(p1.last_name < p2.last_name){
      return true;
   }

   else{
      return false;
   }
}


/*Compare two people alphabetically*/
bool comp(const struct person &p1, const struct person &p2){
   return p1 < p2;
}


int main(){

   ifstream file_input;
   ofstream file_output;

   string file_name;

   //Allow user to enter file name
   cout << "Enter file name to open (a sample file called names.txt is provided within directory). File: ";
   cin >> file_name;

   file_input.open(file_name.c_str());

   //Invalid files will be reprompted
   while(file_input.fail()){
      cout << endl << "An error occured while opening the file" << std::endl;
      cout << "Enter file name to open: ";
      cin >> file_name;
      file_input.open(file_name.c_str());
   }

   if(file_input.good()){

      vector<struct person>people;

      string str;

      /*Get each indiviual's first and last names. Assumptions:
      	  -are names are given in a file formatted as first name then last name
	  -first and last names are seperated by a space
	  -each individual is on a seperate line*/

      while(getline(file_input,str)){ 
	 istringstream ss(str);
	 string fn,ln;
	 ss >> fn; //get first name
	 ss >> ln; //get last name
	 struct person p = {fn,ln}; //create person object
	 people.push_back(p); 
      }

      file_input.close();

      sort(people.begin(), people.end(),comp); //sort names alphabetically by last name

      //Output sorted names to new sorted_names.txt file
      file_output.open("sorted_names.txt");

      for(int i = 0; i < people.size(); i++){
         file_output << people[i].last_name << " " << people[i].first_name << endl;

      }
      file_output.close();

      cout << endl <<  "File sucessfully sorted. Sorted names file is located at sorted_names.txt" << endl;
   }


   return 0;
}
