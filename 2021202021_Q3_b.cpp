#include<iostream>
#define ROW 500
#define COL 500
using namespace std;

template <class T>
struct Node{
	int row,col;
    T val;
	Node<T> *next;
};

template <class T>
void insert(int r,int c,T val,Node<T> **head) {
	if(*head == NULL){
		*head = new Node<T>;
		(*head)->row = r;
        (*head)->col = c;
        (*head)->val = val;
		(*head)->next = NULL;
		return;
	}
	Node<T> *temp = new Node<T>;
	temp->row = (*head)->row;
    temp->col = (*head)->col;
    temp->val = (*head)->val;
	temp->next = (*head)->next;
	(*head)->row=r;
    (*head)->col=c;
    (*head)->val=val;
	(*head)->next=temp;
}

template <class T>
void print(Node<T> *head) {
	Node<T> *temp=head;
	while(temp!=NULL) {
		cout<<temp->row<<" "<<temp->col<<" "<<temp->val<<endl;
		temp = temp->next;
	}
}
template <class T>
Node<T> *merge(Node<T> *fNode,Node<T> *sNode) {
	Node<T> *merged = new Node<T>;
	Node<T> *temp = new Node<T>;
	
	merged = temp;

	while(fNode != NULL && sNode != NULL) {
	
		if(fNode->row < sNode->row || (fNode->row == sNode->row && fNode->col < sNode->col)) {
			temp->next = fNode;
			fNode = fNode->next;
		}
		
		else {
			temp->next = sNode;
			sNode = sNode->next;
		}
		temp = temp->next;
	}
	
	while(fNode!=NULL) {
		temp->next = fNode;
		fNode = fNode->next;
		temp = temp->next;
	}

	while(sNode!=NULL) {
		temp->next = sNode;
		sNode = sNode->next;
		temp = temp->next;
	}

	return merged->next;
}

