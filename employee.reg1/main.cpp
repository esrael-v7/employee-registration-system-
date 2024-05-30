#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Base class for Employee
class Employee {
protected:
    int id;
    string name;
    string email;
    string phone;

public:
    Employee(int id, const string& name, const string& email, const string& phone)
        : id(id), name(name), email(email), phone(phone) {}

    virtual ~Employee() = default;

    int getId() const { return id; }
    string getName() const { return name; }
    string getEmail() const { return email; }
    string getPhone() const { return phone; }

    void setName(const string& name) { this->name = name; }
    void setEmail(const string& email) { this->email = email; }
    void setPhone(const string& phone) { this->phone = phone; }

    virtual void displayDetails() const {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Email: " << email << endl;
        cout << "Phone: " << phone << endl;
    }

    virtual void updateDetails() {
        cout << "Enter new name: ";
        cin >> name;
        cout << "Enter new email: ";
        cin >> email;
        cout << "Enter new phone: ";
        cin >> phone;
    }
};

// Derived class for Address
class Address : public Employee {
protected:
    string street;
    string city;
    string state;
    string zipCode;

public:
    Address(int id, const string& name, const string& email, const string& phone,
            const string& street, const string& city, const string& state, const string& zipCode)
        : Employee(id, name, email, phone), street(street), city(city), state(state), zipCode(zipCode) {}

    string getStreet() const { return street; }
    string getCity() const { return city; }
    string getState() const { return state; }
    string getZipCode() const { return zipCode; }

    void setStreet(const string& street) { this->street = street; }
    void setCity(const string& city) { this->city = city; }
    void setState(const string& state) { this->state = state; }
    void setZipCode(const string& zipCode) { this->zipCode = zipCode; }

    void displayDetails() const override {
        Employee::displayDetails();
        cout << "Address: " << street << ", " << city << ", " << state << ", " << zipCode << endl;
    }

    void updateDetails() override {
        Employee::updateDetails();
        cout << "Enter new street: ";
        cin >> street;
        cout << "Enter new city: ";
        cin >> city;
        cout << "Enter new state: ";
        cin >> state;
        cout << "Enter new zip code: ";
        cin >> zipCode;
    }
};

// Derived class for Department
class Department : public Address {
protected:
    string deptName;
    string description;

public:
    Department(int id, const string& name, const string& email, const string& phone,
               const string& street, const string& city, const string& state, const string& zipCode,
               const string& deptName, const string& description)
        : Address(id, name, email, phone, street, city, state, zipCode), deptName(deptName), description(description) {}

    string getDeptName() const { return deptName; }
    string getDescription() const { return description; }

    void setDeptName(const string& deptName) { this->deptName = deptName; }
    void setDescription(const string& description) { this->description = description; }

    void displayDetails() const override {
        Address::displayDetails();
        cout << "Department: " << deptName << endl;
        cout << "Department Description: " << description << endl;
    }

    void updateDetails() override {
        Address::updateDetails();
        cout << "Enter new department name: ";
        cin >> deptName;
        cout << "Enter new department description: ";
        cin >> description;
    }
};

// Derived class for EmployeeManager
class EmployeeManager : public Department {
private:
    vector<Employee*> employees;

public:
    EmployeeManager()
        : Department(0, "", "", "", "", "", "", "", "", "") {}

    void addEmployee(Employee* employee) {
        employees.push_back(employee);
    }

    void removeEmployee(int id) {
        for (auto it = employees.begin(); it != employees.end(); ++it) {
            if ((*it)->getId() == id) {
                delete *it; // Deallocate memory for the removed employee
                employees.erase(it);
                break;
            }
        }
    }

    Employee* getEmployee(int id) {
        for (const auto& employee : employees) {
            if (employee->getId() == id) {
                return employee;
            }
        }
        return nullptr; // Employee not found
    }

