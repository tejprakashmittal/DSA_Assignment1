#include<iostream>
#include<unordered_map>
using namespace std;

class LRUCache {
public:
    struct DLL{
        int key,value;
        struct DLL *next;
        struct DLL *prev;
        DLL(int k,int v){
            key=k;
            value=v;
            next=NULL;
            prev=NULL;
        }
    };
    unordered_map<int,DLL*> map;
    int n;
    struct DLL *lru,*mfu;
    
    void balance(int key){
        struct DLL *temp1,*temp2;
            temp1=temp2=map[key];
            if(temp1->prev!=NULL){
                temp1=temp1->prev;
                temp1->next->prev=NULL;
                temp1->next=temp1->next->next;
                if(temp1->next!=NULL){
                    temp1->next->prev=temp1;
                }
                /*temp1->next=temp2->next;
                if(temp2->next!=NULL) temp2->next->prev=temp1;*/
                temp2->next=mfu;
                mfu->prev=temp2;
                mfu=temp2;
                if(temp2==lru) lru=temp1;   //&& lru->prev!=NULL
            }
    }
    
    LRUCache(int capacity) {
           n=capacity;
           lru=NULL;
           mfu=NULL;
    }
    
    int get(int key) {
        if(map.find(key)!=map.end()){
            balance(key);
            return (map[key])->value;
        }
        else return -1;
    }
    
    void put(int key, int value) {
        if(map.find(key)!=map.end()){
            (map[key])->value=value;
            balance(key);
        }
        else{
            DLL* node=new DLL(key,value);
            if(map.size()<n){
                map[key]=node;
                if(mfu==NULL) mfu=lru=node;
                else{
                    node->next=mfu;
                    mfu->prev=node;
                    mfu=node;
                }
            }
            else{
                //struct DLL *temp;
               // temp=lru;
                map.erase(lru->key);
                lru=lru->prev;
                //temp->prev=temp->next=NULL;
                if(n==1){
                    map[key]=node;
                    mfu=node;
                    lru=mfu;
                }
                else{
                map[key]=node;
                node->next=mfu;
                mfu->prev=node;
                mfu=node;
                }
            }
        }
    }
};

int main(){
    LRUCache* obj = new LRUCache(2);
    int param_1 = obj->get(2);
    cout<<param_1;
    obj->put(3,3);
}
/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */