#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef enum{NO,YES} SUBSIDY;
typedef enum{NAME_SIZE=20,ADDRESS_SIZE=30,AADHAR_SIZE=13,PAN_SIZE=12,BANK_ACC_SIZE=13} sizes;

typedef struct Aadhar_Node_Tag
{
    char name[NAME_SIZE];
    char address[ADDRESS_SIZE];
    char aadhar_no[AADHAR_SIZE];
    struct Aadhar_Node_Tag *next;
    struct Pan_Node_Tag* pan_ptr;
}Aadhar_Node;

typedef struct Pan_Node_Tag
{
    char name[NAME_SIZE];
    char address[ADDRESS_SIZE];
    char pan_no[PAN_SIZE];
    char aadhar_no[AADHAR_SIZE];
    struct Pan_Node_Tag *next;
    struct Pan_Node_Tag *next_pan;
    struct Bank_Account_Tag* bank_ptr;
}Pan_Node;

typedef struct Bank_Account_Tag
{
    char name[NAME_SIZE];
    char bank_name[NAME_SIZE];
    char bank_acc_no[BANK_ACC_SIZE];
    char pan_no[PAN_SIZE];
    int balance;
    struct Bank_Account_Tag *next;
    struct Bank_Account_Tag *next_bank;
    struct LPG_Tag_List* lpg_ptr;
}Bank_Acc_Node;

typedef struct LPG_Tag_List
{
    char name[NAME_SIZE];
    char bank_acc_no[BANK_ACC_SIZE];
    SUBSIDY subsidy;
    struct LPG_Tag_List *next;
    struct LPG_Tag_List *next_lpg;
}LPG_Node;

//Read Aadhar File Function
Aadhar_Node *Read_Aadhar(Aadhar_Node*lptr)
{
    FILE* fp;
    fp=fopen("aadhar.csv","r");
    Aadhar_Node*tail;

    if(!fp)
    {
        perror("Error opening Aadhar File!!\n");
    }
    else
    {   
        char row[200];
        //printf("Aadhar File Opened!!\n");

        while(fgets(row,sizeof(row),fp)!=NULL)
        {
            char* token = strtok(row,",");

            Aadhar_Node*nptr=(Aadhar_Node*)malloc(sizeof(Aadhar_Node));
            nptr->next=NULL;
            nptr->pan_ptr = NULL;
            strcpy(nptr->name,token);

            token=strtok(NULL,",");
            strcpy(nptr->address,token);

            token=strtok(NULL,",");
            strcpy(nptr->aadhar_no,token);

            //Linking the next pointers
            if(lptr==NULL)
            {
                tail=lptr=nptr;
            }
            else
            {
                tail->next=nptr;
                tail=nptr;
            }
        }
        printf("Aadhar Data Fetched Successfully :)\n");
    }
    fclose(fp);
    return lptr;
}

//Read Pan File Function
Pan_Node* Read_Pan(Pan_Node *lptr)
{
    FILE* fp;
    fp=fopen("pan.csv","r");
    Pan_Node* tail;

    if(!fp)
    {
        perror("Error opening Pan File!!\n");
    }
    else
    {   
        char row[200];
        //printf("Pan File Opened!!\n");

        while(fgets(row,sizeof(row),fp)!=NULL)
        {
            char* token = strtok(row,",");

            Pan_Node* nptr=(Pan_Node*)malloc(sizeof(Pan_Node));
            nptr->next=NULL;
            nptr->next_pan=NULL;
            nptr->bank_ptr=NULL;

            strcpy(nptr->name,token);

            token=strtok(NULL,",");
            strcpy(nptr->address,token);

            token=strtok(NULL,",");
            strcpy(nptr->pan_no,token);

            token=strtok(NULL,",");
            strcpy(nptr->aadhar_no,token);

            //Linking the next pointers
            if(lptr==NULL)
            {
                tail=lptr=nptr;
            }
            else
            {
                tail->next=nptr;
                tail=nptr;
            }
            nptr->next_pan=NULL;
            nptr->bank_ptr=NULL;
        }
        printf("Pan Data Fetched Successfully :)\n");
    }
    fclose(fp);
    return lptr;
}

