#include <iostream>
#include <vector>
#include <string>
#include "Client.h"
using namespace std;

int main() {
    vector<Client> clients;
    clients.push_back({"A101", "Ali", 500.0});
    cout << "تمت إضافة العميل: " << clients[0].Name << endl;
    return 0;
}