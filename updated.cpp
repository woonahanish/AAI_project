#include<iostream>
using namespace std;

class Node{
    public:
    int rule_number=1;
    string data;
    string conditions1;
    string conditions2;
    string conditions3;
    int response1;
    int response2;
    int response3;
    int result;
    Node* next;

    Node(){
        rule_number = 1;
        data = "";
        conditions1 = "";
        response1 = 0;
        response2 = 0;
        response3 = 0;
        result = 0;
        next = NULL;
    }

    Node(int rule_number, string data, string conditions1, string conditions2, string conditions3, int response1, int response2, int response3, int result){
        this->rule_number = rule_number*10;
        this->data = data;
        this->conditions1 = conditions1;
        this->conditions2 = conditions2;
        this->conditions3 = conditions3;
        this->response1 = response1;
        this->response2 = response2;
        this->response3 = response3;
        this->result = result;
        this->next = NULL;
        
    }
};

class LinkedList{
    Node *head;

    public:
    LinkedList(){
        head = NULL;
    }

    void define_conclusionList(int rule_number, string Conclusion, string conditions1, string conditions2, string conditions3, int response1, int response2, int response3){//10 ATTACK PROBLEM=0
        int result = response1;
        if(conditions2 == "" && conditions3 == "")
            result = response1;
        else if(conditions2 != "" && conditions3 == "")
            result = response1 || response2;
        else if(conditions2 != "" && conditions3 != ""){
                result = response1 || response2 || response3;
            if(response1 == 1 && response2 == 1 && response3 ==1)
                result = 5;
            }
        
        Node *newNode = new Node(rule_number, Conclusion, conditions1, conditions2, conditions3, response1, response2, response3, result);
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

    int rule_num_ret(int position){
        Node* temp = head;
        int count=1;

        if(position == 1)
            return temp->rule_number;
        else{
            while(position != count){
                temp = temp->next;
                count++;
            }
        }
        return temp->rule_number;
    }

    string ret_conditions(int rule_num){
        Node* temp = head;
        while(temp->rule_number != rule_num){
            temp = temp->next;
        }
        if(temp->conditions2 == "" && temp->conditions3 == "")
            return temp->conditions1;
    }

    void print(){
        Node* temp = head;
        if(head == NULL){
        return;
        }
        while(temp != NULL){
            if(temp->conditions2 == "" && temp->conditions3 == ""){
            cout<<temp->rule_number<<" "<<temp->data<<" "<<" IF "<<temp->conditions1<<" = "<<temp->response1<<" THEN "<<temp->data<<" = "<<temp->result;
            cout<<endl;
            } else{
                if(temp->conditions2 != "" && temp->conditions3 == ""){
                    cout<<temp->rule_number<<" "<<temp->data<<" "<<" IF "<<temp->conditions1<<" = "<<temp->response1<<" AND "<<temp->conditions2<<" = "<<temp->response2<<" THEN "<<temp->data<<" = "<<temp->result;
                    cout<<endl;
                } else{
                    cout<<temp->rule_number<<" "<<temp->data<<" "<<" IF "<<temp->conditions1<<" = "<<temp->response1<<" AND "<<temp->conditions2<<" = "<<temp->response2<<" AND "<<temp->conditions3<<" = "<<temp->response3<<" THEN "<<temp->data<<" = "<<temp->result;
                    cout<<endl;
                }
            }
            temp = temp->next;
        }
    }   

    int search(Node* h, string variable){
        Node* temp = h;

        if(h == NULL){
        return -1;
        }
        while(temp->data != variable){
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
    Node_Var* ret_head(){
        return head;
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

    void search(int C1, Node_Var* head_clause){

        Node_Var* temp = head_clause;
        cout<<C1<<endl;
        cout<<temp->name;
    }
};

class Node_Clause_var_List{
    public:
    int srl;
    string clause;
    Node_Clause_var_List* next;

    Node_Clause_var_List(){
        srl = 1;
        clause = "";
        next = NULL;
    }

    Node_Clause_var_List(int srl, string clause){
        this->srl = srl;
        this->clause = clause;
        this->next = NULL;
        
    }
};

class LinkedList_Clause_Var_List{
    Node_Clause_var_List *head_clause;

    public:
    LinkedList_Clause_Var_List(){
        head_clause = NULL;
    }

    void define_clause_var_list(int srl, string clause){
        Node_Clause_var_List *newNode = new Node_Clause_var_List(srl, clause);
        if(head_clause == NULL){
            head_clause = newNode;
            return;
        }

        Node_Clause_var_List* temp = head_clause;
        while(temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }

    Node_Clause_var_List *ret_head(){
        return head_clause;
    }

    void print_clause_var_list(){
        Node_Clause_var_List* temp = head_clause;
        if(head_clause == NULL){
            return;
        }
        while(temp != NULL){
            cout<<temp->srl<<" "<<temp->clause<<endl;
            temp = temp->next;
        }
    }/*    
    Node_Clause_var_List *search(int C1, Node_Clause_var_List *head_clause){
        Node_Clause_var_List *temp = head_clause;
        int c=1;
        for(int i_c=0; i_c<4; i_c++){
            if(c == C1){
                check_instantiation(temp->, head_clause);
            }else{
                c++;
                temp = temp->next;
            }
        }
        return temp;
    } 

    Node_Clause_var_List *check_instantiation(int C1, Node_Clause_var_List *head_clause){
        Node_Clause_var_List *temp = head_clause;
        
    } */ 
};

/*
int process(double x){
    return x;
}

int validate_R1(int a, string conclusion){
    process(9.0);
}
*/
void update_VL(int C1, Node_Var *head_clause){ 
    LinkedList_Var l_ins;
    //Node_Clause_var_List *head_clause = 

    l_ins.search(C1, head_clause);
//    validate_R1(a, conclusion);
}

void rule_to_clause(int R1, Node_Var *head_clause){
    int C1;

    int clause_number = 4*(R1/10 -1) +1;
    cout<<"Clause Number "<<clause_number<<endl;
    update_VL(clause_number, head_clause);
}

void search_con(Node* h, string variable, Node_Var *head_clause){
    LinkedList l_s;

    int rule_number = l_s.search(h, variable);
    cout<<"Rule # "<<rule_number<<endl;
    
    rule_to_clause(rule_number, head_clause);
}

void Identify_the_attack(){

    int var_response_n=0, var_response_y=1;
    bool variable_response[4];
    cout<<"\nHAVING PROBLEMS? Press 1.\nNO PROBLEM? Press 0\n";

    cin>>variable_response[0];
/*
    cout<<"Choose From Options that best describes your situation.";
    cout<<"\n----------------------------------------------------\n";

    cout<<"1.Slow? (0/1) ";
        cin>>variable_response[1];
    cout<<"\n2.Unknown Files? (0/1) ";
        cin>>variable_response[2];
    cout<<"\n3.Unusual Activity? (0/1) ";
        cin>>variable_response[3];  

*/    
    LinkedList l;

    l.define_conclusionList(1, "ATTACK", "PROBLEM", "", "", var_response_n, var_response_n, var_response_n);
    l.define_conclusionList(2, "ATTACK", "PROBLEM", "", "", var_response_y, var_response_n, var_response_n);
    l.define_conclusionList(3, "ATTACK", "PROBLEM", "SLOW", "", var_response_y, var_response_n, var_response_n);
    l.define_conclusionList(4, "ATTACK", "PROBLEM", "SLOW", "", var_response_y, var_response_y, var_response_n);
    l.define_conclusionList(5, "ATTACK_TYPE", "PROBLEM", "SLOW", "UNNECESSARY RUNNING PROCESSOR", var_response_y, var_response_y, var_response_n);
    l.define_conclusionList(6, "ATTACK_TYPE", "PROBLEM", "SLOW", "UNNECESSARY RUNNING PROCESSOR", var_response_y, var_response_y, var_response_y);

    Node* head = l.head_ret();
    
    cout<<"\nConclusion List\n";
    cout<<"\n----------------------------------------------------\n";
    l.print();

    LinkedList_Var l_v;
    l_v.variable_name("PROBLEM", variable_response[0]);
    l_v.variable_name("SLOW", 1);//variable_response[2]);
    l_v.variable_name("UNNECESSARY RUNNING PROCESSOR", 1);

    cout<<"\nVariable List";
    cout<<"\n----------------------------------------------------\n";
    
    l_v.print_v();

    LinkedList_Clause_Var_List l_c_var;
    int srl =0;
    Node* temp = head; 
    for(int j=1; j<=6; j++){    
        l_c_var.define_clause_var_list(++srl, temp->conditions1);
        l_c_var.define_clause_var_list(++srl, temp->conditions2);
        l_c_var.define_clause_var_list(++srl, temp->conditions3);
        l_c_var.define_clause_var_list(++srl, "");

        if(temp->next != NULL)
            temp = temp->next;
    }
    cout<<"\nClause Variable List";
    cout<<"\n----------------------------------------------------\n";
    l_c_var.print_clause_var_list();
    Node_Var *head_clause = l_v.ret_head();

    search_con(head, "ATTACK", head_clause);

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
