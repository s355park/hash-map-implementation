#include <iostream>
using namespace std;
#include "doubleHashTable.cpp"
#include "chainHashTable.cpp"

int main () {
    string cmd  = "";
    int PID = 0;
    int startAddress = 0;
    int N;
    int P;
    int ADDR;
    int x;
    int m;
    
    string which;
    cin>>which;
    if(which=="OPEN"){
        DoubleHashTable* doubleHashTable=new DoubleHashTable;
        while ( cin >> cmd )
        {
        if ( cmd == "M")
        {
            cin >> N >> P;
            doubleHashTable->createMemoryArray(N, P);
        }
        else if ( cmd == "INSERT")
        {
            cin >> PID;
            doubleHashTable -> insert(PID);
        }
        else if ( cmd == "SEARCH")
        {
            cin >> PID;
            doubleHashTable -> search(PID);
        }
        else if ( cmd == "WRITE")
        {
            cin >> PID >> ADDR >> x;
            doubleHashTable -> write(PID,ADDR,x);
        }
        else if ( cmd == "READ")
        {
            cin >> PID >> ADDR;
            doubleHashTable -> read(PID,ADDR);
        }
        else if ( cmd == "DELETE")
        {
            cin >> PID;
            doubleHashTable -> deleteProcess(PID);
        }
        else if ( cmd == "PRINT")
        {
            cin >> m;
        }
        else
        {
            delete doubleHashTable;
            break;
        }
    }

    }
    else{
        ChainHashTable* chainHashTable=new ChainHashTable;
        while ( cin >> cmd )
    {
        
        if ( cmd == "M")
        {
            cin >> N >> P;
            chainHashTable->createMemoryArray(N, P);
        }
        else if ( cmd == "INSERT")
        {
            cin >> PID;
            chainHashTable -> insert(PID);
        }
        else if ( cmd == "SEARCH")
        {
            cin >> PID;
            chainHashTable -> search(PID);
        }
        else if ( cmd == "WRITE")
        {
            cin >> PID >> ADDR >> x;
            chainHashTable -> write(PID,ADDR,x);
        }
        else if ( cmd == "READ")
        {
            cin >> PID >> ADDR;
            chainHashTable -> read(PID,ADDR);
        }
        else if ( cmd == "DELETE")
        {
            cin >> PID;
            chainHashTable -> deleteProcess(PID);
        }
        else if ( cmd == "PRINT")
        {
            cin >> m;
            chainHashTable -> print(m);
        }
        else
        {
            delete chainHashTable;
            break;
        }
    }

    }
    
    
    return 0;
}