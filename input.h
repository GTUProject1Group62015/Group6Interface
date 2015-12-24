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
#include "Coor.h"
#define PII 3.14159265

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
        rec = -1;
        fail = false;
    }

    Input(int xi, int yi, int di, int reci) {
        x = xi;
        y = yi;
        d = di;
        fail = false;
        rec = reci;

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
        fail = false;
        rec = 0;
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
    void setInput(string str) {
        vector<string> parsed = split(str, '_');
        if (parsed[0].size() > 0) {
            x = atoi(parsed[0].substr(parsed[0].find('.') + 1).c_str());
            y = atoi(parsed[1].substr(parsed[1].find('.') + 1).c_str());
            d = atoi(parsed[2].substr(0, parsed[2].find('.')).c_str());
            rec = atoi(parsed[3].c_str());
        } else if (parsed.size() > 3) {
            x = 0;
            y = 0;
            d = atoi(parsed[2].substr(0, parsed[2].find('.')).c_str());
            rec = atoi(parsed[3].c_str());
        } else {
            x = 0;
            y = 0;
            d = atoi(parsed[1].substr(0, parsed[1].find('.')).c_str());
            rec = atoi(parsed[2].c_str());
        }
    }

    /**
     * get x coordinate
     */
    int getCoorX() {
        return x;
    }
    /**
     * get y coor
     */
    int getCoorY() {
        return y;
    }

    /**
     * get angle
     */
    int getDegree() {
        return d;
    }

    /**
     * get area number
     */
    int getRect() {
        return rec;
    }

    //static Coor _gps_a = (55280, 41242);
    //static Coor _gps_b = Coor(56954, 40992);
    //static Coor _gps_c = Coor(56298, 39165);
    //static Coor _gps_d = (54942, 39386);

    //static Coor _pixel_a = (589, 200);
    //static Coor _pixel_b = Coor(641, 200);
    //static Coor _pixel_c = (641, 263);
    //static Coor _pixel_d = (589, 263);

#define _one_pixel_to_gps 30.81272932139917

    /**
     * @param x,y ->get gps coordinate
     * return coor
     */
    static Coor gpsCoorToPixel(int x, int y) {
        double gps_angle = calculateAngle(Coor(56954, 40992), Coor(56298, 39165))
                - calculateAngle(Coor(56954, 40992), Coor(x, y));
        double gps_distance = sqrt(
                pow(56954 - x, 2.0) + pow(40992 - y, 2.0));
        int pixel_distance = gps_distance / _one_pixel_to_gps;
        int new_x = sin(gps_angle * PII / 180.0) * pixel_distance;
        int new_y = cos(gps_angle * PII / 180.0) * pixel_distance;
        return Coor(641 + new_x, 200 + new_y);
    }

    static double calculateAngle(const Coor &c1, const Coor &c2) {
        double degree;
        double m;
        int x_dis = c1.x - c2.x;
        int y_dis = (c1.y - c2.y);
        if (x_dis == 0) {
            m = 0.0;
        } else if (y_dis == 0) {
            m = 1.0;
        } else {
            m = y_dis / x_dis;
        }
        degree = atan(m) * 180.0 / PII;
        if (y_dis < 0) {
            degree += 180;
        }
        return degree;
    }
};

#endif /* INPUT_H */
