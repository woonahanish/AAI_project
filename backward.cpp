#include<iostream>
using namespace std;

bool variable_response[5];
int var_n=0;

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
                result = 1;
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

    Node* searchThen(string clause_then, Node* h){//ATTACK
        Node* temp = h, *t =h;
        while(temp->next != NULL){
            if((temp->data).compare(clause_then) == 0){
                return temp;
            }
            else temp = temp->next;
        }
        return NULL;
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
            //cout<<"FOUND NULL\n";
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
    void print_v(Node_Var* head){

        Node_Var* temp = head;
        if(head == NULL){
            return;
        }
        while(temp != NULL){
            cout<<temp->name<<" "<<temp->instantiate<<endl;
            temp = temp->next;
        }
    }

    int check_Ins_2(string cla_2, Node_Var *head_ins){//ATTACK
        cout<<"FROM CHECK_INS_2"<<cla_2<<endl;
        Node_Var* te_2 = head_ins;
        int t_ret2 = -2;//'\0'
        while(te_2 != NULL){
            if(te_2->name == cla_2){//ATTACK
                cout<<endl<<te_2->instantiate<<endl;
                t_ret2 = te_2->instantiate;
                cout<<"t_ret2 "<<t_ret2<<endl;
                }//1
            te_2 = te_2->next;
        }
        return t_ret2;//1
    }
    int check_Ins(string cla_1, Node* h, Node_Var *head_ins){//PROBLEM
        Node* temp = h;
        int t_ret=-1;
        while(temp != NULL){
            if(temp->conditions1 == cla_1){//PROBLEM
                if(temp->response1 == check_Ins_2(temp->conditions1, head_ins))//1
                t_ret = temp->response1;
            }
            temp = temp->next;
        }
        return t_ret;
    }
    void checkForInstantiation(string clause, Node* h, Node_Var *head_ins){//ATTACK
        LinkedList l_from_inst;
        Node_Var* temp = head_ins;
        int k_ol1, k_ol2 = 1;
        while((clause.compare(temp->name) != 0) && temp->next != NULL){
            temp = temp->next;
        }
        if(temp->instantiate ==1 || temp->instantiate == 0){//already instantiated
            return;      
        } else{//not already instantiated//looking in then clause
            Node* found_clause = l_from_inst.searchThen(clause, h);//ATTACK            
            if(found_clause == NULL){//NOT FOUND <= search_Then returns NULL if not found. So, we create new Variable.
                cout<<"\nInstantiate "<<temp->name<<" ";
                cin>>variable_response[var_n];
                temp->instantiate = variable_response[var_n];
                var_n++;
            } else {
                temp->instantiate = found_clause->result;                 
                Node_Var *newNode = new Node_Var(found_clause->data, found_clause->result);//ATTACK,1//instantiating
                Node_Var* temp_var = head_ins;
                while(temp_var->next != NULL)
                    temp_var = temp_var->next;
                temp_var->next = newNode;
                }
        } 
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
    }
    void search(int C1, Node* h, Node_Clause_var_List* head_clause, Node_Var *head_ins){//13
        Node_Clause_var_List* temp = head_clause;
        
        while(C1 != (temp->srl) && temp->next != NULL){
            temp=temp->next;
        }        
        LinkedList_Var l_for_instantiate;
        for(int i_s=0; i_s<4; i_s++){
            if(temp->clause == ""){
                temp = temp->next;
            } else{
                l_for_instantiate.checkForInstantiation(temp->clause, h, head_ins);//1
                temp = temp->next; 
            }         
        }
        cout<<"\n\nNew Variable LIST";
        cout<<"\n----------------------------------------------------\n";
        l_for_instantiate.print_v(head_ins);  
    } 
};
/*
int process(double x){
    return x;
}*/

void assign_attack_type(int rule){
    if(rule == 40)
        cout<<"MALICIOUS CODE";
}
void validate_R1(int R1, Node* h, Node_Var* head_ins){//40
    LinkedList_Var ll_v;
      
    Node* temp = h, *compare_node;
    int ins_comapre_rule;
    while(temp != NULL){
        if(temp->rule_number == R1){
            compare_node = temp;//ATTACK_TYPE
        }
        temp = temp->next;
    }
    Node_Var* ttemp = head_ins;
    while(ttemp != NULL){
        if(compare_node->conditions1 != "" && compare_node->conditions2 == "" && compare_node->conditions3 == ""){
        if(ttemp->name == compare_node->conditions1){
            if(ttemp->instantiate == compare_node->result){
                if(ttemp->instantiate == 0)
                    cout<<"\n\n"<<compare_node->data<<" not happened.\n";
                else cout<<"\n\n"<<compare_node->data<<" happened.\n";
            } else{
                //saidnottodoanything
                cout<<"\n\nRule "<<compare_node->rule_number<<" cannot be executed."<<endl;
            }
        }}else if((compare_node->conditions1 != "" && compare_node->conditions2 != "" && compare_node->conditions3 == "") || (compare_node->conditions1 != "" && compare_node->conditions2 != "" && compare_node->conditions3 != "")){//ATTACK SLOW ""
            int response_check1, response_check2;

            if(ttemp->instantiate == compare_node->result){
                cout<<"\n\n----------------------------------------------------\n";
                cout<<"\t\tCONCLUSION";
                cout<<"\n----------------------------------------------------\n";
                assign_attack_type(compare_node->rule_number);
                return;}else{
                //saidnottodoanything
                cout<<"\n\nRule "<<compare_node->rule_number<<" cannot be executed."<<endl;
            }
        }
        ttemp = ttemp->next;
    }  
    //process(9.0);
}