//Read Bank Accounts File Function
Bank_Acc_Node* Read_Bank(Bank_Acc_Node *lptr, FILE* fp)
{
    Bank_Acc_Node *tail = lptr;

    if(fp != NULL)
    {
        //printf("Bank file opened succesfully!!\n");
        char row[200];

        while(fgets(row,sizeof(row),fp))
        {
            Bank_Acc_Node* nptr=(Bank_Acc_Node*)malloc(sizeof(Bank_Acc_Node));
            nptr->next=NULL;
            nptr->next_bank=NULL;
            nptr->lpg_ptr=NULL;

            char*token = strtok(row,",");
            strcpy(nptr->name,token);

            token=strtok(NULL,",");
            strcpy(nptr->bank_name,token);

            token=strtok(NULL,",");
            strcpy(nptr->bank_acc_no,token);

            token=strtok(NULL,",");
            strcpy(nptr->pan_no,token);

            token=strtok(NULL,",");
            nptr->balance=atoi(token);

            if(lptr==NULL)
            {
                tail=lptr=nptr;
            }
            else
            {
                tail->next=nptr;
                tail=nptr;
            }
            nptr->lpg_ptr=NULL;
            nptr->next_bank=NULL;
        }
        printf("Bank Data fetched successfully :)\n");
    }
    fclose(fp);
    return lptr;
}

//Read LPG List File
LPG_Node* Read_Lpg(LPG_Node *lptr)
{
    FILE *fp;
    fp = fopen("lpg.csv","r");
    LPG_Node *tail;

    if(fp != NULL)
    {
        char row[200];

        while(fgets(row,sizeof(row),fp))
        {
            LPG_Node* nptr=(LPG_Node*)malloc(sizeof(LPG_Node));
            nptr->next=NULL;
            nptr->next_lpg=NULL;
            nptr->subsidy=NO;

            char *token=strtok(row,",");
            strcpy(nptr->name,token);

            token=strtok(NULL,",");
            strcpy(nptr->bank_acc_no,token);

            token=strtok(NULL,",");

            if(strcmp(token,"YES")==0)
            {
                nptr->subsidy=YES;
            }
            else
            {
                nptr->subsidy=NO;
            }

            //Linking next pointers
            if(lptr==NULL)
            {
                tail=lptr=nptr;
            }
            else
            {
                tail->next=nptr;
                tail=nptr;
            }
            nptr->next_lpg=NULL;
        }
        printf("Lpg subsidy data fetched successfully :)\n");
    }
    fclose(fp);
    return lptr;
}

//Print Aadhar Data Function
void Print_Aadhar(Aadhar_Node *lptr)
{
    Aadhar_Node *ptr= lptr;
    //printf("Print_Aadhar() called!!\n\n");
    int i=1;
    while(ptr != NULL)
    {
        printf("%d)",i);
        printf("Name: %s\n",ptr->name);
        printf(" Address: %s\n",ptr->address);
        printf(" Aadhar No.: %s\n",ptr->aadhar_no);
        ptr = ptr->next;
        printf("\n");
        i++;
    }
}

//Print Pan Data Function
void Print_Pan(Pan_Node* lptr)
{
    Pan_Node* ptr = lptr;
    //printf("Print_Pan() called!!\n\n");
    int i=1;
    while(ptr!=NULL)
    {
        printf("%d)",i);
        printf("Name: %s\n",ptr->name);
        printf(" Address: %s\n",ptr->address);
        printf(" Pan No.: %s\n",ptr->pan_no);
        printf("\n");
        ptr=ptr->next;
        i++;
    }
} 

void Print_Lpg(LPG_Node* lptr);

