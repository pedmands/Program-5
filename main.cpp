// Preston Edmands
// CSCI 130 - 002
// Spring 2020
// Program 4 - v2
// This program calculates the cost of throwing a child’s birthday party as determined by the age of the birthday child and the number of guests invited, plus the cost of the birthday cake. It then outputs the report, breaking down the number of each item to purchase and the cost of each item, as well as the total cost, to a file name determined by the user.
// v2 notes: The program now calculates price breakpoints for balloons, napkins and plates, the and number of full and half sheet cakes needed to feed the party.

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <string>
// #include <chrono>
// #include <ctime> // used to work with date and time for exit message
#include <stdio.h>
#include <time.h>
#include <sstream>

// Debug
#include <typeinfo>

using namespace std;

float COST_PER_GIFT_BAG = 4.15;    // Cost per gift bag
int NAPKINS_PER_PACK = 12;         // Number of napkins in a pack
int PLATES_PER_PACK = 8;           // Plates per pack
float COST_PER_PIZZA = 5.35;       // Cost per pizza
int SLICES_PER_PIZZA = 12;         // Number of slices per pizza 🍕
float COST_PER_JUICE_PACK = 4.25;  // Cost per juice pack
int JUICE_BOXES_PER_PACK = 10;     // Number of juice boxes per pack
float COST_PER_FULL_SHEET = 15.75; // Price of each sheet cake
float COST_PER_HALF_SHEET = 10.00; // Price of half sheet cake

/* #region [Charcoal] Function Declarations */
string GetFileName();
float GenerateReport(string fileName);
string GetName();
int GetAge();
int GetGuests();
//float GetCakeCost();
float CalcBalloonsCost(int numBalloons);
float CalcNapkinsCost(int napkinPacks, int NAPKINS_PER_PACK);
float CalcPlatesCost(int platePacks, int PLATES_PER_PACK);
void PrintReport(int age, int guests, int fullSheets, bool halfSheet, string fileName, string name, int numBalloons, float balloonsCost, int numBags, float giftBagsCost, int napkinPacks, float napkinsCost, int platePacks, float platesCost, int pizzas, float pizzaCost, int juiceBoxPacks, float juiceCost, float halfSheetCost, float fullSheetCost, float total);
char ContinuePrompt(char response);
void PrintSummary(string fileName, int numParties, float partiesTotalCost);
void ExitMessage(string message);
/* #endregion */

// ---------------------------------- Main Function -----------------------------------

int main() {
    /* #region Fold Main ⤵️ */ 
    char response;
    int numParties = 0;
    float currentPartyTotal;
    float partiesTotalCost;

    // auto end = chrono::system_clock::now();
    // time_t end_time = chrono::system_clock::to_time_t(end);
    // cout << ctime(&end_time);

    // Welcome the user
    cout << "Welcome to the Birthday Party Cost Calculator!" << endl
         << endl;

    ExitMessage("time of day");

    string fileName = GetFileName();

    do {
        currentPartyTotal = GenerateReport(fileName);
        numParties += 1;
        partiesTotalCost += currentPartyTotal;
        response = ContinuePrompt(response);
    } while(response == 'Y');

    PrintSummary(fileName, numParties, partiesTotalCost);
   
    return 0;
/* #endregion Fold Main */
}

// ------------------------------- User Input Functions -------------------------------

/* #region User Input Functions */
// isNumber() checks whether or not a string contains digits. Used when validating user input during GetName()
// Precondition: str
// Postcondition: returns true if
bool isNumber(string str) { 
        for (int i = 0; i < str.length(); i++) 
            if (isdigit(str[i]) == true) 
                return true; 
        return false; 
}

// GetName() gets the birthday child's name from user and returns it to main()
// Precondition: none
// Postcondition: returns name
string GetName() {
    /* #region [Input] Fold GetName */
    // Returns true if s is a number else false 
    string name;

    do {
        cout << "What is the birthday child's name? ";
        getline(cin, name);
        if (isNumber(name))
            cout << "No digits allowed in name!" << endl;
    }while(isNumber(name));
    return name;
    /* #endregion */
}

