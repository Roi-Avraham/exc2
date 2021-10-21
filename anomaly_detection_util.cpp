/*
 * anomaly_detection_util.cpp
 *
 * Author: Shira Goren 207814989 with Roi Avraham 318778081
 */

#include <math.h>
#include <cstdlib>
#include <iostream>
#include "anomaly_detection_util.h"

//returns average
float avg(float* x, int size){
    float sum = 0.0;
    float m = 0.0;
    for(int i=0; i<size; i++) {
        sum += (x[i]);
    }
    m = (float (1)/float (size)) * sum;
    return m;
}

// returns the variance of X and Y
float var(float* x, int size){
    //initialize variables for sums and return value
    float squaredSum = 0.0;
    float expectedValue = 0.0;
    float inverseSize = (float (1) / float (size));
    float varReturn = 0.0;

    /*
     * this loop adds all floats from x
     * to create a sum and a squared sum.
     * */
    for(int i = 0; i < size; i++) {
        expectedValue += x[i];
        squaredSum += (x[i] * x[i]);
    }
    expectedValue = (inverseSize * expectedValue);
    expectedValue = expectedValue * expectedValue;
    varReturn = (inverseSize * squaredSum) - expectedValue;
    return varReturn;
}

// returns the covariance of X and Y
float cov(float* x, float* y, int size){
    float ex = avg(x, size);
    float ey = avg(y, size);
    float sum = 0.0;
    for(int i=0; i<size; i++) {
        sum += ((x[i] - ex) * (y[i] - ey));
    }
    float covariance = sum * (float (1)/float (size));
    return covariance;
}


// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size){
    float covariance = cov(x, y, size);
    float sigmaX = float (sqrt(double(var(x, size))));
    float sigmaY = float (sqrt(double(var(y, size))));
    float p = covariance / (sigmaX * sigmaY);
    return p;
}

// performs a linear regression and returns the line equation
Line linear_reg(Point** points, int size){

    float* x = new float[size];
    float* y = new float[size];
    float a = 0.0;
    float b = 0.0;

    /*
     * loop to create array with all x values
     * and array with all y values
     * */
    for(int i = 0;i< size; i++) {
        x[i] = points[i]->x;
        y[i] = points[i]->y;
    }
    a = cov(x, y, size) / var(x, size);
    float aveX = avg(x,size);
    float aveY = avg(y, size);
    b = aveY - (a * aveX);
    Line l = Line(a, b);
    return l;
}

// returns the deviation between point p and the line
float dev(Point p,Line l){
    float fX = l.f(p.x);
    float deviation = fX - p.y;
    if (deviation < 0) {
        deviation = (-1) * deviation;
    }
    return deviation;
}

// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size){
    Line line = linear_reg(points, size);
    float fX = line.f(p.x);
    float deviation = fX - p.y;
    if (deviation < 0) {
        deviation = (-1) * deviation;
    }
    return deviation;
}


