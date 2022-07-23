#include<bits/stdc++.h>

using namespace std;

class node{
    public:
        char foodname[50];
        int quantity;
        float price;
        int data;
        node* next;
};

node *headc = NULL, *newnode, *tailc = NULL;
node *heada = NULL, *taila = NULL;
node *head_s;


void adminmenu(){
    // Func defines options available for admin
    cout << "\n\t\t\t\t\t\t\t1. View total sales\n";
    cout << "\t\t\t\t\t\t\t2. Add new items in the order menu\n";
    cout << "\t\t\t\t\t\t\t3. Delete items from the order menu\n";
    cout << "\t\t\t\t\t\t\t4. Display order Menu\n";
    cout << "\t\t\t\t\t\t\t5. Back to main Menu\n";
    cout << "\t\t\t\t\t\t\t     Enter Your Choice ---> \n";
}

void customermenu(){
    // Func defines options for customer
    cout << "\n\t\t\t\t\t\t\t1. Place your order\n";
    cout << "\t\t\t\t\t\t\t2. View your ordered items\n";
    cout << "\t\t\t\t\t\t\t3. Delete an item from order\n";
    cout << "\t\t\t\t\t\t\t4. Display final bill\n";
    cout << "\t\t\t\t\t\t\t5. Back To Main Menu \n\n";
    cout << "\t\t\t\t\t\t\t     Enter Your Choice --->\n";
}

node *createadmin(node *head, int data, char foodname[25], float price){
    // Func creates a node for admin's linked list
    node *newnode = new node;

    newnode->data = data;
    newnode->price = price;
    newnode->quantity = 0;
    strcpy(newnode->foodname, foodname);
    newnode->next = NULL;

    node *temp = head;
    if(temp == NULL)heada = taila = newnode;
    else{
        while(temp->next != NULL) temp = temp->next;

        temp->next = newnode;
        taila = newnode;
    }
    return heada;
}

node *createcustomer(node *head, int data, int quatity){
    // Func create node of customer's linked list
    node *temp1 = heada;
    int flag = 0;
    while(temp1 != NULL){
        if(temp1->data == data){
            flag = 1;
            break;
        }
        temp1 = temp1->next;
    }
    if(flag == 1){
        newnode->data = data;
        newnode->price = quatity * (temp1->price);
        newnode->quantity = quatity;
        strcpy(newnode->foodname, temp1->foodname);
        newnode->next = NULL;
        node *temp = head;

        if(temp == NULL)headc = tailc = newnode;
        else{
            while(temp->next != NULL) temp = temp->next;

            temp->next = newnode;
            tailc = newnode;
        }
    }else{
    cout << "\n\t\t\t\t\t\t\t This item is not present in the menu!\n";
    }
    return headc;
}

void displayList(node *head){
    // Func displays the items whose head pointer is passed
    node *temp1 = head;

    if(temp1 == NULL){
    cout << "\n\t\t\t\t\t\t\t List is empty!!\n\n";
    }else{
        cout << "\n";
        while(temp1 != NULL){
            if(temp1->quantity == 0)
                cout << "\t\t\t\t\t\t\t temp1->data \t temp1->foodname \t temp1->price";
            else{
                cout << "\t\t\t\t\t\t\t temp1->data \t temp1->foodname \t temp1->quantity \t temp1->price";
            }
            temp1 = temp1->next;
        }
        cout << "\n";
    }
}

node *totalsales(int data, int quantity){
    node *newnode = new node;
    int flag = 0;
    node *temp1 = heada;
    while(temp1->data != data) temp1 = temp1->next;

    newnode->data = data;
    newnode->price = quantity*(temp1->price);
    newnode->quantity = quantity;
    strcpy(newnode->foodname, temp1->foodname);
    newnode->next = NULL;

    node *temp = head_s;
    if(temp == NULL) head_s = newnode;
    else{
        while(temp->next != NULL){
            if(temp->data == data){
                flag = 1;
                break;
            }
            temp = temp->next;
        }
        if(flag == 1){
            temp->quantity += newnode->quantity;
            temp->price += newnode->price;
        }else{
            temp->next = newnode;
        }
    }
    return head_s;
}


void calculatetotsales(){
    node *temp = headc;
    while(temp != NULL){
        head_s = totalsales(temp->data, temp->quantity);
        temp = temp->next;
    }
}


node *delette(int data, node *head, node *tail){
    if(head == NULL) cout<<"\n\t\t\t\t\t\t\tList is empty\n";
    else{
        node *temp;
        if(data == head->data){
            temp = head;
            head = head->next;
            delete temp;
        }else if(data == tail->data){
            temp = tail;
            tail->next = NULL;
            delete temp;
        }else{
            temp = head;
            node *temp1 = temp;
            while (data != temp->data){
                temp1 = temp;
                temp = temp->next;
            }
            temp1->next = temp->next;
            delete temp;
        }
    }
    return head;
}

