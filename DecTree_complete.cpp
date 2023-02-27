#include<iostream>
#include<map>
#include<string>
#include <iterator>
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
            result = response1 && response2;
        else if(conditions2 != "" && conditions3 != ""){
            result = response1 && response2 && response3;
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
    if(rule == 50)
        cout<<"MALICIOUS CODE";
    if(rule == 60)
        cout<<"DENIAL OF SERVICE";
    if(rule == 70)
        cout<<"MALICIOUS CODE";
    if(rule == 80)
        cout<<"DENIAL OF SERVICE";
    if(rule == 90)
        cout<<"Indentity Theft";
    if(rule == 100)
        cout<<"MALICIOUS CODE";
    if(rule == 110)
        cout<<"MALICIOUS CODE";
    if(rule == 120)
        cout<<"DENIAL OF SERVICE";
    if(rule == 130)
        cout<<"MALICIOUS CODE";
    if(rule == 140)
        cout<<"DENIAL OF SERVICE";
    if(rule == 150)
        cout<<"Indentity Theft";
    if(rule == 160)
        cout<<"MALICIOUS CODE";
    if(rule == 170)
        cout<<"MALICIOUS CODE";
    if(rule == 180)
        cout<<"DENIAL OF SERVICE";
    if(rule == 190)
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
                //cout<<ttemp->instantiate<<compare_node->result<<endl;
                assign_attack_type(compare_node->rule_number);
                return;}else{
                //saidnottodoanything
                cout<<"\n\nRule "<<compare_node->rule_number<<" cannot be executed."<<endl;
                return;
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
    cout<<"Rule # "<<rule_number<<endl<<endl;

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
    //next 5 AMINA
    l.define_conclusionList(5, "ATTACK_TYPE_M", "ATTACK_TYPE", "SLOW", "UNNECESSARY RUNNING PROCESSOR", var_response_y, var_response_y, var_response_y);
    l.define_conclusionList(6, "ATTACK_TYPE_D", "ATTACK_TYPE", "UNNECESSARY RUNNING PROCESSOR", "NO RESPONSE", var_response_y, var_response_y, var_response_y);
    //make all yes set data to malicious code
    l.define_conclusionList(7, "ATTACK_TYPE_Mal", "ATTACK_TYPE", "UNNECESSARY RUNNING PROCESSOR", "UNKNOWN FILES", var_response_y, var_response_y, var_response_y);
    l.define_conclusionList(8, "ATTACK_TYPE_Den", "ATTACK_TYPE", "SLOW", "NO RESPONSE", var_response_y, var_response_y, var_response_y);
    l.define_conclusionList(9, "ATTACK_TYPE_ID", "UNKNOWN FILES", "UNAUTHORIZED ACTIVITY", "UNKWOWN EMAILS", var_response_y, var_response_y, var_response_y);
    //next 5 HANISH
    l.define_conclusionList(10, "ATTACK_TYPE", "ATTACK", "SLOW", "", var_response_y, var_response_y, var_response_n);
    l.define_conclusionList(11, "ATTACK_TYPE", "ATTACK", "SLOW", "UNNECESSARY RUNNING PROCESSOR", var_response_y, var_response_y, var_response_y);
    l.define_conclusionList(12, "ATTACK_TYPE", "PROBLEM", "SLOW", "UNNECESSARY RUNNING PROCESSOR", var_response_y, var_response_y, var_response_y);
    l.define_conclusionList(13, "ATTACK_TYPE", "SLOW", "UNNECESSARY RUNNING PROCESSOR", "UNKNOWN FILE", var_response_n, var_response_n, var_response_n);
    l.define_conclusionList(14, "ATTACK_TYPE", "PROBLEM", "SLOW", "NO RESPONSE", var_response_y, var_response_n, var_response_n);
    //next 5 PRIYA
    l.define_conclusionList(15, "ATTACK_TYPE", "PROBLEM", "SLOW", "NO RESPONSE", var_response_y, var_response_n, var_response_n);
    l.define_conclusionList(16, "ATTACK_TYPE", "ATTACK", "SLOW", "", var_response_y, var_response_y, var_response_n);
    l.define_conclusionList(17, "ATTACK_TYPE", "ATTACK", "SLOW", "UNNECESSARY RUNNING PROCESSOR", var_response_y, var_response_y, var_response_y);
    l.define_conclusionList(18, "ATTACK_TYPE", "PROBLEM", "SLOW", "UNNECESSARY RUNNING PROCESSOR", var_response_y, var_response_y, var_response_y);
    l.define_conclusionList(19, "ATTACK_TYPE", "PROBLEM", "SLOW", "UNNECESSARY RUNNING PROCESSOR", var_response_y, var_response_y, var_response_y);

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
    l_v.variable_name("ATTACK_TYPE", -1);
    l_v.variable_name("UNAUTHORIZED ACTIVITY", -1);
    l_v.variable_name("UNKWOWN EMAILS", -1);




    cout<<"\nVariable List";
    cout<<"\n----------------------------------------------------\n";

    Node_Var *head_ins = l_v.ret_head();
    l_v.print_v(head_ins);

    LinkedList_Clause_Var_List l_c_var;
    int srl =0;
    Node* temp = head;
    for(int j=1; j<=19; j++){
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

    search_con(head, "ATTACK_TYPE_ID", head_clause, head_ins);
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

class QueueNode {
public:
    string data;
    QueueNode* nextNode;
};

class Queue {
public:
    QueueNode* headNode;

    Queue() {
        headNode = NULL;
    }

    void push(string data) {
        QueueNode* temp = headNode;
        QueueNode tempNode;
        tempNode.data = data;
        tempNode.nextNode = temp;
        headNode = &tempNode;
    }

    string peek() {
        return headNode->data;
    }
};

class Pointer{
public:
    int ri;
    int ci;
};

class FWChaining {
public:
    map<int,string> clauseVariableList;
    map<int,string> knowledgeBase;
    Queue conclusionVariableQueue;
    map<string,bool> variableList;
    Pointer clauseVariablePointer;

    FWChaining() {

        string clause;

        cout<<"Choose the type of Attack: "<<endl;
        cout<<"Press 1 for BasicAttack"<<endl;
        cout<<"Press 2 for IdentityAttack"<<endl;
        cout<<"Press 3 for DenialOfService"<<endl;
        cout<<"Press 4 for MaliciousCode"<<endl;
        cout<<"Press 5 for PasswordAttack"<<endl;
        cout<<"Press 6 for PhishingAttack"<<endl;
        cout<<"Press 7 for ManInTheMiddle"<<endl;

        int i;
        cin>>i;

        switch (i) {
            case 1:
                clause = "BasicAttack";
                break;
            case 2:
                clause = "IdentityAttack";
                break;
            case 3:
                clause = "DenialOfService";
                break;
            case 4:
                clause = "MaliciousCode";
                break;
            case 5:
                clause = "PasswordAttack";
                break;
            case 6:
                clause = "PhishingAttack";
                break;
            case 7:
                clause = "ManInTheMiddle";
                break;
            default:
                cout<<"You entered the wrong Input";
                break;
        }


        knowledgeBase[10] = "IF BasicAttack=true THEN Install antivirus software.";
        knowledgeBase[20] = "IF IdentityAttack=true THEN Use a VPN.";
        knowledgeBase[30] = "IF DenialOfService=true THEN Have multilevel authentication for users.";
        knowledgeBase[40] = "IF MaliciousCode=true THEN Don't download any files from unknown source.";
        knowledgeBase[50] = "IF PasswordAttack=true THEN Use stronger password.";
        knowledgeBase[60] = "IF PhishingAttack=true THEN Implement email filter from unknown source.";
        knowledgeBase[70] = "IF ManInTheMiddle=true THEN Use encryption.";

        clauseVariableList[1] = "BasicAttack";
        clauseVariableList[2] = "";
        clauseVariableList[3] = "";
        clauseVariableList[4] = "";
        clauseVariableList[5] = "IdentityAttack";
        clauseVariableList[6] = "";
        clauseVariableList[7] = "";
        clauseVariableList[8] = "";
        clauseVariableList[9] = "DenialOfService";
        clauseVariableList[10] = "";
        clauseVariableList[11] = "";
        clauseVariableList[12] = "";
        clauseVariableList[13] = "MaliciousCode";
        clauseVariableList[14] = "";
        clauseVariableList[15] = "";
        clauseVariableList[16] = "";
        clauseVariableList[17] = "PasswordAttack";
        clauseVariableList[18] = "";
        clauseVariableList[19] = "";
        clauseVariableList[20] = "";
        clauseVariableList[21] = "PhishingAttack";
        clauseVariableList[22] = "";
        clauseVariableList[23] = "";
        clauseVariableList[24] = "";
        clauseVariableList[21] = "ManInTheMiddle";
        clauseVariableList[22] = "";
        clauseVariableList[23] = "";
        clauseVariableList[24] = "";

        int ci = process(clause);
        int ri = clause_to_rule(ci);
        update_VL(ci);
        validate_Ri(ri);
        prevention();
        debug();

    }

    int search_cvl(string clause) {
        int ci;
        for(int i=1; i<=28; i++){
            if(clauseVariableList[i]==clause) {
                ci = i;
                break;
            }
            else ci = 0;
        }
        return ci;
    }

    int clause_to_rule(int ci) {
        int ri = ((ci/4)+1)*10;
        clauseVariablePointer.ci = ci;
        clauseVariablePointer.ri = ri;
        return ri;
    }

    void update_VL(int ci) {
        variableList[clauseVariableList[ci]] = true;
    }

    void validate_Ri(int ri) {
        for(int i=1; i<=28; i+4){
            string clause = clauseVariableList[i];
            if(knowledgeBase[ri].find(clause)!=0) {
                conclusionVariableQueue.push(clause);
                break;
            }
        }
    }

    int process(string clause) {

        variableList["BasicAttack"] = false;
        variableList["IdentityAttack"] = false;
        variableList["DenialOfService"] = false;
        variableList["MaliciousCode"] = false;
        variableList["PasswordAttack"] = false;
        variableList["PhishingAttack"] = false;
        variableList["ManInTheMiddle"] = false;

        return search_cvl(clause);

    }

    void prevention() {
        string clause = conclusionVariableQueue.peek();
        cout<<"Prevention: ";
        if(clause == "BasicAttack") cout<<"Install antivirus software.";
        else if(clause == "IdentityAttack") cout<<"Use a VPN.";
        else if(clause == "DenialOfService") cout<<"Have multilevel authentication for users.";
        else if(clause == "MaliciousCode") cout<<"Don't download any files from unknown source.";
        else if(clause == "PasswordAttack") cout<<"Use stronger password.";
        else if(clause == "PhishingAttack") cout<<"Implement email filter from unknown source.";
        else if(clause == "ManInTheMiddle") cout<<"Use encryption.";
        cout<<endl;
    }

    void debug() {

        cout<<"\nRules list\n";
        cout<<"----------------------------------------------------\n";
        for (int i=10; i<=70; i=i+10) {
            cout<<"'"<<i<<"'"<<" "<<knowledgeBase[i]<<endl;
        }

        cout<<"\nClause Variable list\n";
        cout<<"----------------------------------------------------\n";
        for(int i=1; i<=28; i++) {
            cout<<"'"<<i<<"'"<<" "<<clauseVariableList[i]<<endl;
        }

        cout<<"\nClause Variable Pointer\n";
        cout<<"----------------------------------------------------\n";
        cout<<"Rule #     Clause#"<<endl;
        cout<<clauseVariablePointer.ri<<"         "<<clauseVariablePointer.ci<<endl;

        cout<<"\nVariable list\n";
        cout<<"----------------------------------------------------\n";
        cout<<"Variable         Value"<<endl;
        cout<<"BasicAttack      "<<variableList["BasicAttack"]<<endl;
        cout<<"IdentityAttack   "<<variableList["IdentityAttack"]<<endl;
        cout<<"DenialOfService  "<<variableList["DenialOfService"]<<endl;
        cout<<"MaliciousCode    "<<variableList["MaliciousCode"]<<endl;
        cout<<"PasswordAttack   "<<variableList["PasswordAttack"]<<endl;
        cout<<"PhishingAttack   "<<variableList["PhishingAttack"]<<endl;
        cout<<"ManInTheMiddle   "<<variableList["ManInTheMiddle"]<<endl;

        cout<<"\nConclusion Variable queue\n";
        cout<<"----------------------------------------------------\n";
        if(variableList["BasicAttack"]) cout<<"BasicAttack";
        else if(variableList["IdentityAttack"]) cout<<"IdentityAttack";
        else if(variableList["DenialOfService"]) cout<<"DenialOfService";
        else if(variableList["MaliciousCode"]) cout<<"MaliciousCode";
        else if(variableList["PasswordAttack"]) cout<<"PasswordAttack";
        else if(variableList["PhishingAttack"]) cout<<"PhishingAttack";
        else if(variableList["ManInTheMiddle"]) cout<<"ManInTheMiddle";

        cout<<"\n";

    }

};

void Attacks_BW() {
    Identify_the_attack();
}

void Prevention_FW() {
    FWChaining fwChaining;
}

int main(){
    int n;
    cout<<"Press 1 to Explore Attacks\nPress 2 to Explore Prevention\n";
    cin>>n;

    if(n == 1)
        Attacks_BW();
    else
        Prevention_FW();

    return 0;
}
