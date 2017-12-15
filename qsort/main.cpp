#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;
int* nums=NULL;
int Count=0;
void write();
void read();
void write();
int main()
{
    write();
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
    out<<10000<<endl;
    srand(time(NULL));
    for(int i=0;i<10000;i++)
    {
        out<<i<<" "<<rand()%500<<endl;
    }
    out.close();
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
    nums=new int[Count];
    for(i=0;i<Count;i++)
    {
        in>>x;
        if(x!=i)
            cout<<"wrong"<<endl;
        in>>value;
        if(in.eof())
            break;
        nums[i]=value;
    }
    if(i<Count)
        cout<<"the nums wrong"<<endl;
    Count=i;
    in.close();
}
