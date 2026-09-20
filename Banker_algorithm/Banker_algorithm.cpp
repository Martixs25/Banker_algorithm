// Banker_algorithm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;


int process_amount = 5;
int resource_amount = 3;
bool system_setup = true;

struct Resource { //Structure for the reousrces with a format name, maximum amount the resources has and the current amount of a resources left
    string name;
    int amount;
    int current;
};
Resource resource[10] = { // Constants for testing purposes
    {"Water", 1000, 300},
    {"Oil", 500, 150},
    {"Electricity", 2000, 900}
};

void Input_Resources(int number) { //Function entering data for the resources for x-th number ofthe array
    cout << "\nEnter resource name: ";
    cin >> resource[number].name;
    cout << "Enter resource amount: ";
    cin >> resource[number].amount;
    resource[number].current = resource[number].amount;
}

bool Update_Resources(string resource_name, int resources_changed_by, bool returned_or_given) { //Function for updating the amount of a resource in the resources array by given name, amount and change type
    for (int i = 0; i < resource_amount; i++) {
        if (resource[i].name == resource_name) {
            if (returned_or_given == true) { //if returned_or_given is true that is interpreted that the resources are returned
                resource[i].current += resources_changed_by;
                return true; //Returns true in a case of correctly updated resource
            }
            else if (returned_or_given == false) { //if returned_or_given is false that is interpreted that the resources are being given to a process
                if (resource[i].current - resources_changed_by < 0) { //Checking whether the resources can be initialized with that amount for this resource
                    cout << "\nError! Not enough resources to initialize this resource update! Please try again by giving fewer of this resource or expand this resource.\n";
                    resource[i].current += resources_changed_by; //Returning the resources back if the resources asked from the process is too much
                    return false;
                }
                else {
                    resource[i].current -= resources_changed_by;
                    return true;
                }
            }
        }
    }
        cout << "\nThe name of the resource is missing or incorrect\n";
        return false; //Returns false in a case of not found resource by name 
    
}

struct Process{ //Structure for the processes with a format name and arrays for the used resources and amount of the resource from the process
    string name;
    int amount_different_resources;
    string resource_name[10];
    int resource_amount_used[10];
    int max_resource_used[10];
};
Process process[10] = { //Constants for testing purposes
    {"Process1", 2, {"Water", "Oil"}, {100, 50}, {200, 100}},
    {"Process2", 3, {"Water", "Oil", "Electricity"}, {200, 150, 500}, {300, 200, 700}},
    {"Process3", 1, {"Electricity"}, {600}, {1000}},
    {"Process4", 2, {"Water", "Electricity"}, {300, 0}, {500, 1000}},
    {"Process5", 1, {"Oil"}, {100}, {200}}
};

void Input_Processes(int number) { //Function for entering inital data for the process variable
    cout << "\nEnter process name: ";
    cin >> process[number].name;
    cout << "\nEnter how many different resources the process will use: ";
    cin >> process[number].amount_different_resources;
    for (int i = 0; i < process[number].amount_different_resources; i++) { //an array consisting of all the resources a process uses
        bool update_value = true;
        do {
            cout << "\nEnter the name of resource " << i + 1 << ": ";
            cin >> process[number].resource_name[i];
            cout << "Enter amount the maximum amount that this process will use of that resource: ";
            cin >> process[number].max_resource_used[i];
            cout << "Enter the inital or current amount of that resource that this process is using: ";
            cin >> process[number].resource_amount_used[i];
            update_value = Update_Resources(process[number].resource_name[i], process[number].resource_amount_used[i], false);
        } while (update_value == false);
    }
}

void Delete_Process(int array_position) {
    for (int i = 0; i < process[array_position].amount_different_resources; i++) {
        Update_Resources(process[array_position].resource_name[i], process[array_position].resource_amount_used[i], true);
    }
    for (int i = 0; i < process_amount; i++) {
        process[i + array_position] = process[i + array_position + 1];
    }
    process_amount--;
}

