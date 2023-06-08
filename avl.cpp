#include<iostream>
using namespace std;
struct Node
    {
        int val,count;
        struct Node* left;
        struct Node* right;
        int height;
    };
class Avl{
    public:
    int hit(Node *nod){
        if(nod==NULL) return 0;
        return nod->height;
    }

    Node* RR(Node* root){
        Node *temp=root->right;
        root->right=temp->left;
        temp->left=root;
        
        root->height=max(hit(root->left),hit(root->right))+1;
        temp->height=max(hit(temp->left),hit(temp->right))+1;
        
        return temp;
    }

    Node* LL(Node* root){
        Node *temp=root->left;
        root->left=temp->right;
        temp->right=root;
        
        root->height=max(hit(root->left),hit(root->right))+1;
        temp->height=max(hit(temp->left),hit(temp->right))+1;
        
        return temp;
    }

/* Insert Function Sction*/

    Node* rotation(Node* root,Node * nod){
        if(root->val < nod->val){
            if(root->right->val < nod->val) return RR(root);
            else{
                root->right=LL(root->right);
                return RR(root);
            }
        }
        else{
            if(root->left->val > nod->val) return LL(root);
            else{
                root->left=RR(root->left);
                return LL(root);
            }
        }
    }

    Node* balance(Node* root,Node * nod){
        int BF=abs(hit(root->left) - hit(root->right));
        //cout<<"BF:"<<BF<<endl;
        if(BF>1) return rotation(root,nod);
        return root;
    }

    Node* insertAVL(Node* root,Node * nod){
        if(root==NULL) return nod;
        else{
            if(root->val < nod->val){
                    root->right = insertAVL(root->right,nod);
            }
            else if(root->val > nod->val){
                    root->left = insertAVL(root->left,nod);
            }
            else{
                root->count++;
                return root;
            }
            root->height=max(hit(root->left),hit(root->right))+1;
            return balance(root,nod);
        }
    }

    Node * insert(Node * root,int val)
    {
        Node* nod=new Node();
        nod->val=val;
        nod->height=1;
        nod->count=1;
        nod->left=NULL;nod->right=NULL;
        return insertAVL(root,nod);
    }
   /*End of Insert Function*/

/*start of delete------------*/
    Node* notBoth(Node* root){
        Node *temp=NULL;
        if(root->left==NULL) temp=root->right;
        else temp=root->left;
        
        return temp;
    }
    
    Node* success(Node* root){
        Node* temp = root;
            while (temp->left != NULL)
                temp = temp->left;
         
            return temp;
    }
    void dataCopy(Node *root,Node *temp){
            root->val=temp->val;
            root->height=temp->height;
            root->count=temp->count;
        }

    Node* findAndDel(Node* root, int key){
            if(root==NULL) return root;
            if(root->val==key) {
                if(root->right==NULL || root->left==NULL) {
                    if( (root->left == NULL) || (root->right == NULL) ) root=notBoth(root);
                }
                else
                {
                    Node* temp=success(root->right);
                    dataCopy(root,temp);
                    root->right=findAndDel(root->right,temp->val);
                }
                if(root==NULL) return root;
            }
            if(root->val > key) root->left=findAndDel(root->left,key);
            else root->right = findAndDel(root->right,key);
            
            root->height=1 + max(hit(root->left),hit(root->right));
            
            int bf=hit(root->left)-hit(root->right);
            
            if(bf > 1){
                int bf_left=hit(root->left->left)-hit(root->left->right);
                if(bf_left >= 0) return LL(root);
                else {
                    root->left=RR(root->left);
                    return LL(root);
                }
            }
            
            else if(bf < -1){
                int bf_right=hit(root->right->left)-hit(root->right->right);
                if(bf_right <= 0) return RR(root);
                else {
                    root->right=LL(root->right);
                    return RR(root);
                }
            }
            
            return root;
    }