//Print Bank Details function
void Print_Bank(Bank_Acc_Node*lptr)
{
    Bank_Acc_Node* ptr=lptr;
    //printf("Print_Bank() called!!\n\n");
    int i=1;
    while(ptr!=NULL)
    {
        printf("%d)Name: %s\n",i,ptr->name);
        printf("  Bank Name: %s\n",ptr->bank_name);
        printf("  Amount Deposited: %d\n",ptr->balance);
        printf("  Account No:- %s\n",ptr->bank_acc_no);
        if(ptr->lpg_ptr != NULL)
        {   
            Print_Lpg(ptr->lpg_ptr);
        }
        ptr = ptr->next;
        printf("\n");
        i++;
    }
}

//Print Lpg Details function
void Print_Lpg(LPG_Node*lptr)
{
    LPG_Node*ptr=lptr;
    //printf("Printf_lpg() called!!\n\n");
    int i=1;
    while(ptr!=NULL)
    {
        printf("%d)",i);
        printf("Name: %s\n",ptr->name);
        printf(" Bank_Account_no: %s\n",ptr->bank_acc_no);
        if(ptr->subsidy==YES)
        {
            printf(" Subsidy Taken: Yes\n");
        }
        else{
            printf(" Subsidy Taken: No\n");
        }
        ptr = ptr->next;
        printf("\n");
        i++;
    }
}

//Function to link bank acc to respective lpg connections
void Link_Bank_Lpg(Bank_Acc_Node *b_ptr,LPG_Node *l_ptr)
{
    Bank_Acc_Node *ptr1 = b_ptr;
    LPG_Node * ptr2 = l_ptr;
    LPG_Node *tail;

    while(ptr1 != NULL)
    {
        ptr2 = l_ptr;
        while(ptr2 != NULL)
        {
            if(strcmp(ptr1->bank_acc_no,ptr2->bank_acc_no)== 0)
            {
                if(ptr1->lpg_ptr == NULL)
                {
                    tail = ptr1->lpg_ptr = ptr2;
                }
                else
                {
                    tail->next_lpg = ptr2;
                    tail = ptr2;
                }
            }
            ptr2 = ptr2->next;
        }
        tail = NULL;
        ptr1 = ptr1->next;
    }
    printf("Bank Acc and Lpg Linked Successfully!!\n");
}

//Function to link pans to respective bank acc
void Link_Bank_Pan(Bank_Acc_Node* B_ptr,Pan_Node* P_lptr)
{
    Bank_Acc_Node* b_ptr=B_ptr;
    Pan_Node* p_ptr=P_lptr;
    Bank_Acc_Node*tail;

    while(p_ptr!=NULL)
    {
        b_ptr=B_ptr;
        while(b_ptr!=NULL)
        {
            if(strcmp(b_ptr->pan_no,p_ptr->pan_no)==0)
            {
                if(p_ptr->bank_ptr==NULL)
                {
                    tail = p_ptr->bank_ptr = b_ptr;
                }
                else
                {
                    tail->next_bank=b_ptr;
                    tail=b_ptr;
                }
            }
            b_ptr=b_ptr->next;
        }
        tail = NULL;
        p_ptr=p_ptr->next;
    }
    printf("Pan and Bank Acc Linked Successfully!!\n");
}

//Function to link aadhar to respective pans
void Link_Aadhar_Pan(Pan_Node*P_ptr,Aadhar_Node* A_ptr)
{
    Pan_Node* p_ptr=P_ptr;
    Aadhar_Node* a_ptr=A_ptr;
    Pan_Node*tail;

    while(a_ptr!=NULL)
    {
        p_ptr=P_ptr;
        while(p_ptr!=NULL)
        {
            if(strcmp(a_ptr->aadhar_no,p_ptr->aadhar_no) == 0)
            {
                if(a_ptr->pan_ptr==NULL)
                {
                    tail=a_ptr->pan_ptr=p_ptr;
                }
                else
                {
                    tail->next_pan=p_ptr;
                    tail=p_ptr;
                }
            }
            p_ptr=p_ptr->next;
        }
        tail = NULL;
        a_ptr=a_ptr->next;
    }
    printf("Aadhar and Pan Linked Succesfully!!\n");
}