// GetAge() gets the age from user and returns it to main()
// Precondition: none
// Postcondition: returns age
int GetAge() {
    /* #region [Input] Fold GetAge */
    int age;
    do {
        cout << "How old will the birthday child be? ";
        cin >> age;
        while ( cin.fail() ) {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Invalid input! Please enter a value between 1-119: ";
            cin >> age;
        }
        if( age < 1 || age >= 120 ) {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Range Error! Please enter a value between 1-119." << endl;
        }
    } while(age < 1 || age >= 120);
    return age;
     /* #endregion */
}

// GetGuests() gets the number of invited guests from user and returns it to main()
// Precondition: none
// Postcondition: returns guests
int GetGuests() {
    /* #region [Input] Fold GetGuests */
    int guests;
    do {
        cout << "How many invited guests? ";
        cin >> guests;
        while ( cin.fail() ) {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Invalid input! Please enter a value between 1-499: ";
            cin >> guests;
        }
        if(guests < 1 || guests >= 500) {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Range Error! Please enter a value between 1-499: " << endl;
        }
    }while(guests < 1 || guests >= 500);
    return guests;
     /* #endregion */
}

// GetFileName() gets the name of the output file from the user and returns it to main()
// Precondition: none
// Postcondition: returns fileName
string GetFileName() {
    /* #region [Input] Fold GetFileName */
    string fileName;
    cout << "What would you like to name the report file? ";
    getline(cin, fileName);
    return fileName;
    /* #endregion */
}

// GetCakeCost() gets the cost of the birthday cake from the user and returns it to main()
// Precondition: none
// Postcondition: returns cakeCost
//float GetCakeCost() {
//    float cakeCost;
//    cout << "How much is the birthday cake? $";
//    cin >> cakeCost;
//    cin.ignore(256, '\n');
//    return cakeCost;
//}
/* #endregion */

// ---------------------------- Price Breakpoint Functions ----------------------------

// CalcBalloonsCost() calculates the price of each balloon based on the number of balloons purchased
// Precondition: numBalloons
// Postcondition: returns total for balloons
float CalcBalloonsCost(int numBalloons) {
    /* #region [Calc] Fold CalcBalloonsCost */
        
    float costPerBalloon; // Cost per balloon
    float total;          // total cost of balloons

    if (numBalloons > 100)
    {
        costPerBalloon = .25;
    }
    else if (numBalloons >= 50)
    {
        costPerBalloon = .35;
    }
    else
    {
        costPerBalloon = .45;
    }
    total = numBalloons * costPerBalloon;
    return total;
    /* #endregion */
}

// CalcNapkinsCost() calculates the price of each napkin pack based on the total number of napkins purchased
// Precondition: napkinPacks, NAPKINS_PER_PACK
// Postcondition: returns total cost of napkins
float CalcNapkinsCost(int napkinPacks, int NAPKINS_PER_PACK) {
    /* #region [Calc] Fold CalcNapkinsCost */
        
    int numNapkins = napkinPacks * NAPKINS_PER_PACK; // Total number of napkins
    float costPerPack;                               // Cost per napkin pack
    float total;                                     // total cost of napkins

    if (numNapkins >= 300)
    {
        costPerPack = 1.50;
    }
    else if (numNapkins > 100)
    {
        costPerPack = 2.50;
    }
    else
    {
        costPerPack = 3.00;
    }
    total = napkinPacks * costPerPack;
    return total;
    /* #endregion */
}

// CalcPlatesCost() calculates the price of each plate pack based on the total number of plates purchased
// Precondition: platePacks, PLATES_PER_PACK
// Postcondition: returns total cost of plates
float CalcPlatesCost(int platePacks, int PLATES_PER_PACK) {
    /* #region [Calc] Fold CalcPlatesCost */
        
    int numPlates = platePacks * PLATES_PER_PACK; // Total number of plates
    float costPerPack;                            // Cost per plate pack
    float total;                                  // total cost of plates

    if (numPlates > 50)
    {
        costPerPack = 3.00;
    }
    else
    {
        costPerPack = 3.15;
    }
    total = platePacks * costPerPack;
    return total;
    /* #endregion */
}

// -------------------------------- Utility Functions ---------------------------------

