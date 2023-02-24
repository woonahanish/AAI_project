
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;


int flag;
char cndvar[10][3];
char varlt[10][3], /* variable list*/ clvarlt[40][3]; /* clause var list */
char c[3], vp[3], /* condition variable */  v[3]; /*variable */
char fedint[10], interest[10], stock[10], dollar[10], fedmon[10];
char po[10], /* position */  qu[10]; /* qualify */
int instlt[10];         /* instantiated list*/
int f, i, j, k, s, fp   /* front pointer */;
int  bp  /* back pointer */,  gr /* grade */,  sn; /* statement number */
int cn;  /* clause number */


int search_cvl(double d);
int clause_rule(int Ci);
void update_VL(int i);
void validate_Ri(int i);
void check_instantiation();
void search();
void instantiate();


int main() {
    /*
    Declaration of the FC main function
     Write functions’ prototypes
     Declare variables, and arrays
     Create list of rules. It may need some organization. You have to
       determine which format you want to use for efficient processing by
       Validate_Ri function.
     Create Variable List as an array.
     Create Clause Variable list as an array.
     Create Global Conclusion variable queue as an array
    Processing of the main function:
    a. Read the value of the given  variable (the variable whose value is
       provided) and call process (variable)
    b. If Global Conclusion Variable Queue is not empty, in  a loop
       call process (variable) for  each variable in  the Global
       Conclusion Variable Queue which occurs in the clause
       variable list. After the function return, it will delete the
       variable from the Global Conclusion Variable Queue.
    c. Print all the derived conclusions from the Derived
       Conclusion List
     */

    /******** INITIALIZATION SECTION ***********/
    fp=1;
    bp=1;
    for (i=1;i < 41; i++)
        strcpy(clvarlt[i], "");
    for (i=1;i < 11; i++)
        strcpy(cndvar[i], "");
    for (i=1;i < 11; i++)
        strcpy(instlt[i], "");
    for (i=1;i < 11; i++)
        strcpy(varlt[i], "");
    for (i=1;i < 11; i++) {
        strcpy(cndvar[i], "");
        strcpy(varlt[i], "");
        strcpy (instlt[i], "");
    }
    /* enter variables which are in the IF part, 1 at a time in
    the exact order that they occur. Up to 3 variables per
    IF statement. Do not duplicate any variable names. Any
    name is used only once. If no more variables left, just
    hit return key */
    /****** comment 367 *************/
    strcpy(varlt[1], "DO");
    strcpy(varlt[2], "FT");
    strcpy(varlt[3], "FM");
    strcpy(varlt[4], "IN");
    strcpy(varlt[5], "ST");
    printf("*** VARIABLE LIST ***\n");
    for (i=1;i < 11; i++)
        printf("ENTER VARIABLE   %d   %s\n", i, varlt[i]);
    printf("HIT RETURN TO CONTINUE");
    getchar();
    /* enter variables as they appear in the IF clauses, Up to 3
    variables per IF statement. If no more variables left, just
    hit return key */
    /****** comment 407, 408 *************/
    strcpy(clvarlt[1], "IN");
    strcpy(clvarlt[5], "IN");
    strcpy(clvarlt[9], "DO");
    strcpy(clvarlt[13], "DO");
    strcpy(clvarlt[17], "FT");
    strcpy(clvarlt[18], "FM");
    printf("*** CLAUSE-VARIABLE LIST ***\n");
    for (i = 1; i < 9; i++)
    {
        printf("** CLAUSE %d\n", i);
        for (j = 1; j < 5; j++)
        {
            k = 4 * (i - 1) + j;
            printf("VARIABLE %d  %s\n", j, clvarlt[k]);
        }
        if (i==4)
        {
            printf("HIT RETURN TO CONTINUE");
            getchar();
        }
    }
    /****** INFERENCE SECTION *****************/
    printf("ENTER CONDITION VARIABLE? ");
    gets(c);
    /* place condition variable c on condition var queue cndvar */
    strcpy(cndvar[bp], c);
    /* move backpointer (bp) to back */
    bp = bp + 1;
    /* set the condition variable pointer consisting of the
    statement number (sn) and the clause number (cn) */
    sn = 1; cn = 1;
    /* find the next statement number containing the condition variable
    which is in front of the queue (cndvar), this statement number
    is located in the clause variable list (clvarlt) */
    /* start at the beginning */
    f=1;
    b496: search();
    /* point to first clause in statement */
    cn=1;
    if (sn != 0)
        /* more statements */
    {
        /* locate the clause */
        i = 4 * (sn-1) + cn;
        /* clause variable */
        strcpy(v, clvarlt[i]);
        /* are there any more clauses for this statement */
        while (strcmp(v, ""))
            /* more clauses */
        {
            /* check instantiation of this clause */
            check_instantiation();
            cn = cn+1;
            /* check next clause */
            i = 4 * (sn-1) + cn;
            strcpy(v, clvarlt[i]);
        }
        /* no more clauses - check IF part of statement */
        s = 0;
        /* sample IF-THEN statements from the position knowledge base */
        switch(sn)
        {
            /* statement 1 */
            /***** comment 1500 *****/
            case 1: if (strcmp(interest, "FALL") == 0) s=1;
                break;
                /* statement 2 */
                /***** comment 1510 *****/
            case 2: if (strcmp(interest, "RISE") == 0) s=1;
                break;
                /* statement 3 */
                /***** comment 1540 *****/
            case 3: if (strcmp(dollar, "FALL") == 0) s=1;
                break;
                /* statement 4 */
                /***** comment 1550 *****/
            case 4: if (strcmp(dollar, "RISE") == 0) s=1;
                break;
                /* statement 5 */
            case 5: if ((strcmp(fedint, "FALL") == 0) &&
                        (strcmp(fedmon, "ADD")) == 0) s=1;
                break;
                /* statement 6 */
            case 6: if ((strcmp(qu, "YES") == 0) && (gr >= 3.5) == 0) s=1;
                break;
                /***** comment 1610 *****/
        }
        /* see if the THEN part should be inovked, i.e., s=1 */
        if (s != 1)
        {
            f = sn + 1;
            goto b496;
        }
        /* invoke THEN part */
        switch (sn)
        {
            /*********** comment 1500 ***********/
            /* put variable on the conclusion variable queue */
            case 1:
                strcpy(stock, "RISE");
                printf("ST=RISE\n");
                strcpy(v, "ST");
                instantiate();
                break;
                /*********** comment 1510 ***********/
                /* put variable on the conclusion variable queue */
            case 2:
                strcpy(stock, "FALL");
                printf("ST=FALL\n");
                strcpy(v, "ST");
                instantiate();
                break;
                /*********** comment 1540 ***********/
                /* put variable on the conclusion variable queue */
            case 3:
                strcpy(interest, "RISE");
                printf("IN=RISE\n");
                strcpy(v, "IN");
                instantiate();
                break;
                /*********** comment 1550 ***********/
                /* put variable on the conclusion variable queue */
            case 4:
                strcpy(interest, "FALL");
                printf("IN=FALL\n");
                strcpy(v, "IN");
                instantiate();
                break;
                /* put variable on the conclusion variable queue */
            case 5:
                strcpy(interest, "FALL");
                printf("IN=FALL\n");
                strcpy(v, "IN");
                instantiate();
                break;
            case 6:
                strcpy(po, "YES");
                printf("PO=YES\n");
                break;
                /*********** comment 1610 ***********/
        }
        f = sn + 1;
        goto b496;
    }
    /* no more clauses in the clause variable list (clvarlt)
    containing the variable in front of the queue (cndvar(fp))
    then remove front variable (cndvar(fp)) and replace it by
    the next variable (cndvar(fp+1)). If no more variables are
    at the front of the queue, stop. */
    /* next queue variable */
    fp=fp+1;
    if (fp < bp)
    {
        /* check out the condition variable */
        f = 1;
        goto b496;
    }
    /* no more conclusion variables on queue */
    return 0;
}

