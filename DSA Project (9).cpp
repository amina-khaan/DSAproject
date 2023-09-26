#include<iostream>
#include<fstream>
#include<string>
#include<deque>
#define MAX_VERTICES 500
#define PRIMS_VERTICES 9
using namespace std;
const int TABLE_SIZE =7000;
//                 AVL TREE
struct Node
{
	string age;
	string education;
	string experience;
	string gender;
	string job_title;
	string salary;
	
	Node *left;
	Node *right;
	int height;
	Node* next;
};
class AVLTREE
{
	public:
		int height(Node *N)
		{
			int leftH;
			int rightH;
			if(N==NULL)
			{
				return 0;
			}
			if(N->left==NULL)
			{
				leftH = 0;
			}
			else 
			{
				leftH = 1+N->left->height;
			}
			if(N->right==NULL)
			{
				rightH = 0;
			}
			else 
			{
				rightH = 1+N->right->height;
			}
			if(leftH > rightH)
			{
				return(leftH);
				return(rightH);
			}
		}
		int max(int a, int b)
		{
			if(a>b)
				return a;
			else
				return b;
		}
		Node* newNode(string age, string gender, string education, string experience, string job_title, string salary)
		{
			Node* node = new Node();
			node->age = age;
			node->gender = gender;
			node->education = education;
			node->experience = experience;
			node->job_title = job_title;
			node->salary = salary;
			node->left = NULL;
			node->right = NULL;
			node->height = 1; 
		
			return(node);
		}
		
		Node *rightRotate(Node *y)
		{
			Node *x = y->left;
			Node *T2 = x->right;
		
			x->right = y;
			y->left = T2;
		
			y->height = max(height(y->left),
							height(y->right)) + 1;
			x->height = max(height(x->left),
							height(x->right)) + 1;
		
			return x;
		}
		
		Node *leftRotate(Node *x)
		{
			Node *y = x->right;
			Node *T2 = y->left;
		
		
			y->left = x;
			x->right = T2;
		
		
			x->height = max(height(x->left),height(x->right)) + 1;
			y->height = max(height(y->left),height(y->right)) + 1;
		
			return y;
		}
		