void System_Message() { //A message of the the possible choices the user has with the system
    cout << "Press 1 to set up a list of resources and processes.\n";
    cout << "Press 2 to give a process resources.\n";
    cout << "Press 3 to show current system.\n";
    cout << "Press 4 to free resources from a process.\n";
    cout << "Press 0 to exit the program.\n";
}

void Clear_Resources() {
    // Clear the resource array
    for (int i = 0; i < 10; i++) {
        resource[i].name = "";
        resource[i].amount = 0;
        resource[i].current = 0;
    }

    // Clear the process array
    for (int i = 0; i < 10; i++) {
        process[i].name = "";
        process[i].amount_different_resources = 0;

        // Clear the arrays within each Process structure
        for (int j = 0; j < 10; j++) {
            process[i].resource_name[j] = "";
            process[i].resource_amount_used[j] = 0;
            process[i].max_resource_used[j] = 0;
        }
    }
}

void Setup() { // A function for setting up a starting point for the system of resources and processes
    
    if (system_setup == true) Clear_Resources();
    cout << "\nHow many processes are there (max. 10): ";
    cin >> process_amount;
    cout << "How many resources are there (max. 10): ";
    cin >> resource_amount;

    for (int i = 0; i < resource_amount; i++) {
        Input_Resources(i);
    }
    for (int i = 0; i < process_amount; i++) {
        Input_Processes(i);
    }
    system_setup = true;
}

void Choice1() {
    if (system_setup == true) {
        char system_restart = 'a';
        while (system_restart != 'y' || system_restart != 'n') {
            cout << "Warrning choosing set up with an already set up system will clear the current one. Do you wish to continue? (y/n): ";
            cin >> system_restart;
            if (system_restart == 'y') {
                Setup();
            }
            else if (system_restart == 'n') {
                break;
            }
        }
    }
    else if (system_setup == false) {
        Setup();
        cout << "Setup is succesful";
        system_setup = true;
    }
}

void Successful_process_array_falsify(bool successful_process[10][10]) { //mad in a function in order to skip clicking 100 times on every debug
    for (int i = 0; i < 10; i++) { //setting of the entries by default so that all the correct flags can be true 
        for (int j = 0; j < 10; j++) {
            successful_process[i][j] = false;
        }
    }
}

void Check_Done_Processes() {
    
    int successful_process_counter = 0;
    bool successful_process[10][10] = {}; 
    Successful_process_array_falsify(successful_process);
    for (int i = 0; i < process_amount; i++) {
        for (int j = 0; j < process[i].amount_different_resources; j++) {
            if (process[i].resource_amount_used[j] == process[i].max_resource_used[j]) {
                successful_process[i][j] = true;
            }
        }
    }

    for (int i = 0; i < process_amount; i++) {
        successful_process_counter = 0;
        for (int j = 0; j < process[i].amount_different_resources; j++) {
            if (successful_process[i][j] == true) {
                successful_process_counter++;
            }
        }
        if (successful_process_counter == process[i].amount_different_resources) {
            Delete_Process(i);
        }
    }
    
}

int Check_Completable_Process() {
    int index_of_resource; //index of the resource to check in the resource array 
    bool successful_process[10][10] = {}; // flag wether the maximum amount of resources can be given to process
    Successful_process_array_falsify(successful_process);
    int successful_process_counter = 0; // counter for the flag of max resources
    for (int i = 0; i < process_amount; i++) { // Checking which of the process can get the maximum resources they need individually
        for (int j = 0; j < process[i].amount_different_resources; j++) {
            for (int k = 0; k < resource_amount; k++) {
                if (process[i].resource_name[j] == resource[k].name) {
                    index_of_resource = k;

                    if (process[i].max_resource_used[j] <= process[i].resource_amount_used[j] + resource[index_of_resource].current) {
                        successful_process[i][j] = true;
                    }
                    else {
                        successful_process[i][j] = false;
                    }
                }
            }

        }
    }

    for (int i = 0; i < process_amount; i++) { // Checking if there is a process we can give the max amount of every resource it needs to finish their job
        successful_process_counter = 0;
        for (int j = 0; j < process[i].amount_different_resources; j++) {
            if (successful_process[i][j] == true) {
                successful_process_counter++;
            }
        }
        if (successful_process_counter == process[i].amount_different_resources) {
            return i;
        }
        else return -1;

    }

}

