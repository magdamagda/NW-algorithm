#include "linearneedlemanwunsch.h"

linearNeedlemanWunsch::linearNeedlemanWunsch(vector<char> signs, int **matrix, int punish):
    similarityMatrix(matrix), punishment(punish)
{
    for(unsigned int i = 0; i<signs.size(); ++i){
        this->signsMap[signs.at(i)] = i;
    }
}

int linearNeedlemanWunsch::calculate(string seq1, string seq2){
    int H = seq1.size();
    int W = seq2.size();
    int* b = new int[H + 1];
    b[0]=0;
    for(int i=1; i<=H; i++)
        b[i]=i * this->punishment;

    for(int i=0; i<W; i++){
        int* f = new int[H+1];
        f[0] = (i+1)*this->punishment;
        for(int j=1; j<=H; j++){
            int x = b[j-1] + similarityMatrix[this->signsMap[seq1.at(j-1)]][this->signsMap[seq2.at(i)]];
            int y = b[j] + this->punishment;
            int z = f[j-1] + this->punishment;
            f[j]=getMax(x, y, z);
        }
        delete [] b;
        b=f;
    }
    return b[H];
}

int linearNeedlemanWunsch::getMax(int a, int b, int c){
    int max = ( a < b ) ? b : a;
    return ( ( max < c ) ? c : max );
}

vector<pair<int, int> > linearNeedlemanWunsch::findWaypoint(string seq1, string seq2, pair<int, int> begin){
    vector<pair<int, int> > result;
    int H = seq1.size();
    int W = seq2.size();
    if(W==1){
        result.push_back(begin);
        return result;
    }

    int* b = new int[H + 1];
    b[0]=0;
    for(int i=1; i<=H; i++)
        b[i]=i * this->punishment;

    int* num = new int[H+1];
    for(int i=0; i<H+1; i++)
        num[i]=i;

    if(W==2){
        result.push_back(begin);
        for(int i=1; i<H; i++){
            result.push_back(make_pair(begin.first+i, begin.second+1));
        }
        return result;
    }

    for(int i=0; i<=W/2; i++){
        int* f = new int[H+1];
        f[0] = (i+1)*this->punishment;
        for(int j=1; j<=H; j++){
            int x = b[j-1] + similarityMatrix[this->signsMap[seq1.at(j-1)]][this->signsMap[seq2.at(i)]];
            int y = b[j] + this->punishment;
            int z = f[j-1] + this->punishment;
            f[j]=getMax(x, y, z);
        }
        delete [] b;
        b=f;
    }
    for(int i=W/2+1; i<W; i++){
        int* f = new int[H+1];
        int* fnum = new int[H+1];
        fnum[0] = 0;
        f[0] = (i+1)*this->punishment;
        for(int j=1; j<=H; j++){
            int max = b[j-1] + similarityMatrix[this->signsMap[seq1.at(j-1)]][this->signsMap[seq2.at(i)]];
            fnum[j] = num[j-1];
            int y = b[j] + this->punishment;
            if(y>max){
                max=y;
                fnum[j] = num[j];
            }
            int z = f[j-1] + this->punishment;
            if(z>max){
                max=z;
                fnum[j] = fnum[j-1];
            }
            f[j]=max;
        }
        if(i!=W/2+1){
            delete [] b;
        }
        b=f;
        delete [] num;
        num=fnum;
    }
    pair<int, int> waypoint = make_pair(begin.first + num[H]-1, begin.second + W/2);
    result = findWaypoint(seq1.substr(0, num[H]), seq2.substr(0, W/2+1), begin);
    vector<pair<int, int> > after = findWaypoint(seq1.substr(num[H]-1, H-num[H]+1), seq2.substr(W/2, W-W/2+1), waypoint);
    //result.push_back(waypoint);
    result.insert(result.end(), after.begin() + 1, after.end());
    return result;
}

pair<string, string> linearNeedlemanWunsch::getBackwardPath(string seq1, string seq2){
    vector<pair<int, int> > path = findWaypoint(seq1, seq2, make_pair(0,0));
    string seq_fit_1="";
    string seq_fit_2="";

    for(auto item = path.begin(); item != path.end(); ++item){
        if(item!=path.begin() && item->first == (item-1)->first){
                seq_fit_1 += "_";
                seq_fit_2+=seq2.at(item->second);
        }
        else{
            if(item!=path.begin() && item->second == (item-1)->second){
                seq_fit_1+=seq1.at(item->first);
                seq_fit_2 += "_";
            }
            else{
                seq_fit_1+=seq1.at(item->first);
                seq_fit_2+=seq2.at(item->second);
            }
        }
    }

    return make_pair(seq_fit_1, seq_fit_2);
}