float GenerateReport(string fileName){
    /* #region [Charcoal] Fold Generate Report */
    string name;     // Birthday child's name, to be entered by user.
    int age;         // Birthday child's age, to be entered by user.
    int guests;      // Number of guests invited, to be entered by user.

    // -------------- Input ---------------------

    // Ask the user for the child's name
    name = GetName();
    // Get birthday child's age from the user
    age = GetAge();
    // Get the number of guests from the user
    guests = GetGuests();

    // -------------- Calculations --------------

    // Calculate total number of children, including birthday child
    int children = guests + 1;

    // Calculate number and cost of balloons
    int numBalloons = guests * age; // Each guest gets one balloon for each year the child is old
    float balloonsCost = CalcBalloonsCost(numBalloons);

    // Calculate number and cost of gift bags
    int numBags = guests; // Each guest gets one gift bag
    float giftBagsCost = numBags * COST_PER_GIFT_BAG;

    // Calculate number and cost of napkin packs
    int napkinPacks = ceil((children * 4) / float(NAPKINS_PER_PACK)); // Each child gets 4 napkins. NAPKINS_PER_PACK converted to float to prevent data loss for rounding up.
    float napkinsCost = CalcNapkinsCost(napkinPacks, NAPKINS_PER_PACK);

    // Calculate number and cost of plates
    int platePacks = ceil((children * 2) / float(PLATES_PER_PACK)); // Each child gets 2 plates. PLATES_PER_PACK converted to float to prevent data loss for rounding up.
    float platesCost = CalcPlatesCost(platePacks, PLATES_PER_PACK);

    // Calculate number and cost of pizzas
    int pizzas = ceil((children * 3) / float(SLICES_PER_PIZZA)); // Each child gets 3 slices of pizza. SLICES_PER_PIZZA converted to float to prevent data loss for rounding up.
    float pizzaCost = pizzas * COST_PER_PIZZA;

    // Calculate number and cost of juice box packs
    int juiceBoxPacks = ceil((children * 2) / float(JUICE_BOXES_PER_PACK)); // Each child gets 2 juice boxes. JUICE_BOXES_PER_PACK converted to float to prevent data loss for rounding up.
    float juiceCost = juiceBoxPacks * COST_PER_JUICE_PACK;

    // Calculate number of full and half sheet cakes and cost for each
    float halfSheetCost = 0; // Cost of half sheet of cake
    float fullSheetCost = 0; // Cost of full sheet cakes

    bool halfSheet = false; // We don't buy a cake until we calculate how many we need

    int fullSheets = children / 50;        // Each full sheet feeds 50 children
    int remainingChildren = children % 50; // Remaining children after dividing by 50

    if (remainingChildren > 25)
    {
        fullSheets += 1;
    }
    else if (remainingChildren > 0) // Make sure there are at least *some* children left
    {
        halfSheet = true;
        halfSheetCost = COST_PER_HALF_SHEET;
    }

    fullSheetCost = fullSheets * COST_PER_FULL_SHEET; // Total cost of full sheet cakes

    // Calculate the total cost
    // We leave halfSheetCost and fullSheetCost as separate variables instead of combining them because they appear as line items in the report
    float total = balloonsCost + giftBagsCost + napkinsCost + platesCost + pizzaCost + juiceCost + halfSheetCost + fullSheetCost;

    // -------------- Output --------------------

    // Print the results to the ofstream output file partyReport.out, located in the same directory as the program.
    PrintReport(age, guests, fullSheets, halfSheet, fileName, name, numBalloons, balloonsCost, numBags, giftBagsCost, napkinPacks, napkinsCost, platePacks, platesCost, pizzas, pizzaCost, juiceBoxPacks, juiceCost, halfSheetCost, fullSheetCost, total);

    return total;
     /* #endregion */
}

