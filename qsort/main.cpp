#include <iostream>
#include <fstream>
#include <limits>
#include <ctime>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#define MAX 5000
#define NUM 200
#define N 100000
using namespace std;
int* nums=NULL;
int* num2=NULL;
int Count=0;
void write();
void Qsort(int first,int last);
void insertSort(int first,int last);
void Swap(int &a,int &b);
void findTemp(int first,int last);
void read();
void write();
void Write();
int main()
{
    for(int i=0;i<10;i++)
    {
    write();
    read();
    int qstart,qend,Start,End;
    qstart=clock();
    Qsort(1,N);
    qend=clock();
    Write();
    bool flag=true;
    Start=clock();
    sort(num2,num2+N);
    End=clock();
    for(int i=0;i<N;i++)
    {
        if(nums[i+1]!=num2[i])
        {
            cout<<"error"<<nums[i+1]<<" "<<num2[i]<<endl;
            flag=false;
        }
    }
    if(flag)
        cout<<"Yes,qsort is as same as sort"<<endl;
    cout<<"qsort time:"<<(qend-qstart)<<"ms"<<endl;
    cout<<"sort time:"<<(End-Start)<<"ms"<<endl;
    }
    return 0;
}
void write()
{
    ofstream out("test.txt",iostream::out);
    if(!out.is_open())
    {
        cout<<"error!"<<endl;
        return;
    }
    out<<N<<endl;
    srand(time(NULL));
    for(int i=0;i<N;i++)
    {
        out<<i<<" "<<rand()%(MAX/NUM)+(i/(MAX/NUM))*(MAX/NUM)<<endl;
        //out<<i<<" "<<rand()%MAX<<endl;
    }
    out.close();
}
void Write()
{
    ofstream out("write.txt",iostream::out);
    if(!out.is_open())
    {
        cout<<"error!"<<endl;
        return;
    }
    for(int i=1;i<=N;i++)
        out<<nums[i]<<endl;
    out.close();
    return;
}
void read()
{
    ifstream in("test.txt",iostream::in);
    if(!in.is_open())
    {
        cout<<"error!"<<endl;
        return;
    }
    int i,value,x;
    in>>Count;
    nums=new int[Count+1];//进行插入排序时设置哨兵
    num2=new int[Count+1];
    for(i=0;i<Count;i++)
    {
        in>>x;
        if(x!=i)
            cout<<"wrong"<<endl;
        in>>value;
        if(in.eof())
            break;
        nums[i+1]=value;//nums[0]为哨兵
        num2[i]=value;
    }
    if(i<Count)
        cout<<"the nums wrong"<<endl;
    Count=i;
    in.close();
}
void Qsort(int first,int last)
{
    if(last-first<15)//若数据量小于16，则用插入排序进行优化
    {
        insertSort(first,last);
        return;
    }
    findTemp(first,last);
    int mid=nums[first];
    int left=first;
    int low=first;
    int right=last;
    int high=last;
    int highlength=0,lowlength=0;//将与中间值相等的元素单独放置
    while(right>left)
    {
        while(right>left&&nums[right]>=mid)
        {
            if(nums[right]==mid)
            {
                Swap(nums[right],nums[high]);
                high--;
                highlength++;
            }
            right--;
        }
        while(right>left&&nums[left]<=mid)
        {
            if(nums[left]==mid)
            {
                Swap(nums[left],nums[low]);
                low++;
                lowlength++;
            }
            left++;
        }
        Swap(nums[left],nums[right]);
    }
    for(int i=first,j=left;i<low&&nums[j]!=mid;i++,j--)
        Swap(nums[i],nums[j]);
    for(int i=last,j=right+1;i>high&&nums[j]!=mid;i--,j++)
        Swap(nums[i],nums[j]);
    Qsort(first,left-lowlength);
    Qsort(right+highlength,last);
}
void insertSort(int first,int last)
{
    int t=nums[first-1];
    nums[first-1]=INT_MIN;
    for(int i=first+1;i<=last;i++)
    {
        for(int j=i;;j--)
        {
            if(nums[j]>=nums[j-1])
                break;
            else
                Swap(nums[j-1],nums[j]);
        }
    }
    nums[first-1]=t;
}
void Swap(int &a,int &b)
{
    int temp;
    temp=a;
    a=b;
    b=temp;
}
void findTemp(int first,int last)//三数取中得到中间值并将其放在首位
{
    int M=(first+last)>>1;
    if((nums[first]<=nums[M]&&nums[last]>=nums[M])||(nums[first]>=nums[M]&&nums[last]<=nums[M]))
    {
        Swap(nums[first],nums[M]);
        return;
    }
    if((nums[M]<=nums[first]&&nums[last]>=nums[first])||(nums[M]>=nums[first]&&nums[last]<=nums[first]))
    {
        return;
    }
    else
    {
        Swap(nums[first],nums[last]);
        return;
    }
}