		int getBalance(Node *T)
		{
			int leftH;
			int rightH;
			if(T==NULL)
			{
				return 0;
			}
			if(T->left==NULL)
			{
				leftH = 0;
			}
			else 
			{
				leftH = 1+T->left->height;
			}
			if(T->right==NULL)
			{
				rightH = 0;
			}
			else 
			{
				rightH = 1+T->right->height;
			}
			
			return (leftH - rightH);
		}
		Node* insertAVL(Node *node,string age, string gender, string education, string experience, string job_title, string salary)
		{
			if (node == NULL)
				return(newNode(age,gender,education,experience,job_title,salary));
		
			if (salary < node->salary)
				node->left = insertAVL(node->left,age,gender,education,experience,job_title,salary);
			else if (salary > node->salary)
				node->right = insertAVL(node->right,age,gender,education,experience,job_title,salary);
			else 
				return node;
			
		
			node->height = 1 + max(height(node->left),
								height(node->right));
			int balance = getBalance(node);
		
			if (balance > 1 && salary < node->left->salary)
				return rightRotate(node);
		
		
			if (balance < -1 && salary > node->right->salary)
				return leftRotate(node);
		
		
			if (balance > 1 && salary > node->left->salary)
			{
				node->left = leftRotate(node->left);
				return rightRotate(node);
			}
		
			if (balance < -1 && salary < node->right->salary)
			{
				node->right = rightRotate(node->right);
				return leftRotate(node);
			}
			
			return node;
		}
		void Display(Node* root)
		{
			if(root != NULL)
			{
				cout << root->age <<" "<< root->gender <<" "<< root->education <<" "<< root->job_title <<" "
				<< root->experience<<" "<<root->salary<<endl; 
				Display(root->left);
				Display(root->right);
			}
		}
};
//                BREADTH FIRST SEARCH and DEPTH FIRST SEARCH
class BFSDFS
{
private:
    int adjacencyMatrix[8][8];

public:
    BFSDFS() 
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                adjacencyMatrix[i][j] = 0;
            }
        }
    }

    void addEdge(int source, int destination, int salary)
    {
        adjacencyMatrix[source][destination] = salary;
        adjacencyMatrix[destination][source] = salary;
    }
    
    void printGraph()
    {
        for (int i = 0; i < 8; i++)
        {
            cout << "Vertex " << i << " connections: ";
            for (int j = 0; j < 8; j++)
            {
                if (adjacencyMatrix[i][j] != 0)
                {
                    cout << j << "(" << adjacencyMatrix[i][j] << ") ";
                }
            }
            cout << endl;
        }
    }

    void printMatrix()
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                cout << adjacencyMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    void bfsTraversal(int startVertex)
    {
        bool visited[8] = {false};
        deque<int> q;

        visited[startVertex] = true;
        q.push_back(startVertex);

        while (!q.empty())
        {
            int currentVertex = q.front();
            q.pop_front();

            cout << currentVertex << " ";

            for (int i = 0; i < 8; i++)
            {
                if (adjacencyMatrix[currentVertex][i] != 0 && !visited[i])
                {
                    visited[i] = true;
                    q.push_back(i);
                }
            }
        }
        cout << endl;
    }
    
    void dfsTraversal(int startVertex)
    {
        bool visited[8] = {false};
        deque<int> stack;

        stack.push_back(startVertex);

        while (!stack.empty())
        {
            int currentVertex = stack.back();
            stack.pop_back();

            if (!visited[currentVertex])
            {
                cout << currentVertex << " ";
                visited[currentVertex] = true;
            }
            for (int i = 8 - 1; i >= 0; i--)
            {
                if (adjacencyMatrix[currentVertex][i] != 0 && !visited[i])
                {
                    stack.push_back(i);
                }
            }
        }
        cout << endl;
    }

};

//                         BUBBLE SORT
class BubbleSort
{
	private:
		Node *head, *tail;
	public:
		BubbleSort()
		{
			head = tail = NULL;
		}
		void insert(string age,string gender,string education,string experience,string job_title,string salary)
		{
			Node *p = new Node;
			p->age = age;
			p->gender = gender;
			p->education = education;
			p->experience = experience;
			p->job_title = job_title;
			p->salary = salary;
			
			if(head==NULL)
			{
				head = tail = p;
				p->next=NULL;
			}
			else
			{
				tail->next = p;
				tail = p;
			}
		}
		void bubbleSort()
		{
			 if (head == NULL || head->next == NULL) 
			 {
            		return;  
        	}

	        bool sorted = false;
	        while (!sorted) {
	            sorted = true;
	            Node* current = head;
	            Node* prev = NULL;
	
	            while (current->next != NULL) 
				{
	                if (current->salary > current->next->salary) 
					{
	                    Node* nextNode = current->next;
	                    if (prev == NULL) {

	                        current->next = nextNode->next;
	                        nextNode->next = current;
	                        head = nextNode;
	                    } else {
	                        prev->next = nextNode;
	                        current->next = nextNode->next;
	                        nextNode->next = current;
	                    }
	                    current = nextNode;
	                    sorted = false;
	                }
	                prev = current;
	                current = current->next;
	            }
	        }
		}
		
