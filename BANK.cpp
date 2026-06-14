//ms.X
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>
#include <iomanip>

using namespace std;

struct ClientInfo {

    string AccountNumber;
    string PinCode;
    string ClientName;
    string Phone;
    double Balance;

};

ClientInfo Read_Client_Info() {

    ClientInfo p;

    cout << "Enter client account number \n";
    cin >> p.AccountNumber;

    cout << "Enter pin code \n";
    cin >> p.PinCode;

    cin.ignore();
    cout << "Enter client name \n";
    getline(cin, p.ClientName);

    cout << "Enter phone number \n";
    cin >> p.Phone;

    cout << "Client balance \n";
    cin >> p.Balance;

    return p;

}
string collect_client_info_in_one_line(const ClientInfo& p) {

    string InfoLine = "";

    InfoLine += p.AccountNumber + "#//#";
    InfoLine += p.PinCode + "#//#";
    InfoLine += p.ClientName + "#//#";
    InfoLine += p.Phone + "#//#";
    InfoLine += to_string(p.Balance) + "#//#";

    return InfoLine;
}
void storage_client_info_in_file(const string& line) {

    fstream myfile;

    myfile.open("clientsinfo.txt", ios::app | ios::out);
    if (myfile.is_open()) {
        myfile << (line) << endl;
    }

    myfile.close();
}

void extract_client_row_data(vector<string>& client_data_line) {

    fstream myfile;
    myfile.open("clientsinfo.txt", ios::in);

    if (myfile.is_open()) {

        string line = "";

        while (getline(myfile, line)) {

            client_data_line.push_back(line);

        }
        myfile.close();
    }

}

void lode_person_info_in_vector(vector<string>& personinfo, vector<ClientInfo>& clients_final_info_after_process) {

    ClientInfo person;

    person.AccountNumber = personinfo.at(0);
    person.PinCode = personinfo.at(1);
    person.ClientName = personinfo.at(2);
    person.Phone = personinfo.at(3);
    person.Balance = stod(personinfo.at(4));

    clients_final_info_after_process.push_back(person);
}
void organizing_client_data(vector<string>& client_data_in_line, vector<ClientInfo>& clients_final_info_after_process) {

    int i = 1;
    do {

        vector<string> personinfo;
        string line = "";

        line = client_data_in_line.at(i - 1);

        for (int a = 0; a < 5; a++) {

            string info = "";
            size_t cutpoint = line.find("#//#");
            info = line.substr(0, cutpoint);
            personinfo.push_back(info);
            line = line.erase(0, cutpoint + 4);

        }

        lode_person_info_in_vector(personinfo, clients_final_info_after_process);

        i++;

    } while (client_data_in_line.size() >= i);


}
void manage_client_data_extraction(vector<ClientInfo>& clients_final_info_after_process)
{
    vector<string>client_data_in_line;
    extract_client_row_data(client_data_in_line);
    organizing_client_data(client_data_in_line, clients_final_info_after_process);

}

void show_one_client_info(ClientInfo client) {

    cout << "AccountNumber : " << client.AccountNumber << endl;
    cout << "PinCode : " << client.PinCode << endl;
    cout << "ClientName : " << client.ClientName << endl;
    cout << "Phone : " << client.Phone << endl;
    cout << "Balance : " << client.Balance << endl;
}
int select_option(int numberofoptions, int option) {

    do {

        cout << "Choose what do you want to do [ 1 to " + to_string(numberofoptions) + " ]" << endl;
        cin >> option;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            option = -1;
        }

    } while (option > numberofoptions || option < 1);

    return option;

}
int dashboard() {

    int i = 0;

    cout << string(60, '=') << endl;

    cout << string(20, ' ') + "Main Menu Screen" << endl;

    cout << string(60, '=') << endl;

    cout << string(8, ' ') + "[1] Show client list.\n";
    cout << string(8, ' ') + "[2] Add new client.\n";
    cout << string(8, ' ') + "[3] Delete client.\n";
    cout << string(8, ' ') + "[4] Update client info.\n";
    cout << string(8, ' ') + "[5] Find client.\n";
    cout << string(8, ' ') + "[6] transaction page.\n";
    cout << string(8, ' ') + "[7] Exit.\n";

    cout << string(60, '=') << endl;

    i = select_option(6, i);

    return i;

};
void show_client_list(vector<ClientInfo>& cleints_final_info_after_process) {

    cout << string(100, '=') << endl;
    cout << "=" + string(40, ' ') + "Client Number is : (" + to_string(cleints_final_info_after_process.size()) + ")" << string(36, ' ') + "=\n";
    cout << string(100, '=') << endl;
    cout << "=" << left << setw(18) << "  AccountNumber" << "=" << left << setw(18) << "  PinCode" << "=" << left << setw(20) << "  ClientName" << "=" << left << setw(19) << "  Phone" << "=" << left << setw(19) << "  Balance" << "=" << endl;
    cout << string(100, '=') << endl;

    for (ClientInfo& p : cleints_final_info_after_process) {
        cout << "=" << left << setw(18) << " " + p.AccountNumber << "=" << left << setw(18) << " " + p.PinCode << "=" << left << setw(20) << " " + p.ClientName << "=" << left << setw(19) << " " + p.Phone << "=" << left << setw(19) << " " + to_string(p.Balance) << "=" << endl;
        cout << string(100, '=') << endl;

    }
}

ClientInfo search_client_in_clients_data(string client_account_number) {

    vector<ClientInfo>clients_final_info_after_process;
    manage_client_data_extraction(clients_final_info_after_process);

    ClientInfo person;
    person.AccountNumber = "not found";

    for (ClientInfo& p : clients_final_info_after_process) {

        if (p.AccountNumber == client_account_number) {
            person = p;
            return person;
        }
    }

    return person;
}
void delete_client(string client) {

    ClientInfo client_data;
    client_data = search_client_in_clients_data(client);

    vector<ClientInfo>cleints_final_info_after_process;
    manage_client_data_extraction(cleints_final_info_after_process);

    if (client_data.AccountNumber == "not found") {
        cout << "Client not found !!!!" << endl;
    }
    else if (client_data.AccountNumber != "not found") {

        if (cleints_final_info_after_process.size() == 1 && cleints_final_info_after_process.at(0).AccountNumber == client_data.AccountNumber) {

            fstream myfile;
            myfile.open("clientsinfo.txt", ios::out);
            myfile.close();
            cout << "\n Client deleted successfully " << endl;
        }
        else if (cleints_final_info_after_process.size() > 1) {

            cout << endl << endl;
            show_one_client_info(client_data);
            cout << " \n\nDo you want to continue to delete this client? \n\n";
            system("pause");

            fstream myfile;
            myfile.open("clientsinfo.txt", ios::out);
            myfile.close();

            for (ClientInfo& p : cleints_final_info_after_process) {

                if (p.AccountNumber != client) {

                    fstream myfile;

                    myfile.open("clientsinfo.txt", ios::app);
                    if (myfile.is_open()) {

                        string s = collect_client_info_in_one_line(p);
                        myfile << s << endl;

                    }

                    myfile.close();
                }

            }
                cout << "\n Client deleted successfully " << endl;
        }
    }

}
void update_client_info(string client) {

    ClientInfo client_data;
    ClientInfo copy_client_data;

    client_data = search_client_in_clients_data(client);

    int options = 0;

    cout << endl;

    show_one_client_info(client_data);
    cout << "\n\n";
    cout << "What information you want to modify ? \n [1] PinCode . \n[2] Client Name . \n[3] Phone .\n[4] Balance \n";
    do {
        cin >> options;
    } while (options > 4 || options < 1);
    {
        copy_client_data.AccountNumber = client_data.AccountNumber;
        if (options == 1) {
            cout << "Enter pin code \n";
            cin >> copy_client_data.PinCode;
            copy_client_data.ClientName = client_data.ClientName;
            copy_client_data.Phone = client_data.Phone;
            copy_client_data.Balance = client_data.Balance;
        }

        else if (options == 2) {

            cin.ignore();
            cout << "Enter client name \n";
            getline(cin, copy_client_data.ClientName);

            copy_client_data.PinCode = client_data.PinCode;
            copy_client_data.Phone = client_data.Phone;
            copy_client_data.Balance = client_data.Balance;
        }
        else if (options == 3) {
            cout << "Enter phone number \n";
            cin >> copy_client_data.Phone;
            copy_client_data.ClientName = client_data.ClientName;
            copy_client_data.PinCode = client_data.PinCode;
            copy_client_data.Balance = client_data.Balance;
        }
        else if (options == 4) {
            cout << "Client balance \n";
            cin >> copy_client_data.Balance;
            copy_client_data.ClientName = client_data.ClientName;
            copy_client_data.Phone = client_data.Phone;
            copy_client_data.PinCode = client_data.PinCode;
        }
    }

    delete_client(client_data.AccountNumber);
    storage_client_info_in_file(collect_client_info_in_one_line(copy_client_data));

}

int transaction_dashboard(){

    int i = 0;

    cout << string(60, '=') << endl;

    cout << string(20, ' ') + "transaction Screen" << endl;

    cout << string(60, '=') << endl;

    cout << string(8, ' ') + "[1] Deposit.\n";
    cout << string(8, ' ') + "[2] Withdraw .\n";
    cout << string(8, ' ') + "[3] total balances .\n";
    cout << string(8, ' ') + "[4] main menue .\n";

    cout << string(60, '=') << endl;

    i = select_option(4, i);

    return i;

}
void update_client_balance(ClientInfo client, int new_balance, string type_of_transaction) {

    

    if (type_of_transaction == "Deposit") {

        client.Balance += new_balance;

        delete_client(client.AccountNumber);
        storage_client_info_in_file(collect_client_info_in_one_line(client));
       
            cout << "Done successfully" << endl;

    }
    else if (type_of_transaction == "Withdraw") {

        if (client.Balance >= new_balance) {

        client.Balance -= new_balance;
        delete_client(client.AccountNumber);
        storage_client_info_in_file(collect_client_info_in_one_line(client));

        }
        else if (client.Balance < new_balance) {

            cout << "Balance unavailable" << endl;

        }
    }

}
void show_clients_balances(vector<ClientInfo>& cleints_final_info_after_process) {

    cout << string(100, '=') << endl;
    cout << "=" + string(40, ' ') + "Client Number is : (" + to_string(cleints_final_info_after_process.size()) + ")" << string(36, ' ') + "=\n";
    cout << string(100, '=') << endl;
    cout << "=" << left << setw(18) << "  AccountNumber" << "=" << left << setw(20) << "  ClientName" << "=" << left << setw(19) << "  Balance" << "=" << endl;
    cout << string(100, '=') << endl;

    for (ClientInfo& p : cleints_final_info_after_process) {
        cout << "=" << left << setw(18) << " " + p.AccountNumber << "=" << left << setw(20) << " " + p.ClientName << "=" << left << setw(19) << " " + to_string(p.Balance) << "=" << endl;
        cout << string(100, '=') << endl;

    }
}

void function_call_regulation() {
    int page_number = 0;

    {
        vector<string>client_data_in_line;
        extract_client_row_data(client_data_in_line);
        if (client_data_in_line.empty()) {

            int page_num = 0;
            do {
                system("cls");
                cout << "Your client list is empty! Press option [2] to add clients!" << endl << endl;
                page_num = dashboard();

            } while (page_num != 2);

            system("cls");
            ClientInfo person;
            person = Read_Client_Info();
            storage_client_info_in_file(collect_client_info_in_one_line(person));
            cout << "Added successfully . press enter to back to dashboard \n";
            page_number = -1;
            system("pause");

        }

    }
    do {

        system("cls");
        page_number = dashboard();

        if (page_number == 1) {

            system("cls");

            vector<ClientInfo>cleints_final_info_after_process;
            manage_client_data_extraction(cleints_final_info_after_process);

            show_client_list(cleints_final_info_after_process);
            system("pause");

            page_number = -1;
        }
        else if (page_number == 2) {

            ClientInfo person_info;

            do {


                system("cls");
                person_info = Read_Client_Info();

                if (search_client_in_clients_data(person_info.AccountNumber).AccountNumber == person_info.AccountNumber) {

                    cout << "This account number is already used. Try again!\n";
                    system("pause");
                }

            } while (search_client_in_clients_data(person_info.AccountNumber).AccountNumber == person_info.AccountNumber);

            storage_client_info_in_file(collect_client_info_in_one_line(person_info));
            cout << "Added successfully . press enter to back to dashboard \n";
            page_number = -1;
            system("pause");
        }
        else if (page_number == 3) {

            system("cls");

            string client = "";
            cout << " - Enter client account number please :\n";
            cin >> client;

            delete_client(client);

            fstream myfile;
            myfile.open("clientsinfo.txt", ios::in);

            int filesize = 0;
            if (myfile.is_open()) {

                string lien;

                while (getline(myfile, lien)) {
                    filesize++;
                }

                myfile.close();
            }

            if (filesize == 0) {
                page_number = 2;
            }
            else if (filesize > 0) {
                page_number = -1;
            }
            system("pause");

        }
        else if (page_number == 4) {

            system("cls");

            string client = "";
            cout << " - Enter client account number please to update :\n";
            cin >> client;

            update_client_info(client);

            cout << "\n Client updating is successfully " << endl;

            page_number = -1;
            system("pause");

        }
        else if (page_number == 5) {

            system("cls");
            ClientInfo data;
            string cleintnumbercaount = "";
            cout << "enter client number account :\n";
            cin >> cleintnumbercaount;
            data = search_client_in_clients_data(cleintnumbercaount);
            if (data.AccountNumber == "not found") {

                cout << "cleint not found \n" << endl;
            }
            else if (data.AccountNumber != "not found") {

                system("cls");
                show_one_client_info(data);
            }


            cout << "\n press enter to back to main page \n";
            system("pause");
            page_number = -1;
        }
        else if (page_number == 6) {

            int page = 0;

            do {

                system("cls");
                page = transaction_dashboard();

                if (page == 1) {

                    system("cls");
                    string client_account = "";
                    ClientInfo client_data;

                    cout << "enter client account number" << endl;
                    cin >> client_account;

                    client_data = search_client_in_clients_data(client_account);

                    if (client_data.AccountNumber != "not found") {

                        cout << endl;
                        show_one_client_info(client_data);
                        double new_balance = 0;

                        cout << "\n enter new balance : ";
                        cin >> new_balance;

                        update_client_balance(client_data, new_balance, "Deposit");
                        cout << endl;
                        show_one_client_info(client_data);

                        system("pause");

                        page = -1;
                    }

                }
                else if (page == 2) {

                    system("cls");
                    string client_account = "";
                    ClientInfo client_data;

                    cout << "enter client account number" << endl;
                    cin >> client_account;

                    client_data = search_client_in_clients_data(client_account);

                    if (client_data.AccountNumber != "not found") {

                        cout << endl;
                        show_one_client_info(client_data);
                        double new_balance = 0;

                        cout << "\n enter new balance : ";
                        cin >> new_balance;

                        update_client_balance(client_data, new_balance, "Withdraw");
                        cout << endl;
                        show_one_client_info(client_data);

                    }
                    else if (client_data.AccountNumber == "not found") {
                        cout << "client not found \n";
                    }
                    system("pause");
                    page = -1;

                }
                else if (page == 3) {
                    system("cls");

                    vector<ClientInfo>clients_final_info_after_process;
                    manage_client_data_extraction(clients_final_info_after_process);
                    show_clients_balances(clients_final_info_after_process);

                    system("pause");
                    page = -1;
                }
                else if (page == 4) {
                    page = -1;
                }

            }while (page > 0);

            page_number = -1;
        }
        else if (page_number == 7) {
            page_number = 2;
        }


    }while (page_number < 1);

}


int main()
{

    function_call_regulation();
    system("cls");
    cout << "END" << endl;

}
