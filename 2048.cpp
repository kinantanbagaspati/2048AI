#include<bits/stdc++.h>
using namespace std;

const int boardSize = 4;
const int winTile = 2048;
int** board;
int strategy;

int** init(){
    int** b = new int*[boardSize];
    for(int i=0; i<boardSize; i++){
        b[i] = new int[boardSize];
        for(int j=0; j<boardSize; j++){
            b[i][j] = 0;
        }
    }
    return b;
}

void newTile(){
    int candidate[boardSize*boardSize], nbCandidate = 0;
    for(int i=0; i<boardSize*boardSize; i++){
        if(board[i/boardSize][i%boardSize] == 0){
            candidate[nbCandidate] = i;
            nbCandidate++;
        }
    }

    int chosen = candidate[rand()%nbCandidate];
    if(rand()%100<20){
        board[chosen/boardSize][chosen%boardSize] = 4;
    }else{
        board[chosen/boardSize][chosen%boardSize] = 2;
    }
}

void print(){
    for(int i=0; i<boardSize; i++){
        if(i>0){
            for(int j=0; j<boardSize*5-1; j++){cout << '-';}
        }cout << endl;
        for(int j=0; j<boardSize; j++){
            if(j>0){cout << '|';}
            int cpy = max(1,board[i][j]);
            while(cpy<1000){
                cout << ' ';
                cpy *= 10;
            }
            cout << board[i][j];
        }cout << endl;
    }
}

int gameState(int** b){
    int cnt = 0;
    for(int i=0; i<boardSize; i++){
        for(int j=0; j<boardSize; j++){
            if(b[i][j] == winTile){
                return 1;
            }
            if(b[i][j] == 0){
                cnt++;
            }
        }
    }
    if(cnt>0){
        return 0;
    }
    for(int i=0; i<boardSize-1; i++){
        for(int j=0; j<boardSize; j++){
            if(b[i][j] == b[i+1][j] || b[j][i] == b[j][i+1]){
                return 0;
            }
        }
    }
    return -1;
}

bool mv(char e, int** awal, int** akhir){
    int idx, j;
    bool isChanged = false;
    for(int i=0; i<boardSize; i++){
        //compacting zeros
        idx = 0;
        if(e == 'a'){
            for(j=0; j<boardSize; j++){
                if(awal[i][j]>0){
                    akhir[i][idx] = awal[i][j];
                    isChanged = isChanged||(idx!=j);
                    idx++;
                }
            }
            while(idx<boardSize){
                akhir[i][idx] = 0;
                idx++;
            }
        }else if(e == 'w'){
            for(j=0; j<boardSize; j++){
                if(awal[j][i]>0){
                    akhir[idx][i] = awal[j][i];
                    isChanged = isChanged||(idx!=j);
                    idx++;
                }
            }
            while(idx<boardSize){
                akhir[idx][i] = 0;
                idx++;
            }
        }else if(e == 'd'){
            for(j=0; j<boardSize; j++){
                if(awal[i][boardSize-1-j]>0){
                    akhir[i][boardSize-1-idx] = awal[i][boardSize-1-j];
                    isChanged = isChanged||(idx!=j);
                    idx++;
                }
            }
            while(idx<boardSize){
                akhir[i][boardSize-1-idx] = 0;
                idx++;
            }
        }else if(e == 's'){
            for(j=0; j<boardSize; j++){
                if(awal[boardSize-1-j][i]>0){
                    akhir[boardSize-1-idx][i] = awal[boardSize-1-j][i];
                    isChanged = isChanged||(idx!=j);
                    idx++;
                }
            }
            while(idx<boardSize){
                akhir[boardSize-1-idx][i] = 0;
                idx++;
            }
        }

        //fuse fusables
        idx = 0;
        if(e == 'a'){
            for(j=1; j<boardSize; j++){
                if(akhir[i][j] == akhir[i][j-1]){
                    akhir[i][idx] = 2*akhir[i][j];
                    isChanged = isChanged||(akhir[i][j]>0);
                    j++;
                }else{
                    akhir[i][idx] = akhir[i][j-1];
                }
                idx++;
            }
            if(j==boardSize){
                akhir[i][idx] = akhir[i][j-1];
                idx++;
            }

            while(idx<boardSize){
                akhir[i][idx] = 0;
                idx++;
            }
        }else if(e == 'w'){
            for(j=1; j<boardSize; j++){
                if(akhir[j][i] == akhir[j-1][i]){
                    akhir[idx][i] = 2*akhir[j][i];
                    isChanged = isChanged||(akhir[j][i]>0);
                    j++;
                }else{
                    akhir[idx][i] = akhir[j-1][i];
                }
                idx++;
            }
            if(j==boardSize){
                akhir[idx][i] = akhir[j-1][i];
                idx++;
            }
            while(idx<boardSize){
                akhir[idx][i] = 0;
                idx++;
            }
        }else if(e == 'd'){
            for(j=1; j<boardSize; j++){
                if(akhir[i][boardSize-1-j] == akhir[i][boardSize-j]){
                    akhir[i][boardSize-1-idx] = 2*akhir[i][boardSize-j];
                    isChanged = isChanged||(akhir[i][boardSize-j]>0);
                    j++;
                }else{
                    akhir[i][boardSize-1-idx] = akhir[i][boardSize-j];
                }
                idx++;
            }
            if(j==boardSize){
                akhir[i][boardSize-1-idx] = akhir[i][boardSize-j];
                idx++;
            }
            while(idx<boardSize){
                akhir[i][boardSize-1-idx] = 0;
                idx++;
            }
        }else if(e == 's'){
            for(j=1; j<boardSize; j++){
                if(akhir[boardSize-1-j][i] == akhir[boardSize-j][i]){
                    akhir[boardSize-1-idx][i] = 2*akhir[boardSize-j][i];
                    isChanged = isChanged||(akhir[boardSize-j][i]>0);
                    j++;
                }else{
                    akhir[boardSize-1-idx][i] = akhir[boardSize-j][i];
                }
                idx++;
            }
            if(j==boardSize){
                akhir[boardSize-1-idx][i] = akhir[boardSize-j][i];
                idx++;
            }
            while(idx<boardSize){
                akhir[boardSize-1-idx][i] = 0;
                idx++;
            }
        }
    }
    return isChanged;
}

