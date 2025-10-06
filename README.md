#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;
const string ClientsFileName = "Clients.txt";
enum enMainMenueOptions {eShow = 1, eAdd = 2, eDelete = 3, eUqdat = 4, eFind = 5, eExit = 6 };

short Raed_Number()
{
    int Number;
    cout << "Choose What do you want to do ? [ 1 to 6 ] ? ";
    cin >> Number;
    return Number;
}

string Read_ClinetAccountNumber()
{
    string AccountNumber = "";
    cout << "Please Enter Account Number ? ";
    getline(cin >> ws, AccountNumber);
    return AccountNumber;

}

struct stClient
{
    string AccountNumber;
    string pinCode;
    string Name;
    string Phone;
    double AccountBalance = 0;
    bool MarkForDelete = false;
};

vector <string> SPlit_String(string S1, string Delim)
{
    vector <string> vString;
    int pos = 0;
    string sWord;

    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // stors the word


        if (sWord != "")
        {

            vString.push_back(sWord);
        }

        S1.erase(0, pos + Delim.length());
    }

    if (S1 != "")
    {
        vString.push_back(S1); // it adds last word of the string .
    }


    return vString;
}

string ConvertRecordToLine(stClient Client, string Seperator = "#//#")
{
    string stClientRecord = "";

    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.pinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;
}

stClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{
    stClient Client;
    vector<string> vClientData;

    vClientData = SPlit_String(Line, Seperator);

    if (vClientData.size() < 5)
    {
        return Client;
    }

    Client.AccountNumber = vClientData[0];
    Client.pinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]); //cast string to double
    return Client;
}

void AddDataLineToFile(string fileName, string stDataLine)
{
    fstream MyFile;
    MyFile.open(fileName, ios::out | ios::app);

    if (MyFile.is_open())
    {
        MyFile << stDataLine << endl;

        MyFile.close();
    }
}

vector< stClient> LoadClientsDataFromFile(string fileName)
{
    vector< stClient> vClient;

    fstream MyFile;

    MyFile.open(fileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        stClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line);

            vClient.push_back(Client);
        }

        MyFile.close();
    }

    return vClient;
}