//==========================================================================
/* Routine to instantiate a variable (v) if it isn't already.
The instantiate indication (instlt) is a 0 if not, a 1 if it is.
The vriable list (varlt) contains the variable (v) */
void check_instantiation()
{
    i=1;
    /* find variable in the variable list */
    while ((strcmp(v, varlt[i]) != 0) && (i <= 10)) i = i+1;
    /* check if already instantiated */
    if (instlt[i] != 1)
    {
        /* mark instantiated */
        instlt[i] = 1;
        /* the designer of this knowledge base places the input
        statements to instantiate the variables in this case
        statement */
        switch (i)
        {
            /* input statements for sample position knowledge base */
            case 1:
                printf("RISE OR FALL FOR DO? ");
                gets(dollar);
                break;
            case 2:
                printf("RISE OR FALL FOR FT? ");
                gets(fedint);
                break;
            case 3:
                printf("ADD OR SUBTRACT FOR FM? ");
                gets(fedmon);
                break;
            case 4:
                printf("RISE OR FALL FOR IN? ");
                gets(interest);
                break;
            case 5:
                printf("RISE OR FALL FOR ST? ");
                gets(stock);
                break;
        }
    }
    /* end of input statements for the position knowledge base */
}
//==========================================================================
/* Search clause variable list for a varialbe (clvarlt) equal to the
one in front of the conclusion queue (cndvar). Return the statement
number (sn). If there is no match, i.e., sn=0, the first statement
for the space is f. */
void search()
{
    flag = 0;
    sn = f;
    while ((flag == 0) && (sn <= 10))
    {
        cn=1;
        k = (sn-1)*4+cn;
        while ((strcmp(clvarlt[k], cndvar[fp]) != 0) && (cn < 4))
        {
            cn = cn+1;
            k = (sn-1)*4+cn;
        }
        if (strcmp(clvarlt[k], cndvar[fp]) == 0) flag = 1;
        if (flag == 0) sn = sn+1;
    }
    if (flag == 0) sn=0;
}
//==========================================================================
/* Routine to instantiate a varialbe (v) and then place it on the
back of the queu (cndvar[bp]), if it is not already there. */
void instantiate()
{
    i=1;
    /* find varialbe in the varialbe list (varlt) */
    while ((strcmp(v, varlt[i]) != 0) && (i <= 10)) i=i+1;
    /* instantiate it */
    instlt[i] = 1;
    i = 1;
    /* determine if (v) is or already has been on the queue (cndvar) */
    while ((strcmp(v, cndvar[i] != 0) && (i <= 10)) i=i+1;
    /* variable has not been on the queue. Store it in the back of the queue */
    if (strcmp(v, cndvar[i]) != 0)
    {
        strcpy(cndvar[bp], v);
        bp=bp+1;
    }
}


int search_cvl(double d) {
    /*
    search_cvl(double variable): this function will search for an entry in the
    clause variable list and find the entry which matches the argument variable
    and returns the clause number, Ci, corresponding to the matching entry.
    Then first call update_VL (Ci). Then call clause_to_rule (Ci):
     */
    int Ci;
    return Ci;
}

int clause_rule(int Ci) {
    /*
    clause_to_rule (integer variable): - This function will convert Clause
    number, Ci, to rule number, Ri, using the following formula. After
    computing the value of Ri, it will call validate_Ri (Ri):
    If the clause numbers in the clause variable  list are sequenced like
    1,2,3,4,5, ......), the formula is:
    Rule # = [({Quotient  (Clause # / 4)} +1)]
    If the rule numbers are sequenced like 10,20,30,40,50, ......), the formula is:
    Rule # = [({Quotient  (Clause # / 4)} +1) * 10]
    It has been assumed that four slots have been assigned for each rule in the
    Clause Variable list. If other than four has been assigned replace 4 by that
    number.
     */
    int Ri;
    return Ri;
}

void update_VL(int i) {
    /*
    update_VL (integer variable): For each variable (maximum of four)
    starting location Ci, It will check if the variable is instantiated in the variable
    list or not. If not, it will ask the user to provide the values of variables and
    instantiate them.
     */
}

void validate_Ri(int i) {
    /*
    validate_Ri (integer variable): It will check if the values of the variable
    in the ‘if’ clauses of the rule, Ri, are satisfied with the values in the variable
    list. If they do, add the conclusion of the rule to the global derived
    conclusions list as well as to the Global Conclusion Variable Queue and
    return.
     */
}