/*=====================================================*
 * Filename: Data Structures HW 3                      *
 * Description:                                        *
 * Author: Jack Lambert                                *
 * Date: 10/08/2018                                    *
 *=====================================================*/

/* ================================================================ */
#include "main.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;
/* ================================================================ */

int main(int argc, char* argv[])
{

    // Object representing our network of cities.
    // (Linked list representation is in CityNetwork)
    CityNetwork cityNet;

    // this will loop until user selects quit option
    handleUserInput(cityNet);

    // quit: clean up.
    cityNet.printPath();
    cityNet.deleteEntireNetwork();
    if (cityNet.isEmpty())
    {
        cout << "Path cleaned" << endl;
    }
    else
    {
        cout << "Error: Path NOT cleaned!" << endl;
        cityNet.printPath();
    }

    cout << "Goodbye!" << endl;
    return 0;
}
/* ================================================================ */


/***************************************************************/
/* CityNetwork Methods                                         */
/***************************************************************/

CityNetwork::CityNetwork() {
    head = NULL;
}
/* ================================================================ */

bool CityNetwork::isEmpty() {
    return (head == NULL);
}
/* ================================================================ */

void CityNetwork::addCity(city* previous, string cityName) {

    city* NewCity = new city;
    NewCity->next = NULL;
    NewCity->name = cityName;

    if (previous == NULL)
    {
        NewCity->next = head;
        head = NewCity;
        // if adding to front of list, instead print:
        cout << "adding: " << cityName << " (HEAD)" << endl;
    }
    else
    {
        NewCity->next = previous->next;
        previous->next = NewCity;
        cout << "adding: " << cityName << " (prev: " << previous->name << ")" << endl;
    }

}
/* ================================================================ */

void CityNetwork::deleteCity(string cityName)
{

    if(head->name == cityName)
    {
        head = head->next;
    }

    else
    {
        city* temp = head;
        city* prev = NULL;
        while(temp != NULL && temp->name != cityName)
        {
            prev = temp;
            temp = temp->next;
        }
        if(temp == NULL)
        {
            cout << "City does not exist." << endl;
        }
        else
        {
            prev->next = temp->next; //changes the previous next pointer to skip the deleted node
            free(temp);
        }

    }

}
/* ================================================================ */

void CityNetwork::loadDefaultSetup() {

    deleteEntireNetwork();
    addCity(NULL, "Los Angeles");
    addCity(head, "Phoenix");
    addCity(head->next, "Denver");
    addCity(head->next->next, "Dallas");
    addCity(head->next->next->next, "Atlanta");
    addCity(head->next->next->next->next, "New York");

}
/* ================================================================ */

city* CityNetwork::searchNetwork(string cityName) {

    city* tempC = head;
    while(tempC != NULL )
    {
        if ( tempC->name == cityName)
        {
            return tempC;
        }
        tempC = tempC->next;
    }
    return NULL;

}
/* ================================================================ */

void CityNetwork::deleteEntireNetwork() {
    // TODO: implement this function.
    if (head == NULL)
    {
        cout << "Deleted network" << endl;
    }
    else
    {
        city *ptr = head;
        city *NextP = NULL;
        while (ptr != NULL) {
            // required print statement:
            //   print the city name as it's deleted, e.g.,
            cout << "deleting: " << ptr->name << endl;
            NextP = ptr->next;
            free(ptr);
            ptr = NextP;

        }
        head = NULL;
        cout << "Deleted network" << endl;
    }
}
/* ================================================================ */

void CityNetwork::transmitMsg(string receiver, string message) {

    // if list is empty, print and return
    if(head == NULL)
    {
        cout << "Empty list" << endl;
        return;
    }
    else
    {
        city* sender = head;
        while (sender != NULL)
        {
            if( sender->name == receiver )
            {
                sender->message = message;
                sender->numberMessages++;
                cout << sender->name << " [# messages passed: " << sender->numberMessages << "] received: " << sender->message << endl;
                break;
            }
            else
            {
                sender->message = message;
                sender->numberMessages++;
                cout << sender->name << " [# messages passed: " << sender->numberMessages << "]" << endl;
            }
            sender = sender->next;
        }

    }

}
/* ================================================================ */

void CityNetwork::printPath() {
    
    cout << "== CURRENT PATH ==" << endl;

    city* ptr = head;
    while (ptr != NULL)
    {
        cout<< ptr->name << "->";
        ptr = ptr->next;
    }
    cout << " NULL" << endl;
    if (head == NULL)
    {
        cout << "nothing in path" << endl;
    }

    cout << "===" << endl;
}
/* ================================================================ */


/***************************************************************/
/* User Interface                                              */
/***************************************************************/

void handleUserInput(CityNetwork& cityNet)
{
    bool quit = false;
    string s_input;
    UserSelection::Choice input;

    // loop until the user quits
    while (!quit)
    {
        displayMenu();

        // read in input, assuming a number comes in
        getline(cin, s_input);
        try
        {
            input = static_cast<UserSelection::Choice>(stoi(s_input));
        }
        catch (exception& e)
        {
            // non-numeric input. trigger the default switch case.
            input = UserSelection::Choice::_default;
        }

        switch (input)
        {
            case UserSelection::Choice::rebuildNetwork:        
                cityNet.loadDefaultSetup();
                cityNet.printPath();
                break;

            case UserSelection::Choice::printPath:
                cityNet.printPath();
                break;

            case UserSelection::Choice::transmitMessage: 
            {
                string cityReceiver;
                cout << "Enter name of the city to receive the message: " << endl;
                getline(cin, cityReceiver);

                cout << "Enter the message to send: " << endl;
                string message;
                getline(cin, message);

                cityNet.transmitMsg(cityReceiver, message);
            }
                break;

            case UserSelection::Choice::addCity:
            {
                string newCityName;
                string prevCityName;

                cout << "Enter a new city name: " << endl;
                getline(cin, newCityName);

                cout << "Enter the previous city name (or First): " << endl;
                getline(cin, prevCityName);

                // find the node containing prevCity
                city *tmp = NULL;
                if(prevCityName != "First")
                {
                    tmp = cityNet.searchNetwork(prevCityName);
                }
                cityNet.addCity(tmp, newCityName);
                cityNet.printPath();
            }
                break;

            case UserSelection::Choice::deleteCity:
            {
                string city;
                cout << "Enter a city name: " << endl;
                getline(cin, city);
                cityNet.deleteCity(city);
                cityNet.printPath();
            }
                break;

            case UserSelection::Choice::deleteNetwork: 
                cityNet.deleteEntireNetwork();
                break;

            case UserSelection::Choice::quit:  
                quit = true;
                cout << "Quitting... cleaning up path: " << endl;
                break;
            
            default:  
                cout << "Invalid Input" << endl;
                break;
        }
    }
}
/* ================================================================ */

void displayMenu()
{
    cout << endl;
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build Network " << endl;
    cout << " 2. Print Network Path " << endl;
    cout << " 3. Transmit Message " << endl;
    cout << " 4. Add City " << endl;
    cout << " 5. Delete City " << endl;
    cout << " 6. Clear Network " << endl;
    cout << " 7. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
/* ================================================================ */