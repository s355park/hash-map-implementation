#include <iostream>
#include <vector>
using namespace std;

class DProcess{
    private:
    int m_PID;
    int m_page_index_start;
    public:
    DProcess(int PID, int hash_index, int page_size){
        m_PID=PID;
        m_page_index_start=hash_index*page_size;
    }
    int getPID(){
        return this->m_PID;
    }

    int getPhysicalIndex(int ADDR){
        return m_page_index_start+ADDR;
    }
    //, int ADDR,
    //m_physical_index=m_page_index_start+ADDR;
};

class DoubleHashTable{
    private:
    int *m_p_memory_array;
    DProcess **m_p_process_array;
    int m_page_size;
    int m_hash_size;
    
    int hashingFunc(int PID, int iter_index){
        int hash2=(PID/m_hash_size)%m_hash_size;
        if(hash2%2==0){
            hash2+=1;
        }
        return (PID%m_hash_size+iter_index*hash2)%m_hash_size;
    }

    public:
      DoubleHashTable(){
        this->m_p_memory_array=nullptr;
      }  
      void createMemoryArray(int memory_size, int page_size){
        this->m_page_size=page_size;
        this->m_p_memory_array=new int[memory_size];
        this->m_p_process_array=new DProcess*[memory_size/page_size];
        this->m_hash_size=memory_size/page_size;
        for (int i=0;i<m_hash_size;i++){
            m_p_process_array[i]=nullptr;
        }
        cout<<"success"<<endl;
      }
        void search(int PID){
        int hash_index=this->getHashIndex(PID);
        if(hash_index>-1){
            cout<<"found "<<PID<<" in "<<hash_index<<endl;
        }
        else{
            cout<<"not found"<<endl;
        }
      }

      void insert(int PID){
        bool success=false;
        if(this->getHashIndex(PID)==-1){
            for(int i=0; i<m_hash_size; i++){
                int hash_index=hashingFunc(PID, i);
                if(m_p_process_array[hash_index]==nullptr){
                    m_p_process_array[hash_index]=new DProcess(PID, hash_index, m_page_size);
                    success=true;
                    break;
                }
            }
        }
        if(success){
            cout<<"success"<<endl;      
        }
        else{
            cout<<"failure"<<endl;
        }
      }
      int getHashIndex(int PID){
        int hash_index = 0;
        bool success=false;
        for(int i=0; i<m_hash_size; i++){
            hash_index=hashingFunc(PID, i);
            if(m_p_process_array[hash_index]!=nullptr){
                if(m_p_process_array[hash_index]->getPID()==PID){
                    success=true;
                    break;
                }
            }
        }
        if(success){
            return hash_index;
        }
        else{
            return -1;
        }
      }
    

    void write(int PID, int ADDR, int x){
        int hash_index=this->getHashIndex(PID);
        if((ADDR>=m_page_size)||(hash_index<0)){
            cout<<"failure"<<endl;
        }
        else{
            m_p_memory_array[m_p_process_array[hash_index]->getPhysicalIndex(ADDR)]=x;
            cout<<"success"<<endl;
        }
    }

    void read(int PID, int ADDR){
        int hash_index=getHashIndex(PID);
        if((hash_index>-1)&&(ADDR<m_page_size)){
            cout<<ADDR<<" "<<m_p_memory_array[m_p_process_array[hash_index]->getPhysicalIndex(ADDR)]<<endl;
        }
        else{
            cout<<"failure"<<endl;
        }
    }

    void deleteProcess(int PID){
        int hash_index=getHashIndex(PID);
        if(hash_index>-1){
            delete m_p_process_array[hash_index];
            m_p_process_array[hash_index]=nullptr;
            cout<<"success"<<endl;
        }
        else{
            cout<<"failure"<<endl;
        }
    }
    ~DoubleHashTable(){
        for(int i=0; i<m_hash_size;i++){
            if(m_p_process_array[i]!=nullptr){
                delete m_p_process_array[i];
                m_p_process_array[i]=nullptr;
            }
        }
        delete[] m_p_process_array;
        delete[] m_p_memory_array;
        m_p_process_array=nullptr;
        m_p_memory_array=nullptr;
    }
};