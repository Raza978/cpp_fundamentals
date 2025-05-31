#include <iostream> //use <> to include c library files
//#include "test.h" //use "" to include project files

//using namespace std; //avoid doing this. std contains many libraries and this might cause a conflict.
//instead do "using std::" to make it easier to type out some of the std libraries
//"using" also makes it harder to understand where things are defined.
using std::cout;
using std::endl;

namespace first {   //namespaces are used if you want to reuse the same variable names inside a different context to avoid naming conflicts.
    int x = 1;
}

namespace second {
    int x = 2;
}

namespace {         //anonyomous namespaces are namspaces without names and can only be referenced in the file they're defined.
    int test = 5;
}

class Person {
    public:
        //default constructor. Allows you to create an object without any input parameters. Ex. Person person;
        //constructors have no return type
        Person() = default;

        //overiding the default constructor. This allows you to set the first and last names.
        Person(std::string first, std::string last): mFirst(first), mLast(last) {}

        /* another way of setting parameters from the constructor
        Person(std::string first, std::string last) {
            mFirst = first;
            this->mLast = last;
        }
        */

        //any class with virtual functions and will be inherited by another class must use a virtual destructor.
        //Otherwise you will get undefined behavior when deallocating objects.
        virtual ~Person() {}

        //encapsulation: guarding how members of a class can be accessed. In this case first and last name can only be changed/viewed by the setter and getter functions.
        void setFirstName(std::string first) {mFirst = first;}
        void setLastName(std::string last) {mLast = last;}
        //"this" should only be used to help identify the correct parameter when both parameters have the same name
        void setMiddleName(std::string middle) {this->middle = middle;}
        std::string GetName() {
            return mFirst + " " + mLast;
        }

        void PrintName() {
            cout << mFirst << " " << mLast << endl;
        }

        //virtual means a class inheriting this function can override this base class function.
        //virtual functions can not be static.
        virtual void PrintInfo() {
            cout << mFirst << " " << mLast << endl;
        }

    private:
        std::string middle;
    
    /*protected members can only be accessed inside of an inherited class. 
      Ex. Inside class Employee we can use inherited protected members from class Person,
      but objects (Employee e1) can't directly access the protected members.
    */
    protected:
        std::string mFirst;
        std::string mLast;
};

class Age {
    public:
        virtual ~Age() {}

        /*Pure virtual functions means that in the base class there is no implementation of this function. Only a definition.
        The implementation is located in the inherited class.
        The base class of a pure virtual function can not be turned into an object. Ex. Age age; -> error.
        Use Age *myAge = new Dog(); to create an object of type Age. This is useful to pass a generic type into functions.
        */
        virtual void PrintAge()=0;
};

class Dog : public Age {
    public:
        //Classes inheriting virtual functions don't need to declare their destructors as virtual.
        ~Dog() {}

        void PrintAge() override {
            cout << "Dog age = 23" << endl;
        }
};

//inheritance: inherit all public and protected members of the parent class Person and Age.
//Employee doesn't inherit the private members of class Person, but it can access the public getter/setter functions of class Person.
class Employee : public Person, Age {
    public:
        //use the constructor of Person to set firstName and lastName.
        Employee(std::string firstName, std::string lastName, std::string department): Person(firstName, lastName), mDepartment(department) {}

        ~Employee() {}

        std::string GetDepartment() {
            return mDepartment;
        }

        //polymorphism: function overloading. This occurs when the program is being compiled.
        void PrintDepartment() {
            cout << mDepartment << endl;
        }
        void PrintDepartment(std::string department) {
            cout << department << endl;
        }

        //override means to override the inherited virtual base function from class Person.
        //polymorphism. function override. This occurs at runtime.
        void PrintInfo() override {
            //Employee can acces mFirst and mLast because Employee inherited these protected members from Person.
            cout << mFirst << " " << mLast << " " << mDepartment << endl;
        }

        //implementation of the pure virtual function
        void PrintAge() override {
            cout << "Age = 21" << endl;
        }

    private:
        std::string mDepartment;
};

int main()
{
    cout << "Hello world! " << first::x << endl; //endl will print a newline

    Person person1;
    person1.setFirstName("Muhammad");
    person1.setLastName("Raza");
    person1.PrintName();

    Person *person2 = new Person("John", "Doe");    //new: allocates memory and always needs to be manually deleted
    person2->PrintName();
    delete person2;

    Person person3("Mary", "Jane");
    person3.PrintInfo();

    Employee employee1("Muhammad", "Raza", "Residental");
    employee1.PrintInfo();
    employee1.PrintAge();

    //use child class Dog to create an object of type Age
    Age *myAge = new Dog();
    myAge->PrintAge();
    delete myAge;

    /*TO DO:
        c++ static
        review and check examples of encapsulation, polymorphism, inheritance, abstraction
        c++ smart pointers
        c++ strings
        c++ RAII
    */

    return 0;
}