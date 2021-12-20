#include <iostream>
#include<string.h>
#include<string>
#include<fstream>
#include<iomanip>
#include<map>
#include<vector>
#include <Windows.h>
#include <cstdio>
using namespace std;

void sortTasks(){                    //function to sort the tasks and store  per priority in task.txt 
    map<int,vector<string>> tasks;
    string task;
    fstream myfile("task.txt", ios::in);
    while(getline(myfile,task)){
         int priority=task[0]-48;
         tasks[priority].push_back(task.substr(2));
        }
    myfile.close();
    string line;
    ofstream temp;
    temp.open("sort.txt",ios::out);
    int count=1,flag=0;
    for(auto i=tasks.begin(); i!=tasks.end();i++){
        int p=i->first;
        
        vector<string> tasks_list=i->second;
        if(tasks_list.size()==0) temp<<p<<" "<<tasks_list[0]<<endl;
        else{
            temp<<p<<" "<<tasks_list[0]<<endl;
            for(int j=1;j<tasks_list.size();j++)
            temp<<p<<" "<<tasks_list[j]<<endl;
        }
    }
    temp.close();
    remove("task.txt");
    rename("sort.txt", "task.txt");
   
}

int main(int argc, char* argv[])
{
    SetConsoleOutputCP(CP_UTF8);    // to print UTF-8 strings to std::cout on Windows
    setvbuf(stdout, nullptr, _IOFBF, 1000);

    if(argc==1)                         //prints help when no additional args are provided
    { cout<<"Usage :-"<<endl;
       cout<<"$ ./task add 2 hello world    # Add a new item with priority 2 and text " <<"\"hello world\"" <<" to the list";
       cout<<"\n$ ./task ls                   # Show incomplete priority list items sorted by priority in ascending order";
       cout<<"\n$ ./task del INDEX            # Delete the incomplete item with the given index";
       cout<<"\n$ ./task done INDEX           # Mark the incomplete item with the given index as complete";
       cout<<"\n$ ./task help                 # Show usage";
       cout<<"\n$ ./task report               # Statistics";
       }
    else if(strcmp(argv[1],"help")==0)  //prints help
       { cout<<"Usage :-";
       cout<<"\n$ ./task add 2 hello world    # Add a new item with priority 2 and text " <<"\"hello world\"" <<" to the list";
       cout<<"\n$ ./task ls                   # Show incomplete priority list items sorted by priority in ascending order";
       cout<<"\n$ ./task del INDEX            # Delete the incomplete item with the given index";
       cout<<"\n$ ./task done INDEX           # Mark the incomplete item with the given index as complete";
       cout<<"\n$ ./task help                 # Show usage";
       cout<<"\n$ ./task report               # Statistics";
       }
    
    else if(strcmp(argv[1],"add")==0)   //add a single task
    {
        if (argc==2) cout<<"Error: Missing tasks string. Nothing added!\n";  //show error message when add is not followed by a tasks
        else{
        int p = stoi(argv[2]);
        string task=argv[3];
        ofstream myfile;
        myfile.open ("task.txt",ios::app);
        myfile  << p <<" "<<task<<endl;
        myfile.close();
        cout<<"Added task: "<<"\""<<task<<"\""<<" with priority "<<p<<endl;
        sortTasks();
        }

    }
    else if(strcmp(argv[1],"ls")==0){   //list tasks in order of priority
        
        int p;
        string task;
        fstream myfile("task.txt", ios::in);
        int i=1;
        int flag=0;
        while(getline(myfile,task)){
            flag=1;

         cout<<i<<". "<<task.substr(2)<<" ["<<task[0]<<"]"<<endl;
         
         i++;
        }
        if(flag==0) cout<<"There are no pending tasks!\n";  //list when there are no remaining tasks
        
         myfile.close();
        

    }
    else if(strcmp(argv[1],"del")==0){       //delete a task
        if (argc==2) cout<<"Error: Missing NUMBER for deleting tasks.";  //delete does not have enough arguments
        else{
        int lineNo=stoi(argv[2]);
        string line;
        ifstream fin;
    
        fin.open("task.txt");
    
        std::ofstream temp;
        temp.open("temp.txt");
        int count=1,flag=0;
        while (getline(fin, line)) {
        if(count==lineNo)
         {
             flag=1; 
             count++;
             continue;
        }
        else{
            temp << line <<endl;
            count++;
        }
       }
       if(flag==0) cout<<"Error: task with index "<<"#"<<lineNo<<" does not exist. Nothing deleted.";  //delete non-existent tasks
       else cout<<"Deleted task #"<<lineNo;

       temp.close();
       fin.close();
       remove("task.txt");
       rename("temp.txt", "task.txt");
        }

    }
    else if(strcmp(argv[1],"done")==0){    //mark a tasks as done
        if (argc==2) cout<<"Error: Missing NUMBER for marking tasks as done.";    //mark as done without providing a tasks number
        else{

        int lineNo=stoi(argv[2]);
        string line;
        ifstream fin;
    
        fin.open("task.txt");
    
        std::ofstream temp;
        temp.open("temp.txt");
        ofstream myfile;
        myfile.open ("completed.txt",ios::app);
        
        int count=1,flag=0;
        while (getline(fin, line)) {
        if(count==lineNo)
         {
             flag=1; 
             count++;
             

             myfile << line.substr(2)<<endl;

             continue;
        }
        else{
            temp << line <<endl;
            count++;
        }
        
       }
       if(flag==0) cout<<"Error: no incomplete item with index #"<<lineNo<<" exists."<<endl;    //mark as done a tasks which does not exist
       else cout<<"Marked item as done."<<endl;

       temp.close();
       fin.close();
       myfile.close();

       remove("task.txt");
       rename("temp.txt", "task.txt");

        }

    }
    else if(strcmp(argv[1],"report")==0){    //report pending & completed tasks
        string task;
        fstream myfile("task.txt", ios::in);
        int count=0;
        while(getline(myfile,task)) count++;
        myfile.close();
        cout<<"Pending : "<<count;
        int i=1;
        myfile.open("task.txt",ios::in);
        while(getline(myfile,task)) {
            cout<<endl;
            cout<<i<<". "<<task.substr(2)<< " ["<<task[0]<<"]";
            i++;
        }
        myfile.close();
        fstream myF("completed.txt", ios::in);
        count=0;
        while(getline(myF,task)) count++;
        cout<<"\nCompleted : "<<count;
        i=1;
        myF.close();
        myF.open("completed.txt",ios::in);
        while(getline(myF,task)) {
            cout<<"\n"<<i<<". "<<task;
            i++;
        }
         myF.close();
    }
    

   return 0;
}

