#include <iostream>
#include<bits/stdc++.h>
#include<fstream>

using namespace std;

struct Node 
{ 
    string key;
    //vector<string> key;
    int level;
    vector<Node *>child; 
    struct Node *prev;
}; 
   
Node *newNode(string key) 
{ 
    Node *temp = new Node; 
    temp->key = key; 
    temp->level = 0;
    return temp; 
} 
  
  
void LevelOrderTraversal(Node * root) 
{ 
    if (root==NULL) 
        return; 
   

    queue<Node *> q; 
    q.push(root); 
    int counter = -1;
    while (!q.empty()) 
    { 
        int n = q.size(); 
        counter++;

        while (n > 0) 
        { 

            Node * p = q.front(); 
            q.pop(); 
            //for(int i = 0;i<p->key.size();i++)
            //{
                cout << p->key <<endl;
            //}
             
 
            for (int i=0; i<p->child.size(); i++) 
                q.push(p->child[i]); 
                cout<<"\n---------------"<<endl;
            n--; 
        } 
   
        cout << "\nLevel========"<<counter<<endl; 
    } 
}


//Split String

vector<string> split(string strToSplit, char delimeter)
{
    stringstream ss(strToSplit);
    string item;
    vector<string> splittedStrings;
    while (getline(ss, item, delimeter))
    {
       splittedStrings.push_back(item);
    }
    return splittedStrings;
}



int main()
{
   string str = "";
   string line;
    while(std::getline(cin, line)){
        if (line.empty()){
            break;
        }
        str+=line;
    }
   cout<<str<<endl;
   cout<<"-----------------------------------"<<endl;
    stack<char> stack;
    list<int> l;
    vector<string> vvv;
    vvv.push_back("data");
    Node *root = newNode("data");
    Node *temp = root;
    int pos = str.find("{");
    int lpos = pos;
    stack.push('{');
    bool flag = true;
    int lvl=0;
    int aC = 0;
    for(int i=pos+1;i<str.length();i++)
    {
        
        if(str[i]=='{')
        { 
            //cout<<"dddddd + "<<endl;
            int len = i-lpos;
            string s = str.substr(lpos+1,len-1);
            vector<string> vv = split(s, ',');
            if(lvl==0)
            {
                for(int k=0;k<vv.size();k++)
                {
                    temp->child.push_back(newNode(vv[k]));
                    temp->prev = temp;
                }
                
                lvl++;
            }
            else
            {
                int lll = temp->level;
                //int lll = vv.size()-1;
                for(int k=0;k<vv.size();k++)
                {
                    (temp->child[lll]->child).push_back(newNode(vv[k]));
                    temp->child[lll]->prev = temp;
                }
                
                temp = temp->child[lll];
                if(vv.size()!=0)
                {
                    temp->level = temp->level+vv.size()-1;
                }
                
            }
            lpos = i;
            stack.push('{');
            l.push_back(i);
            flag = true;
        }
        else if(str[i] == '[')
        { 
            //cout<<"1111111111111 + "<<endl;
            int len = i-lpos;
            string s = str.substr(lpos+1,len-1);
            vector<string> vv = split(s, ',');
            //Node *c = newNode(vv);
            if(lvl==0)
            {
                for(int k=0;k<vv.size();k++)
                {
                    temp->child.push_back(newNode(vv[k]));
                    temp->prev = temp;
                }
                lvl++;
            }
            else
            {
                int lll = temp->level;
                
                for(int k=0;k<vv.size();k++)
                {
                    (temp->child[lll]->child).push_back(newNode(vv[k]));
                    temp->child[lll]->prev = temp;
                }
                temp = temp->child[lll];
                aC = vv.size()-1;
            }
            lpos = i;
            stack.push('[');
            l.push_back(i);
            flag = true;
        }
        
        else if(str[i] == ']')
        {
            //cout<<"2222222222222 + "<<endl;
            int len = i-l.back();
            string s = str.substr(l.back()+1,len-1);
            vector<string> vv = split(s, ',');
            //Node *c = newNode(vv);
            if(!l.empty())
            {
                l.pop_back();
            }
            stack.pop();
            
            if(lvl==0)
            {
                for(int k=0;k<vv.size();k++)
                {
                    temp->child.push_back(newNode(vv[k]));
                    temp->prev = temp;
                } 
                lvl++;
            }
            else
            {
                if(flag)
                {
                    int lll = temp->level;
                    //cout<<"oiuytr + "<<temp->key<<"  "<<temp->child.size()<<endl;
                    
                    for(int k=0;k<vv.size();k++)
                    {
                        (temp->child[aC]->child).push_back(newNode(vv[k]));
                        temp->child[aC]->prev = temp;
                    }
                    //cout<<"wewre + "<<endl;
                    temp = temp->prev;
                }
            }
            
            lpos = i+1;
            if(i+1 !=str.length() && str[i+1]==',')
            {
                flag =true;
            }
            else
            {
                flag = false;
            }
            l.push_back(i+1);
            
        }
        
        
        
        else if(str[i] == '}')
        {
            //cout<<"eeeeeeeeeeeee + "<<endl;
            int len = i-l.back();
            string s = str.substr(l.back()+1,len-1);
            vector<string> vv = split(s, ',');
            //Node *c = newNode(vv);
            if(!l.empty())
            {
                l.pop_back();
            }
            stack.pop();
            
            
            if(i+1 !=str.length() && str[i+1]==',')
            {
                if(flag)
                {
                        int lll = temp->level;
                        for(int k=0;k<vv.size();k++)
                        {
                            (temp->child[lll]->child).push_back(newNode(vv[k]));
                            temp->child[lll]->prev = temp;
                        }
                        temp->level = temp->level+1;
                        temp = temp->prev;
                        //temp->level = temp->level+1;
                        lpos = i+1;
                }
                else
                {
                    temp->level = temp->level+1;
                    temp = temp->prev;
                    lpos = i+1;
                }
                
            }
            else
            {
            
                if(lvl==0)
                {
                    for(int k=0;k<vv.size();k++)
                    {
                        temp->child.push_back(newNode(vv[k]));
                        temp->prev = temp;
                    }
                    lvl++;
                }
                else
                {
                    if(flag)
                    {
                        int lll = temp->level;
                        for(int k=0;k<vv.size();k++)
                        {
                            (temp->child[lll]->child).push_back(newNode(vv[k]));
                            temp->child[lll]->prev = temp;
                        }
                        temp = temp->prev;
                    }
                }
            }
            flag = false;
        }
    }
    
    cout << "\nLevel order traversal Before Mirroring\n"; 
    LevelOrderTraversal(root);
    
    cout<<root->child[0]->child[2]->child[0]->child[1]->child[0]->key<<endl;

   return 0;
}