int deleteadmin(){
    cout << "\n\t\t\t\t\tEnter serial no. of the food item which is to be deleted: ";
    int num;
    cin >> num;

    node *temp = heada;
    while(temp){
        if(temp->data == num){
            heada = delette(num, heada, taila);
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

int deletecustomer(){
    cout << "\n\t\t\t\t\tEnter serial no. of the food item which is to be deleted: ";
    int num;
    cin >> num;

    node *temp = headc;
    while(temp){
        if(temp->data == num){
            headc = delette(num, headc, tailc);
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

void displaybill(){
    displayList(headc);
    node *temp = headc;
    float total_price = 0;
    while(temp){
        total_price += (temp->quantity) * (temp->price);
        temp = temp->next;
    }
    cout << "\t\t\t\t\t\t\t Total price: " << total_price;
}

node *deleteList(node *head){
    if(head == NULL)return NULL;
    else{
        node *n, *temp = head;
        while(temp != NULL){
            n = temp->next;
            delete temp;
            temp = n;
        }
        head = NULL;
    }
}


void admin()
{
    cout << "\n\t\t\t\t\t   ----------------------------------------------\n";
    cout << "\t\t\t\t\t\t\t    ADMIN SECTION\n";
    cout << "\t\t\t\t\t   ----------------------------------------------\n";
    
    while(1){
        adminmenu();

        int opt;
        cout << "%d",&opt;

        if(opt==5)break;

        switch (opt){
            case 1:
                displayList(head_s);
                break;
            case 2:

                cout << "\n\t\t\t\t\t\t\tEnter serial no. of the food item: ";
                int num,flag = 0;
                char name[50];
                float price;
                cout << "%d",&num;

                struct node *temp = heada;

                while(temp!=NULL){
                    if(temp->data==num){
                        cout << "\n\t\t\t\t\t\tFood item with given serial number already exists!!\n\n";
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }

                if(flag==1)break;

                cout << "\t\t\t\t\t\t\tEnter food item name: ";
                cout << "%s",name;
                cout << "\t\t\t\t\t\t\tEnter price: ";
                cout << "%f",&price;
                heada = createadmin(heada, num, name, price);
                cout << "\n\t\t\t\t\t\t\tNew food item added to the list!!\n\n";
                break;
            case 3:
                if(deleteadmin()){
                    cout << "\n\t\t\t\t\t\t### Updated list of food items menu ###\n";
                    displayList(heada);
                }
                else 
                    cout << "\n\t\t\t\t\t\tFood item with given serial number doesn't exist!\n\n";

                break;
            case 4:
                printf("\n\t\t\t\t\t\t\t   ### Order menu ###\n");
                displayList(heada);
                break;

            default:
                cout << "\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n";
                break;
        }
    }
}


void customer(){
    int flag=0,j=1;
    char ch;
    cout << "\n\t\t\t\t\t   ----------------------------------------------\n";
    cout << "\t\t\t\t\t\t\t    CUSTOMER SECTION\n";
    cout << "\t\t\t\t\t   ----------------------------------------------\n";
    while(1){
        customermenu();

        int opt;
        cout << "%d",&opt;

        if(opt==5) break;

        switch (opt){
            case 1:
                displayList(heada);
                cout << "\n\t\t\t\t\t\tEnter number corresponding to the item you want to order: ";
                int n;
                cout <<"%d",&n;
                cout << "\t\t\t\t\t\tEnter quantity: ";
                int quantity;
                cout << "%d",&quantity;
                headc = createcustomer(headc, n, quantity);
                break;
            case 2:
                cout << "\n\t\t\t\t\t\t\t  ### List of ordered items ###\n";
                displayList(headc);
                break;
            case 3:
                if(deletecustomer()){
                    cout << "\n\t\t\t\t\t\t### Updated list of your ordered food items ###\n";
                    displayList(headc);
                }
                else
                    cout << "\n\t\t\t\t\t\tFood item with given serial number doesn't exist!!\n";
                break;
            case 4:
                calculatetotsales();
                cout << "\n\t\t\t\t\t\t\t  ### Final Bill ###\n";
                displaybill();
                headc = deleteList(headc);
                cout << "\n\t\t\t\t\t\tPress any key to return to main menu:\n\t\t\t\t\t\t";
                fflush(stdin);
                ch=fgetc(stdin);
                flag=1;
                break;

            default:
                cout << "\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n";
                break;
        }
        if(flag==1)
            break;
    }
}


void mainnenu(){
    cout << "\n                                 **************************************************************************\n";
    cout << "                                                     WELCOME TO RESTAURANT MANAGEMENT SYSTEM\n";
    cout << "                                 **************************************************************************\n\n\n";
    cout << "\t\t\t\t\t\t\t1. ADMIN SECTION--> \n";
    cout << "\t\t\t\t\t\t\t2. CUSTOMER SECTION--> \n";
    cout << "\t\t\t\t\t\t\t3. Exit--> \n\n";
    cout << "\t\t\t\t\t\t\tEnter Your Choice --->";
}


int main(){
    heada = createadmin(heada,1,"Hot and Sour Soup",100);
    heada = createadmin(heada,2,"Manchow Soup",200);
    heada = createadmin(heada,3,"Manchurian Noodles",150);
    heada = createadmin(heada,4,"Fried Rice",180);
    heada = createadmin(heada,5,"Hakka Noodles",80);

    while(1){
        mainnenu();
        int choice;
        cout << "%d",&choice;

        if(choice==3){
            cout << "\n\n\t\t\t\t\t\t\t**********Thank you!!**********\n";
            break;
        }

        switch (choice){
            case 1:
                admin();
                break;
            case 2:
                customer();
                break;
            case 3:
                break;

            default:
                cout << "\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n";
                break;
        }
    }
}