// PrintReport() prints the report generated by the program to the ofstream output file partyReport.out, located in the same directory as the program.
// Precondition: guests fileName, name, numBalloons, balloonsCost, numBags, giftBagsCost, napkinPacks, napkinsCost, platePacks, platesCost, pizzas, pizzaCost, juiceBoxPacks, juiceCost, cakeCost, total
// Postcondition: prints the result to the output file partyReport.out
void PrintReport(int age, int guests, int fullSheets, bool halfSheet, string fileName, string name, int numBalloons, float balloonsCost, int numBags, float giftBagsCost, int napkinPacks, float napkinsCost, int platePacks, float platesCost, int pizzas, float pizzaCost, int juiceBoxPacks, float juiceCost, float halfSheetCost, float fullSheetCost, float total) {
    /* #region [Utilities] Fold PrintReport */
        
    // Open an output filestream
    ofstream partyReport;

    // Open a report file using the ofstream with the file name previously provided by user
    partyReport.open(fileName, ios::app);

    // Format floats to two decimal places
    partyReport << fixed << showpoint << setprecision(2);

    partyReport << endl;
    partyReport << "Report for birthday child: " << name << endl;
    partyReport << "Birthday child's age:      " << age << endl;
    partyReport << "Number of invited guests:  " << guests << endl << endl;   
    partyReport << "           Balloons:  " << setw(5) << numBalloons << "     $ " << setw(8) << balloonsCost << endl;
    partyReport << "          Gift Bags:  " << setw(5) << numBags << "     $ " << setw(8) << giftBagsCost << endl;
    partyReport << "       Napkin Packs:  " << setw(5) << napkinPacks << "     $ " << setw(8) << napkinsCost << endl;
    partyReport << "        Plate Packs:  " << setw(5) << platePacks << "     $ " << setw(8) << platesCost << endl;
    partyReport << "             Pizzas:  " << setw(5) << pizzas << "     $ " << setw(8) << pizzaCost << endl;
    partyReport << "     Juicebox Packs:  " << setw(5) << juiceBoxPacks << "     $ " << setw(8) << juiceCost << endl;
    if (fullSheets)
    {
        partyReport << "  Cake - full sheet:     " << setw(2) << fullSheets << "     $ " << setw(8) << fullSheetCost << endl;
    }
    if (halfSheet)
    {
        partyReport << "  Cake - half sheet:     " << "1      $    " << halfSheetCost << endl;
    }
    partyReport << "         Total cost:            $ " << setw(8) << total << endl << endl;
    partyReport << string(44, '*') << endl;

    // Close the report file
    partyReport.close();
    /* #endregion */
}

char ContinuePrompt(char response) {
    do {
        cout << "Do you have another report to enter? 'Y'/'N': ";
        cin >> response;
        cin.ignore(256, '\n');
        response = toupper(response);
        if(response != 'Y' && response != 'N')
            cout << "Error! Please Enter 'Y' or ’N’: " << endl;
    }while(response != 'Y' && response != 'N');

    return response;
}

void PrintSummary(string fileName, int numParties, float partiesTotalCost) {
     /* #region [Utilities] Fold PrintSummary */
    float partyAverage = partiesTotalCost / numParties;

      // Open an output filestream
    ofstream partyReport;
    // Open a report file using the ofstream with the file name previously provided by user
    partyReport.open(fileName, ios::app);

    partyReport << fixed << showpoint << setprecision(2);

    partyReport << endl << endl;
    partyReport << "Number of Parties:                " << setw(8) << numParties << endl;
    partyReport << "Total cost of all parties:      $ " << setw(8) << partiesTotalCost << endl;
    partyReport << "Average spent on each party:    $ " << setw(8) << partyAverage << endl << endl << endl;
    partyReport << string(44, '*') << endl;
    partyReport << string(44, '*') << endl << endl;

    partyReport.close();
    /* #endregion */
}

void ExitMessage(string message) {
     /* #region [Utilities] Fold ExitMessage */
    // Get system time: http://www.cplusplus.com/reference/ctime/strftime/
    time_t rawtime;
    struct tm * timeinfo;
    char hour [80], day [80];

    time (&rawtime);
    timeinfo = localtime (&rawtime);

    strftime(hour,80,"%I", timeinfo);
    strftime(day,80,"%A", timeinfo);

    // string hourTens = {1, hour[0]};
    // string hourOnes = {1, hour[1]};

    // cout << "hourTens: " << hourTens << ", type: " << typeid(hourTens).name() << endl;

    // string wholeHour = hourTens + hourOnes;

    // cout << "wholeHour: " << wholeHour << ", type: " << typeid(wholeHour).name() << endl;

    // Convert string to integer: http://www.cplusplus.com/forum/articles/9645/
    int intHour;
    std::stringstream convert(hour); // stringstream used for the conversion initialized with the contents of wholeHour

    if ( !(convert >> intHour) ) // give the value to intHour using the characters in the string
        intHour = 0; // If that fails set intHour to 0

    // intHour = 17;

    if (message == "time of day") {
        int timeOfDay;
        cout << "intHour: " << intHour << endl;
        /* #region switch(intHour) */
        if ( intHour <= 10 )
            timeOfDay = 0; // Morning
        else if ( intHour > 10 && intHour <= 16 )
            timeOfDay = 1; // Afternoon
        else
            timeOfDay = 2;
        switch (timeOfDay)
        {
            case 0: cout << "Have a nice " << day << " morning!" << endl;
                    break;
            case 1: cout << "Have a nice " << day << " afternoon!" << endl;
                    break;
            case 2: cout << "Have a nice " << day << " evening!" << endl;
                    break;
        } // switch (hour) /* #endregion */
    } else {
         cout << "Have a good " << day << "!" << endl;
    }// if (message == "time of day")
    /* #endregion */
}











