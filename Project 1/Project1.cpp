#include<iostream>
using namespace std;

class Node{
    public:
    int rule_number=1;
    string data;
    string conditions;
    Node* next;

    Node(){
        rule_number = 1;
        data = "";
        conditions = "";
        next = NULL;
    }

    Node(int rule_number, string data, string conditions){
        this->rule_number = rule_number*10;
        this->data = data;
        this->conditions = conditions;
        this->next = NULL;
        
    }
};

class LinkedList{
    Node *head;

    public:
    LinkedList(){
        head = NULL;
    }

    void define_conclusionList(int rule_number, string Conclusion, string conditions){//10 ATTACK PROBLEM=0
        Node *newNode = new Node(rule_number, Conclusion, conditions);
        if(head == NULL){
            head = newNode;
            return;
        }

        Node* temp = head;
        while(temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }


    Node* head_ret(){
        return head;
    }


    void print(){
        Node* temp = head;
        if(head == NULL){
        return;
        }
        while(temp != NULL){
            cout<<temp->rule_number<<" "<<temp->data<<" "<<temp->conditions;
            cout<<endl;
            temp = temp->next;
        }
    }   

    int search(Node* h, string variable){
        Node* temp = h;

        if(h == NULL){
        return -1;
        }
        while(temp->conditions != variable){
            
            temp = temp->next;
        }
        return temp->rule_number;
    } 
};

class Node_Var{
    public:
    string name;
    int instantiate;
    Node_Var* next;

    Node_Var(){
        name = "";
        instantiate = 0;
        next = NULL;
    }

    Node_Var(string name, int instantiate){
        this->name = name;
        this->instantiate = instantiate;
        this->next = NULL;
        
    }
};

class LinkedList_Var{
    Node_Var *head;

    public:
    LinkedList_Var(){
        head = NULL;
    }

    string variable_name(string name, int instantiate){
        Node_Var *newNode = new Node_Var(name, instantiate);

        Node_Var* temp = head;      
        if(temp == NULL){
            head = newNode;
            return head->name;
        }
        
        while(temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;

        return newNode->name;
    }

    
    void print_v(){
        Node_Var* temp = head;
        if(head == NULL){
        return;
        }
        while(temp != NULL){
            cout<<temp->name<<" "<<temp->instantiate<<endl;
            temp = temp->next;
        }
    }
};

class Node_Clause_var_List{
    public:
    int instantiate;
    string clause1;
    string clause2;
    string clause3;
    string clause4;
    Node_Clause_var_List* next;

    Node_Clause_var_List(){
        instantiate = 1;
        clause1 = "";
        clause2 = "";
        clause3 = "";
        clause4 = "";
        next = NULL;
    }

    Node_Clause_var_List(int instantiate, string clause1, string clause2, string clause3, string clause4){
        this->instantiate = instantiate;
        this->clause1 = clause1;
        this->clause2 = clause2;
        this->clause3 = clause3;
        this->clause4 = clause4;
        this->next = NULL;
        
    }
};

class LinkedList_Clause_Var_List{
    Node_Clause_var_List *head;

    public:
    LinkedList_Clause_Var_List(){
        head = NULL;
    }

    void define_conclusionList(int instantiate, string clause1, string clause2, string clause3, string clause4){//10 ATTACK PROBLEM=0
        Node_Clause_var_List *newNode = new Node_Clause_var_List(instantiate, clause1, clause2, clause3, clause4);
        if(head == NULL){
            head = newNode;
            return;
        }

        Node_Clause_var_List* temp = head;
        while(temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }


    Node_Clause_var_List* head_ret(){
        return head;
    }


    void print(){
        Node_Clause_var_List* temp = head;
        if(head == NULL){
        return;
        }
        while(temp != NULL){
            cout<<temp->instantiate<<"\n"<<temp->clause1<<"\n"<<temp->clause2<<"n"<<temp->clause3<<"\n"<<temp->clause4;
            cout<<endl;
            temp = temp->next;
        }
    }   
/*
int search(Node_Clause_var_List* h, string variable){
        Node_Clause_var_List* temp = h;

        if(h == NULL){
        return -1;
        }
        while(temp->conditions != variable){
            
            temp = temp->next;
        }
        return temp->rule_number;
    } 
*/
    
};

/*
class create_Conclusion_List{
    public:
    void set_Conclusion_Associated_with_Rule_Number(){

    }

    void set_Rule_Number(){
        
    }
    
};


int process(double x){
    return x;
}

int validate_R1(int a, string conclusion){
    process(9.0);
}
*/
void update_VL(int C1){
    int a;
    string conclusion;

    LinkedList_Clause_Var_List l_c_v;

//    validate_R1(a, conclusion);
}

void rule_to_clause(int R1){
    int C1;

    int clause_number = 4*(R1/10 -1) +1;
    cout<<"Clause Number "<<clause_number<<endl;
    update_VL(C1);

}

void search_con(Node* h, string variable){
    LinkedList l_s;

    int rule_number = l_s.search(h, variable);
    cout<<"Rule # "<<rule_number<<endl;
    
    rule_to_clause(rule_number);
    

}

void Identify_the_attack(){
    bool PROBLEM, SLOW, UNKNOWN_FILES, UNUSUAL_ACTIVITY;

    bool variable_response[4];
    cout<<"\nHAVING PROBLEMS? Press 1.\nNO PROBLEM? Press 0\n";

    cin>>variable_response[0];

    cout<<"Choose From Options that best describes your situation.";
    cout<<"\n----------------------------------------------------\n";

    cout<<"1.Slow? (0/1) ";
        cin>>variable_response[1];
    cout<<"\n2.Unknown Files? (0/1) ";
        cin>>variable_response[2];
    cout<<"\n3.Unusual Activity? (0/1) ";
        cin>>variable_response[3];    
    
    LinkedList l;

    LinkedList_Var l_v;

    l.define_conclusionList(1, "ATTACK", l_v.variable_name("PROBLEM", variable_response[0]));
    l.define_conclusionList(2, "ATTACK", l_v.variable_name("PROBLEM", variable_response[2]));
    l.define_conclusionList(3, "ATTACK_TYPE", l_v.variable_name("SLOW", variable_response[1]));

    Node* head = l.head_ret();
    
    cout<<"\nConclusion List\n";
    cout<<"\n----------------------------------------------------\n";
    l.print();

    cout<<"\nVariable List";
    cout<<"\n----------------------------------------------------\n";
    
    l_v.print_v();

    search_con(head, "PROBLEM");

}
/*
int prevention(){

    return 0;
}

int Attacks_BW(){

}

int Prevention_FW(){

}

*/

int main(){
    int n;
    cout<<"Press 1 to Explore Attacks\nPress 2 to Explore Prevention\n";
    cin>>n;   
    
    if(n == 1)
        Identify_the_attack();  
    //else prevention();

/*    Attacks_BW();
    Prevention_FW();

*/
    
}