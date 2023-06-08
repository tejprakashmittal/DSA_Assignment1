#include<iostream>
#define ROW 500
#define COL 500
using namespace std;

template<class T>
void printMat(T (*a)[3],int r){
    for(int i=1;i<r;i++){
        if(a[i][2]==0) continue;
        cout<<a[i][0]<<" "<<a[i][1]<<" "<<a[i][2]<<endl;
    }
}

template <class T>
void* insertion_sort(T (*a)[3],int r){
   
    int i, j; T key[3];
    for (i = 1; i < r; i++)
    {
        key[0] = a[i][0];key[1] = a[i][1];key[2] = a[i][2];
        j = i - 1;
        while (j >= 0 && (a[j][0] > key[0] || (a[j][0] == key[0] && a[j][1]>key[1])))
        {
            a[j + 1][0] = a[j][0];
            a[j + 1][1] = a[j][1];
            a[j + 1][2] = a[j][2];
            j = j - 1;
        }
        a[j + 1][0] = key[0];
        a[j + 1][1] = key[1];
        a[j + 1][2] = key[2];
    } 
   return a;
}
template <class T>
void *transpose(T arr[ROW][COL],int r,int c){
    T ary[r*c][3]={0},(*ary_res)[3]=new T[r*c][3];int k=1,count=0,cnt;
    int total[c]={0},index[c+1]={0};
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            if(arr[i][j]!=0) {
                ary[k][0]=i;
                ary[k][1]=j;
                ary[k][2]=arr[i][j];
                k++;
                count++;
            }

        }
    }
    cnt=count;
    ary[0][0]=r;ary[0][1]=c;ary[0][2]=count;
    //for(int i=0;i<=cnt;i++) cout<<ary[i][0]<<" "<<ary[i][1]<<" "<<ary[i][2]<<endl;
    //cout<<endl;
    count=0,k=0;
    for(int i=0;i<c;i++){
        count=0;
        for(int j=0;j<r;j++){
            if(arr[j][i]!=0) count++;
        }
        total[k++]=count;
    }
    index[0]=1;
    for(int i=1;i<c+1;i++) index[i]=index[i-1]+total[i-1];
    //for(int i=0;i<=4;i++) cout<<index[i]<<" ";cout<<endl;
    for(int i=1;i<=cnt;i++){
        int ind=index[(int)ary[i][1]];
        ary_res[ind][0]=ary[i][1];
        ary_res[ind][1]=ary[i][0];
        ary_res[ind][2]=ary[i][2];
        index[(int)ary[i][1]]++;
    }
    ary_res[0][0]=c;ary_res[0][1]=r;ary_res[0][2]=ary[0][2];
    //for(int i=0;i<=cnt;i++) cout<<ary_res[i][0]<<" "<<ary_res[i][1]<<" "<<ary_res[i][2]<<endl;
    return ary_res;
}

template <class T>
void* multiply(T arr1[ROW][COL],int r1,int c1,T arr2[ROW][COL],int r2,int c2){
    T (*first)[3]=new int[r1*c1][3],(*second)[3]=new int[r2*c2][3],(*result)[3]=new int[r1*c2][3];int k=1,count=0;
    second=(T (*)[3])transpose(arr2,r2,c2);

    for(int i=0;i<r1;i++){
        for(int j=0;j<c1;j++){
            if(arr1[i][j]!=0) {
                first[k][0]=i;
                first[k][1]=j;
                first[k][2]=arr1[i][j];
                k++;
                count++;
            }
        }
    }
    first[0][0]=r1;first[0][1]=c1;first[0][2]=count;
    int l=1;
    bool check=false;
    for(int i=1;i<=count;i++){
        for(int j=1;j<r2*c2;j++){
            check=false;
            if(second[j][2]==0) break;
            if(first[i][1]==second[j][1]){
                int t=l-1;
                while(t>0){
                    if(result[t][0]==first[i][0] && result[t][1]==second[j][0])
                    {
                        result[t][2]+=first[i][2]*second[j][2];
                        check=true;
                    }
                    t--;
                }
                if(check==false){
                    result[l][0]=first[i][0];
                    result[l][1]=second[j][0];
                    result[l][2]=first[i][2]*second[j][2];
                    l++;
                }
            }
        }
    }
    result=(int (*)[3])insertion_sort(result,--l);
    result[0][0]=r1;result[0][1]=c2;result[0][2]=--l;
  return result;
}