bool Check_For_Deadlock(string process_check, string resource_check, int resource_amount_chceck) {
    Resource resource_buffer[10]; //Remembering the current state of the system in case valdiation fails 
    Process process_buffer[10];
    int process_amount_buffer = process_amount;

    for (int i = 0; i < resource_amount; i++) {
        resource_buffer[i] = resource[i];
    }
    for (int i = 0; i < process_amount; i++) {
        process_buffer[i] = process[i];
    }
    bool process_found = false;
    for (int i = 0; i < process_amount; i++) {
        if (process[i].name == process_check) {
            process_found = true;
            for (int j = 0; j < process[i].amount_different_resources; j++) { //Updating the system with the query 
                if (process[i].resource_name[j] == resource_check) {
                    process[i].resource_amount_used[j] += resource_amount_chceck;
                    Update_Resources(resource_check, resource_amount_chceck, false);
                }
            }
        }
    }
    if (process_found == false){
        cout << "Process not found!\n";
        return false;
    }

    int returned_process_check = -1; //Checking if the system is in a safe state
    while (process_amount != 0) {
        returned_process_check = Check_Completable_Process();
        if (returned_process_check == -1) {
            break;
        }
        else {
            Delete_Process(returned_process_check);
        }
    }

    if (process_amount == 0) { // System is in a safe state
        for (int i = 0; i < resource_amount; i++) { // returning the system back to normal with the quruied resource
            resource[i] = resource_buffer[i];
        }
        for (int i = 0; i < process_amount_buffer; i++) {
            process[i] = process_buffer[i];
        }

        process_amount = process_amount_buffer;

        for (int i = 0; i < process_amount; i++) {
            if (process[i].name == process_check) {
                process_found = true;
                for (int j = 0; j < process[i].amount_different_resources; j++) { //Updating the system with the query 
                    if (process[i].resource_name[j] == resource_check) {
                        process[i].resource_amount_used[j] += resource_amount_chceck;
                        Update_Resources(resource_check, resource_amount_chceck, false);
                    }
                }
            }
        }


    }
    else {
        for (int i = 0; i < resource_amount; i++) { // returning the system back to normal if it can't fina a process to resolve
            resource[i] = resource_buffer[i];
        }
        for (int i = 0; i < process_amount; i++) {
            process[i] = process_buffer[i];
        }

        process_amount = process_amount_buffer;
        cout << "The queried resource for this process couldn't be given as it will put the system in an unsafe position.";
        return false;
    }
}

void Choice2() {
    string process_to_check;
    int amount_to_check;
    string resource_to_chceck;
    bool returned_value = false;
    cout << "\nChoose a process whom to give resources to: ";
    cin >> process_to_check;
    cout << "Choose a resources to give this process: ";
    cin >> resource_to_chceck;
    cout << "Choose an amount of the resource to give to process " << process_to_check << ": ";
    cin >> amount_to_check;
    returned_value = Check_For_Deadlock(process_to_check, resource_to_chceck, amount_to_check);
    if (returned_value == true) {
        cout << "Successfully given resource";
    }
    Check_Done_Processes();
}

void Show_Resources(int array_index) {
        cout << left << setw(15) << resource[array_index].name  << "| " << setw(13) << resource[array_index].current  << "| " << setw(13) << resource[array_index].amount << "|";
    
}

