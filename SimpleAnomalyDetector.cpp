
#include "SimpleAnomalyDetector.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {
	// TODO Auto-generated constructor stub
}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
	// TODO Auto-generated destructor stub
}

Point** arrayPoints(float* x, float* y, int size) {
    Point** points = new Point*[size];
    for (int i=0; i < size; i++) {
        Point* point = new Point(x[i], y[i]);
        points[i] = point;
    }
    return points;
}
void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts){
    vector<string> namesOfFeatures = ts.countColumns();
    int size = ts.numOfRows();
    for (int i = 0; i < namesOfFeatures.size(); i++) {
        float m = 0.0;
        int c = -1;
        for (int j = i + 1;j < namesOfFeatures.size(); j++) {
            float* x = ts.dataOfFeatures(i);
            float* y = ts.dataOfFeatures(j);
            float p = pearson(x, y, size);
            if(p > m || (-1*p > m)) {
                m = p;
                c = j;
            }
        }
        correlatedFeatures correlated;
        correlated.feature1 = namesOfFeatures[i];
        correlated.feature2 = namesOfFeatures[c];
        correlated.corrlation = m;
        float* x = ts.dataOfFeatures(i);
        float* y = ts.dataOfFeatures(c);
        Point** arrayOfPoints = arrayPoints(x, y, size);
        correlated.lin_reg = linear_reg(arrayOfPoints, size);
        float* deviation = new float [size];
        for (int k=0;k< size;k++) {
            Point point(arrayOfPoints[k]->x, arrayOfPoints[k]->y);
            float d = dev(point, correlated.lin_reg);
            deviation[k] = d*1.1;
        }
        correlated.deviation = deviation;
        cf.push_back(correlated);
    }
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
	// TODO Auto-generated destructor stub
}

