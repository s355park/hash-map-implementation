#include <iostream>
using namespace std;


class CProcess{
    private:
    int m_PID;
    int m_page_index_start;
    CProcess *m_p_next;
    CProcess *m_p_prev;
    public:
    CProcess(int PID);
    int getPID();
    int getPhysicalIndex(int ADDR);
    void setNext(CProcess *next);
    int getPageIndexStart();
    void setPageindexStart(int page_index_start);
    void setPrev(CProcess *prev);
    CProcess* getNext();
    CProcess* getPrev();
};

class ChainHashTable{
    private:
        int *m_p_memory_array;
        CProcess **m_p_process_array;
        int m_page_size;
        int m_hash_size;
        int *m_p_process_page;

        int hashingFunc(int PID);
        bool checkPID(int PID);
        int getFreePage();
        CProcess* getProcess(int PID);
    public:
        void createMemoryArray(int memory_size, int page_size);
        void search(int PID);
        void insert(int PID);
        void write(int PID, int ADDR, int x);
        void read(int PID, int ADDR);
        void print(int m);
        void deleteProcess(int PID);
        ~ChainHashTable();
    
};