//Person with aadhar but no pan
void Que1(Aadhar_Node *A_lptr)
{
    //printf("Que1 called\n");
    Aadhar_Node *ptr = A_lptr;
    int i=1;
    while(ptr != NULL)
    {
        if(ptr->pan_ptr == NULL)
        {
            printf("%d)Name: %s\n",i,ptr->name);
            printf("  Address: %s\n",ptr->address);
            printf("  Aadhar No.: %s\n",ptr->aadhar_no);
            i++;
            printf("\n");
        }
        ptr = ptr->next;
    }
}

//Print info of people with multiple pan no.s
void Que2(Aadhar_Node *A_lptr)
{
    //printf("Que2 called\n");
    Aadhar_Node *a_ptr = A_lptr;
    Pan_Node* p_ptr;
    int i=1;
    while(a_ptr != NULL)
    {
        if(a_ptr->pan_ptr != NULL && a_ptr->pan_ptr->next_pan != NULL)
        {
            printf("%d)Name: %s\n",i,a_ptr->name);
            printf("  Address: %s\n",a_ptr->address);
            printf("  Aadhar No.: %s\n",a_ptr->aadhar_no);

            p_ptr=a_ptr->pan_ptr;
            printf("  Pan no.s are: ");
            while(p_ptr!=NULL)
            {
                printf("%s ",p_ptr->pan_no);
                p_ptr=p_ptr->next_pan;
            }

            i++;
            printf("\n\n");
        }
        a_ptr = a_ptr->next;
    }
}

//Person with multiple bank acc under multiple pan
void Que3(Aadhar_Node*A_lptr)
{
    //printf("Que3 called\n");
    Aadhar_Node *ptr = A_lptr;
    int count = 0,i=1;

    while(ptr != NULL)
    {
        if(ptr->pan_ptr != NULL && ptr->pan_ptr->next_pan != NULL)
        {
            Pan_Node *p_ptr = ptr->pan_ptr;
            Bank_Acc_Node*b_ptr;
            while(p_ptr != NULL)
            {
                b_ptr = p_ptr->bank_ptr;
                while(b_ptr != NULL)
                {
                    count++;
                    b_ptr=b_ptr->next_bank;
                }
                p_ptr=p_ptr->next_pan;
            }
            if(count > 1)
            {
                printf("%d)Name: %s\n",i,ptr->name);
                printf("  Address: %s\n",ptr->address);
                printf("  Aadhar No.: %s\n",ptr->aadhar_no);
                i++;
                printf("\n");
            }
            count = 0;
        }
        ptr=ptr->next;
    }
}

//Person who have availed LPG subsidy
void Que4(Aadhar_Node *A_lptr)
{
    Aadhar_Node *a_ptr = A_lptr;
    Pan_Node *p_ptr ;
    Bank_Acc_Node *b_ptr;
    LPG_Node *l_ptr;
    //printf("Que4 called!!\n\n");
    int i=1;

    while(a_ptr != NULL)
    {
        p_ptr = a_ptr->pan_ptr;
        while(p_ptr != NULL)
        {
            b_ptr = p_ptr->bank_ptr;
            while(b_ptr != NULL)
            {
                l_ptr = b_ptr->lpg_ptr;
                while(l_ptr!=NULL)
                {
                    if(l_ptr->subsidy == YES)
                    {
                        printf("%d)Name: %s\n",i,l_ptr->name);
                        printf("  Aadhar No: %s\n",a_ptr->aadhar_no);
                        printf("  Pan No: %s\n",p_ptr->pan_no);
                        printf("  Bank Name: %s\n",b_ptr->bank_name);
                        printf("  Bank Acc No: %s\n",b_ptr->bank_acc_no);
                        printf("  Balance: %d\n",b_ptr->balance);
                        printf("\n");i++;
                    }
                    l_ptr = l_ptr->next_lpg;
                }
                b_ptr = b_ptr->next_bank;
            }
            p_ptr = p_ptr->next_pan;
        }
        a_ptr = a_ptr->next;
    }
}

