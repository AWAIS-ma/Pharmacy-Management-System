#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

const int maxmed = 1000;

string medicinename[maxmed];
double medicineprice[maxmed];
int medicinequantity[maxmed];

int initialmed = 0;

void addMedicine();
void searchMedicine();
void editMedicine();
void generateBill();
void loadMedicines();
void updateStockFile();
void showAllMedicinesSorted();

int main() 
{
    int choice;
    
    loadMedicines();
    while (1) {
        cout << "\n\n\t\t\t*********************************\n";
        cout << "\t\t\t*\t\t\t\t*\n";
        cout << "\t\t\t*\tMEDIX PHARMAS\t\t*" << endl;
        cout << "\t\t\t*\t\t\t\t*\n";
        cout << "\t\t\t*********************************\n";
        cout << "\n\t\t--> Press '1' to Add Medicine.\n"; 
        cout << "\n\t\t--> Press '2' to Search Medicine.\n";
        cout << "\n\t\t--> Press '3' to Edit Medicine.\n";
        cout << "\n\t\t--> Press '4' to show the stock.\n";
        cout << "\n\t\t--> Press '5' to Generate Bill.\n";
        cout << "\n\t\t--> Press '6' to Exit." << endl;
        cout << "\n--> Enter your choice : ";
        cin >> choice;

        switch (choice) {
            case 1:
            	 system("cls");
                addMedicine();
                break;
            case 2:
            	 system("cls");
                searchMedicine();
                break;
            case 3:
            	 system("cls");
                editMedicine();
                break;
            case 4:
            	 system("cls");
                showAllMedicinesSorted();
                break;
            case 5:
            	 system("cls");
            	generateBill();
            	break;
            case 6:
                cout << "\n\n\t\t*********(THANKS FOR PURCHASING)***********" << endl;
                exit(0);
                break;
            default:
                system("cls");
                cout << "\n\t********('" << choice << "' is an Invalid choice. Please Try again.)********" << endl;
                cout << "\n______________________________________________________________________________" << endl;
                main();
        }
    }

    return 0;
}

void addMedicine() {
    system("cls");
    if (initialmed < maxmed) {
        string name;
        double price;
        int quantity;
        cout << "\n\t*********(Enter The Medicine You Want to Add to Inventory)************" << endl;
        cout << "\n\n\t\t--> Enter medicine name: ";
        cin >> name;
        cout << "\n\t\t--> Enter price (each tab/syp): ";
        cin >> price;
        cout << "\n\t\t--> Enter quantity (tab/syp): ";
        cin >> quantity;

        medicinename[initialmed] = name;
        medicineprice[initialmed] = price;
        medicinequantity[initialmed] = quantity;

        initialmed++;

        ofstream medFile("medicines.txt", ios::app);
        if (medFile.is_open()) {
            medFile << name << " " << price << " " << quantity << endl;
            medFile.close();
        }
        
        cout << "\n\t**********(Medicine added to inventory.)************" << endl;
        cout << "\n_________________________________________________________________\n";
        
    } else {
        cout << "\n\tWARNING::  Inventory is full. Cannot add more medicines." << endl;
        cout << "\n_________________________________________________________________\n";
    }
}

