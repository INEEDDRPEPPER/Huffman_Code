#include <iostream>
#include <fstream>

using namespace std;

class Node
{
public:
    Node()
    {
        weight=0;
        symbol=' ';
        left=-1;
        right=-1;
        parent=-1;
    }

    int weight;
    char symbol;

    int left;
    int right;
    int parent;
};

class HuffmanTree
{
private:
    int root;
    int weight[62];
    char symbol[62];
    int numofsymbol;
    int numofnode;
    Node tree[123];


public:
    HuffmanTree()
    {
        root=0;
        for (int i=0;i<62;i++)
            weight[i]=0;
        for (int i=0;i<62;i++)
            symbol[i]=' ';
        numofsymbol=0;
        numofnode=0;

    }

    void setTree(int frequency[],int numofletter,char letter[])
    {
        numofsymbol=numofletter;
        for (int i=0;i<numofsymbol;i++)
        {
            weight[i]=frequency[i];
            symbol[i]=letter[i];
        }
    }

    void build(int n)
    {
            int numofequal=0;
            int index[2];
            index[0]=-1;
            index[1]=-1;
            for (int i=0;i<numofnode;i++)
            {
                if (tree[i].weight==weight[n] && tree[i].left!=-1 && tree[i].right!=-1 && tree[i].parent==-1)
                {
                    index[0]=i;
                    numofequal++;
                    break;
                }
            }

            for (int i=0;i<numofnode;i++)
            {
                if (tree[i].weight==weight[n-1] && tree[i].left!=-1 && tree[i].right!=-1 && i!=index[0] && tree[i].parent==-1)
                {
                    index[1]=i;
                    numofequal++;
                    break;
                }
            }
            if (numofequal==0)
            {
                tree[numofnode].symbol=symbol[n];
                tree[numofnode].parent=numofnode+2;
                tree[numofnode].weight=weight[n];
                tree[numofnode+1].symbol=symbol[n-1];
                tree[numofnode+1].parent=numofnode+2;
                tree[numofnode+1].weight=weight[n];
                tree[numofnode+2].left=numofnode+1;
                tree[numofnode+2].right=numofnode;
                tree[numofnode+2].weight=weight[n]+weight[n-1];
                numofnode=numofnode+3;
            }
            else if (numofequal==1)
            {
                if (index[0]!=-1)
                {
                    tree[numofnode].symbol=symbol[n-1];
                    tree[numofnode].parent=numofnode+1;
                    tree[numofnode].weight=weight[n-1];
                    tree[numofnode+1].right=index[0];
                    tree[index[0]].parent=numofnode+1;
                    tree[numofnode+1].left=numofnode;
                }

                else if (index[1]!=-1)
                {
                    tree[numofnode].symbol=symbol[n];
                    tree[numofnode].parent=numofnode+1;
                    tree[numofnode].weight=weight[n];
                    tree[numofnode+1].left=index[1];
                    tree[index[1]].parent=numofnode+1;
                    tree[numofnode+1].right=numofnode;
                }
                tree[numofnode+1].weight=weight[n]+weight[n-1];
                numofnode=numofnode+2;
            }
            else
            {
                tree[index[0]].parent=numofnode;
                tree[index[1]].parent=numofnode;
                tree[numofnode].right=index[0];
                tree[numofnode].left=index[1];
                tree[numofnode].weight=weight[n]+weight[n-1];
                numofnode++;
            }





        weight[n-1]+=weight[n];
        for (int i=n-1;i>0;i--)
        {
            if (weight[i]>weight[i-1])
            {
                int temp=weight[i];
                weight[i]=weight[i-1];
                weight[i-1]=temp;

                char temp1=symbol[i];
                symbol[i]=symbol[i-1];
                symbol[i-1]=temp1;
            }
        }
        n--;

        if (n==0)
            return;
        build(n);
    }

    void display()
    {
        for (int i=0;i<2*numofsymbol-1;i++)
        {
            cout<<tree[i].symbol<<" "<<tree[i].weight<<endl;
        }
    }

    string getCode(char ch)
    {
        if (ch==' ')
            return "There is not this symbol\n";
        for (int i=0;i<numofnode;i++)
        {
            string str="";
            if (tree[i].symbol==ch)
            {
                int j=i;
                while (tree[j].parent!=-1)
                {
                    if (tree[tree[j].parent].left==j)
                        str="0"+str;
                    if (tree[tree[j].parent].right==j)
                        str="1"+str;
                    j=tree[j].parent;
                }
                return str;
            }
        }
        return "There is not this symbol\n";
    }
};


int main()
{
    ifstream infile;
    infile.open("infile.dat");
    if (!infile)
    {
        cout << "The store data is not existing!";
        return 0;
    }
    char ch[100000];
    for (int i=0;i<100000;i++)
        ch[i]=' ';

    int n=0;
    char c;
    while(infile>>c)
    {
        if ((c>=48 && c<=57) || (c>=65 && c<=90) || (c>=97 && c<=122))
        {
            ch[n]=c;
            n++;
        }
    }

    if(n<2)
    {
        cout<<"Cannot build a Huffman tree"<<endl;
        return 0;
    }
    char letter[62];
    int frequency[62];
    for (int i=0;i<62;i++)
    {
        frequency[i]=0;
    }

    int numofletter=0;
    for (int i=0;i<n;i++)
    {
        bool isnew=true;
        for (int j=0;j<numofletter;j++)
        {
            if (letter[j]==ch[i])
                isnew=false;
        }
        if (isnew==true)
        {
            numofletter++;
            letter[numofletter-1]=ch[i];
        }
    }

    for (int i=0;i<numofletter;i++)
    {
        for (int j=0;j<n;j++)
        {
            if (letter[i]==ch[j])
                frequency[i]++;
        }
    }


    for (int pass=0;pass<numofletter-1;pass++)
    {
        int swapCount=0;
        for (int i=0;i<numofletter-1;i++)
        {
            if (frequency[i]<frequency[i+1])
            {
                int temp=frequency[i];
                frequency[i]=frequency[i+1];
                frequency[i+1]=temp;

                char temp1=letter[i];
                letter[i]=letter[i+1];
                letter[i+1]=temp1;

                swapCount++;
            }
        }
        if (swapCount==0)
            break;
    }

    ofstream outfile;
    outfile.open("outfile.dat");

    outfile<<"symbol frequency\n";
    for (int i=0;i<numofletter;i++)
    {
        outfile<<letter[i]<<", ";
        double f= double(frequency[i])/n;
        int fr=int (f*1000+0.5);
        f=double (fr)/10;
        outfile<<f<<"%\n";
    }

    HuffmanTree tree;
    tree.setTree(frequency,numofletter,letter);
    tree.build(numofletter-1);
    outfile<<"\n";

    int numofbits=0;
    for (int i=0;i<numofletter;i++)
    {
        outfile<<letter[i]<<", ";
        outfile<<tree.getCode(letter[i])<<"\n";
        numofbits+=frequency[i]*tree.getCode(letter[i]).length();
    }

    outfile<<"Length: "<<numofbits;
    outfile.close();

    return 0;
}