void Show_Processes(int array_index) {

    cout << left << process[array_index].name << setw(9) << " | " << process[array_index].amount_different_resources << "| " << setw(15);
    for (int i = 0; i < resource_amount; i++) {
        cout << setw(13) << process[array_index].resource_name[i] << "| " << setw(13) << process[array_index].resource_amount_used[i] << "| " << setw(13) << process[array_index].max_resource_used[i] << "| ";
    }
}

void Choice3() {
    cout << "Resources: \n\n";
    cout << "_____________________________________________\n";
    cout << left << setw(15) << "Name" << setw(15) << "| Current" << setw(15) <<"| Total" << "|\n";
    cout << "_______________|______________|______________|\n";
    for (int i = 0; i < resource_amount; i++) {
        Show_Resources(i);
        cout << endl;
    }
    cout << "_____________________________________________|\n";
    cout << endl << endl << endl; 
    cout << "Processes: \n\n";
    cout << "_____________________________________________\n";
    cout << left << setw(9) << "Name" << setw(9) << "| Amount |";
    for (int i = 0; i < resource_amount; i++) {
        cout << setw(13 + i) << "R. Name" << setw(15) << "| Current use" << setw(15) << "| Max use" << "|";
    }
    cout << endl << "_________|________|";
    for (int i = 0; i < resource_amount; i++) {
        cout << "_____________|______________|______________|";
    }
    cout << endl;
    for (int i = 0; i < process_amount; i++) {
        Show_Processes(i);
        cout << endl;
    }
}

void Choice4() {
    string process_to_update;
    int process_to_update_number = -1; //number of the process in the array
    string resource_to_update_name;
    int resource_to_update_in_process; //numer of the resource in the process array
    int resource_to_update = -1;
    int resource_to_update_amount = -1;
    cout << "Choose a process to free resources from: ";
    cin >> process_to_update;
    for (int i = 0; i < process_amount; i++) {
        if (process[i].name == process_to_update) {
            process_to_update_number = i;
            break;
        }
    }
    if (process_to_update_number == -1) {
        cout << "Process was not found!";
        return;
    }
    
    cout << "Process " << process_to_update << " has " << process[process_to_update_number].amount_different_resources << " resources: \n";
    for (int i = 0; i < process[process_to_update_number].amount_different_resources; i++) {
        cout << "   " << i + 1 << ". " << process[process_to_update_number].resource_name[i]  << endl;
    }
    do  {
        cout << endl << "Which resource would you like to free (Choose the number of the resource): ";
        cin >> resource_to_update;
    } while (resource_to_update < 0 && resource_to_update >= process[process_to_update_number].amount_different_resources);
    resource_to_update--;

    for (int i = 0; i < process[process_to_update_number].amount_different_resources; i++) {
        if (process[process_to_update_number].resource_name[i] == resource[resource_to_update].name) {
            resource_to_update_name = resource[resource_to_update].name;
            resource_to_update_in_process = i;
            break;
        }
    }
    do {
        cout << "How much of resource \"" << resource_to_update_name << "\" do you want to free from " << process_to_update << ": ";
        cin >> resource_to_update_amount;
    } while (resource_to_update_amount >= 0 && resource_to_update_amount < process[process_to_update_number].resource_amount_used[resource_to_update_in_process]);

    Update_Resources(resource_to_update_name, resource_to_update_amount, true);
    process[process_to_update_number].resource_amount_used[resource_to_update_in_process] -= resource_to_update_amount;
    process[process_to_update_number].max_resource_used[resource_to_update_in_process] -= resource_to_update_amount;

    cout << "Successfully freed up resources.";
}


void main()
{
    int user_choice = -1;
    do {
        System_Message();
        cin >> user_choice;
        if (user_choice == 1) Choice1();
        else if (user_choice == 2) Choice2();
        else if (user_choice == 3) Choice3();
        else if (user_choice == 4) Choice4();
        cin >> user_choice;
    } while (user_choice != 0);
    cout << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