		void display()
		{
			Node *temp = head;
			while(temp != NULL)
			{
				cout<<temp->age<<" "<<temp->education<<" "<<temp->experience<<" "<<temp->gender<<" "<<temp->job_title<<" "<<temp->salary<<endl;
				temp = temp->next;
			}
		}
	
};
//             SELECTION SORT
class SelectionSort
{
	private:
		Node *head, *tail;
	public:
		SelectionSort()
		{
			head = tail = NULL;	
		}	
		void insert(string age,string gender,string education, string experience, string job_title,string salary) 
		{
			Node *p = new Node;
			p->age = age;
			p->education = education;
			p->experience = experience;
			p->gender = gender;
			p->job_title = job_title;
			p->salary = salary;
			if(head==NULL)
			{
				head = tail = p;
				p->next=NULL;
			}
			else
			{
				tail->next = p;
				tail = p;
			}
		}
		void swapData(Node* node1, Node* node2) 
		{
		    string temp = node1->salary;
		    node1->salary = node2->salary;
		    node2->salary = temp;
		}
		void selectionSort() 
		{
		    Node* current = head;
		
		    while (current != NULL) {
		        Node* minNode = current;
		        Node* temp = current->next;
		
		        while (temp != NULL) 
				{
		            if (minNode->salary >  temp->salary) {
		                minNode = temp;
		            }
		            temp = temp->next;
		        }
		
		        swapData(current, minNode);
		        current = current->next;
		    }
		}
		void printList() 
		{
		    Node* current = head;
		    while (current != NULL) {
		        cout << current->age<< " "<<current->gender<<" "<<current->education<<" "<<current->experience<<" "<<current->job_title<<" "<<current->salary<<endl;;
		        current = current->next;
		    }
		    cout <<endl;
		}
};
//                INSERTION SORT
class InsertionSort
{
	private:
		Node *head, *tail;
	public:
		InsertionSort()
		{
			head = tail = NULL;
		}
		void insert(string age,string gender,string education, string experience, string job_title,string salary) 
		{
			Node *p = new Node;
			p->age = age;
			p->education = education;
			p->experience = experience;
			p->gender = gender;
			p->job_title = job_title;
			p->salary = salary;
			if(head==NULL)
			{
				head = tail = p;
				p->next=NULL;
			}
			else
			{
				tail->next = p;
				tail = p;
			}
		}
		void insertNode(Node*& head, Node* newNode) 
		{
    	if (head == NULL || newNode->salary < head->salary) 
		{
        	newNode->next = head;
       		head = newNode;
    	} 
		else 
		{
        	Node* current = head;
        	while (current->next != NULL && current->next->salary < newNode->salary)
			{
            	current = current->next;
        	}
        	newNode->next = current->next;
        	current->next = newNode;
    	}
}

	void insertionSort() 
	{
	    Node* sortedList = NULL;
	    Node* current = head;
	    while (current != NULL) {
	        Node* nextNode = current->next;
	        insertNode(sortedList, current);
	        current = nextNode;
	    }
	    head = sortedList;
	}

	void printList() {
	    Node* current = head;
	    while (current != NULL) {
	        cout << current->age<< " "<<current->gender<<" "<<current->education<<" "<<current->experience<<" "<<current->job_title<<" "<<current->salary<<endl;;
	        current = current->next;
	    }
	    cout <<endl;
	}

};
//                   LINEAR SEARCH
struct LSNode
{
	string age;
	string education;
	string experience;
	string gender;
	string job_title;
	string salary;
	LSNode* next;
	
    LSNode(string a, string g, string edu, string title, string exp, string s)
    {
        age = a;
        gender = g;
        education = edu;
        job_title = title;
        experience = exp;
        salary = s;
        LSNode* next = NULL;
    }
};

class LinkedList {
public:
    LSNode* head;
    LinkedList() {
        head = NULL;
    }
     void push(string age, string gender, string edu, string title, string exp, string sal)
    {
        LSNode* newNode = new LSNode(age, gender, edu, title, exp, sal);
		newNode->next = head;
		head = newNode;
	}

     bool search(string value) {
        LSNode* current = head;
        while (current != NULL) {
            if (current->salary == value ) {
                return true;
            }
            else
            {
            	current = current->next;
			}
        }
        return false;
    }
    void Display(string value) {
        LSNode* current = head;
        while (current != NULL) {
            if (current->salary == value) 
			{
               cout << current->age <<" "<< current->gender <<" "<< current->education <<" "<< current->job_title <<" "<< current->experience<<" "<<current->salary<<endl; 
               current= current->next;
			}
			else
			{
				current= current->next;
			 } 
			   
        }
    }
};

