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

using namespace std;

/* #region [Charcoal] Function Declarations */
void GenerateReport(string fileName, float COST_PER_GIFT_BAG, int NAPKINS_PER_PACK, int PLATES_PER_PACK, float COST_PER_PIZZA, int SLICES_PER_PIZZA, float COST_PER_JUICE_PACK, int JUICE_BOXES_PER_PACK, float COST_PER_FULL_SHEET, float COST_PER_HALF_SHEET);
string GetName();
int GetAge();
int GetGuests();
//float GetCakeCost();
string GetFileName();

float CalcBalloonsCost(int numBalloons);
float CalcNapkinsCost(int napkinPacks, int NAPKINS_PER_PACK);
float CalcPlatesCost(int platePacks, int PLATES_PER_PACK);

void PrintReport(int age, int guests, int fullSheets, bool halfSheet, string fileName, string name, int numBalloons, float balloonsCost, int numBags, float giftBagsCost, int napkinPacks, float napkinsCost, int platePacks, float platesCost, int pizzas, float pizzaCost, int juiceBoxPacks, float juiceCost, float halfSheetCost, float fullSheetCost, float total);
/* #endregion */

// ---------------------------------- Main Function -----------------------------------

int main() {
    /* #region Fold Main ⤵️ */ 
    /* #region [Grey] Declarations */ 
    float COST_PER_GIFT_BAG = 4.15;    // Cost per gift bag
    int NAPKINS_PER_PACK = 12;         // Number of napkins in a pack
    int PLATES_PER_PACK = 8;           // Plates per pack
    float COST_PER_PIZZA = 5.35;       // Cost per pizza
    int SLICES_PER_PIZZA = 12;         // Number of slices per pizza 🍕
    float COST_PER_JUICE_PACK = 4.25;  // Cost per juice pack
    int JUICE_BOXES_PER_PACK = 10;     // Number of juice boxes per pack
    float COST_PER_FULL_SHEET = 15.75; // Price of each sheet cake
    float COST_PER_HALF_SHEET = 10.00; // Price of half sheet cake
    /* #endregion */

    // Welcome the user
    cout << "Welcome to the Birthday Party Cost Calculator!" << endl
         << endl;

    string fileName = GetFileName();
    
    GenerateReport(fileName, COST_PER_GIFT_BAG, NAPKINS_PER_PACK, PLATES_PER_PACK, COST_PER_PIZZA, SLICES_PER_PIZZA, COST_PER_JUICE_PACK, JUICE_BOXES_PER_PACK, COST_PER_FULL_SHEET, COST_PER_HALF_SHEET);

   
    return 0;
/* #endregion Fold Main */
}

void GenerateReport(string fileName, float COST_PER_GIFT_BAG, int NAPKINS_PER_PACK, int PLATES_PER_PACK, float COST_PER_PIZZA, int SLICES_PER_PIZZA, float COST_PER_JUICE_PACK, int JUICE_BOXES_PER_PACK, float COST_PER_FULL_SHEET, float COST_PER_HALF_SHEET){
    string name;     // Birthday child's name, to be entered by user.
    int age;         // Birthday child's age, to be entered by user.
    int guests;      // Number of guests invited, to be entered by user.

    // Ask the user for the child's name
    name = GetName();
    // Get birthday child's age from the user
    age = GetAge();
    // Get the number of guests from the user
    guests = GetGuests();

    // Calculations

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
    else
    {
        halfSheet = true;
        halfSheetCost = COST_PER_HALF_SHEET;
    }

    fullSheetCost = fullSheets * COST_PER_FULL_SHEET; // Total cost of full sheet cakes

    // Calculate the total cost
    // We leave halfSheetCost and fullSheetCost as separate variables instead of combining them because they appear as line items in the report
    float total = balloonsCost + giftBagsCost + napkinsCost + platesCost + pizzaCost + juiceCost + halfSheetCost + fullSheetCost;

    // Output

    // Print the results to the ofstream output file partyReport.out, located in the same directory as the program.
    PrintReport(age, guests, fullSheets, halfSheet, fileName, name, numBalloons, balloonsCost, numBags, giftBagsCost, napkinPacks, napkinsCost, platePacks, platesCost, pizzas, pizzaCost, juiceBoxPacks, juiceCost, halfSheetCost, fullSheetCost, total);


}

// ------------------------------- User Input Functions -------------------------------

/* #region [Input] Input Function Definitions */
    
// GetName() gets the birthday child's name from user and returns it to main()
// Precondition: none
// Postcondition: returns name
string GetName() {
    string name;
    cout << "What is the birthday child's name? ";
    getline(cin, name);
    return name;
}

// GetAge() gets the age from user and returns it to main()
// Precondition: none
// Postcondition: returns age
int GetAge() {
    int age;
    cout << "How old will the birthday child be? ";
    cin >> age;
    cin.ignore(256, '\n');
    return age;
}

// GetGuests() gets the number of invited guests from user and returns it to main()
// Precondition: none
// Postcondition: returns guests
int GetGuests() {
    int guests;
    cout << "How many invited guests? ";
    cin >> guests;
    cin.ignore(256, '\n');
    return guests;
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

// GetFileName() gets the name of the output file from the user and returns it to main()
// Precondition: none
// Postcondition: returns fileName
string GetFileName() {
    string fileName;
    cout << "What would you like to name the report file? ";
    getline(cin, fileName);
    return fileName;
}
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
    partyReport << "           Balloons:  " << setw(4) << numBalloons << "   $ " << setw(7) << balloonsCost << endl;
    partyReport << "          Gift Bags:  " << setw(4) << numBags << "   $ " << setw(7) << giftBagsCost << endl;
    partyReport << "       Napkin Packs:  " << setw(4) << napkinPacks << "   $ " << setw(7) << napkinsCost << endl;
    partyReport << "        Plate Packs:  " << setw(4) << platePacks << "   $ " << setw(7) << platesCost << endl;
    partyReport << "             Pizzas:  " << setw(4) << pizzas << "   $ " << setw(7) << pizzaCost << endl;
    partyReport << "     Juicebox Packs:  " << setw(4) << juiceBoxPacks << "   $ " << setw(7) << juiceCost << endl;
    if (fullSheets)
    {
        partyReport << "  Cake - full sheet:    " << setw(2) << fullSheets << "   $ " << setw(7) << fullSheetCost << endl;
    }
    if (halfSheet)
    {
        partyReport << "  Cake - half sheet:     " << "1   $   " << halfSheetCost << endl;
    }

    partyReport << "         Total cost:         $ " << setw(7) << total << endl
                << endl;
    partyReport << string(40, '*') << endl;

    // Close the report file
    partyReport.close();
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
    