long long boardVal(int** b){
    long long sum = 0;
    if(strategy == 1){
        long long cnt = 0;
        for(int i=0; i<boardSize; i++){
            for(int j=0; j<boardSize; j++){
                sum += (long long)b[i][j];
                cnt += (b[i][j]>0);
            }
        }
        return sum/cnt;
    }else if(strategy == 2){
        long long sorter[boardSize*boardSize];
        for(int i=0; i<boardSize; i++){
            for(int j=0; j<boardSize; j++){
                sorter[i*boardSize +j] = b[i][j];
            }
        }
        sort(sorter, sorter+(boardSize*boardSize));
        for(int i=0; i<boardSize*boardSize; i++){
            sum += (i+1)*sorter[i];
        }
        return sum;
    }else if(strategy == 3){
        for(int i=0; i<boardSize; i++){
            for(int j=0; j<boardSize; j++){
                if((boardSize-i)%2){
                    sum += (boardSize*i + j + 1)*(long long)b[i][j];
                }else{
                    sum += (boardSize*(i+1) - j)*(long long)b[i][j];
                }
            }
        }
        return sum;
    }else if(strategy == 4){
        for(int i=0; i<boardSize; i++){
            for(int j=0; j<boardSize; j++){
                if((boardSize-i)%2){
                    sum += (1<<(2*(boardSize*i+j)))*(long long)b[i][j];
                }else{
                    sum += (1<<(2*(boardSize*(i+1)-j-1)))*(long long)b[i][j];
                }
            }
        }
        return sum;
    }
    return 0;
}

const long long minVal = -1e18, maxVal=1e18;
char moves[4] = {'w','a','s','d'};

int** initCpy(int**awal){
    int** akhir = new int*[boardSize];
    for(int i=0; i<boardSize; i++){
        akhir[i] = new int[boardSize];
        for(int j=0; j<boardSize; j++){
            akhir[i][j] = awal[i][j];
        }
    }
    return akhir;
}

long long minimax(int** b, int depth, bool maximize){
    if(gameState(b)<0){
        return minVal;
    }else if(gameState(b)>0){
        return maxVal;
    }
    if(depth==0){
        return boardVal(b);
    }
    vector<int**> next;
    if(maximize){
        for(int i=0; i<4; i++){
            int** toAdd = init();
            if(mv(moves[i], b, toAdd)){
                next.push_back(toAdd);
            }
        }
        long long toReturn = minVal;
        for(int i=0; i<next.size(); i++){
            toReturn = max(toReturn, minimax(next[i], depth-1, false));
        }
        return toReturn;
    }else{
        for(int i=0; i<boardSize; i++){
            for(int j=0; j<boardSize; j++){
                if(b[i][j]==0){
                    int** toAdd1 = initCpy(b);
                    int** toAdd2 = initCpy(b);
                    toAdd1[i][j] = 2;
                    toAdd2[i][j] = 4;
                    next.push_back(toAdd1);
                    next.push_back(toAdd2);
                }
            }
        }
        long long toReturn = maxVal;
        for(int i=0; i<next.size(); i++){
            toReturn = min(toReturn, minimax(next[i], depth-1, true));
        }
        return toReturn;
    }
}

char comMove(int depth){
    int **next;
    char toReturn = 'w';
    long long val = minVal;
    for(int i=0; i<4; i++){
        next = init();
        if(mv(moves[i], board, next)){
            if(minimax(next, depth, false) > val){
                toReturn = moves[i];
            }

        }
    }
    return toReturn;
}

int main(){
    srand(time(NULL));
    cout << "Choose Algorithms:\n"
    << "0. Main Sendokir\n"
    << "1. Minimax with average utility function\n"
    << "2. Minimax with sorted utility function\n"
    << "3. Minimax with greedy weighted utility function\n"
    << "4. Minimax with greedy power weighted utility function\n"
    << endl;
    strategy = -1;
    while(strategy <0 || strategy>4){
        cout << "Your option: " << endl;
        cin >> strategy;
    }
    board = init();
    newTile();
    print();
    char e;
    while(gameState(board) == 0){
        if(strategy == 0){
            cout << "Your move (wasd): " << endl;
            cin >> e;
            while(!mv(e, board, board)){
                cout << "Gabisa jalan kesitu bro, jalan lagi: " << endl;
                cin >> e;
            };
        }else{
            system("pause");
            e = comMove(0);
            cout << "Move generated: " << e << endl;
            mv(e, board, board);
        }
        newTile();
        print();
    }
    if(gameState(board)<0){
        cout << "GAME OVER" << endl;
    }else{
        cout << "YOU WIN!" << endl;
    }

}