//People with LPG subsidy and balance>X
void Que5(Aadhar_Node *A_lptr,int X)
{
    Aadhar_Node *a_ptr = A_lptr;
    Pan_Node *p_ptr ;
    Bank_Acc_Node *b_ptr;
    LPG_Node *l_ptr;
    int total = 0,i=1;
    //printf("Ques 5 called!!\n");

    while(a_ptr != NULL)
    {
        p_ptr = a_ptr->pan_ptr;
        int flag = 0,subsidy=0;
        int flag1 = 0;
        
        while(p_ptr!=NULL && flag==0)
        {
            b_ptr=p_ptr->bank_ptr;
            while(b_ptr!=NULL && flag==0)
            {
                total+=b_ptr->balance;
                if(total > X)
                {
                    flag1 = 1;
                }
                l_ptr=b_ptr->lpg_ptr;
                while(l_ptr!=NULL && subsidy==0)
                {
                    if(l_ptr->subsidy==YES)
                    {
                        subsidy=1;
                    }
                    l_ptr=l_ptr->next_lpg;
                }
                
                if(flag1 == 1 && subsidy == 1)
                {
                    printf("%d)Name: %s\n",i,a_ptr->name);
                    printf("  Address: %s\n",a_ptr->address);
                    printf("  Aadhar No.: %s\n",a_ptr->aadhar_no);
                    flag = 1;i++;
                    printf("\n");
                }
                b_ptr=b_ptr->next_bank;

            }
            p_ptr=p_ptr->next_pan;
        }
        total=0;subsidy=0;
        flag1 = 0;
        a_ptr = a_ptr->next;
    }
}      

//Printing Inconsistant Data 
void Que6(Aadhar_Node* A_lptr)
{
    int flag1=0,flag2=0,flag3=0,i=1;
    Aadhar_Node* a_ptr=A_lptr;
    Pan_Node* p_ptr;
    Bank_Acc_Node* b_ptr;
    LPG_Node* l_ptr;
    //printf("Que6 called!!\n\n");

    while(a_ptr!=NULL)
    {
        p_ptr=a_ptr->pan_ptr;
        while(p_ptr!=NULL && flag1==0)
        {
            if(strcmp(a_ptr->name,p_ptr->name)!=0)
            {
                printf("%d)Name on Aadhar: %s\n",i,a_ptr->name);
                printf("  Name on Pan: %s\n",p_ptr->name);
                printf("  Aadhar No: %s\n",a_ptr->aadhar_no);
                printf("  Address: %s\n",a_ptr->address);
                printf("\n");
                flag1=1;flag2=1;flag3=1;i++;
            }
            b_ptr=p_ptr->bank_ptr;
            while(b_ptr!=NULL && flag2==0)
            {
                if(strcmp(p_ptr->name,b_ptr->name)!=0)
                {
                    printf("%d)Name in Bank: %s\n",i,b_ptr->name);
                    printf("  Name on Pan: %s\n",p_ptr->name);
                    printf("  Aadhar No: %s\n",a_ptr->aadhar_no);
                    printf("  Address: %s\n",a_ptr->address);
                    printf("\n");
                    flag1=1; flag2=1; flag3=1; i++;
                }
                l_ptr=b_ptr->lpg_ptr;
                while(l_ptr!=NULL && flag3==0)
                {
                    if(strcmp(l_ptr->name,b_ptr->name)!=0)
                    {
                        printf("%d)Name on Lpg: %s\n",i,l_ptr->name);
                        printf("  Name in Bank: %s\n",b_ptr->name);
                        printf("  Aadhar No: %s\n",a_ptr->aadhar_no);
                        printf("  Address: %s\n",a_ptr->address);
                        printf("\n");
                        flag1=1; flag2=1; flag3=1; i++;
                    }
                    l_ptr=l_ptr->next_lpg;
                }
                b_ptr=b_ptr->next_bank;
            }
            p_ptr=p_ptr->next_pan;
        }
        flag1=0,flag2=0,flag3=0;
        a_ptr=a_ptr->next;
    }
}

