#include<iostream>
using namespace std;

class Node{
    public:
    string data;
    int rule_number;
    Node* next;

    Node(){
        data = "";
        rule_number = 1;
        next = NULL;
    }

    Node(string data, int rule_number){
        this->data = data;
        this->rule_number = rule_number*10;
        this->next = NULL;
    }
};

class LinkedList{
    Node *head;

    public:
    LinkedList(){
        head = NULL;
    }

void print(){
    Node* temp = head;

    if(head == NULL){
        cout<<"EMPTY";
        return;
    }

    while(temp != NULL){
        cout<<temp->data<<" ";
        cout<<temp->rule_number<<endl;
        temp = temp->next;
    }

}
    void define_conclusionList(string Conclusion, int rule_number){
       // cout<<"Rule Number "<<rule_number<<endl;
        Node *newNode = new Node(Conclusion, rule_number);
        if(head == NULL){
            head = newNode;
            return;
        }

        Node* temp = head;
        while(temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }
};


class NodeVar{
    public:
    string data;
    int Instantiate;
    NodeVar* next;

    NodeVar(){
        data = "";
        Instantiate = 1;
        next = NULL;
    }

    NodeVar(string data){
        this->data = data;
        this->Instantiate = Instantiate*10;
        this->next = NULL;
    }
};

class LinkedListVar{
    NodeVar *head;

    public:
    LinkedListVar(){
        head = NULL;
    }

    void define_variableList(string Conclusion, int Instantiate){
        NodeVar *newNode = new NodeVar(Conclusion);
        if(head == NULL){
            head = newNode;
            return;
        }

        NodeVar* temp = head;
        while(temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }
};

int process(double x){
    return x;
}

int validate_R1(int a, string conclusion){
    process(9.0);
}

int update_VL(int C1){
    int a;
    string conclusion;

    validate_R1(a, conclusion);
}

int rule_to_clause(int R1){
    int C1;
    update_VL(C1);

}

int search_con(double x){

    int R1;
    rule_to_clause(R1);

}

int Identify_the_attack(int n){
    int x;



    search_con(x);

}

int prevention(){

    return 0;
}

int Attacks_BW(){

}

int Prevention_FW(){

}



int main(){

    LinkedList l;
    //here

    l.define_conclusionList("ATTACK", 1);
    l.define_conclusionList("ATTACK", 2);
    l.define_conclusionList("ATTACK_TYPE", 3);

    l.print();
//here


    LinkedListVar l_v;
    l_v.define_variableList("PROBLEM", NULL);
    l_v.define_variableList("SLOW", NULL);
    

    bool variable_response[4];
    cout<<"\nHAVING PROBLEMS? Press 1.\nNO PROBLEM? Press 0\n";
    cout<<"\n----------------------------------------------------\n";

    cin>>variable_response[0];

    cout<<"Choose From Options that best describes your situation.";
    cout<<"\n----------------------------------------------------\n";

    cout<<"1.Slow? ";
        cin>>variable_response[1];
    cout<<"\n2.Unknown Files? ";
        cin>>variable_response[2];
    cout<<"\n3.Unusual Activity? ";
        cin>>variable_response[3];
    
    Identify_the_attack(variable_response[0]);
    prevention();

    Attacks_BW();
    Prevention_FW();
}