#include <iostream>
#include "chainHashTable.h"
using namespace std;

CProcess::CProcess(int PID){
    m_PID=PID;
    m_p_next=nullptr;
    m_p_prev=nullptr;
}
int CProcess::getPID(){
    return m_PID;
}

int CProcess::getPhysicalIndex(int ADDR){
    return m_page_index_start+ADDR;;
}

void CProcess::setNext(CProcess *next){
    m_p_next=next;
}

int CProcess::getPageIndexStart(){
    return m_page_index_start;
}

void CProcess::setPageindexStart(int page_index_start){
    m_page_index_start=page_index_start;
}

void CProcess::setPrev(CProcess *prev){
    m_p_prev=prev;
}

CProcess* CProcess::getNext(){
    return m_p_next;
}

CProcess* CProcess::getPrev(){
    return m_p_prev;
}




int ChainHashTable::hashingFunc(int PID){
    return PID%m_hash_size;
}
bool ChainHashTable::checkPID(int PID){
    bool repeat=false;
    bool space_left=false;
    for(int i=0; i<m_hash_size;i++){
        if(m_p_process_page[i]==PID){
            repeat=true;
            break;
        }
        if(m_p_process_page[i]==0){
            space_left=true;
        }
    }
    return (!repeat && space_left);
}

int ChainHashTable::getFreePage(){
    int index=-1;
    for(int i=0; i<m_hash_size; i++){
        if(m_p_process_page[i]==0){
            index=i;
            break;
        }
    }
    return index;
}

CProcess* ChainHashTable::getProcess(int PID){
    CProcess* iterator=m_p_process_array[hashingFunc(PID)];
    while(iterator!=nullptr){
        if(iterator->getPID()==PID){
            break;
        }
        iterator=iterator->getNext();
    }
    return iterator;
}

void ChainHashTable::createMemoryArray(int memory_size, int page_size){
    this->m_page_size=page_size;
    this->m_p_memory_array=new int[memory_size];
    this->m_p_process_array=new CProcess*[memory_size/page_size];
    this->m_hash_size=memory_size/page_size;
    this->m_p_process_page=new int[m_hash_size]();
    for (int i=0;i<m_hash_size;i++){
        m_p_process_array[i]=nullptr;
    }
    cout<<"success"<<endl;
}
void ChainHashTable::search(int PID){
    int hash_index=this->hashingFunc(PID);
    CProcess *iterator=this->getProcess(PID);
    if(iterator!=nullptr){
        cout<<"found "<<PID<<" in "<<hash_index<<endl;
    }
    else{
        cout<<"not found"<<endl;
    }
    
}
void ChainHashTable::insert(int PID){
    bool success=false;
    int hash_index=this->hashingFunc(PID);
    CProcess* iterator=m_p_process_array[hash_index];
    CProcess* head=m_p_process_array[hash_index];
    if(this->checkPID(PID)){
        success=true;
        int page_index=this->getFreePage();
        m_p_process_page[page_index]=PID;
        CProcess* temp=new CProcess(PID);
        temp->setPageindexStart(page_index*m_page_size);
        if(m_p_process_array[hash_index]==nullptr){
            m_p_process_array[hash_index]=temp;
        }
        else{
            while(iterator!=nullptr){
                if(PID>iterator->getPID()){
                    if(iterator==head){
                        head->setPrev(temp);
                        temp->setNext(head);
                        m_p_process_array[hash_index]=temp;
                        break;
                    }
                    else{
                        iterator->getPrev()->setNext(temp);
                        temp->setPrev(iterator->getPrev());
                        temp->setNext(iterator);
                        iterator->setPrev(temp);
                        break;
                    }
                }
                if(iterator->getNext()==nullptr){
                    iterator->setNext(temp);
                    temp->setPrev(iterator);
                    break;
                }
                iterator=iterator->getNext();
                
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
void ChainHashTable::write(int PID, int ADDR, int x){
    CProcess *target=this->getProcess(PID);
    if((target!=nullptr)&&(ADDR<m_page_size)){
        m_p_memory_array[target->getPhysicalIndex(ADDR)]=x;
        cout<<"success"<<endl;
    }
    else{
        cout<<"failure"<<endl;
    }
}

void ChainHashTable::read(int PID, int ADDR){
    CProcess *target=this->getProcess(PID);
    if((target!=nullptr)&&(ADDR<m_page_size)){
        cout<<ADDR<<" "<<m_p_memory_array[target->getPhysicalIndex(ADDR)]<<endl;
    }
    else{
        cout<<"failure"<<endl;
    }
}

void ChainHashTable::print(int m){
    CProcess* iterator=m_p_process_array[m];
    if(iterator==nullptr){
        cout<<"chain is empty"<<endl;
    }
    else{
        while(iterator!=nullptr){
            cout<<iterator->getPID()<<" ";
            iterator=iterator->getNext();
        }
        cout<<endl;
    }
}

void ChainHashTable::deleteProcess(int PID){
    int hash_index=hashingFunc(PID);
    CProcess *target=this->getProcess(PID);
    if(target==nullptr){
        cout<<"failure"<<endl;
    }
    else{
        if((target->getNext()==nullptr)&&(target->getPrev()==nullptr)){
            m_p_process_array[hash_index]=nullptr;
        }
        else if((target->getNext()==nullptr)&&(target->getPrev()!=nullptr)){
            target->getPrev()->setNext(nullptr);
        }
        else if((target->getNext()!=nullptr)&&(target->getPrev()==nullptr)){
            target->getNext()->setPrev(nullptr);
            m_p_process_array[hash_index]=target->getNext();
        }
        else{
            target->getPrev()->setNext(target->getNext());
            target->getNext()->setPrev(target->getPrev());
        }
        m_p_process_page[target->getPageIndexStart()/m_page_size]=0;
        delete target;
        cout<<"success"<<endl;
    }
}

ChainHashTable::~ChainHashTable(){
    for(int i=0; i<m_hash_size;i++){
        CProcess* iterator=m_p_process_array[i];
        while(iterator!=nullptr){
            CProcess* temp=iterator;
            iterator=iterator->getNext();
            delete temp;
        }
    }
    delete[] m_p_process_array;
    delete[] m_p_memory_array;
    delete[] m_p_process_page;
}