//Merge Bank Accounts 
Bank_Acc_Node* Que7(Bank_Acc_Node* B_lptr1,Bank_Acc_Node* B_lptr2)
{
    Bank_Acc_Node*b_ptr1=B_lptr1;
    Bank_Acc_Node*b_ptr2=B_lptr2;
    Bank_Acc_Node* result,*tail,*ptr;

    if(B_lptr1==NULL)
    {
        printf("Blptr1 is NULL\n");
        result=B_lptr2;
    }
    else if(B_lptr2==NULL)
    {
        printf("Blptr2 is NULL\n");
        result=B_lptr1;
    }
    else
    {
        result=B_lptr1;
        int flag=0;
        while(b_ptr2!=NULL)
        {
            b_ptr1=B_lptr1;
            while(b_ptr1!=NULL && flag==0)
            {
                if(strcmp(b_ptr1->bank_acc_no,b_ptr2->bank_acc_no)==0)
                {
                    flag=1;
                }
                b_ptr1=b_ptr1->next;
            }
            ptr = b_ptr2;
            b_ptr2=b_ptr2->next;
            if(flag==0)
            {
                ptr->next = result;
                result = ptr;
            }
            flag=0;
        }
    }
    return result;
}

int main()
{
    //Input data
    Aadhar_Node*A_lptr=NULL;
    A_lptr=Read_Aadhar(A_lptr);
    //Print_Aadhar(A_lptr);
    
    Pan_Node* P_lptr=NULL;
    P_lptr=Read_Pan(P_lptr);
    //Print_Pan(P_lptr);

    LPG_Node* L_lptr=NULL;
    L_lptr=Read_Lpg(L_lptr);
    //Print_Lpg(L_lptr);
    
    Bank_Acc_Node *B_lptr = NULL;
    FILE* fp;
    fp=fopen("bank.csv","r");
    B_lptr = Read_Bank(B_lptr,fp);
    //Print_Bank(B_lptr);

    //Linking All Data
    Link_Bank_Lpg(B_lptr,L_lptr);
    Link_Bank_Pan(B_lptr,P_lptr);
    Link_Aadhar_Pan(P_lptr,A_lptr);

    printf("\n(Enter 0 to EXIT)\n");
    int i=-1;
    while(i!=0)
    {
        printf("\nEnter your choice: \n");
        scanf("%d",&i);
        
        switch (i)
        {
            case 1:
            {
                Que1(A_lptr);
                break;
            }
            case 2:
            {
                Que2(A_lptr);
                break;
            }
            case 3:
            {
                Que3(A_lptr);
                break;
            }
            case 4:
            {
                Que4(A_lptr);
                break;
            }
            case 5:
            {
                int x;
                printf("Enter value of X: \n");
                scanf("%d",&x);
                Que5(A_lptr,x);
                break;
            }
            case 6:
            {
                Que6(A_lptr);
                break;
            }
            case 7:
            {
                //Reading first bank file
                fp=fopen("bank1.csv","r");
                Bank_Acc_Node* B_lptr1=NULL;
                B_lptr1=Read_Bank(B_lptr1,fp);
                //Print_Bank(B_lptr1);

                //Reading sec bank file
                fp=fopen("bank2.csv","r");
                Bank_Acc_Node* B_lptr2=NULL;
                B_lptr2=Read_Bank(B_lptr2,fp);
                //Print_Bank(B_lptr2);

                //Merging Both List
                Bank_Acc_Node* B_lptr3=NULL;
                B_lptr3=Que7(B_lptr1,B_lptr2);
                Print_Bank(B_lptr3);
                break;
            }
        }   
    }
    return 0;
}