void update_VL(int R1, int C1, Node* h, Node_Clause_var_List *head_clause, Node_Var *head_ins){//40 13
    LinkedList_Clause_Var_List l_ins;
    
    l_ins.search(C1, h, head_clause, head_ins);
    validate_R1(R1, h, head_ins);//40
}
void rule_to_clause(int R1, Node* h, Node_Clause_var_List *head_clause, Node_Var *head_ins){
    int C1;

    int clause_number = 4*(R1/10 -1) +1;
    cout<<"Clause Number "<<clause_number<<endl;
    update_VL(R1, clause_number, h, head_clause, head_ins);
}
void search_con(Node* h, string variable, Node_Clause_var_List *head_clause, Node_Var *head_ins){//attack_type
    LinkedList l_s;
    int rule_number = l_s.search(h, variable);
    cout<<"Rule # "<<rule_number<<endl;
    
    rule_to_clause(rule_number, h, head_clause, head_ins);
}

void Identify_the_attack(){

    int var_response_n=0, var_response_y=1;
    cout<<"\nHAVING PROBLEMS? Press 1.\nNO PROBLEM? Press 0\n";
    
    cin>>variable_response[var_n];
    var_n++;
    
    LinkedList l;

    l.define_conclusionList(1, "ATTACK", "PROBLEM", "", "", var_response_y, var_response_y, var_response_y);
    l.define_conclusionList(2, "ATTACK", "PROBLEM", "", "", var_response_n, var_response_n, var_response_n);
    l.define_conclusionList(3, "ATTACK", "PROBLEM", "SLOW", "", var_response_y, var_response_y, var_response_n);
    l.define_conclusionList(4, "ATTACK_TYPE", "ATTACK", "SLOW", "", var_response_y, var_response_y, var_response_n);
    l.define_conclusionList(5, "ATTACK_TYPE", "ATTACK", "SLOW", "UNNECESSARY RUNNING PROCESSOR", var_response_y, var_response_y, var_response_y);
    l.define_conclusionList(6, "ATTACK_TYPE", "PROBLEM", "SLOW", "UNNECESSARY RUNNING PROCESSOR", var_response_y, var_response_y, var_response_y);
    //make all yes set data to malicious code
        l.define_conclusionList(7, "ATTACK_TYPE", "SLOW", "UNNECESSARY RUNNING PROCESSOR", "UNKNOWN FILE", var_response_n, var_response_n, var_response_n);
        l.define_conclusionList(8, "ATTACK_TYPE", "PROBLEM", "SLOW", "NO RESPONSE", var_response_y, var_response_n, var_response_n);
        l.define_conclusionList(9, "ATTACK_TYPE", "PROBLEM", "SLOW", "NO RESPONSE", var_response_y, var_response_n, var_response_n);
        l.define_conclusionList(10, "ATTACK_TYPE", "ATTACK", "SLOW", "", var_response_y, var_response_y, var_response_n);
        l.define_conclusionList(11, "ATTACK_TYPE", "ATTACK", "SLOW", "UNNECESSARY RUNNING PROCESSOR", var_response_y, var_response_y, var_response_y);
        l.define_conclusionList(12, "ATTACK_TYPE", "PROBLEM", "SLOW", "UNNECESSARY RUNNING PROCESSOR", var_response_y, var_response_y, var_response_y);
    l.define_conclusionList(13, "ATTACK_TYPE", "SLOW", "UNNECESSARY RUNNING PROCESSOR", "UNKNOWN FILE", var_response_n, var_response_n, var_response_n);
        l.define_conclusionList(14, "ATTACK_TYPE", "PROBLEM", "SLOW", "NO RESPONSE", var_response_y, var_response_n, var_response_n);
        l.define_conclusionList(15, "ATTACK_TYPE", "PROBLEM", "SLOW", "NO RESPONSE", var_response_y, var_response_n, var_response_n);
        l.define_conclusionList(16, "ATTACK_TYPE", "ATTACK", "SLOW", "", var_response_y, var_response_y, var_response_n);
        l.define_conclusionList(17, "ATTACK_TYPE", "ATTACK", "SLOW", "UNNECESSARY RUNNING PROCESSOR", var_response_y, var_response_y, var_response_y);
        l.define_conclusionList(18, "ATTACK_TYPE", "PROBLEM", "SLOW", "UNNECESSARY RUNNING PROCESSOR", var_response_y, var_response_y, var_response_y);

    Node* head = l.head_ret();
    
    cout<<"\nConclusion List\n";
    cout<<"\n----------------------------------------------------\n";
    l.print();

    LinkedList_Var l_v;
    l_v.variable_name("PROBLEM", variable_response[0]);
    l_v.variable_name("SLOW", -1);
    l_v.variable_name("UNNECESSARY RUNNING PROCESSOR", -1);
    l_v.variable_name("UNKNOWN FILE", -1);
    l_v.variable_name("NO RESPONSE", -1);


    cout<<"\nVariable List";
    cout<<"\n----------------------------------------------------\n";

    Node_Var *head_ins = l_v.ret_head();    
    l_v.print_v(head_ins);

    LinkedList_Clause_Var_List l_c_var;
    int srl =0;
    Node* temp = head; 
    for(int j=1; j<=18; j++){    
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
    Node_Clause_var_List *head_clause = l_c_var.ret_head();

    search_con(head, "ATTACK_TYPE", head_clause, head_ins);
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
