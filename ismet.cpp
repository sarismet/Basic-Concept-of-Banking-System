#include <iostream>

#include <thread>

#include <chrono>

#include<vector>

#include<queue>

#include <mutex>

#include <utility>

#include <fstream>

#include <sstream>

#include <string>

#include <iterator>

#include <atomic>

using namespace std;

//I create a Class called CUstomer to store values read from file
class Customer {
        public:
                //we have 5 different values
        int Sleep_Time;
        int ATM_Number;
        string Bill_type;
        int Amount_to_pay;
        int order;
        public:
                //this is constructor
                Customer(int Sleep_Time, int ATM_Number, string Bill_type, int Amount_to_pay, int order);

};
Customer::Customer(int Sleep_Time, int ATM_Number, string Bill_type, int Amount_to_pay, int order) {
        this->Sleep_Time = Sleep_Time;
        this->ATM_Number = ATM_Number;
        this->Bill_type = Bill_type;
        this->Amount_to_pay = Amount_to_pay;
        this->order = order;
}

//I define a file that later on I open in main thread and write the customer accorging to their waking time one by one 
ofstream myfile;
//this atomic int variables dont need to be atomic it could be normal int since I used below mutex but it is cool.
atomic < int > total_electricity;
atomic < int > total_water;
atomic < int > total_gas;
atomic < int > total_cableTV;
atomic < int > total_telecommunication;
//this Customer pointors is to point the Customer who want to make operarion on a certain ATM
//for instance if a customer wants to use ATM1 then the pointer of ATM_1_s_customer would point his/her address space

Customer * ATM_X_s_customer[10];

//this is the total number of customer read from file.
atomic < int > NUMBER_OF_CUSTUMMERS;
//this "adding" mutex is to protect the order of Customer_Who_Finished. By using that no two Customer are pushed to Customer_Who_Finished
mutex adding;
// this ATMS mutexs are to lock and unlock each ATMS if a customer wants to use one of the ATMS then s/he lock the ATMS by using on of these mutex
mutex ATM1, ATM2, ATM3, ATM4, ATM5, ATM6, ATM7, ATM8, ATM9, ATM10;
//these are to make correct summation of the values of electricity, water ... however it is not needed actually since I define them atomic but I used anyway
mutex electricity, water, gas, telecommunication, cableTV;
//this part is to divide the line we read from file by using delimeter "," and store them in a vector just like the order in file
template < class Container >
        void split1(const std::string & str, Container & cont) {
                char delim = ',';
                std::size_t current, previous = 0;
                current = str.find(delim);
                while (current != std::string::npos) {
                        cont.push_back(str.substr(previous, current - previous));
                        previous = current + 1;
                        current = str.find(delim, previous);
                }
                cont.push_back(str.substr(previous, current - previous));
        }