// Old main() contents

//  // -------------- Input ---------------------
//     /* #region [Input] Input */
//     // Ask the user for the child's name
//     name = GetName();

//     // Get birthday child's age from the user
//     age = GetAge();

//     // Get the number of guests from the user
//     guests = GetGuests();

//     // Get the cost of the cake from the user
//     // cakeCost = GetCakeCost();

//     // Get the file name for the output file from the user
//     fileName = GetFileName();
//     /* #endregion */

//     // -------------- Calculations --------------
//     /* #region [Calc] Calculations */
//     // Calculate total number of children, including birthday child
//     int children = guests + 1;

//     // Calculate number and cost of balloons
//     int numBalloons = guests * age; // Each guest gets one balloon for each year the child is old
//     float balloonsCost = CalcBalloonsCost(numBalloons);

//     // Calculate number and cost of gift bags
//     int numBags = guests; // Each guest gets one gift bag
//     float giftBagsCost = numBags * COST_PER_GIFT_BAG;

//     // Calculate number and cost of napkin packs
//     int napkinPacks = ceil((children * 4) / float(NAPKINS_PER_PACK)); // Each child gets 4 napkins. NAPKINS_PER_PACK converted to float to prevent data loss for rounding up.
//     float napkinsCost = CalcNapkinsCost(napkinPacks, NAPKINS_PER_PACK);

//     // Calculate number and cost of plates
//     int platePacks = ceil((children * 2) / float(PLATES_PER_PACK)); // Each child gets 2 plates. PLATES_PER_PACK converted to float to prevent data loss for rounding up.
//     float platesCost = CalcPlatesCost(platePacks, PLATES_PER_PACK);

//     // Calculate number and cost of pizzas
//     int pizzas = ceil((children * 3) / float(SLICES_PER_PIZZA)); // Each child gets 3 slices of pizza. SLICES_PER_PIZZA converted to float to prevent data loss for rounding up.
//     float pizzaCost = pizzas * COST_PER_PIZZA;

//     // Calculate number and cost of juice box packs
//     int juiceBoxPacks = ceil((children * 2) / float(JUICE_BOXES_PER_PACK)); // Each child gets 2 juice boxes. JUICE_BOXES_PER_PACK converted to float to prevent data loss for rounding up.
//     float juiceCost = juiceBoxPacks * COST_PER_JUICE_PACK;

//     // Calculate number of full and half sheet cakes and cost for each
//     float halfSheetCost = 0; // Cost of half sheet of cake
//     float fullSheetCost = 0; // Cost of full sheet cakes

//     bool halfSheet = false; // We don't buy a cake until we calculate how many we need

//     int fullSheets = children / 50;        // Each full sheet feeds 50 children
//     int remainingChildren = children % 50; // Remaining children after dividing by 50

//     if (remainingChildren > 25)
//     {
//         fullSheets += 1;
//     }
//     else
//     {
//         halfSheet = true;
//         halfSheetCost = COST_PER_HALF_SHEET;
//     }

//     fullSheetCost = fullSheets * COST_PER_FULL_SHEET; // Total cost of full sheet cakes

//     // Calculate the total cost
//     // We leave halfSheetCost and fullSheetCost as separate variables instead of combining them because they appear as line items in the report
//     float total = balloonsCost + giftBagsCost + napkinsCost + platesCost + pizzaCost + juiceCost + halfSheetCost + fullSheetCost;
//     /* #endregion */

//     // -------------- Output --------------------
//     /* #region [Utilities] Utilities */
//     // Print the results to the ofstream output file partyReport.out, located in the same directory as the program.
//     PrintReport(age, guests, fullSheets, halfSheet, fileName, name, numBalloons, balloonsCost, numBags, giftBagsCost, napkinPacks, napkinsCost, platePacks, platesCost, pizzas, pizzaCost, juiceBoxPacks, juiceCost, halfSheetCost, fullSheetCost, total);
//     /* #endregion */
    