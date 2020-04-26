// Preston Edmands
// CSCI 130 - 002
// Spring 2020
// Program 4 - v2
// This program calculates the cost of throwing a child’s birthday party as determined by the age of the birthday child and the number of guests invited and outputs the report to a file determined by the user, breaking down number of items and cost. It can calculate multiple party reports and will print a summary containing the total number of parties calculated, the total cost of all parties, and the average cost for each party at the bottom of the file. It will also output the summary to the console.
// v2 notes: The program now calculates price breakpoints for balloons, napkins and plates, the and number of full and half sheet cakes needed to feed the party.
// v3 notes: Added functions to generate individual party reports as long as the user wants and print a summary of the run of reports when the user is done. All input is also now validated. Broke out call party item calculations into their own functions. Added functions to output a welcome message from a file and output a dynamic message on exit.

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <sstream>

using namespace std;

/* #region [Charcoal] Constant Declarations */
const float COST_PER_GIFT_BAG = 4.15;    // Cost per gift bag
const int NAPKINS_PER_PACK = 12;         // Number of napkins in a pack
const int PLATES_PER_PACK = 8;           // Plates per pack
const int SLICES_PER_PIZZA = 12;         // Number of slices per pizza 🍕
const float COST_PER_PIZZA = 5.35;       // Cost per pizza
const int JUICE_BOXES_PER_PACK = 10;     // Number of juice boxes per pack
const float COST_PER_JUICE_PACK = 4.25;  // Cost per juice pack
const float COST_PER_HALF_SHEET = 10.00; // Price of half sheet cake
const float COST_PER_FULL_SHEET = 15.75; // Price of each sheet cake
/* #endregion */

/* #region [Charcoal] Function Declarations */
void WelcomeMessage(string artName);
string GetFileName();
void GenerateReport(string fileName, float& currentPartyCost, int& numParties);
bool IsNumber(string str);
string GetName();
int GetAge();
int GetGuests();
//float GetCakeCost();
void CalcBalloons(int age, int guests, int& numBalloons, float& balloonsCost);
void CalcBags(int guests, int& numBags, float& giftBagsCost);
void CalcNapkins(int children, int& napkinPacks, float& napkinsCost);
void CalcPlates(int children, int& platePacks, float& platesCost);
void CalcPizzas(int children, int& pizzas, float& pizzaCost);
void CalcJuice(int children, int& juiceBoxPacks, float& juiceCost);
void CalcCake(int children, bool& halfSheet, int& fullSheets, float& halfSheetCost, float& fullSheetCost);
void PrintReport(int age, int guests, int fullSheets, bool halfSheet, string fileName, string name, int numBalloons, float balloonsCost, int numBags, float giftBagsCost, int napkinPacks, float napkinsCost, int platePacks, float platesCost, int pizzas, float pizzaCost, int juiceBoxPacks, float juiceCost, float halfSheetCost, float fullSheetCost, float currentPartyCost);
char ContinuePrompt(char response);
void PrintSummary(string fileName, int numParties, float partiesTotalCost);
void ExitMessage(string adjective);
/* #endregion */

// ---------------------------------- Main Function -----------------------------------

int main() {
    /* #region [Main] Fold Main */ 
    char response; // The user's response to the question as to whether to run the program again
    float currentPartyCost; // Total cost of party currently being calculated
    int numParties = 0; // Total number of pariy reports generated
    float partiesTotalCost; // Total cost of all parties reported

    // Welcome the user
    WelcomeMessage("cake-man");

    // Get the name for the report file from the user
    string fileName = GetFileName();

    do { // Using a do while loop ensures the code gets run at least once
        GenerateReport(fileName, currentPartyCost, numParties); // Calculate the total cost of the party, appaend a report to the file determined by GetFileName()
        partiesTotalCost += currentPartyCost; // Add cost of party to the total cost of all parties
        // Ask the user if they have any more parties to  calculate
        response = ContinuePrompt(response);
    } while(response == 'Y');

    // Append the summary report to the bottom of the file determined by GetFileName()
    PrintSummary(fileName, numParties, partiesTotalCost);

    // Bid farewell to the user
    ExitMessage("great");

    return 0;
/* #endregion Fold Main */
}

// ------------------------------- User Input Functions -------------------------------

/* #region User Input Functions */

// GetFileName() gets the name of the output file from the user and returns it to main()
// Precondition: none
// Postcondition: returns fileName
string GetFileName() {
    /* #region [Input] Fold GetFileName */
    string fileName;
    cout << "Please enter the file name to use for the report: " << endl;
    cin >> fileName;
    cin.clear();
    cin.ignore(256, '\n');
    return fileName;
    /* #endregion */
}

// isNumber() checks whether or not a string contains digits. Used when validating user input during GetName()
// Precondition: str
// Postcondition: returns true if str contains a number
bool IsNumber(string str) { 
     /* #region [Input] Fold IsNumber */
    //  https://bit.ly/2zcocKT
        for (int i = 0; i < str.length(); i++) 
            if (isdigit(str[i]) == true) 
                return true; 
        return false; 
        /* #endregion */
}

// GetName() gets the birthday child's name from user and returns it to main()
// Precondition: none
// Postcondition: returns name
string GetName() {
    /* #region [Input] Fold GetName */
    string name;

    do { /* Input validation: Using a do while loop we check whether name contain a number
            with isNumber(), and return an error while it does */
        cout << endl << "What is the birthday child's name? " << endl;
        getline(cin, name);
        if (IsNumber(name))
            cout << "No digits allowed in name!" << endl;
    }while(IsNumber(name));
    return name;
    /* #endregion */
}

