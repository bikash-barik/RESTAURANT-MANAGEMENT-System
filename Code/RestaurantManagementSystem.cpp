#include<bits./stdc++.h>
#include<stdlib.h>
#include<string.h>
#include <iostream> 

using namespace std;
struct node
{
    char foodname[50];
    int quantity;
    int price;
    int data;
    struct node *next;
    struct node *prev;
    
    
};
struct node *headc =NULL,*newnode,*tailc=NULL;
struct node *heada =NULL,*taila=NULL;
struct node *head_s;

void adminmenu(){
    cout<<" View total sales"<<endl;
    cout<<" Add new items  in the order menu"<<endl;
    cout<<"delete items from the order menu"<<endl;
    cout<<" Display order menu"<<endl;
    cout<<" Back to menu"<<endl;
    cout<<" Enter your Choice -->"<<endl;

    }
void customermenu()
    {
    cout<<" Place your order"<<endl;;
    cout<<"1.View your ordered items"<<endl;
    cout<<"2.Delete an item from order"<<endl;
    cout<<"3.Display final bill"<<endl;
    cout<<"4.Back To Main Menu "<<endl;
    cout<<"Enter Your Choice"<<endl;
}
struct node* createadmin(struct node *head,int data, char foodname[25], float price)
{
    newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->price = price;
    newnode-> quantity = 0;
    strcpy(newnode->foodname,foodname);
    newnode->next = NULL;
    newnode->prev = NULL;
    struct node *temp=head;
    if(temp==NULL)
        heada = taila = newnode;
    else
    {
        while(temp->next!=NULL)
            temp=temp->next;

        temp->next=newnode;
        newnode->prev = taila;
        taila = newnode;
    }

    return heada;
}
struct node* createcustomer(struct node *head,int data,int quantity)
{
    newnode = (struct node*)malloc(sizeof(struct node));

    struct node *temp1 = heada;
    int flag = 0;
    while(temp1!=NULL)
    {
        if(temp1->data==data)
        {
            flag = 1;
            break;
        }
        temp1 = temp1->next;
    }

if(flag==1){
    newnode->data =data;
    newnode->price=quantity*(temp1->price);
    newnode->quantity=quantity;
    strcpy(newnode->foodname,temp1->foodname);
    newnode->next=NULL;
    newnode->prev=NULL;
    struct node *temp =head;
    if(temp==NULL)
    headc =tailc =newnode;
    
        else
        {
            while(temp->next!=NULL)
                temp=temp->next;

            temp->next=newnode;
            newnode->prev = tailc;
            tailc = newnode;
        }

    }
      else
    {
       cout<<"This item is not present in the menu!"<<endl;
    }
    return headc;
}
void displayList(struct node *head)
{
    struct node *temp1 = head;
    if(temp1==NULL)
    {
        cout<<"List is empty!!"<<endl;
    }
    else
    {
       cout<<endl;
        while(temp1!=NULL)
        {
            if(temp1->quantity==0)
               cout<<temp1->data,temp1->foodname,temp1->price;
            else
            {
                cout<<temp1->data,temp1->foodname,temp1->quantity,temp1->price;
            }

            temp1 = temp1->next;
        }
        cout<<endl;
    }

}
struct node* totalsales(int data,int quantity)
{
    newnode = (struct node*)malloc(sizeof(struct node));
    int flag = 0;

    struct node *temp1 = heada;
    while(temp1->data!=data)
    {
        temp1 = temp1->next;
    }

    newnode->data = data;
    newnode->price = quantity*(temp1->price);
    newnode-> quantity = quantity;
    strcpy(newnode->foodname,temp1->foodname);
    newnode->next = NULL;
    newnode->prev = NULL;

    struct node *temp = head_s;

