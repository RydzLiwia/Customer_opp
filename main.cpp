#include <cmath>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

using namespace std;

class Customer {
public:
  Customer(string name, string phone_number)
      : name_(name), phone_number_(phone_number) {}
  string getName() const { return name_; }
  string getPhoneNumber() const { return phone_number_; }

private:
  string name_;
  string phone_number_;
};

class CustomerTable {
public:
  void addCustomer(string name, string phone_number) {
    Customer customer(name, phone_number);
    customers_.push_back(customer);
  }

  void removeCustomer(string name) {
    for (auto it = customers_.begin(); it != customers_.end(); it++) {
      if (it->getName() == name) {
        customers_.erase(it);
        break;
      }
    }
  }

  void printTable() {
    cout << "Customer Table:\n";
    for (auto customer : customers_) {
      cout << customer.getName() << ", " << customer.getPhoneNumber() << "\n";
    }
  }

  void saveTableToFile(string file_name) {
    ofstream output_file(file_name);
    if (output_file.is_open()) {
      for (auto customer : customers_) {
        output_file << customer.getName() << "," << customer.getPhoneNumber()
                    << "\n";
      }
      output_file.close();
      cout << "Table saved to file.\n";
    } else {
      cout << "Unable to open output file.\n";
    }
  }

  void loadTableFromFile(string file_name) {
    ifstream input_file(file_name);
    if (input_file.is_open()) {
      customers_.clear();
      string line;
      while (getline(input_file, line)) {
        string name = line.substr(0, line.find(","));
        string phone_number = line.substr(line.find(",") + 1);
        addCustomer(name, phone_number);
      }
      input_file.close();
      cout << "Table loaded from file.\n";
    } else {
      cout << "Unable to open input file.\n";
    }
  }

private:
  vector<Customer> customers_;
};
bool validateName(string name) {
  regex name_regex("/[a-zA-Z]+/g");
  return regex_match(name, name_regex);
}
bool validatePhoneNumber(string phone_number) {
  regex phone_regex("/[0-9]/g");
  return regex_match(phone_number, phone_regex);
}

int main() {

  CustomerTable table;
  table.loadTableFromFile("customers.txt");
  string name, phone_number;
  while (true) {
    while (true) {
      cout << "Enter a customer name (or 'p' to print): ";
      cin >> name;
      if (bool validateName = 1) {
        break;
      }
    }
    if (name == "p") {
      break;
    }
    while (true) {
      cout << "Enter " << name << "'s phone number: ";
      cin >> phone_number;
      if (bool validatePhoneNumber = 1) {
        break;
      }
    }
    table.addCustomer(name, phone_number);
  }

  table.printTable();
  table.saveTableToFile("customers.txt");
  string remove_name;
  cout << "Enter a customer name to remove (or 'q' to print all customers): ";
  cin >> remove_name;
  if (remove_name != "p") {
    table.removeCustomer(remove_name);
    cout << "Customer " << remove_name << " removed.\n";
    table.printTable();
    table.saveTableToFile("customers.txt");
  }

  return 0;
}