// GetAge() gets the age from user and returns it to main()
// Precondition: none
// Postcondition: returns age
int GetAge() {
    /* #region [Input] Fold GetAge */
    int age;
    do {  /* Input validation: Using a do while loop we check if age is within acceptable range,
            and prompt the user if it's not */
        cout << "How old will the birthday child be? " << endl;
        cin >> age;
        cin.ignore(256, '\n');
        while (cin.fail()) {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "INPUT ERROR, Please enter an integer between 1-119!" << endl << endl;
            cout << "How old will the birthday child be?" << endl;
            cin >> age;
            cin.ignore(256, '\n');
        }
        if(age < 1 || age >= 120) { // Input validation: If input is outside of acceptable range, output an error
            cout << "RANGE ERROR, Please enter a value between 1-119!" << endl << endl;
            cin.clear();
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
    do { /* Input validation: Using a do while loop we check if guests is within acceptable range,
            and prompt the user if it's not */
        cout << "How many invited guests? " << endl;
        cin >> guests;
        cin.ignore(256, '\n');
        while ( cin.fail() ) {  // Input validation: While input is not of type int output an error
            cin.clear();
            cin.ignore(256, '\n');
            cout << "INPUT ERROR, Please enter an integer between 1-499! " << endl << endl;
            cout << "How many invited guests? " << endl;
            cin >> guests;
            cin.ignore(256, '\n');
        }
        if(guests < 1 || guests >= 500) { // Input validation: If input is outside of acceptable range, output an error
            cout << "RANGE ERROR, Please enter a value between 1-499! " << endl << endl;
            cin.clear();
        }
    } while(guests < 1 || guests >= 500);

    return guests;
     /* #endregion */
}

// ContinuePrompt() Asks the user if they would like to process another party, and returns their reponse
// Pre-condition: response
// Post-condition: returns char response to main()
char ContinuePrompt(char response) {
     /* #region [Input] Fold ContinuePrompt */
    do {
        cout << "Would you like to process another party (Y/N)? " << endl << endl;
        cin >> response;
        cin.ignore(256, '\n');
        response = toupper(response);
        if(response != 'Y' && response != 'N')
            cout << "ERROR, Please enter Y or N! " << endl << endl << endl;
    }while(response != 'Y' && response != 'N');

    return response;
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

// ------------------------------- Calculation Functions ------------------------------

/* #region Calculation Functions */

// CalcBalloons() calculates the price of each balloon based on the number of balloons purchased
// Precondition: age, guests, numBalloons, balloosCost
// Postcondition: returns number of balloons needed and total cost for balloons
void CalcBalloons(int age, int guests, int& numBalloons, float& balloonsCost) {
    /* #region [Calc] Fold CalcBalloonsCost */
    numBalloons = age * guests; // Each guest gets one balloon for each year the child is old
    float costPerBalloon; // Cost per balloon

    if (numBalloons > 100) {
        costPerBalloon = .25;
    } else if (numBalloons >= 50) {
        costPerBalloon = .35;
    } else {
        costPerBalloon = .45;
    }
    balloonsCost = numBalloons * costPerBalloon;
    /* #endregion */
}

// CalcBags() calculates the number of gift bags needed and their total cost
// Precondition: guests, numBags, giftBagsCost, COST_PER_GIFT_BAG
// Postcondition: returns number of gift bags needed and their total cost
void CalcBags(int guests, int& numBags, float& giftBagsCost) {
    numBags = guests; // Each guest gets one gift bag
    giftBagsCost = numBags * COST_PER_GIFT_BAG;
}

// CalcNapkins() calculates number of napkin packs and total cost of napkins
// Precondition: children, napkinPacks, nakpinsCost, NAPKINS_PER_PACK
// Postcondition: calculates number of napkin packs and total cost of napkins
void CalcNapkins(int children, int& napkinPacks, float& napkinsCost) {
    /* #region [Calc] Fold CalcNapkins */
    napkinPacks = ceil((children * 4) / float(NAPKINS_PER_PACK)); // Each child gets 4 napkins. NAPKINS_PER_PACK converted to float to prevent data loss for rounding up.
    int numNapkins = napkinPacks * NAPKINS_PER_PACK; // Total number of napkins
    float costPerPack;                               // Cost per napkin pack

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
    napkinsCost = napkinPacks * costPerPack; // total cost of napkins
    /* #endregion */
}

// CalcPlates() calculates the number of plate packs needed and the price of each plate pack based on the total number of plates being purchased
// Precondition: platePacks, PLATES_PER_PACK
// Postcondition: returns total cost of plates
void CalcPlates(int children, int& platePacks, float& platesCost) {
    /* #region [Calc] Fold CalcPlatesCost */
    platePacks = ceil((children * 2) / float(PLATES_PER_PACK)); // Each child gets 2 plates. PLATES_PER_PACK converted to float to prevent data loss for rounding up.
    int numPlates = platePacks * PLATES_PER_PACK; // Total number of plates
    float costPerPack; // Cost per plate pack
    if (numPlates > 50)
        costPerPack = 3.00;
    else
        costPerPack = 3.15;
    platesCost = platePacks * costPerPack;
    /* #endregion */
}

// CalcPizzas() calculates the number of pizzas needed and their total cost
// Precondition: children, pizzas, pizzaCost, SLICES_PER_PIZZA, COST_PER_PIZZA
// Postcondition: returns the numbder of pizzas and their total cost
void CalcPizzas(int children, int& pizzas, float& pizzaCost) {
    pizzas = ceil((children * 3) / float(SLICES_PER_PIZZA)); // Each child gets 3 slices of pizza. SLICES_PER_PIZZA converted to float to prevent data loss for rounding up.
    pizzaCost = pizzas * COST_PER_PIZZA;
}

// CalcJuice() calculates the number of juice box packs needed and their total cost
// Precondtion: children, juiceBoxPacks, juiceCost, JUICE_BOXES_PER_PACK, COST_PER_JUICE_PACK
// Postcondition: returns the number of juice box packs needed and their total cost
void CalcJuice(int children, int& juiceBoxPacks, float& juiceCost) {
    juiceBoxPacks = ceil((children * 2) / float(JUICE_BOXES_PER_PACK)); // Each child gets 2 juice boxes. JUICE_BOXES_PER_PACK converted to float to prevent data loss for rounding up.
    juiceCost = juiceBoxPacks * COST_PER_JUICE_PACK;
}

// CalcCake() calculates the number of full and half sheet cakes needed and their total cost
// Precondition: children, halfSheet, fullSheets, halfSheetCost, fullSheetCost, COST_PER_HALF_SHEET, COST_PER_FULL_SHEET
// Postcondition: returns the number of full and half sheet cakes needed and their total cost
void CalcCake(int children, bool& halfSheet, int& fullSheets, float& halfSheetCost, float& fullSheetCost) {
     /* #region [Calc] Fold CalcCake */
    halfSheet = false; // We don't buy a cake until we calculate how many we need
    fullSheets = children / 50;        // Each full sheet feeds 50 children
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
    /* #endregion */
}
/* #endregion */

// -------------------------------- Utility Functions ---------------------------------

/* #region Utility Functions */

// WelcomeMessage() Welcomes the user to the program with a custom art ASCII.
// Pre-condition: artName
// Post-condition: prints the artName to the console.
void WelcomeMessage(string artName) {
     /* #region [Utilities] Fold WelcomeMessage */
    string artFileName = "art/" + artName + ".txt"; // The file to read the art from
    // https://bit.ly/2Vjy5iq
    // Open art file and grab its contents
    ifstream artFile (artFileName.c_str());

    if(artFile.is_open())
    // Output ASCII art to the console
        cout << artFile.rdbuf() 
             << endl << endl;
    // Close the art file
    artFile.close();
    /* #endregion */
}

// GenerateReport() calculates the current party's items and costs and prints the report to the file determined by the user
// Precondition: fileName, currentPartyCost, numParties
// Postcondition: prints the report to the file determined by the user
void GenerateReport(string fileName, float& currentPartyCost, int& numParties){
    /* #region [Utilities] Fold Generate Report */
    string name;     // Birthday child's name, to be entered by user.
    int age;         // Birthday child's age, to be entered by user.
    int guests;      // Number of guests invited, to be entered by user.
    int numBalloons; // The number of balloons needed
    float balloonsCost; // The total cost of the balloons
    int numBags; // Number of gifts bags needed
    float giftBagsCost; // The total cost of gift bags
    int napkinPacks; // The number of napkin packs needed
    float napkinsCost; // Total cost of napkins
    int platePacks; // The number of plate packs needed
    float platesCost; // The total cost of plates
    int pizzas; // The number of pizzas needed
    float pizzaCost; // The total cost of pizza
    int juiceBoxPacks; // The number of juice box packs needed
    float juiceCost; // The tot cost of juice
    bool halfSheet; // Whether or not we need a half sheet cake
    int fullSheets; // The number of full sheet cakes needed
    float halfSheetCost = 0; // Cost of half sheet of cake
    float fullSheetCost = 0; // Cost of full sheet of cake

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
    CalcBalloons(age, guests, numBalloons, balloonsCost);
    // Calculate number and cost of gift bags
    CalcBags(guests, numBags, giftBagsCost);
    // Calculate number and cost of napkin packs
    CalcNapkins(children, napkinPacks, napkinsCost);
    // Calculate number and cost of plates
    CalcPlates(children, platePacks, platesCost);
    // Calculate number and cost of pizzas
    CalcPizzas(children, pizzas, pizzaCost);
    // Calculate number and cost of juice box packs
    CalcJuice(children, juiceBoxPacks, juiceCost);
    // Calculate number of full and half sheet cakes and cost for each
    CalcCake(children, halfSheet, fullSheets, halfSheetCost, fullSheetCost);
    // Calculate the total cost
    currentPartyCost = balloonsCost + giftBagsCost + napkinsCost + platesCost + pizzaCost + juiceCost + halfSheetCost + fullSheetCost;

    // -------------- Output --------------------

    // Print the results to the ofstream output file partyReport.out, located in the same directory as the program.
    PrintReport(age, guests, fullSheets, halfSheet, fileName, name, numBalloons, balloonsCost, numBags, giftBagsCost, napkinPacks, napkinsCost, platePacks, platesCost, pizzas, pizzaCost, juiceBoxPacks, juiceCost, halfSheetCost, fullSheetCost, currentPartyCost);

    numParties += 1;

    /* #endregion */
}

// PrintReport() prints the report generated by the program to the ofstream output file partyReport.out, located in the same directory as the program.
// Precondition: guests fileName, name, numBalloons, balloonsCost, numBags, giftBagsCost, napkinPacks, napkinsCost, platePacks, platesCost, pizzas, pizzaCost, juiceBoxPacks, juiceCost, cakeCost, currentPartyCost
// Postcondition: prints the result to the output file partyReport.out
void PrintReport(int age, int guests, int fullSheets, bool halfSheet, string fileName, string name, int numBalloons, float balloonsCost, int numBags, float giftBagsCost, int napkinPacks, float napkinsCost, int platePacks, float platesCost, int pizzas, float pizzaCost, int juiceBoxPacks, float juiceCost, float halfSheetCost, float fullSheetCost, float currentPartyCost) {
    /* #region [Utilities] Fold PrintReport */
    // Open an output filestream
    ofstream partyReport;
    // Open a report file using the ofstream with the file name previously provided by user
    partyReport.open(fileName.c_str(), ios::app);
    // Format floats to two decimal places
    partyReport << fixed << showpoint << setprecision(2);

    partyReport << endl << endl;
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
        partyReport << "  Cake - half sheet:      1     $    " << halfSheetCost << endl;
    }
    partyReport << "         Total cost:            $ " << setw(8) << currentPartyCost << endl << endl << endl;
    partyReport << string(44, '*') << endl;

    // Close the report file
    partyReport.close();
    /* #endregion */
}


// PrintSummary() calculates and prints the summary of parties calculated by the program to the output file and console
// Precondition: fileName, numParties, partiesTotalCost
// Postcondition: prints the summary of parties calculated by the program to the output file and console
void PrintSummary(string fileName, int numParties, float partiesTotalCost) {
     /* #region [Utilities] Fold PrintSummary */
    float partyAverage = partiesTotalCost / numParties;

      // Open an output filestream
    ofstream partyReport;
    // Open a report file using the ofstream with the file name previously provided by user
    // partyReport.open(fileName, ios::app);

    partyReport.open(fileName.c_str(), ios::app);

    partyReport << fixed << showpoint << setprecision(2);

    partyReport << endl << endl;
    partyReport << "Number of parties:                " << setw(8) << numParties << endl;
    partyReport << "Total cost of all parties:      $ " << setw(8) << partiesTotalCost << endl;
    partyReport << "Average spent on each party:    $ " << setw(8) << partyAverage << endl << endl;
    partyReport << string(44, '*') << endl;
    partyReport << string(44, '*') << endl << endl;

    // Close the filestream
    partyReport.close();

    // Print the above to the console
    cout << fixed << showpoint << setprecision(2);

    cout << string(44, '*') << endl << endl  << endl;
    cout << "Number of parties:                " << setw(8) << numParties << endl;
    cout << "Total cost of all parties:      $ " << setw(8) << partiesTotalCost << endl;
    cout << "Average spent on each party:    $ " << setw(8) << partyAverage << endl << endl;
    cout << string(44, '*') << endl;
    cout << string(44, '*') << endl << endl;
    /* #endregion */
}


// ExitMessage() prints an exit message to the console
// Precondition: adj
// Postcondition: prints an exit message to the console
void ExitMessage(string adj) {
     /* #region [Utilities] Fold ExitMessage */
    // Get system time: http://www.cplusplus.com/reference/ctime/strftime/
    time_t rawtime;
    struct tm * timeinfo;
    char hour [80], day [80];

    time (&rawtime);
    timeinfo = localtime (&rawtime);

    strftime(hour,80,"%H", timeinfo); // the current hour in 24H format
    strftime(day,80,"%A", timeinfo); // the current day of the week, full name

    // Convert string to integer: http://www.cplusplus.com/forum/articles/9645/
    int intHour; // int to cast to hour to
    std::stringstream convert(hour); // stringstream used for the conversion initialized with the contents of wholeHour

    if ( !(convert >> intHour) ) // give the value to intHour using the characters in the string
        intHour = 0; // If that fails set intHour to 0

    int timeOfDay; // value to keep track of what period of the day it us: morning, afternoon, and evening

    if ( intHour <= 10 )
        timeOfDay = 0; // 12AM - 10AM: Morning
    else if ( intHour > 10 && intHour <= 16 )
        timeOfDay = 1; // 11PM - 4PM: Afternoon
    else
        timeOfDay = 2; // 5PM-11PM: Evening

    cout << "             Thanks for using              " << endl;
    cout << "            The Birthday Party             " << endl;
    cout << "           Cost Calculator v.3.1           " << endl;

    switch (timeOfDay) {
        case 0: cout << "      Have a " << adj << " " << day << " morning!" << endl;
                break;
        case 1: cout << "     Have a " << adj << " " << day << " afternoon!" << endl;
                break;
        case 2: cout << "      Have a " << adj << " " << day << " evening!" << endl;
                break;
    } // switch (timeOfDat)

    cout << endl << string(44, '*') << endl << endl;
    /* #endregion */
}
/* #endregion */