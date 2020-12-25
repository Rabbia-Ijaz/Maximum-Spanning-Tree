#include <iostream>
#include "string.h"
#include <fstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include<numeric>
using namespace std;
#include <iostream>
#include <string>
//const int total = 5;
const int long total=193037;//8;
const int long edge=790433;//6;
class Node
{
public:
	int id;
	int weight;
	Node* next;
	string name;
	Node(int ID,string NAME) {
		name=NAME;
		id = ID;
		next = NULL;
		weight = 0;
	}

	void displayNode()
	{
		cout << id <<" "<<name<< " " << weight;
	}
};

class Graph {
public:
	Node** nodeArray;
	int p;
	Graph() 
	{
		nodeArray = new Node * [total+1];
		p = 1;
	}

	void insert(int SRC,int DEST, int WEI)
	{
		Node* temp = nodeArray[SRC];
		Node* newNode = new Node(nodeArray[DEST]->id, nodeArray[DEST]->name);
		newNode->weight = WEI;
		newNode->next = temp->next;
		temp->next = newNode;
	}

	void insertNode(int ID,string Name)
	{
		Node* newNode = new Node(ID,Name);
		nodeArray[p] = newNode;
		p++;
	}

	void printNeighbors(int i)
	{
		Node* temp = nodeArray[i];
		while (temp)
		{
			temp->displayNode();
			cout << " --- ";
			temp = temp->next;
		}
		cout << endl;
	}

	void printNodes()
	{
		for (int i = 1; i <= total; ++i)
		{
			nodeArray[i]->displayNode();
			cout << endl;

		}
		cout << "************* Nodes printed successfully ************* " << endl << endl;
	}

	void printAllNodeNeighbors()
	{
		for(int i=1;i<=total;++i)
		{
			printNeighbors(i);
		}
		cout<<"************* All Nodes Neighbours printed successfully ************* "<<endl<<endl;
	}

	int maxKey(int key[], bool mstSet[])
	{
		// Initialize min value  
		int max = -1, max_index;

		for (int v = 1; v < total+1; v++)
			if (mstSet[v] == false && key[v] > max)
				max = key[v], max_index = v;

		return max_index;
	}

	void print(int parent[],int keys[])
	{
		cout << "Edge    Weight "<<endl;
		for (int i = 1; i < total+1; i++)
		{
			cout<< parent[i]<<" - "<<i << "   "<< keys[i]<<endl;
		}
	}

	void prim()
	{
		cout<<"Prim start "<<endl;
		int parent[total+1];
		int key[total+1];
		bool mstSet[total+1];
		int sum=0;
		// Initialize all keys as minimum
		for (int i = 0; i <= total; i++)
			key[i] = 0, mstSet[i] = false;

		// Always include first 1st vertex in MST.  
		// Make key 0 so that this vertex is picked as first vertex.  
		key[1] = 1;
		parent[1] = -1; // First node is always root of MST

		for(int count=0;count<total-1;++count)
		{
			//cout<<"hey"<<endl;
			int max_index=maxKey(key,mstSet);
			if(max_index>0 and max_index<=total)
			{
				mstSet[max_index]=true;
				//updating neighbours
				Node* newNode= nodeArray[max_index];
				int p=newNode->id;
				while(newNode->next)
				{
					if(mstSet[newNode->next->id]==false && newNode->next->weight>key[newNode->next->id])
					{
						key[newNode->next->id]=newNode->next->weight;
						parent[newNode->next->id]=p;
					}
					newNode=newNode->next;
				}
			}



		} 

		//print(parent, key);
		sum=accumulate(key,key+(total+1),total+1);
		cout<<"SUM: "<<sum<<endl;
	}
	void ReadNodes()
	{
		string line;
		ifstream infile;
		infile.open("G:/UNIVERSITY/6th Semester/Algorithms/AlgoProject/Algo/coauth-DBLP-node-labels.txt");
		if(infile.is_open())
		{
			int b=0;
			 while(/*!infile.eof()*/ b<=total) // To get you all the lines.
			 {
				b++;
				getline(infile,line); // Saves the line in STRING.
				//cout<<line<<endl; // Prints our STRING.

				int len=line.length();
				string ID="";
				string NAME="";
				bool num=false;

				for(int i=0;i<len;++i)
				{
					if(num==false)
					{
						if(line[i]!=' ')
						{
						   ID=ID+line[i];
						}
						else
						{
							num=true;
						}

					}
					else
					{
						NAME=NAME+line[i];
					}
				}
				//cout<<ID<<" "<<NAME<<endl;
				int id=atoi(ID.c_str());
				insertNode(id,NAME);
			 }
		}
		infile.close();
		cout<<"Nodes file read successfully "<<endl;
	}

	void ReadEdges()
	{
		string line2;
		ifstream infile2;
		infile2.open("G:/UNIVERSITY/6th Semester/Algorithms/AlgoProject/Algo/coauth-DBLP-proj-graph.txt");
		if(infile2.is_open())
		{
			int b=0;
			 while(b!=edge) // To get you all the lines.
			 {
				getline(infile2,line2); // Saves the line in STRING.
				//cout<<line<<endl; // Prints our STRING.

				int len=line2.length();
				string SRC="";
				string DEST="";
				string weight="";
				bool num=false;
				bool num2=false;

				for(int i=0;i<len;++i)
				{
					if(num==false)
					{
						if(line2[i]!=' ')
						{
						   SRC=SRC+line2[i];
						}
						else
						{
							num=true;
						}

					}
					else if(num2==false && num==true)
					{
						if(line2[i]!=' ')
						{
						   DEST=DEST+line2[i];
						}
						else
						{
							num2=true;
						}
					}
					else if(num2==true && num==true)
					{
						weight=weight+line2[i];
					}
				}
				int src=atoi(SRC.c_str());
				int dest=atoi(DEST.c_str());
				int wei=atoi(weight.c_str());
				//cout<<src<<" "<<dest<<" "<<weight<<endl;
				//WEIGHTS[b][0]=wei;
				if(src>0 && src<p && dest >0 && dest<p)
				{
					insert(src,dest,wei);
				    insert(dest,src,wei);
				}
				
				b++;
			 }
		}
		infile2.close();
		cout<<"Edges file read successfully "<<endl;
	}
	void ReadEdge()
	{
		fstream file;
		string SRC,DEST,WEI;
		file.open("coauth-DBLP-proj-graph.txt");
		int b = 0;
		while (b < edge)
		{
			file >> SRC;
			file >> DEST;
			file >> WEI;
			int src = atoi(SRC.c_str());
			int dest = atoi(DEST.c_str());
			int wei = atoi(WEI.c_str());
			if (src > 0 && src < p && dest >0 && dest < p)
			{
				insert(src, dest, wei);
				insert(dest, src, wei);
			}
			b++;
		}
		cout << "Edges file read successfully " << endl;
		//file.close();
	}
	void ReadNode()
	{
		fstream file;
		string ID,temp;
		file.open("coauth-DBLP-node-labels.txt");
		int b = 0;
		file >> ID;
		while (b < total)
		{
			string NAME;

			file >> temp;
			while(atoi(temp.c_str())==0)
			{
				NAME=NAME+" "+temp;
				file>>temp;
			}
			int id = atoi(ID.c_str());
			insertNode(id,NAME);
			//cout<<id <<" "<<NAME<<endl;
			ID=temp;
			b++;
		}
			cout << "Node file read successfully " << endl;
			//file.close();
	}

};

int main()
{
	Graph L;


	L.ReadNode();
	L.ReadEdge();
	//L.printNeighbors(1);
	//L.printAllNodeNeighbors();
	L.prim();
}