template <class T>
Node<T> *middle(Node<T> *head) {
	Node<T> *slow = head;
	Node<T> *fast = head->next;
	
	while(slow->next != NULL && (fast!=NULL && fast->next!=NULL)) {
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}

template <class T>
Node<T> *sort(Node<T> *head){
	
	if(head->next == NULL) {
		return head;
	}

	Node<T> *mid = new Node<T>;
	Node<T> *head2 = new Node<T>;
	mid = middle(head);
	head2 = mid->next;
	mid->next = NULL;
	Node<T> *finalhead = merge(sort(head),sort(head2));
	return finalhead;
}

template <class T>
Node<T>* multiply(Node<T> *head1,int r1,int c1,Node<T> *head2,int r2,int c2){
    Node<T> *result=NULL,*temp1,*temp2,*temp3=NULL,*result_temp=NULL;
    temp2=head2=sort(head2);
    temp1=head1=sort(head1);
    //print(head1);
    //cout<<endl;
    //print(head2);
    //cout<<endl;
    bool check=false;
    int count=0;
    while(temp1!=NULL){
        temp2=head2;
        while (temp2!=NULL)
        {
           check=false;
           if(temp1->col == temp2->col) {
               temp3=result;
               while(result!=NULL && temp3!=NULL && temp3!=result_temp->next){
                   if(temp3->row == temp1->row && temp3->col == temp2->row)
                    {
                        count++;
                        temp3->val+=temp1->val * temp2->val;
                        check=true;
                    }
                    temp3=temp3->next;
               }
               if(check==false){
                    if(result==NULL){
                        result=new Node<T>();
                        result->row = temp1->row;
                        result->col = temp2->row;
                        result->val =temp1->val * temp2->val;
                        result_temp=result;
                    }
                    else{
                    Node<T> *node=new Node<T>();
                    node->row = temp1->row;
                    node->col = temp2->row;
                    node->val =temp1->val * temp2->val;
                    result_temp->next=node;
                    result_temp=result_temp->next;
                    }
               }
           }
           temp2=temp2->next;
        }
        temp1=temp1->next;
    }
    //cout<<count<<endl;
    return result;
}

template <class T>
Node<T>* addition(Node<T> *head1,int r1,int c1,Node<T> *head2,int r2,int c2){
   Node<T> *result=NULL,*temp1,*temp2,*temp3=NULL;
   temp1=head1=sort(head1);
   temp2=head2=sort(head2);
   
   result=new Node<T>();
   if(temp1->row < temp2->row) {
       result->row=temp1->row;result->col=temp1->col;result->val=temp1->val;
       temp3=result;temp1=temp1->next;
   }
   else if(temp1->row > temp2->row){
       result->row=temp2->row;result->col=temp2->col;result->val=temp2->val;
       temp3=result;temp2=temp2->next;
   }
   else{
       if(temp1->col < temp2->col){
           result->row=temp1->row;result->col=temp1->col;result->val=temp1->val;
           temp3=result;temp1=temp1->next;
       }
       else if(temp1->col > temp2->col){
           result->row=temp2->row;result->col=temp2->col;result->val=temp2->val;
           temp3=result;temp2=temp2->next;
       }
       else{
           result->row=temp2->row;result->col=temp2->col;result->val=temp1->val + temp2->val;
           temp3=result;temp2=temp2->next;temp1=temp1->next;
       }
   }

   while(temp1!=NULL && temp2!=NULL){
   if(temp1->row < temp2->row){
            Node<T> *node=new Node<T>();
            node->row=temp1->row;node->col=temp1->col;node->val=temp1->val;
            temp3->next=node;temp1=temp1->next;temp3=temp3->next;
        }
        else if(temp1->row > temp2->row){
            Node<T> *node=new Node<T>();
            node->row=temp2->row;node->col=temp2->col;node->val=temp2->val;
            temp3->next=node;temp2=temp2->next;temp3=temp3->next;
        }
        else{
            if(temp1->col < temp2->col){
                Node<T> *node=new Node<T>();
                node->row=temp1->row;node->col=temp1->col;node->val=temp1->val;
                temp3->next=node;temp1=temp1->next;temp3=temp3->next;
            }
            else if(temp1->col > temp2->col){
                Node<T> *node=new Node<T>();
                node->row=temp2->row;node->col=temp2->col;node->val=temp2->val;
                 temp3->next=node;temp2=temp2->next;temp3=temp3->next;
            }
            else{
                Node<T> *node=new Node<T>();
                node->row=temp2->row;node->col=temp2->col;node->val=temp1->val + temp2->val;
                 temp3->next=node;temp2=temp2->next;temp1=temp1->next;temp3=temp3->next;
            }
        }
    }
    if(temp1 || temp2){
        while( temp1){
            Node<T> *node=new Node<T>();
            node->row=temp1->row;node->col=temp1->col;node->val=temp1->val;
            temp3->next=node;temp1=temp1->next;temp3=temp3->next;
        }
        while( temp2){
            Node<T> *node=new Node<T>();
            node->row=temp2->row;node->col=temp2->col;node->val=temp2->val;
            temp3->next=node;temp2=temp2->next;temp3=temp3->next;
        }
    }

   return result;
}

int main(void) {
    int r=3,c=4,choice;
    cin>>choice;
    double n[ROW][COL]={{0,5.5,0,6},{2,0,4,0},{0,0,7.8,0}};
	Node<double> *head = NULL;
	for(int i=0;i<r;i++) {
        for(int j=0;j<c;j++)
          if(n[i][j]!=0)
		    insert(j,i,n[i][j],&head); //inserting in the list
	}
    if(choice==1)   //transpose
	    print(sort(head));
    else if(choice==2)   //multiplcation
    {
        double arr1[ROW][COL]={{0,10.1,12},{1.5,0,2.4}};
        Node<double> *head1 = NULL;
        for(int i=0;i<2;i++) {
            for(int j=0;j<3;j++)
                if(arr1[i][j]!=0)
                    insert(i,j,arr1[i][j],&head1); //inserting in the list
        }
        double arr2[ROW][COL]={{2,5},{0,1},{8,0}};
        Node<double> *head2 = NULL;
        for(int i=0;i<3;i++) {
            for(int j=0;j<2;j++)
                if(arr2[i][j]!=0)
                    insert(j,i,arr2[i][j],&head2); //inserting in the list
        }
        //print(sort(head1));
        print(sort(multiply(head1,2,3,head2,3,2)));
    }
    else if(choice==3){
        double arr1[ROW][COL]={{0,10,12},{1,0,2}};
        Node<double> *head1 = NULL;
        for(int i=0;i<2;i++) {
            for(int j=0;j<3;j++)
                if(arr1[i][j]!=0)
                    insert(i,j,arr1[i][j],&head1); //inserting in the list
        }
        double arr2[ROW][COL]={{0.2,10.5,12},{1,0,2}};
        Node<double> *head2 = NULL;
        for(int i=0;i<2;i++) {
            for(int j=0;j<3;j++)
                if(arr2[i][j]!=0)
                    insert(i,j,arr2[i][j],&head2); //inserting in the list
        }
        print(addition(head1,2,3,head2,2,3));
    }
	return 0;
}