    if(temp==NULL)
        head_s = newnode;
    else
    {
        while(temp->next!=NULL)
        {
            if(temp->data==data)
            {
                flag = 1;
                break;
            }
            temp=temp->next;
        }

        if(flag==1)
        {
            temp->quantity += newnode-> quantity;
            temp->price += newnode->price;
        }
        else
        {
            temp->next=newnode;
        }
    }

    return head_s;
}
void calculatetotsales(){
    struct node *temp =headc;
    while(temp!=NULL){
         head_s = totalsales(temp->data, temp->quantity);
        temp=temp->next;

    }
}

struct node* free(int data,struct node *head, struct node* tail)
{
    if(head==NULL)
    {
       cout<<"\n\t\t\t\t\t\t\tList is empty\n";
    }
    else
    {
        struct node* temp;
        if(data==head->data)
        {
            temp = head;
            head = head->next;
            if (head != NULL)
                head->prev = NULL;
            free(temp);
        }
        else if(data==tail->data)
        {
            temp = tail;
            tail = tail->prev;
            tail->next = NULL;
            free(temp);
        }
        else
        {
            temp = head;
            while(data!=temp->data)
            {
                temp = temp->next;
            }
            (temp->prev)->next = temp->next;
            (temp->next)->prev = temp->prev;
            free(temp);
        }
    }
    return head;
}
int deleteadmin()
{
    cout<<"\n\t\t\t\t\tEnter serial no. of the food item which is to be deleted: "<<endl;
    int num;
    cin>>num;

    struct node* temp=heada;
    while(temp!=NULL)
    {
        if (temp->data == num)
        {
            heada = free(num, heada, taila);
            return 1;
        }
        temp=temp->next;
    }

    return 0;
}
int deletecustomer()
{
    cout<<"\n\t\t\t\t\tEnter serial no. of the food item which is to be deleted: ";
    int num;
    cin>>num;

    struct node* temp=headc;
    while(temp!=NULL)
    {
        if (temp->data == num)
        {
            headc = free(num, headc, tailc);
            return 1;
        }
        temp=temp->next;
    }

    return 0;
}

// From Praveen
void displaybill()
{
    displayList(headc);
    struct node *temp = headc;
    float total_price = 0;
    while (temp!=NULL)
    {
        total_price +=temp->price;
        temp = temp->next;
    }

    cout<<"\t\t\t\t\t\t\tTotal price: %0.02f\n"<<total_price;
}

struct node* deleteList(struct node* head)
{
    if(head==NULL)
    {
        return NULL;
    }
    else
    {
        struct node* temp = head;
        while(temp->next!=0)
        {
            temp = temp->next;
            free(temp->prev);
        }
        free(temp);
        head = NULL;
    }

    return head;
}

//void admin()
//{
//    cout<<"\n\t\t\t\t\t   ----------------------------------------------\n";
//    cout<<"\t\t\t\t\t\t\t    ADMIN SECTION\n";
//    cout<<"\t\t\t\t\t   ----------------------------------------------\n";
//    while(1)
//    {
//        adminmenu();
//
//        int opt;
//        cin>>opt;
//
//        if(opt==5)
//            break;
//
//        switch (opt)
//        {
//            case 1:
//                displayList(head_s);
//                break;
//            case 2:
//
//                cout<<"\n\t\t\t\t\t\t\tEnter serial no. of the food item: ";
//                int num;
//				int flag = 0;
//                char name[50];
//                float price;
//                cin>>num;
//                //int temp;
//                struct node *temp = heada;
//
//                while(temp!=NULL)
//                {
//                    if(temp->data==num)
//                    {
//                        cout<<"\n\t\t\t\t\t\tFood item with given serial number already exists!!\n\n";
//                        flag = 1;
//                        break;
//                    }
//                    temp = temp->next;
//                }
//
//                if(flag==1)
//				{
//			
//                    break;
//                }
//                else{
//                cout<<"\t\t\t\t\t\t\tEnter food item name: ";
//                cin>>name;
//                cout<<"\t\t\t\t\t\t\tEnter price: ";
//                cin>>price;
//                heada = createadmin(heada, num, name, price);
//                cout<<"\n\t\t\t\t\t\t\tNew food item added to the list!!\n\n";
//                break;
//                }
//            case 3:
//                if(deleteadmin())
//                {
//                    cout<<"\n\t\t\t\t\t\t### Updated list of food items menu ###\n";
//                    displayList(heada);
//                }
//                else{
//			
//                    cout<<"\n\t\t\t\t\t\tFood item with given serial number doesn't exist!\n\n";
//                    break;
//              	}
//            case 4:
//                cout<<"\n\t\t\t\t\t\t\t   ### Order menu ###\n";
//                displayList(heada);
//                break;
//            
//            default:
//                cout<<"\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n";
//                break;
//        }
//    }
//}