//                 Binary Search
struct BNode {
    string age;
    string education;
    string experience;
    string gender;
    string job_title;
    string salary;
    BNode* next;

    BNode(string a, string g, string edu, string title, string exp, string s) {
        age = a;
        gender = g;
        education = edu;
        job_title = title;
        experience = exp;
        salary = s;
        next = NULL;
    }
};

class BinarySearch {
public:
    BNode* head;
	    BinarySearch() {
	        head = NULL;
	        
	    }
	void push(string a, string g, string edu, string title, string exp, string s) {
        BNode* newNode = new BNode(a, g, edu, title, exp, s);
        newNode->next = head;
        head = newNode;
    }
   BNode* middle(BNode* first, BNode* last) 
   {
	    if (first == NULL) {
	        return NULL;
	    }
	    BNode* slow = first;
	    BNode* fast = first->next;

	    while (fast != last && fast != NULL) 
		{
	        fast = fast->next;
	        if (fast != last) {
	            slow = slow->next;
	            fast = fast->next;
	        }
	    }
   	 	return slow;
	}

		void binarySearch(BNode* head, string value) 
		{
		    BNode* start = head;
		    BNode* end = NULL;

		    while (end == NULL || start != end) 
			{
			        BNode* mid = middle(start, end);
			        if (mid == NULL) {
			            Display(mid,value);
			        } else if (mid->salary == value) {
			            Display(mid,value);
			        } else if (mid->salary < value) {
			        	
			            start = mid->next;
			            Display(start,value);
			        } else {
			            end = mid;
			            Display(end,value);
			        }
		    }
		}

