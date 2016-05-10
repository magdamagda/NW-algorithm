#ifndef LINEARNEEDLEMANWUNSCH_H
#define LINEARNEEDLEMANWUNSCH_H

#include<QString>
#include<iostream>
#include<map>
#include<vector>
#include<string>
#include<utility>

using namespace std;

class linearNeedlemanWunsch
{
public:
    linearNeedlemanWunsch(vector<char> signs, int **matrix, int punish = -5);
    int calculate(string seq1, string seq2);
    pair<string, string> getBackwardPath(string seq1, string seq2);


private:
    QString seq1;
    QString seq2;

    map<char, int> signsMap;
    int** similarityMatrix;
    int punishment;
    string best_fit_1;
    string best_fit_2;

    int getMax(int a, int b, int c);

    vector<pair<int, int> > findWaypoint(string seq1, string seq2, pair<int, int> begin, int startValue);
};

#endif // LINEARNEEDLEMANWUNSCH_H
