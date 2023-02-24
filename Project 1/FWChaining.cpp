#include<iostream>
#include<map>
#include<string>
#include<queue>
#include <iterator>


using namespace std;

class FWChaining {
public:
    map<int,string> clauseVariableList;
    map<int,string> knowledgeBase;
    queue<string> conclusionVariableQueue;
    map<string,bool> variableList;
    map<int,int> clauseVariablePointer;

    FWChaining(string clause) {

        knowledgeBase[10] = "IF BasicAttack=true THEN Prevention 1";
        knowledgeBase[20] = "IF IdentityAttack=true THEN Prevention 2";
        knowledgeBase[30] = "IF DenialOfService=true THEN Prevention 3";
        knowledgeBase[40] = "IF MaliciousCode=true THEN Prevention 4";

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

        int ci = process(clause);
        int ri = clause_to_rule(ci);
        update_VL(ci);
        validate_Ri(ri);

    }

    int search_cvl(string clause) {
        int ci;
        for(int i=1; i<=16; i++){
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
        clauseVariablePointer[ri] = ci;
        return ri;
    }

    void update_VL(int ci) {
        variableList[clauseVariableList[ci]] = true;
    }

    void validate_Ri(int ri) {
        for(int i=1; i<=16; i+4){
            string clause = clauseVariableList[i];
            if(variableList[clause]==true && knowledgeBase[ri].find(clause)!=0) {
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

        return search_cvl(clause);

    }

};
