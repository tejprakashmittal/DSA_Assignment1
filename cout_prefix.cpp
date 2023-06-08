struct TrieNode{
        char c;
        int char_count=0;
        struct TrieNode *arr[26];
        int count=0;
        string word;
    };
    
    struct TrieNode* createNode(struct TrieNode* node){
        node=new TrieNode();
        memset(node->arr, NULL, 26);
        node->c='\0';
        node->char_count=0;
        node->word="";
        return node;
    }
    
    struct TrieNode *root;

     void insertIfNull(TrieNode* cur_root,string word,string org_word){
        TrieNode *temp=cur_root;
        for(int i=0;i<word.size();i++){
                struct TrieNode *node;
                temp->arr[word[i]-'a']=node=createNode(node);
                node->c=word[i];
                node->char_count=1;
                temp=node;
            }
            temp->count=1;
            temp->word=org_word;
    }
    
    void insert(string word) {
        TrieNode *temp=root;
        
        int i=0;
        while(temp->arr[word[i]-'a']!=NULL && i<word.size()){
                temp->arr[word[i]-'a']->char_count++;
                temp=temp->arr[word[i]-'a'];
                i++;
        }
        if(i==word.size()){
            temp->count=1;
            temp->word=word;
        }
        else insertIfNull(temp,word.substr(i,word.size()-i),word);
    }
    
    bool search(string word) {
            TrieNode* temp=root;
            for(int i=0;i<word.size();i++){
                if(temp->arr[word[i]-'a']!=NULL) temp=temp->arr[word[i]-'a'];
                else return false;
            }
        if(temp->count==0) return false;
        return true;
    }
    
    bool startsWith(string prefix) {
            TrieNode* temp=root;
            for(int i=0;i<prefix.size();i++){
                if(temp->arr[prefix[i]-'a']!=NULL) temp=temp->arr[prefix[i]-'a'];
                else return false;
            }
        return true;
    }

int auto_complete(string prefix){
    TrieNode* temp=root;
    int count=0,i=0;
    for(i=0;i<prefix.size()-1;i++){
        if(temp->arr[prefix[i]-'a']!=NULL){
            temp=temp->arr[prefix[i]-'a'];
        }
        else{
            return 0;
        }
    }
    if(temp->arr[prefix[i]-'a']!=NULL){
            return temp->arr[prefix[i]-'a']->char_count;
        }
        return 0;
}

vector<int> contacts(vector<vector<string>> queries) {
    root=createNode(root);
    vector<int> res;
    for(int i=0;i<queries.size();i++){
        if(queries[i][0] == "add"){
            insert(queries[i][1]);
        }
        else if(queries[i][0] == "find"){
            res.push_back(auto_complete(queries[i][1]));
        }
    }
    return res;
}