//this is the thread we create the Customers as we read a line from the file
void Create_Custommer(string line, int Customer_index) {
        vector < string > words;
        split1(line, words);
        //        we create the customer here
        Customer * tempcustommer = new Customer(stoi(words[0]), stoi(words[1]), words[2], stoi(words[3]), Customer_index);
        //then we go to sleeep for a while
        std::this_thread::sleep_for(std::chrono::milliseconds(stoi(words[0])));
        //we define the the number of ATM so that everytime we need this number we dont call the fonstion again.
        int ATM_NUMBER_IS = stoi(words[1]);
        //then we compare the number with 1,2,3,... up to 10 to determine which ATMs is going to be lock and which pointer is going to be assinged.
        if (ATM_NUMBER_IS == 1) {
                ATM1.lock();
                ATM_X_s_customer[0] = & * tempcustommer;
        } else if (ATM_NUMBER_IS == 2) {
                ATM2.lock();
                ATM_X_s_customer[1] = & * tempcustommer;
        } else if (ATM_NUMBER_IS == 3) {
                ATM3.lock();
                ATM_X_s_customer[2] = & * tempcustommer;
        } else if (ATM_NUMBER_IS == 4) {
                ATM4.lock();
                ATM_X_s_customer[3] = & * tempcustommer;
        } else if (ATM_NUMBER_IS == 5) {
                ATM5.lock();
                ATM_X_s_customer[4] = & * tempcustommer;
        } else if (ATM_NUMBER_IS == 6) {
                ATM6.lock();
                ATM_X_s_customer[5] = & * tempcustommer;
        } else if (ATM_NUMBER_IS == 7) {
                ATM7.lock();
                ATM_X_s_customer[6] = & * tempcustommer;
        } else if (ATM_NUMBER_IS == 8) {
                ATM8.lock();
                ATM_X_s_customer[7] = & * tempcustommer;
        } else if (ATM_NUMBER_IS == 9) {
                ATM9.lock();
                ATM_X_s_customer[8] = & * tempcustommer;
        } else if (ATM_NUMBER_IS == 10) {
                ATM10.lock();
                ATM_X_s_customer[9] = & * tempcustommer;
        }

        //after all these steps The customer waits for certain ATM to finish the process
        //meanwhile s/he makes spinlock because Critical sections are short and we dont need to use block
        //every while loop we check if the certain pointer again points the nullptr when it does we go out the while and delete the customer object and unlock the ATM
        if (ATM_NUMBER_IS == 1) {
                while (ATM_X_s_customer[0] != nullptr);
                delete tempcustommer;
                ATM1.unlock();
        } else if (ATM_NUMBER_IS == 2) {
                while (ATM_X_s_customer[1] != nullptr);
                delete tempcustommer;
                ATM2.unlock();
        } else if (ATM_NUMBER_IS == 3) {
                while (ATM_X_s_customer[2] != nullptr);
                delete tempcustommer;
                ATM3.unlock();
        } else if (ATM_NUMBER_IS == 4) {
                while (ATM_X_s_customer[3] != nullptr);
                delete tempcustommer;
                ATM4.unlock();
        } else if (ATM_NUMBER_IS == 5) {
                while (ATM_X_s_customer[4] != nullptr);
                delete tempcustommer;
                ATM5.unlock();
        } else if (ATM_NUMBER_IS == 6) {
                while (ATM_X_s_customer[5] != nullptr);
                delete tempcustommer;
                ATM6.unlock();
        } else if (ATM_NUMBER_IS == 7) {
                while (ATM_X_s_customer[6] != nullptr);
                delete tempcustommer;
                ATM7.unlock();
        } else if (ATM_NUMBER_IS == 8) {
                while (ATM_X_s_customer[7] != nullptr);
                delete tempcustommer;
                ATM8.unlock();
        } else if (ATM_NUMBER_IS == 9) {
                while (ATM_X_s_customer[8] != nullptr);
                delete tempcustommer;
                ATM9.unlock();
        } else if (ATM_NUMBER_IS == 10) {
                while (ATM_X_s_customer[9] != nullptr);
                delete tempcustommer;
                ATM10.unlock();
        }

        //afterall the customer thread exits the system

}
//I personally could have written all these ATMS theads in a single therad but I chose to split them in separete parts,
//each ATM works the same so read just here to see how it is works
//first the ATM is going to look at the NUMBER_OF_CUSTUMMERS if it is bigger than 0 or not if it is bigger than we begin to works
// then we look at if the ATM has a job to do or not if the ATM's pointer points nullptr then it does not have but it points a address space of a CUstomer
//then it has, and ATM take the bill_type and Amount_to_pay and lock the related mutexses and make the summation opearation
//after we did the summation operation such as electricity,gas etc. we lock the adding mutex to keep the order or its queue and decrease the NUMBER_OF_CUSTUMMERS,
//and make the related pointer point nullptr so that the customer who gave the necassary information to the ATM can unlock the ATM in its thread
void * ATM_X(int atm_index) {

        while (NUMBER_OF_CUSTUMMERS > 0) {

                if (ATM_X_s_customer[atm_index] != nullptr) {

                        string bill_choise = ATM_X_s_customer[atm_index]->Bill_type;
                        int Amount = ATM_X_s_customer[atm_index]->Amount_to_pay;
                        if (bill_choise == "electricity") {
                                electricity.lock();
                                total_electricity += Amount;
                                electricity.unlock();
                        } else if (bill_choise == "gas") {
                                gas.lock();
                                total_gas += Amount;
                                gas.unlock();
                        } else if (bill_choise == "water") {
                                water.lock();
                                total_water += Amount;
                                water.unlock();
                        } else if (bill_choise == "telecommunication") {
                                telecommunication.lock();
                                total_telecommunication += Amount;
                                telecommunication.unlock();
                        } else if (bill_choise == "cableTV") {
                                cableTV.lock();
                                total_cableTV += Amount;
                                cableTV.unlock();
                        }
                        adding.lock();

                        myfile << "Customer" << ATM_X_s_customer[atm_index]->order << "," << ATM_X_s_customer[atm_index]->Amount_to_pay << "TL" << "," << ATM_X_s_customer[atm_index]->Bill_type << endl;

                        NUMBER_OF_CUSTUMMERS--;

                        adding.unlock();

                        ATM_X_s_customer[atm_index] = nullptr;
                }
        }

}