    void updateEmployee(int id) {
        Employee* employee = getEmployee(id);
        if (employee != nullptr) {
            employee->updateDetails();
            cout << "Employee updated successfully!" << endl;
        } else {
            cout << "Employee not found." << endl;
        }
    }

    void displayAllEmployees() {
        cout << "Employee List:" << endl;
        for (const auto& employee : employees) {
            employee->displayDetails();
            cout << "------------------------" << endl;
        }
    }

    ~EmployeeManager() {
        // Deallocate memory for all employees
        for (auto& employee : employees) {
            delete employee;
        }
        employees.clear();
    }
};

// Class for Login
class Login {
public:
    bool authenticate(const string& username, const string& password) {
        // Dummy authentication logic
        return (username == "admin" && password == "password");
    }

    void displayLoginPage() {
        cout << "Welcome to the Employee Registration System!" << endl;
        cout << "Please log in to continue." << endl;
        cout << "Username: ";
    }

    void displayInvalidCredentialsMessage() {
        cout << "Invalid username or password. Please try again." << endl;
    }
};

// Function to add an employee
void addEmployee(EmployeeManager& manager) {
    // Prompt for employee details
    int id;
    string name, email, phone, street, city, state, zipCode, deptName, deptDesc;
    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter email: ";
    cin >> email;
    cout << "Enter phone: ";
    cin >> phone;
    cout << "Enter street: ";
    cin >> street;
    cout << "Enter city: ";
    cin >> city;
    cout << "Enter state: ";
    cin >> state;
    cout << "Enter zip code: ";
    cin >> zipCode;
    cout << "Enter department name: ";
    cin >> deptName;
    cout << "Enter department description: ";
    cin >> deptDesc;

    // Create employee
    Employee* employee = new Department(id, name, email, phone, street, city, state, zipCode, deptName, deptDesc);

    // Add employee to manager
    manager.addEmployee(employee);

    cout << "Employee added successfully!" << endl;
}

// Function to search for an employee
void searchEmployee(EmployeeManager& manager) {
    int id;
    cout << "Enter ID of employee to search: ";
    cin >> id;

    Employee* employee = manager.getEmployee(id);
    if (employee != nullptr) {
        cout << "Employee found:" << endl;
        employee->displayDetails();
    } else {
        cout << "Employee not found.\n"<<"Please Enter Registered ID and Try Again. \n"<< "Thank you!" << endl;
    }
}

// Function to display all employees
void displayEmployees(EmployeeManager& manager) {
    manager.displayAllEmployees();
}

// Function to delete an employee
void deleteEmployee(EmployeeManager& manager) {
    int id;
    cout << "Enter ID of employee to delete: ";
    cin >> id;

    manager.removeEmployee(id);
    cout << "Employee deleted successfully!" << endl;
}

// Main function
int main() {
    // Create an EmployeeManager object
    EmployeeManager manager;

    // Create a Login object
    Login login;

    string username, password;
    bool loggedIn = false;
    do {
        login.displayLoginPage();
        cin >> username;
        cout << "Password: ";
        cin >> password;

        loggedIn = login.authenticate(username, password);

        if (!loggedIn) {
            login.displayInvalidCredentialsMessage();
        }
    } while (!loggedIn);

    int choice;
    do {
        cout << "\nMain Menu" << endl;
        cout << "1. Add Employee" << endl;
        cout << "2. Search Employee" << endl;
        cout << "3. Update Employee" << endl;
        cout << "4. Display All Employees" << endl;
        cout << "5. Delete Employee" << endl;
        cout << "6. Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addEmployee(manager);
                break;
            case 2:
                searchEmployee(manager);
                break;
            case 3: {
                int id;
                cout << "Enter ID of employee to update: ";
                cin >> id;
                manager.updateEmployee(id);
                break;
            }
            case 4:
                displayEmployees(manager);
                break;
            case 5:
                deleteEmployee(manager);
                break;
            case 6:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice." << endl;
        }
    } while (choice != 6);

    return 0;
}