    Node* deleteNode(Node* root, int val)
    {
        if(root==NULL) return NULL;
            return findAndDel(root,val);
    }/*End of delete-----------------------------------------------------------------*/

/*K-th largest element---------------------------------------------------------------*/
    Node* inOrd(Node *root,int &k){
        if(root==NULL) return root;
        Node *temp=NULL;
        temp=inOrd(root->right,k);

        if(temp!=NULL) return temp;

        k=k-root->count;
        if(k<=0) return root;
        
        temp=inOrd(root->left,k);
        
        return temp;
    }
    Node* kthLargest(Node *root, int k)
    {
        return inOrd(root,k);
    }

/*Count the number of elements in the tree whose values fall into a given range.*/
    void findRange(Node* root, int low, int high , int &count){
        if(root==NULL) return;
        if(root->val >= low && root->val <= high) count+=root->count;
        if(root->val < low) findRange(root->right,low,high,count);
        else if(root->val > high) findRange(root->left,low,high,count);  
        else {
            findRange(root->right,low,high,count);
            findRange(root->left,low,high,count); 
        }
    }
    int getCount(Node *root, int l, int h)
    {
            int count=0;
            findRange(root,l,h,count);
            return count;  
    }

/*Find Closest Element--------------------------------*/
    void findClosest(Node *root, int k,int &_minDiff,int &minVal){
	    if(root==NULL) return;
	    int diff=abs(root->val-k);
	    
	    if(diff<_minDiff){
	        _minDiff=diff;
	        minVal=root->val;
	    }
	    findClosest(root->left,k,_minDiff,minVal);
	    findClosest(root->right,k,_minDiff,minVal);
	}
	
    int closest(Node *root, int k)
    {
        int _minDiff=__INT_MAX__,minVal=root->val;
        findClosest(root,k,_minDiff,minVal);
        return minVal;
    } 

/*Search an element -------------------------------*/
    bool find(Node *root,int k){
        if(root==NULL) return false;
        if(root->val==k) return true;
        if(root->val < k) return find(root->right,k);
        return find(root->left,k);
    }

/*Count occurrences of element----------------------------------*/
    int countOccur(Node *root,int k){
        if(root==NULL) return 0;
        if(root->val==k) return root->count;
        if(root->val < k) return countOccur(root->right,k);
        return countOccur(root->left,k);
    }

/*Lower Bound---------------------------------------------------------*/
    int lower_bound(Node *root,int k){
        int ans=-1;
        while(root!=NULL){
            if(root->val == k) return root->val;
            else if(k < root->val){
                ans=root->val;
                root=root->left;
            }
            else root=root->right;
        }
        return ans;
    }

/*Upper Bound---------------------------------------------------------*/
    int upper_bound(Node *root,int k){
        int ans=-1;
        while(root!=NULL){
            if(k < root->val){
                ans=root->val;
                root=root->left;
            }
            else root=root->right;
        }
        return ans;
    }

};

void preOrder(struct Node* root)
{
    if (root != NULL) {
        cout << root->val << "("<<root->count << ")"<< " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}
 
/* Driver program to test above function*/
int main()
{
    struct Node* root = NULL;
    Avl *obj=new Avl();
    /* Constructing tree given in the above figure */
    root = obj->insert(root, 9);
    root = obj->insert(root, 5);
    root = obj->insert(root, 10);
    root = obj->insert(root, 5);
    root = obj->insert(root, 9);
    root = obj->insert(root, 7);
    root = obj->insert(root, 17);
 
    cout <<"Pre order traversal of the constructed AVL tree is \n";
    preOrder(root);
    cout<<endl;
    //root=obj->kthLargest(root,6);
    //cout<<root->val;
    //cout<<obj->getCount(root,5,17)<<endl;
    //cout<<obj->closest(root,10)<<endl;
    cout<<obj->upper_bound(root,18);
    //root=obj->deleteNode(root,9);
    //root=obj->deleteNode(root,10);
 
    //cout <<"\nPre order traversal after deletion of 9 \n";
    //preOrder(root);
}
     