int main(int argc, char * argv[]) {
        //I accept and inputfile the argument size need to be 2 if it is not we return
        if (argc != 2) {
                cout << "Run the code with the following command: ./simulation [input_file]" << endl;
                return 1;
        }

        // first see the size of the char array and 

        int size = sizeof(argv[1]) / sizeof(char);
        //and take the chars one by one until the char "."
        string s = "";
        for (int i = 0; i < size; i++) {
                if (argv[1][i] == '.') break;
                s = s + argv[1][i];

        }
        //we define the name of output file here
        s = s + "_log.txt";

        //and open the file just to write
        myfile.open(s, ios::out);

        //I read the file here
        ifstream read(argv[1]);
        string line; //to store the line
        string temp; //take the first line
        getline(read, temp);
        //and convert it to integar
        NUMBER_OF_CUSTUMMERS = stoi(temp);
        //and store the customer value here since I decrease the NUMBER_OF_CUSTUMMERS I need to who the exact value
        int for_last = NUMBER_OF_CUSTUMMERS;
        //we define 10 ATMS threads
        thread ATMS[10];
        //I create 10 threads here
        for (int i = 0; i < 10; ++i) {
                ATM_X_s_customer[i] = nullptr;
                ATMS[i] = thread(ATM_X, i);

        }

        //I define as threads as NUMBER_OF_CUSTUMMERS
        thread threads[for_last];
        //and we define an index to determine the coming Customer numbers
        int index = 0;
        while (index < for_last) {
                getline(read, line);
                //each time I read a line I create a thread and give the thread the CUstomer index and line I read from file
                threads[index] = thread(Create_Custommer, line, (index + 1));
                index++;
        }
        //Afterall All ATMS and Customer threads join
        for (int i = 0; i < for_last; i++) {
                threads[i].join();
        }

        for (int i = 0; i < 10; i++) {
                ATMS[i].join();
        }
        //I open a file to write the report

        // I take to total payments that all customers made and append "TL" and write to file
        string cablo = to_string(total_cableTV) + "TL";
        string elec = to_string(total_electricity) + "TL";
        string dogalgas = to_string(total_gas) + "TL";
        string tel = to_string(total_telecommunication) + "TL";
        string waters = to_string(total_water) + "TL";
        myfile << "All payments are completed." << endl;
        myfile << "CableTV: " << cablo << endl;
        myfile << "Electricity: " << elec << endl;

        myfile << "Gas: " << dogalgas << endl;

        myfile << "Telecommunication: " << tel << endl;
        myfile << "Water: " << waters << endl;
        //and close the file
        myfile.close();
        return 0;

}