	void Display(BNode* head, string value) {
	    BNode* current = head;
	    bool found = false;
	    if(head->salary==value)
	    {
	    	cout << current->age << " " << current->gender << " " << current->education << " " << current->job_title << " " << current->experience << " " << current->salary << endl;
	    	found = true;
		}
		else if(current==NULL)
		{
			cout<<"No value present at that node"<<endl;
		}
		else
		{
			 while (current != NULL)
			{
	        	if (current->salary == value) {
	            	cout << current->age << " " << current->gender << " " << current->education << " " << current->job_title << " " << current->experience << " " << current->salary << endl;
	            	found = true;
	        	}
	        	current = current->next;
	    	}
		}
		if(found)
		{
			cout<<"Data Found"<<endl;
			
		}
		else
		{
			cout<<"Data not Found"<<endl;
			
		}
	}

};
//                 PRIMS 
class Prims
{
	private:
		int adjacencyMatrix[PRIMS_VERTICES][PRIMS_VERTICES];
		int distance[PRIMS_VERTICES];
		bool visited[PRIMS_VERTICES];
		int parent[PRIMS_VERTICES];
		int cost;
	public:
		Prims()
		{
			for(int i=0;i<PRIMS_VERTICES;i++)
			{
				for (int j = 0; j < PRIMS_VERTICES; j++)
            	{
                	adjacencyMatrix[i][j] = 0;
            	}
			}
			cost = 0;
		}
		void addEdge(int source, int destination, int salary)
	    {
	        adjacencyMatrix[source][destination] = salary;
	        adjacencyMatrix[destination][source] = salary;
	    }
	    void primsMST()
	    {
	    	
	   	  	for (int i = 0; i < PRIMS_VERTICES; i++) 
			{
	        	distance[i] = INT_MAX;
	        	visited[i] = false;
    		}
    		distance[0] = 0;
    		parent[0] = -1;
    		for(int i=0;i<PRIMS_VERTICES;i++)
    		{
    			int u = minKey(distance,visited);
    			visited[u] = true;
    			
    			for(int j=0;j<PRIMS_VERTICES;j++)
    			{
    				if(adjacencyMatrix[u][j] != 0 && visited[j]==false && adjacencyMatrix[u][j] < distance[j])
    				{
    					parent[j] = u;
    					distance[j] = adjacencyMatrix[u][j];
					}
				}
			}
			
			printMST(parent, adjacencyMatrix);
		}
	    int minKey(int distance[], bool visited[])
	    {
	    	int min = INT_MAX;
	    	int minIndex = -1;
	    	for(int i=0;i<PRIMS_VERTICES;i++)
	    	{
	    		if(visited[i]==false && distance[i] < min)
	    		{
	    			min = distance[i];
	    			minIndex = i;
				}
	    		
			}
			return minIndex;
		}
		void printMST(int parent[], int adjacencyMatrix[PRIMS_VERTICES][PRIMS_VERTICES])
		{
			cout << "Edge   Weight\n";
    		for (int i = 1; i < PRIMS_VERTICES; i++)
    		{
        		cout << parent[i] << " - " << i << "    " << adjacencyMatrix[i][parent[i]] << "\n";
        		cost+= adjacencyMatrix[i][parent[i]];
        	}
        	cout<<"Cost = "<<cost<<endl;
		}
		void printMatrix()
	    {
	        for (int i = 0; i < PRIMS_VERTICES; i++)
	        {
	            for (int j = 0; j < PRIMS_VERTICES; j++)
	            {
	                cout << adjacencyMatrix[i][j] << " ";
	            }
	            cout << endl;
	        }
	    }
};
//            HASHTABLE
class HashTable {
private:
    Node* table[TABLE_SIZE];

public:
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = NULL;
        }
    }

    int hash1(const string& key) {
        int sum = 0;
        for (size_t i = 0; i < key.length(); i++) {
            sum += static_cast<int>(key[i]);
        }
        return sum % TABLE_SIZE;
    }

    void insert(Node* employee) {
        int index = hash1(employee->salary);

        while (table[index] != NULL) 
		{
            index = (index + 1) % TABLE_SIZE;
        }

        table[index] = employee;
        cout << "Employee with salary " << employee->salary << " inserted into the hash table." << endl;
    }

    void display() {
        cout << "Hash Table:" << endl;
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[i] != NULL) {
                cout << "Index " << i << ": " << "Age: " << table[i]->age << ", Gender: " << table[i]->gender << ", Education: " << table[i]->education << ", Job Title: " << table[i]->job_title << ", Experience: " << table[i]->experience << ", Salary: " << table[i]->salary << endl;
            }
        }
    }
};
//                   DIJKSTRA
class Graph
{
private:
    int adjacencyMatrix[8][8];

public:
    Graph() 
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                adjacencyMatrix[i][j] = 0;
            }
        }
    }

    void addEdge(int source, int destination, int weight)
    {
        adjacencyMatrix[source][destination] = weight;
        adjacencyMatrix[destination][source] = weight;
    }
    
    void printGraph()
    {
        for (int i = 0; i < 8; i++)
        {
            cout << "Vertex " << i << " connections: ";
            for (int j = 0; j < 8; j++)
            {
                if (adjacencyMatrix[i][j] != 0)
                {
                    cout << j << "(" << adjacencyMatrix[i][j] << ") ";
                }
            }
            cout << endl;
        }
    }

    void printMatrix()
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                cout << adjacencyMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    void dijkstra(int source)
    {
        int distance[8];
        bool visited[8];

        for (int i = 0; i < 8; i++)
        {
            distance[i] = INT_MAX;
            visited[i] = false;
        }

        distance[source] = 0;


        for (int i = 0; i < 8 - 1; i++)
        {
            
            int minDistance = INT_MAX;
            int minIndex = -1;
            for (int j = 0; j < 8; j++)
            {
                if (!visited[j] && distance[j] <= minDistance)
                {
                    minDistance = distance[j];
                    minIndex = j;
                }
            }

            visited[minIndex] = true;

            for (int j = 0; j < 8; j++)
            {
                if (!visited[j] && adjacencyMatrix[minIndex][j] != 0 &&  distance[minIndex] + adjacencyMatrix[minIndex][j] < distance[j])
                {
                    distance[j] = distance[minIndex] + adjacencyMatrix[minIndex][j];
                }
            }
        }

        cout << "Shortest distances from source vertex " << source << ":\n";
        for (int i = 0; i < 8; i++)
        {
            cout << "Vertex " << i << ": " << distance[i] << endl;
        }
    }
};
int main()
{
	AVLTREE AT;
	string age;
	string gender;
	string education;
	string job_title;
	string experience;
	string salary;
	
	Node *root = new Node;
			root = NULL;
	cout<<"Enter : "<<endl;
	cout<<"1  AVL TREE"<<endl;
	cout<<"2  BFS / DFS"<<endl;
	cout<<"3  BUBBLE SORT"<<endl;
	cout<<"4  SELECTION SORT"<<endl;
	cout<<"5  INSERTION SORT"<<endl;
	cout<<"6  LINEAR SEARCH"<<endl;
	cout<<"7  Binary SEARCH"<<endl;
	cout<<"8  PRIMS"<<endl;
	cout<<"9  HASHTABLE"<<endl;
	cout<<"10 DIJKSTRA"<<endl;
	cout<<"Enter your Choice = ";
	int n;
	cout<<endl;
	cin>>n;
	//                     AVL
	if(n==1)
	{
		int i=0;
		ifstream File;
		File.open("Salary_Data.csv");
		if(File.is_open())
		{
				while(!File.eof())
				{
					getline(File,age,',');
					getline(File,gender,',');
					getline(File,education,',');
					getline(File,job_title,',');
					getline(File,experience,',');
					getline(File,salary,'\n');
					root = AT.insertAVL(root,age,gender,education,experience,job_title,salary);
					AT.Display(root);
				}
			
			
			File.close();
			
		}
		else
		{
			cout<<"File is not opening";
		}	
	}
	else if(n==2)
	{
		BFSDFS b;
    	b.addEdge(0,1,90000);
	    b.addEdge(0,2,65000);
	    b.addEdge(1,2,150000);
	    b.addEdge(1,3,60000);
	    b.addEdge(3,4,200000);
	    b.addEdge(2,4,55000);
	    b.addEdge(2,5,120000);
	    b.addEdge(5,6,80000);
	    b.addEdge(4,6,45000);
	    b.addEdge(3,7,110000);
	    b.addEdge(6,7,75000);
	    b.addEdge(6,8,65000);
	    
	    b.printGraph();
	    cout << "BFS Traversal: ";
    	b.bfsTraversal(0);

    	cout << "DFS Traversal: ";
    	b.dfsTraversal(0);

	}
	else if(n==3)
	{
		BubbleSort BS;
		string age;
		string gender;
		string education;
		string job_title;
		string experience;
		string salary;
	
		ifstream File;
		File.open("Salary_Data.csv");
		if(File.is_open())
		{
			while(!File.eof())
			{
				getline(File,age,',');
				getline(File,gender,',');
				getline(File,education,',');
				getline(File,job_title,',');
				getline(File,experience,',');
				getline(File,salary,'\n');
				BS.insert(age,gender,education,experience,job_title,salary);
			}
			File.close();
		}
		BS.bubbleSort();
		BS.display();
	}
	else if(n==4)
	{
		
		SelectionSort ss;
		
		string age;
		string education;
		string experience;
		string gender;
		string job_title;
		string salary;

		ifstream File;
		File.open("Salary_Data.csv");
		if(File.is_open())
		{
				while(!File.eof())
				{
					getline(File,age,',');
					getline(File,gender,',');
					getline(File,education,',');
					getline(File,job_title,',');
					getline(File,experience,',');
					getline(File,salary,'\n');
					ss.insert(age,gender,education,experience,job_title,salary);
				}
			
			File.close();	
		}
		
		cout<<"After Selection Sort : "<<endl;
		ss.selectionSort();
		ss.printList();
	}
	else if(n==5)
	{
		InsertionSort is;
		
		string age;
		string education;
		string experience;
		string gender;
		string job_title;
		string salary;


		ifstream File;
		File.open("Salary_Data.csv");
		if(File.is_open())
		{
				while(!File.eof())
				{
					getline(File,age,',');
					getline(File,gender,',');
					getline(File,education,',');
					getline(File,job_title,',');
					getline(File,experience,',');
					getline(File,salary,'\n');
					is.insert(age,gender,education,experience,job_title,salary);
				}
			
			File.close();	
		}
		
		is.insertionSort();
		is.printList();
	}
	else if(n==6)
	{
		 LinkedList list;
    
		string age;
		string gender;
		string education;
		string job_title;
		string experience;
		string salary;
			 ifstream File;
        File.open("Salary_Data.csv");
        if (File.is_open()) {
            while (!File.eof()) {
                getline(File, age, ',');
                getline(File, gender, ',');
                getline(File, education, ',');
                getline(File, job_title, ',');
                getline(File, experience, ',');
                getline(File, salary, '\n');
                list.push(age, gender, education, job_title, experience, salary);
            }

            File.close();
        }
			string key;
		    cout << "Enter Salary to search data: ";
		    cin >> key;
		
		    list.search(key);
	}
	else if(n==7)
	{
		BinarySearch list;
    
		string age;
		string gender;
		string education;
		string job_title;
		string experience;
		string salary;
		
		BNode *head = NULL;
		ifstream File;
		File.open("Salary_Data.csv");
		if (File.is_open())
		{
			while (!File.eof())
			{
				getline(File, age, ',');
				getline(File, gender, ',');
				getline(File, education, ',');
				getline(File, job_title, ',');
				getline(File, experience, ',');
				getline(File, salary, '\n');
				list.push(age, gender, education, job_title, experience, salary);
			}
			
			File.close();
	    }
	    else {
       	    cout << "Failed to open file." << endl;
	    }
	
	    string key;
	    cout << "Enter Salary to search data: ";
	    cin >> key;
	
	    list.binarySearch(list.head, key);
	}
	else if(n==8)
	{
		Prims p;
	 	p.addEdge(0,1,90000);
	    p.addEdge(0,2,65000);
	    p.addEdge(1,2,150000);
	    p.addEdge(1,3,60000);
	    p.addEdge(2,4,55000);
	    p.addEdge(2,5,120000);
	    p.addEdge(3,4,200000);
	    p.addEdge(3,7,110000);
	    p.addEdge(4,6,45000);
	    p.addEdge(5,6,80000);
	    p.addEdge(6,7,75000);
	    p.addEdge(6,8,65000);
	    p.addEdge(7,8,140000);
	    
	    p.primsMST();
	}
	else if(n==9)
	{
		HashTable HT;
	    string age;
	    string gender;
	    string education;
	    string job_title;
	    string experience;
	    string salary;
		
		 ifstream File;
        File.open("Salary_Data.csv");
        if (File.is_open()) {
            while (!File.eof()) {
                string age, gender, education, job_title, experience, salary;
                getline(File, age, ',');
                getline(File, gender, ',');
                getline(File, education, ',');
                getline(File, job_title, ',');
                getline(File, experience, ',');
                getline(File, salary, '\n');

                Node* emp = new Node;
                emp->age = age;
                emp->gender = gender;
                emp->education = education;
                emp->job_title = job_title;
                emp->experience = experience;
                emp->salary = salary;

                HT.insert(emp);
            }
            File.close();
        }
        else {
            cout << "Failed to open the file." << endl;
        }
        HT.display();
	}
	else if(n==10)
	{
		Graph graph;

    	graph.addEdge(0,1,90000);
	    graph.addEdge(0,2,65000);
	    graph.addEdge(1,2,150000);
	    graph.addEdge(1,3,60000);
	    graph.addEdge(3,4,200000);
	    graph.addEdge(2,4,55000);
	    graph.addEdge(2,5,120000);
	    graph.addEdge(5,6,80000);
	    graph.addEdge(4,6,45000);
	    graph.addEdge(3,7,110000);
	    graph.addEdge(6,7,75000);
	    graph.addEdge(7,8,140000);
	    graph.addEdge(6,8,65000);

    // Print the graph
    graph.printGraph();


    	graph.dijkstra(0);
	
	}
	
}