void customer()
{
    int flag=0,j=1;
    char ch;
    cout<<"\n\t\t\t\t\t   ----------------------------------------------\n";
    cout<<"\t\t\t\t\t\t\t    CUSTOMER SECTION\n";
    cout<<"\t\t\t\t\t   ----------------------------------------------\n";
    while(1)
    {
        customermenu();

        int opt;
        cin>>opt;

        if(opt==5)
            break;

        switch (opt)
        {
            case 1:
                displayList(heada);
                cout<<"\n\t\t\t\t\t\tEnter number corresponding to the item you want to order: ";
                int n;
                cin>>n;
                cout<<"\t\t\t\t\t\tEnter quantity: ";
                int quantity;
                cin>>quantity;
                headc = createcustomer(headc, n, quantity);
                break;
            case 2:
                cout<<"\n\t\t\t\t\t\t\t  ### List of ordered items ###\n";
                displayList(headc);
                break;
            case 3:
                if(deletecustomer())
                {
                    cout<<"\n\t\t\t\t\t\t### Updated list of your ordered food items ###\n";
                    displayList(headc);
                }
                else
                    cout<<"\n\t\t\t\t\t\tFood item with given serial number doesn't exist!!\n";
                break;
            case 4:
                calculatetotsales();
                cout<<"\n\t\t\t\t\t\t\t  ### Final Bill ###\n";
                displaybill();
                headc = deleteList(headc);
                cout<<"\n\t\t\t\t\t\tPress any key to return to main menu:\n\t\t\t\t\t\t";
                fflush(stdin);
                ch=fgetc(stdin);
                flag=1;
                break;

            default:
                cout<<"\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n";
                break;
        }
        if(flag==1)
            break;
    }
}

void mainnenu()
{
    cout<<"\n                                 **************************************************************************\n";
    cout<<"                                                     WELCOME TO RESTAURANT MANAGEMENT SYSTEM\n";
    cout<<"                                 **************************************************************************\n\n\n";
    cout<<"\t\t\t\t\t\t\t1. ADMIN SECTION--> \n";
    cout<<"\t\t\t\t\t\t\t2. CUSTOMER SECTION--> \n";
    cout<<"\t\t\t\t\t\t\t3. Exit--> \n\n";
    cout<<"\t\t\t\t\t\t\tEnter Your Choice --->";
}

int main()
{
    heada = createadmin(heada,1,"Hot and Sour Soup",100);
    heada = createadmin(heada,2,"Manchow Soup",200);
    heada = createadmin(heada,3,"Manchurian Noodles",150);
    heada = createadmin(heada,4,"Fried Rice",180);
    heada = createadmin(heada,5,"Hakka Noodles",80);

    while(1)
    {
        mainnenu();
        int choice;
        scanf("%d",&choice);

        if(choice==3)
        {
            cout<<"\n\n\t\t\t\t\t\t\t**********Thank you!!**********\n";
            break;
        }

        switch (choice)
        {
            case 1:
                //admin();
                break;
            case 2:
                customer();
                break;
            case 3:
                break;

            default:
                cout<<"\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n";
                break;
        }
    }
    return 0;
}