void Print_ClientRecord(stClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.pinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void Print_ClientsData(vector< stClient> & vClient)
{
    system("cls");
    vClient = LoadClientsDataFromFile(ClientsFileName);
    cout << "\n\t\t\t\t\tClient List (" << vClient.size() << ") Client(s) . ";
    cout << "\n--------------------------------------------------------------";
    cout << "------------------------------------------\n" << endl;

    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(10) << "pin Code  ";
    cout << "| " << left << setw(40) << "Name ";
    cout << "| " << left << setw(12) << "Phone ";
    cout << "| " << left << setw(12) << "Account Balance ";
    cout << "\n------------------------------------------------------";
    cout << "--------------------------------------------------\n" << endl;

    for (stClient Client : vClient)
    {
        Print_ClientRecord(Client);
        cout << endl;
    }
    cout << "\n-------------------------------------------------------";
    cout << "--------------------------------------------------\n" << endl;

    cout << " go back to Main Menue....";
    system("pause");
}

void Print_ClientCard(stClient Client)
{
    cout << "\nThe  Following are Client datails : \n";
    cout << "----------------------------------------------\n";
    cout << "\nAccount Number  : " << Client.AccountNumber;
    cout << "\npin Code        : " << Client.pinCode;
    cout << "\nName            : " << Client.Name;
    cout << "\nPhone           : " << Client.Phone;
    cout << "\nAccount Balance : " << Client.AccountBalance;
    cout << "\n----------------------------------------------\n";
    cout << endl;
}

stClient  ChangeClientRecord(string AccountNumber)
{
    stClient Client;
    Client.AccountNumber = AccountNumber;

    cout << "Enter pinCode ? ";
    getline(cin >> ws, Client.pinCode);

    cout << "Einter Name ? ";
    getline(cin, Client.Name);

    cout << "Enter  Phone ? ";
    getline(cin, Client.Phone);

    cout << "Enter  AccountBalance ? ";
    cin >> Client.AccountBalance;

    return  Client;
}

void  AddNewClient(string AccountNumber)
{
    stClient Client;

    Client = ChangeClientRecord(AccountNumber);
    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}

bool FindClient_ByAccountNumber(string AccountNumber, vector<stClient> vClients, stClient& Client)
{
    for (stClient C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

void AddClients(vector<stClient> & vClients)
{
    char AddMore = 'Y';
    stClient Client;
    string AccountNumber;

    do
    {
        system("cls");
        cout << "----------------------------------------------\n";
        cout << "\t\t Add New Clients Screen \n";
        cout << "----------------------------------------------\n";
        cout << "Adding New Client : \n";
        cout << endl;

        vClients = LoadClientsDataFromFile(ClientsFileName);

        cout << "Enter Account Number? ";
        getline(cin >> ws, AccountNumber);

        while (FindClient_ByAccountNumber(AccountNumber, vClients, Client))
        {
            cout << "\nClient With [" <<AccountNumber << "]already exists, Einter another Number ? ";
            getline(cin >> ws, AccountNumber);
        }

        AddNewClient(AccountNumber);

        cout << "\nClient Addeb Successfully , do you want to add more clients Y/N ? ";
        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');

}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<stClient>& vClients)
{
    for (stClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

vector< stClient> SaveClientsDataToFile(string fileName, vector<stClient> vClients)
{
    fstream MyFile;
    MyFile.open(fileName, ios::out); // overwrite

    string DataLine;

    if (MyFile.is_open())
    {

        for (stClient C : vClients)
        {

            if (C.MarkForDelete == false)
            {
                // we only write records that are not marked for delete.

                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
        }

        MyFile.close();
    }
    return vClients;
}

bool Delete_ClientByAccountNumber( vector<stClient>& vClients)
{
    stClient Client;
    char Answer = 'n';
    string AccountNumber;
    system("cls");

    cout << "----------------------------------------------\n";
    cout << "\t\t Delete Clients Screen \n";
    cout << "----------------------------------------------\n";
    AccountNumber = Read_ClinetAccountNumber();
    vClients = LoadClientsDataFromFile(ClientsFileName);

    if (FindClient_ByAccountNumber(AccountNumber, vClients, Client))
    {
        Print_ClientCard(Client);

        cout << "\n\nAre you sure you want delete this Client ? y/n ? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveClientsDataToFile(ClientsFileName, vClients);

            vClients = LoadClientsDataFromFile(ClientsFileName);//Refresh Clients

            cout << "\n\nClient Deleted Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number ( " << AccountNumber << " ) Not found \n\n";
        system("pause");
        cout << " go back to Main Menue....";
        return false;
    }
}

bool  Update_ClientByAccountNumber( vector<stClient>& vClients)
{
    stClient Client;
    char Answer = 'n';
    string AccountNumber;

    system("cls");
    cout << "----------------------------------------------\n";
    cout << "\t\t Update Clients Info Screen \n";
    cout << "----------------------------------------------\n";

    AccountNumber = Read_ClinetAccountNumber();

    if (FindClient_ByAccountNumber(AccountNumber, vClients, Client))
    {
        Print_ClientCard(Client);

        cout << "\n\nAre you sure you want Update this Client ? y/n ?\n ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {

            for (stClient& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }

            SaveClientsDataToFile(ClientsFileName, vClients);

            cout << "\n\nClient Deleted Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number ( " << AccountNumber << " ) Not found \n\n";
        system("pause");
        cout << " go back to Main Menue....";
        return false;
    }
}

bool Find_Client(vector<stClient>& vClients)
{
    stClient Client;
    string AccountNumber;

    system("cls");
    cout << "----------------------------------------------\n";
    cout << "\t\t Find Clients Screen \n";
    cout << "----------------------------------------------\n";

    AccountNumber = Read_ClinetAccountNumber();
    vClients = LoadClientsDataFromFile(ClientsFileName);

    if (FindClient_ByAccountNumber(AccountNumber, vClients, Client))
    {

        Print_ClientCard(Client);
        system("pause");
        return true;
    }
    else
    {
        cout << "\nClient with Account Number ( " << AccountNumber << " ) Not found \n\n";
        cout << " go back to Main Menue...."<< system("pause");
        return false;
    }

}

void Exit_Client()
{
    system("cls");
    cout << "-------------------------------------------\n";
    cout << "\t\tProgram Ends :~)\n";
    cout << "-------------------------------------------\n";
}

void MainMenueScreen(short Number, vector< stClient> & vClient)
{
    switch (Number)
    {
    case enMainMenueOptions::eShow:
        Print_ClientsData(vClient);
        break;

    case enMainMenueOptions::eAdd:
        AddClients(vClient);
        break;

    case enMainMenueOptions::eDelete:
        Delete_ClientByAccountNumber( vClient);
        break;

    case enMainMenueOptions::eUqdat:
        Update_ClientByAccountNumber(vClient);
        break;

    case enMainMenueOptions::eFind:
        Find_Client(vClient);
        break;

    case enMainMenueOptions::eExit:
        Exit_Client();
        break;
    }
}

void ShowMainMenue()
{
    system("cls");
    cout << "============================================\n";
    cout << "\t\tMain Menue Screen \n";
    cout << "============================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Exit.\n";
    cout << "============================================\n";
}

void showEndScreen()
{
    vector< stClient> vClient;
    short Number = 0;

    do {

        ShowMainMenue();

        Number = Raed_Number();
        MainMenueScreen(Number, vClient);

    } while (Number != enMainMenueOptions::eExit);
}

int main()
{
    showEndScreen();
}
