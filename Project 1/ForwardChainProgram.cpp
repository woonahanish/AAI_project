#include <iostream>
#include<map>

using namespace std;

//Global variables declaration.
map <int, string> variablesMap;


int main() {

    //Inputing variables from the user.
    cout<<"Enter the variables below: ";
    int i=0;
    while(true){
        string inputString;
        cin>>inputString;
        if(inputString=="END")
            break;
        variablesMap[i] = inputString;
        i++;
        cout<<"Enter the next variable[To terminate the list enter 'END']: ";
    }




    return 0;

}