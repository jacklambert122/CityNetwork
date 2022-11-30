#pragma once

// Libraries / Namespaces
#include <string>
using namespace std;

/* ======================================================================
 * Struct name: city
 * Purpose: Struct to represent a city
========================================================================= */
struct city
{
    string  name;            // name of the city
    city *  next;            // pointer to the next city
    int     numberMessages;  // how many messages passed through this city
    string  message;         // message we are sending accross
};

/* ======================================================================
 * Namespace name: UserSelection
 * Purpose: enumerate case/switch in handleUserInput with a non-public scope
========================================================================= */
namespace UserSelection
{
    enum class Choice {
        rebuildNetwork  = 1,
        printPath       = 2,
        transmitMessage = 3,
        addCity         = 4,
        deleteCity      = 5,
        deleteNetwork   = 6,
        quit            = 7,
        _default        = 8
    };
};

/* ======================================================================
 * Class name: CityNetwork
 * Purpose: uses a linked list of city structs to store city routes and message counts. 
========================================================================= */
class CityNetwork {
private:
    // pointer to head of linked list of cities
    city* head;
public:
    /* ======================================================================
     * Purpose: Constructer for empty linked list
     * @param none
     * @return none
     * Do not modify.
    ========================================================================= */
    CityNetwork();

    /* ======================================================================
     * Purpose: Check if list is empty
     * @return true if empty; else false
     * Do not modify.
    ========================================================================= */
    bool isEmpty();

    /* ======================================================================
     * Purpose: Add a new city to the network
     *   between the city *previous and the city that follows it in the network.
     * @param previous name of the city that comes before the new city
     * @param cityName name of the new city
     * @return none
    ========================================================================= */
    void addCity(city* previous, string cityName);

    /* ======================================================================
     * Purpose: delete the city in the network with the specified name.
     * @param cityName name of the city to delete in the network
     * @return none
    ========================================================================= */
    void deleteCity(string cityName);

    /* ======================================================================
     * Purpose: populates the network with the predetermined cities
     * @param none
     * @return none
    ========================================================================= */
    void loadDefaultSetup();                       

    /* ======================================================================
     * Purpose: Search the network for the specified city and return a pointer to that node
     * @param cityName name of the city to look for in network
     * @return pointer to node of cityName, or NULL if not found
     * @see addCity, deleteCity
    ========================================================================= */
    city* searchNetwork(string cityName);          

    /* ======================================================================
     * Purpose: deletes all cities in the network starting at the head city.
     * @param none
     * @return none
    ========================================================================= */
    void deleteEntireNetwork();                    

    /* ======================================================================
     * Purpose: Transmit a message across the network to the
     *   receiver and increment count in each city it passes through
     * @param receiver name of the city to receive the message
     * @param message the message to send to the receiver
     * @return none
    ========================================================================= */
    void transmitMsg(string receiver, string msg); 

    /* ======================================================================
     * Purpose: prints the current list nicely
     * @param ptr head of list
    ========================================================================= */
    void printPath();                              
};

/***************************************************************/
/* User Interface Functionality                                */
/***************************************************************/
/* These functions implement the menu display and handle the   */
/*   user's menu selection by calling the appropriate          */
/*   CityNetwork methods.                                      */
/* These functions are complete, DO NOT MODIFY BELOW!          */
/***************************************************************/

/* ======================================================================
 * Purpose: handle the interaction with the user
 * @param CityNetwork to modify through menu actions
 * @return None
========================================================================= */
void displayMenu();

/* ======================================================================
 * Purpose: displays a menu with options
========================================================================= */
void handleUserInput(CityNetwork& cityNet);

/* ====================================================================== */
