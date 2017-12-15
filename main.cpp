#include<iostream>
#include<fstream>
using namespace std;
struct Index
{
    int index;
    struct Index *next;
};
typedef struct Index *indexs;
typedef struct Equals
{
    int value;
    indexs the_index;
}*equals;
typedef struct Nodes
{
    equals all;
    struct Nodes *lchild;
    struct Nodes *rchild;
}nodes;
nodes *tree=NULL;
int *nums;
int Count=0;
void read();
void setTree();
void add_node(int index,int value);
nodes* Insert(int index,int value);
void output(nodes *p);
void Search(nodes *tree,int value);
void Delete(nodes* &p,int value);
equals delmin(nodes* &p);
int main()
{
    int choice,value;
    char flag;
    read();
    setTree();
    do{
        output(tree);
        cout<<"1.Search the indexs of the value"<<endl;
        cout<<"2.Delete the node of the value"<<endl;
        cout<<"3.Insert the value"<<endl;
        cin>>choice;
        cout<<"Please input the value"<<endl;
        cin>>value;
        getchar();
        switch(choice)
        {
        case 1:
            Search(tree,value);
            break;
        case 2:
            Delete(tree,value);
            break;
        case 3:
            add_node(Count++,value);
            break;
        default:
            break;
        }
        cout<<"Do you want to continue?(Y/y)"<<endl;
        cin>>flag;
    }while(flag=='Y'||flag=='y');
}
void read()
{
    ifstream in("test.txt",iostream::in);
    if(!in.is_open())
    {
        cout<<"error!"<<endl;
        return;
    }
    int i,value;
    in>>Count;
    nums=new int[Count];
    for(i=0;i<Count;i++)
    {
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
void setTree()
{
    for(int i=0;i<Count;i++)
    {
        add_node(i,nums[i]);
    }
}
void add_node(int index,int value)
{
    if(tree==NULL)
    {
        tree=Insert(index,value);
        return;
    }
    nodes *p=tree;
    while(p!=NULL)
    {
        if(value>p->all->value)
        {
            if(p->rchild==NULL)
            {
                p->rchild=Insert(index,value);
                return;
            }
            p=p->rchild;
        }
        else if(value<p->all->value)
        {
            if(p->lchild==NULL)
            {
                p->lchild=Insert(index,value);
                return;
            }
            p=p->lchild;
        }
        else
            break;
    }
    indexs t=new Index;
    t->index=index;
    t->next=p->all->the_index;
    p->all->the_index=t;
}
nodes* Insert(int index,int value)
{
    nodes *p=new nodes;
    p->lchild=NULL;
    p->rchild=NULL;
    p->all =new struct Equals;
    p->all->value=value;
    p->all->the_index=NULL;
    indexs t=new Index;
    t->index=index;
    t->next=p->all->the_index;
    p->all->the_index=t;
    return p;
}
void output(nodes *p)
{
    if(p==NULL)
    {
        cout<<"No data"<<endl;
        return;
    }
    cout<<"value: "<<p->all->value<<" index: ";
    indexs q=p->all->the_index;
    while(q!=NULL)
    {
        cout<<q->index<<" ";
        q=q->next;
    }
    if(p->lchild!=NULL)
    {
        cout<<"  lchild: "<<p->lchild->all->value;
    }
    if(p->rchild!=NULL)
    {
        cout<<"  rchild: "<<p->rchild->all->value;
    }
    cout<<endl;
    if(p->lchild!=NULL)
    {
        output(p->lchild);
    }
    if(p->rchild!=NULL)
    {
        output(p->rchild);
    }
}
void Search(nodes *p,int value)
{
    if(p==NULL)
        cout<<"Not find"<<endl;
    else if(p->all->value==value)
    {
        indexs q=p->all->the_index;
        while(q!=NULL)
        {
            cout<<q->index<<endl;
            q=q->next;
        }
        return;
    }
    else if(p->all->value>value)
        Search(p->lchild,value);
    else
        Search(p->rchild,value);
}
void Delete(nodes* &p ,int value)
{
    if(p==NULL)
        cout<<"Not find"<<endl;
    else if(p->all->value>value)
    {
        Delete(p->lchild,value);
    }
    else if(p->all->value<value)
    {
        Delete(p->rchild,value);
    }
    else
    {
        nodes *q;
        if(p->lchild==NULL)
        {
            q=p;
            p=p->rchild;
            delete q;
        }
        else if(p->rchild==NULL)
        {
            q=p;
            p=p->lchild;
            delete q;
        }
        else
        {
            p->all=delmin(p->rchild);
        }
    }
}
equals delmin(nodes* &p)
{
    if(p->lchild==NULL)
    {
        nodes *q=p;
        p=p->rchild;
        return q->all;
        delete q;
    }
    else
    {
        return delmin(p->lchild);
    }
}
