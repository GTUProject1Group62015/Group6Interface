/*
 * Edge.h
 *
 *  Created on: 12 Kas 2015
 *      Author: Guner
 */

#ifndef INPUT_H_
#define INPUT_H_
#include <cmath>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;
class Input {
public:
    int x;
    int y;
    int d;
    bool fail;
    int rec;/* if zero,*/
    /*constructors*/
    Input() {
        x = -1;
        y = -1;
        d = -1;
        rec=-1;
        fail=false;
    }

    Input(int xi, int yi, int di) {
        x = xi;
        y = yi;
        d = di;
        fail=false;
    }

    Input(string parseString, int) {
        //double dereceDouble;
        int fractionPart, floatPart;
        string s1 = parseString.substr(parseString.find_first_of('.') + 1);
        string p1 = s1.substr(0, s1.find_first_of(','));
        s1 = s1.substr(s1.find_first_of('.') + 1);
        string p2 = s1.substr(0, s1.find_first_of(','));
        string p3 = s1.substr(s1.find_last_of(' ') + 1);

        string p4 = p3.substr(p3.find_first_of('.') + 1);
        floatPart = atoi(p4.c_str());
        x = atoi(p1.c_str());
        y = atoi(p2.c_str());
        //dereceDouble = atof(p3.c_str());
        d = atoi(p3.c_str());
        fail=false;
        rec=0;
        //control float part
        fractionPart = floatPart / 10;
        while (fractionPart != 0) {
            floatPart = fractionPart;
            fractionPart = floatPart / 10;
        }
        if (floatPart >= 5) {
            d += 1;
        }

        cerr << "coorX : " << x << endl << "coorY : " << y << endl
                << "Degree : " << d << endl;
    }



    /**
     * splinter sensei
     * @param str -> input string
     * @param delimiter -> delim char
     * @return parsed strings in vector<string>
     *
     */
    vector<string> split(string str, char delimiter) {

        vector<string> internal;

        stringstream ss(str); // Turn the string into a stream.
        string tok;

        while (getline(ss, tok, delimiter)) {
            internal.push_back(tok);
        }

        return internal;
    }

    /**
     * set input
     * @param str input string
     */
    void setInput(string str){
        vector<string> parsed=split(str,'_');
        if(parsed.size()>2)
        {
            x=atoi(parsed[0].substr(parsed[0].find('.')+1).c_str());
            y=atoi(parsed[1].substr(parsed[1].find('.')+1).c_str());
            d=atoi(parsed[2].substr(0,parsed[2].find('.')).c_str());
            rec=atoi(parsed[2].c_str());
        }
        else
        {
            x=0;
            y=0;
            d=atoi(parsed[1].substr(parsed[1].find('.')).c_str());
            rec=atoi(parsed[2].c_str());
        }
    }


    int getCoorX() {
        return x;
    }
    int getCoorY() {
        return y;
    }
    int getDegree() {
        return d;
    }
};

#endif /* INPUT_H */
