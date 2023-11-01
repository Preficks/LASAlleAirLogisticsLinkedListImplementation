
//
//  main.cpp
//  LLTemplate
//
//  Created by James Shockey on 12/6/16.
//  Copyright © 2016 James Shockey. All rights reserved.
//


/*
 *
 *	Linked List lab.
 *	- Build a library for singly linked list.
 *	- Replace the airport array in main with a Linked List.
 *  - sort the array. 
 *	
 */


#include <iostream>
#include <fstream>
#include <cmath> 
#include "slist.h"
#include <string>
#include <sstream>

using namespace std;

class Airport
{
public:
    char    code[5];
    double   longitude;
    double   latitude;
    
};

class Node
{
public: 
    Airport data;
    Node* next;
    Node(Airport d){
        this->data=d;
        this->next=NULL;
    }
};

class LinkedList
{
public: 
    Node* head; 

    LinkedList(){
        this->head=NULL;
    }
    void insert(Airport * data){
        Node * next = new Node(*data);
        if(head==NULL){
            head = next;
            return;
        }

        Node * temp = head;
        while(temp->next!=NULL){
            temp = temp->next;
        }

        temp->next = next;
    }
};

void simpleSortTotal(Airport* s[], int c);
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);
double distanceAus(double lat1d, double lon1d);

int main()
{
    ifstream infile;
    int i=0;
    char cNum[20];
    Airport* airportArr[22343];			// Replace array with Linked List
    int   airportCount;
    //Airport* a[13500];
    infile.open ("airport-codes_US.csv", ifstream::in);
    if (infile.is_open())
    {
        int c=0;
        while (infile.good())
        {
            char temp[999];
            airportArr[c] = new Airport();
            infile.getline(airportArr[c]->code, 256, ',');
            //cout << airportArr[c]->code;
            infile.getline(temp,256,',');
            infile.getline(temp,256,',');
            infile.getline(cNum,256,',');
            airportArr[c]->latitude = std::atof(cNum);
            infile.getline(cNum,256,',');
            airportArr[c]->longitude = std::atof(cNum);
            infile.getline(temp,256);
            //cout << airportArr[i]->code << " long: " << airportArr[i]->longitude << " lat: " << airportArr[i]->latitude <<  endl;
            i++;
            c++;
            
        }
        infile.close();

        //infile.getline(airportArr[1]->code, 256,',');
        Airport *xi = new Airport;
        LinkedList * all = new LinkedList();
        for(int i = 0; i < c; i++){
            all->insert(airportArr[i]);
        }
        Node * x;
        x= all->head;
        double d=0;
        double deltad=0;
        Airport te;
        for(int i=0;i<c;i++){
            //-97.66989899,30.19449997 reference point coordinates
            d = max(distanceAus(x->data.latitude,x->data.longitude),d);
            if(deltad!=d){
                te = x->data;
                deltad = d;
                cout << x->data.code << endl;
            }
            x=x->next;
        }
        cout << "Furthest Airport from the reference is: "<<te.code << endl;
        x= all->head;
        
        for(int i=0;i<c;i++){
           // cout<<" "<< distanceAus(x->data.latitude,x->data.longitude) <<endl;
            //-97.66989899,30.19449997 reference point coordinates
            if(distanceAus(x->data.latitude,x->data.longitude)<160.93){

                cout << x->data.code << ", ";
            }
           // cout <<distanceEarth(x->data.latitude,x->data.longitude,-97.66989899,30.19449997) << endl;
            x=x->next;
        }
        /*airportCount = c-1;
         for (int c=0; c < airportCount; c++)
            if (!(c % 1000))
            {
                cout << airportArr[c]->code << " long: " << airportArr[c]->longitude << " lat: " << airportArr[c]->latitude <<  endl;
                cout << airportArr[c+1]->code << " long: " << airportArr[c+1]->longitude << " lat: " << airportArr[c+1]->latitude <<  endl;
                cout <<"Distance between " << airportArr[c]->code << " and " << airportArr[c+1]->code << " is "
                  << distanceEarth( airportArr[c]->longitude, airportArr[c]->latitude , airportArr[c+1]->longitude, airportArr[c+1]->latitude) << endl;
            }
        */
    }
    else
    {
        cout << "Error opening file";
    }
}



#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

// This function converts decimal degrees to radians
double deg2rad(double deg) {
  return (deg * pi / 180);
}

//  This function converts radians to decimal degrees
double rad2deg(double rad) {
  return (rad * 180 / pi);
}


/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r)/2);
  v = sin((lon2r - lon1r)/2);
  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

double distanceAus(double lat1d, double lon1d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(-97.66989899);
  lon2r = deg2rad(30.19449997);
  u = sin((lat2r - lat1r)/2);
  v = sin((lon2r - lon1r)/2);
  return 2.0 * earthRadiusKm * (asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v)));
}

/*
	Provide sort routine on linked list
*/
/*
void simpleSortTotal()
{
}
*/
//-97.66989899,30.19449997