template <class T>
void* addition(T arr1[ROW][COL],int r1,int c1,T arr2[ROW][COL],int r2,int c2){
   T (*first)[3]=new T[r1*c1][3],(*second)[3]=new T[r2*c2][3],(*result)[3]=new T[r1*c1][3]; int k=1,count=0;
   for(int i=0;i<r1;i++){
        for(int j=0;j<c1;j++){
            if(arr1[i][j]!=0) {
                first[k][0]=i;
                first[k][1]=j;
                first[k][2]=arr1[i][j];
                k++;
                count++;
            }
        }
    }
    int len1=count;
    first[0][0]=r1;first[0][1]=c1;first[0][2]=count;
    count=0;k=1;
    for(int i=0;i<r1;i++){
        for(int j=0;j<c1;j++){
            if(arr2[i][j]!=0) {
                second[k][0]=i;
                second[k][1]=j;
                second[k][2]=arr2[i][j];
                k++;
                count++;
            }
        }
    }
    int len2=count;
    second[0][0]=r1;second[0][1]=c1;second[0][2]=count;

    int i=1,j=1;k=1;
    while(i<=len1 && j<=len2){
        if(first[i][0]<second[j][0]){
            result[k][0]=first[i][0];
            result[k][1]=first[i][1];result[k][2]=first[i][2];
            i++;k++;
        }
        else if(first[i][0] > second[j][0]){
            result[k][0]=second[j][0];
            result[k][1]=second[j][1];result[k][2]=second[j][2];
            j++;k++;
        }
        else{
            if(first[i][1] == second[j][1]){
                if(first[i][2] + second[j][2] == 0){
                    i++;j++;
                    continue;
                }
                result[k][0]=second[j][0];
                result[k][1]=second[j][1];result[k][2]=first[i][2] + second[j][2];
                i++;j++;k++;
            }
            else if(first[i][1] < second[j][1]){
                result[k][0]=first[i][0];
                result[k][1]=first[i][1];result[k][2]=first[i][2];
                i++;k++;
            }
            else{
                result[k][0]=second[j][0];
                result[k][1]=second[j][1];result[k][2]=second[j][2];
                j++;k++;
            }
        }
    }
    if(i<=len1 || j<=len2){
        while( i<=len1 && first[i][2]!=0){
            result[k][0]=first[i][0];
            result[k][1]=first[i][1];result[k][2]=first[i][2];
            i++;k++;
        }
        while( j<=len2 && second[j][2]!=0){
            result[k][0]=second[j][0];
            result[k][1]=second[j][1];result[k][2]=second[j][2];
            j++;k++;
        }
    }
    result[0][0]=r1;result[0][1]=c1;result[0][2]=k-1;
    return result;
}

int main(){
    int r=3,c=4,choice;
    //cin>>r>>c;
    cin>>choice;
    //int arr[ROW][COL];
    double arr[ROW][COL]={{0,5,0,6},{2,0,4,0},{0,0,7,0}};
    /*for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            cin>>arr[i][j];
        }
    }*/
    if(choice==1)
    {
    double (*a)[3]=(double (*)[3])transpose(arr,r,c);
    for(int i=0;i<r*c;i++) {if(a[i][2]!=0) cout<<a[i][0]<<" "<<a[i][1]<<" "<<a[i][2]<<endl;}
    }
    else if(choice==2)
    {
    int arr1[ROW][COL]={{0,10,12},{1,0,2}};
    int arr2[ROW][COL]={{2,5},{0,1},{8,0}};
    printMat((int (*)[3])multiply(arr1,2,3,arr2,3,2),5);
    }
    else if(choice==3){
        double arr1[ROW][COL]={{0,10,12},{1,0,2}};
        double arr2[ROW][COL]={{0,5.6,0},{-1,0,2}};
        printMat((double (*)[3])addition(arr1,2,3,arr2,2,3),6);
    }
}