#include<unordered_map>
#include<iostream>
using namespace std;
class LFUCache {
public:
    struct DLL{
        int key,value,freq;
        struct DLL *next;
        struct DLL *prev;
        DLL(int k,int v){
            key=k;
            value=v;
            next=NULL;
            prev=NULL;
            freq=1;
        }
    };
    unordered_map<int,DLL*> hash;
    unordered_map<int,pair<DLL*,DLL*>> lfu_map;
    int cap,freq=0;
    void del_node(struct DLL *node,int curFreq){
        //delete node
        //check if node->freq==freq and update min freq
        struct DLL *temp=node;
        /*if(temp->key==2){
            cout<<((lfu_map[curFreq]).second==NULL);
        }*/
        if(temp->prev==NULL) {
            node=node->next;
            (lfu_map[curFreq]).first=node;
            temp->next=NULL;
            if(node!=NULL) node->prev=NULL;
            /*if(temp==(lfu_map[temp->freq]).second)
            {
                lfu_map.erase(curFreq);
                //(lfu_map[temp->freq]).second=NULL;
            }*/
        }
        else if(temp->next==NULL){
            node=node->prev;
            node->next=NULL;
            temp->prev=NULL;
            (lfu_map[curFreq]).second=node;
        }
        else{
            node=node->prev;
            node->next=temp->next;
            temp->next->prev=node;
            temp->prev=NULL;temp->next=NULL;
        }
        if((lfu_map[curFreq]).first == NULL)
        {
            lfu_map.erase(curFreq);
            if(curFreq==freq) freq=curFreq+1;
        }
        //if(temp->key==1) cout<<((lfu_map[temp->freq]).second)->key<<freq;
    }
    
    void add_node(struct DLL *temp){
            if(lfu_map.find(temp->freq)==lfu_map.end()){
                lfu_map[temp->freq]={temp,temp};
            }
            else{
                temp->next=(lfu_map[temp->freq]).first;
                temp->prev=NULL;
                (lfu_map[temp->freq]).first=temp;
                if(temp->next!=NULL) temp->next->prev=temp;
            }
    }
    
    LFUCache(int capacity) {
        cap=capacity;
    }
    
    int get(int key) {
        if(hash.find(key)==hash.end() || cap==0) return -1;
        else{
            struct DLL *temp=hash[key];
            int curFreq=temp->freq;
            temp->freq++;
            del_node(temp,curFreq);
            add_node(temp);
            //if(key==3) cout<<((lfu_map[temp->freq]).second)->key<<" "<<temp->freq;
            //if(key==1) cout<<freq<<" ";
            return (hash[key])->value;
        }
    }
    
    void put(int key, int value) {
       if(hash.find(key)!=hash.end()){
           struct DLL *temp=hash[key];
           int curFreq=temp->freq++;
           temp->value=value;
           del_node(temp,curFreq);
           add_node(temp);
       }
        else{
            struct DLL *node=new DLL(key,value);
            if(hash.size() < cap)
            {
                if(lfu_map.find(1)==lfu_map.end()){
                    add_node(node);
                }
                else{
                    add_node(node);
                }
            }
            else{
                struct DLL *temp=(lfu_map[freq]).second;
                //if(key==4) cout<<freq;
                if(temp!=NULL)
                {
                    del_node(temp,temp->freq);
                    hash.erase(temp->key);
                }
                add_node(node);
            }
            hash[key]=node;
            freq=1;
        }
    }
};

int main(){
    LFUCache* obj = new LFUCache(2);
    int param_1 = obj->get(1);
    cout<<param_1;
    obj->put(2,2);
    obj->put(1,1);
    param_1 = obj->get(2);
    cout<<param_1;
}
/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */