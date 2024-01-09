#include "ItemsPool.hpp"
#include <iostream>
using namespace std;

ItemsNode::ItemsNode(const int &index,Items &items)
{
    this->index=index;
    this->items=items;
}

ItemsPool::ItemsPool(const int &SIndex,Items &StartItems)
{
    StartItems.closure();
    this->que.push(pair<int,Items>(SIndex,StartItems));
}

ItemsPool::~ItemsPool()
{

}

int ItemsPool::findItems(Items &items)
{
    for(int i=0;i<this->pool.size();i++)
    {
        if(this->pool[i].items==items)
        {
            return i;
        }
    }
    //tmp暂存
    queue<pair<int,Items>> temp=this->que;
    while(!temp.empty())
    {
        pair<int,Items> head=temp.front();
        temp.pop();
        if(head.second==items)
        {
            return head.first;
        }
    }
    return -1;
}

void ItemsPool::getDFA(SymbolPool *tpool,SymbolPool *npool)
{
    int k=0;
    int cnt=1;
    while(!que.empty())
    {
        Items head=que.front().second;
        ItemsNode curNode=ItemsNode(k,head);
        // print DFA
        // cout<<endl<<"I"<<k<<":"<<endl;
        // for(int i=0;i<head.size();i++)
        // {
        //     Item tempItem=head.Its[i];
        //     cout<<npool->getString(tempItem.left)<<"->";
        //     for(int j=0;j<tempItem.right.size();j++)
        //     {
        //         if(j==tempItem.pos)
        //             cout<<"• ";
        //         if(tempItem.right[j].type==Symbol::TSymbol)
        //             cout<<tpool->getString(tempItem.right[j].index)<<" ";
        //         else
        //             cout<<npool->getString(tempItem.right[j].index)<<" ";
        //     }
        //     if(tempItem.pos==tempItem.right.size())
        //         cout<<"•";

        //     if(tempItem.forward==-1)
        //         cout<<"     $"<<endl;
        //     else
        //         cout<<"     "<<tpool->getString(tempItem.forward)<<endl;
        // }

        // NSymbol
        Items nextItems=Items(head.PPool);
        for(int j=0;j<npool->size();j++)
        {
            nextItems.Its.clear();
            if(head.go(Symbol(j,Symbol::NSymbol),nextItems))
            {
                nextItems.closure();
                int index=this->findItems(nextItems);
                if(index<0)
                {
                    curNode.mapper.insert(pair<int,Symbol>(cnt,Symbol(j,Symbol::NSymbol)));
                    this->que.push(pair<int,Items>(cnt,nextItems));
                    cnt++;
                }
                else
                {
                    curNode.mapper.insert(pair<int,Symbol>(index,Symbol(j,Symbol::NSymbol)));
                }
            }    
        }
        // TSymbol
        for(int j=0;j<tpool->size();j++)
        {
            nextItems.Its.clear();
            if(head.go(Symbol(j,Symbol::TSymbol),nextItems))
            {
                nextItems.closure();
                int index=this->findItems(nextItems);
                if(index<0)
                {
                    curNode.mapper.insert(pair<int,Symbol>(cnt,Symbol(j,Symbol::TSymbol)));
                    this->que.push(pair<int,Items>(cnt,nextItems));
                    cnt++;
                }
                else
                {
                    curNode.mapper.insert(pair<int,Symbol>(index,Symbol(j,Symbol::TSymbol)));
                }
            }
        }
        this->pool.push_back(curNode);
        k++;
        que.pop();
    }
}
/*
0->.n1 	-1
1->.n2 t0 n3 	-1
1->.n3 	-1
2->.t2 n3 	0
2->.t1 	0
3->.n2 	-1
2->.t2 n3 	-1
2->.t1 	-1

I0:
S'->• S      $
S->• L = R      $
S->• R      $
L->• * R      =
L->• i      =
R->• L      $
L->• * R      $
L->• i      $

I1:
S'->S •     $

I2:
S->L • = R      $
R->L •     $

I3:
S->R •     $

I4:
L->i •     =
L->i •     $

I5:
L->* • R      =
L->* • R      $
R->• L      =
R->• L      $
L->• * R      =
L->• i      =
L->• * R      $
L->• i      $

I6:
S->L = • R      $
R->• L      $
L->• * R      $
L->• i      $

I7:
R->L •     =
R->L •     $

I8:
L->* R •     =
L->* R •     $

I9:
R->L •     $

I10:
S->L = R •     $

I11:
L->i •     $

I12:
L->* • R      $
R->• L      $
L->• * R      $
L->• i      $

I13:
L->* R •     $
 */