void searchMedicine() {
    system("cls");
    string searchName;
    cout << "\n\t\t*******(Search The Medicine)********\n" << endl;
    cout << "\t--> Enter medicine name: ";
    cin >> searchName;

    bool found = false;

    for (int i = 0; i < initialmed; i++) {
        if (medicinename[i] == searchName) {
            cout << "\n\t--> Medicine Found: " << medicinename[i] << endl;
            cout << "\n\n\t\t********(Details)*********\n";
            cout << "\n\t--> Price (each tab/syp): " << medicineprice[i] << endl;
            cout << "\n\t--> Quantity: " << medicinequantity[i] << endl;
            cout << "\n_________________________________________________________________\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\n\t\t*********(Medicine not found in inventory.)*********" << endl;
        cout << "\n_________________________________________________________________\n";
    }
}

void editMedicine() {
    system("cls");
    string editname;
    cout << "\n\t\t*********(Edit The Medicine)***********\n";
    cout << "\n\t--> Enter medicine name to edit: ";
    cin >> editname;

    bool found = false;

    for (int i = 0; i < initialmed; i++) {
        if (medicinename[i] == editname) {
            double newprice;
            int newquantity;

            cout << "\n\n\t--> Enter new price: ";
            cin >> newprice;
            cout << "\n\n\t--> Enter new quantity: ";
            cin >> newquantity;

            medicineprice[i] = newprice;
            medicinequantity[i] = newquantity;

            updateStockFile();

            cout << "\n\n\t\t*******(Medicine details updated.)********" << endl;
            cout << "\n_________________________________________________________________\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "*******(Medicine not found in inventory.)*******" << endl;
        cout << "\n_________________________________________________________________\n";
    }
}

void generateBill() {
    system("cls");
    string customername;
    double total = 0;
    cout << "\n\n\t\t*******(Generate a Bill for Customer)*******\n";

    cout << "\n\t--> Enter customer name: ";
    cin >> customername;

    const int maxItems = 1000; 
    string billNames[maxItems];
    double billPrices[maxItems];
    int billQuantities[maxItems];
    double billTotalPrices[maxItems];
    int itemCount = 0;

    while (true) {
        string medname;
        int quantity;

        cout << "\n\n--> Medicine name (Press 'n' to finish purchasing and print the bill): ";
        cin >> medname;

        if (medname == "n" || medname == "N") {
            break;
        }

        bool found = false;
        int medIndex = -1;
        double price = 0;

        for (int i = 0; i < initialmed; i++) {
            if (medicinename[i] == medname) {
                price = medicineprice[i];
                medIndex = i;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "\n\n\t\t*******(Medicine not found in inventory.)*******" << endl;
            continue;
        }

        cout << "\n\n\t--> Enter quantity: ";
        cin >> quantity;

        if (medicinequantity[medIndex] < quantity) {
            cout << "\n\t*** Not enough stock. Available quantity: " << medicinequantity[medIndex] << " ***" << endl;
            continue;
        }

        double totalPrice = price * quantity;
        total += totalPrice;
        medicinequantity[medIndex] -= quantity;

        if (itemCount < maxItems) {
            billNames[itemCount] = medname;
            billPrices[itemCount] = price;
            billQuantities[itemCount] = quantity;
            billTotalPrices[itemCount] = totalPrice;
            itemCount++;
        } else {
            cout << "\n\t*** Maximum number of items in the bill reached. ***" << endl;
            break;
        }
    }

    updateStockFile();

    cout << "\n\n\t\t\t*********************************\n";
    cout << "\t\t\t*\t\t\t\t*\n";
    cout << "\t\t\t*\t  MEDIX PHARMAS BILL\t*" << endl;
    cout << "\t\t\t*\t\t\t\t*\n";
    cout << "\t\t\t*********************************\n";
    cout << "\n\tCustomer: " << customername << "\n";
    cout << "\n\tMedicine\tPrice\tQuantity\tTotal\n";
    cout << "------------------------------------------------------\n";

    for (int i = 0; i < itemCount; i++) {
        cout << "\t" << setw(10) << billNames[i] << "\t" << billPrices[i] << "\t" << billQuantities[i] << "\t" << billTotalPrices[i] << endl;
    }

    cout << "------------------------------------------------------\n";
    cout << "\t\t\t\t\tNet Amount: " << total << endl;
    cout << "\t\t\t*******(Thanks for Coming)*******\n";
    cout << "\t\t\t*********************************\n";
    char m;
    
    do
    {
    	cout<<"go back to main menu(y or Y) : ";
	cin>>m;
	}while(m=='m');
	
}

void showAllMedicinesSorted() {
    
    vector<string> names(medicinename, medicinename + initialmed);
    vector<double> prices(medicineprice, medicineprice + initialmed);
    vector<int> quantities(medicinequantity, medicinequantity + initialmed);

    
    for (int i = 0; i < initialmed - 1; i++) {
        for (int j = 0; j < initialmed - i - 1; j++) {
            if (names[j] > names[j + 1]) {
                swap(names[j], names[j + 1]);
                swap(prices[j], prices[j + 1]);
                swap(quantities[j], quantities[j + 1]);
            }
        }
    }

    
    cout << "\n\n\t\t*********(CURRENT STOCK)*********\n";
    cout << "\n\tMedicine\tPrice\tQuantity\n";
    cout << "---------------------------------------------\n";
    for (int i = 0; i < initialmed; i++) {
        cout << "\t" << setw(10) << names[i] << "\t" << prices[i] << "\t" << quantities[i] << endl;
    }
    cout << "---------------------------------------------\n";
}

void loadMedicines() {
    ifstream medfile("medicines.txt");
    if (medfile.is_open()) {
        string name;
        double price;
        int quantity;
        while (medfile >> name >> price >> quantity) 
        {
            medicinename[initialmed] = name;
            medicineprice[initialmed] = price;
            medicinequantity[initialmed] = quantity;
            initialmed++;
        }
        medfile.close();
    }   
}

void updateStockFile() {
    ofstream medfile("medicines.txt", ios::out);
    if (medfile.is_open()) {
        for (int i = 0; i < initialmed; i++) {
            medfile << medicinename[i] << " " << medicineprice[i] << " " << medicinequantity[i] << endl;
        }
        medfile.close();
    }
}

