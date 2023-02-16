#include <iostream>

using namespace std;

class DProcess{
    private:
        int m_PID;
        int m_page_index_start;
    
    public:
        DProcess(int PID, int hash_index, int page_size);
        int getPID();
        int getPhysicalIndex(int ADDR);
};

class DoubleHashTable{
    private:
        int *m_p_memory_array;
        DProcess **m_p_process_array;
        int m_page_size;
        int m_hash_size;
        int hashingFunc(int PID, int iter_index);

    public:
        DoubleHashTable();
        void createMemoryArray(int memory_size, int page_size);
        void search(int PID);
        void insert(int PID);
        int getHashIndex(int PID);
        void write(int PID, int ADDR, int x);
        void read(int PID, int ADDR);
        void deleteProcess(int PID);
        ~DoubleHashTable();
};