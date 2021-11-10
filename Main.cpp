//Billing System Project By Mr. Vikas Bharti

#include<iostream>
#include<iomanip> //for designing purpose...
#include<conio.h>
#include<stdio.h>
#include<fstream> //file handling...

using namespace std;
fstream file, file1; //for file accessing..

class product
{
    int pno;
    string name;
    float price, qty, tax, dis;

public:
    void create();
    void show();
    void write();
    void display();
    void admin();
    void search(int n);
    void modify(int n);
    void del(int n);
    void order();
    void menu();
};


void product :: create()
{
    cout<<"\n\n Please Enter The Product No. Of the Product : ";
    cin>>pno;
    cout<<"\n\n Please Enter the Name of The Product : ";
    cin>>name;
    cout<<"\n\n Please Enter the Price of the Product : ";
    cin>>price;
    cout<<"\n\n Please Enter the Discount (%): ";
    cin>>dis;
}

void product ::show()
{
    cout<<"\n The Product No. of the Product : "<<pno;
    cout<<"\n The Name of the Product : "<<name;
    cout<<"\n The Price of the Product : "<<price;
    cout<<"\n Discount : "<<dis<<"%";
}
void product :: write()
{
    file.open("Shop.txt", ios::out|ios::app);
    create();
    file<<" "<<pno<<" "<<name<<" "<<price<<" "<<dis<<" ";
    file.close();
    cout<<"\n\n The Product Has Been CREATED ";
    getch();
}

void product::display()
{
    system("cls");
    cout<<"\n\n\n\t\t DISPLAY ALL RECORDS !!!\n\n";
    file.open("Shop.txt", ios::in);
    if(!file)
    admin();
    file>>pno>>name>>price>>dis;
    while(!file.eof())
    {
        show();
        cout<<"\n\n ===================================================================\n";
        file>>pno>>name>>price>>dis;
    }
    file.close();
    getch();
}

void product::search(int n)
{
    int found=0;
    file.open("Shop.txt", ios::in);
    if(!file)
    admin();
    file>>pno>>name>>price>>dis;
    while(!file.eof())
    {
        if(pno==n)
        {
            system("cls");
            show();
            found = 1;
        }
    file>>pno>>name>>price>>dis;
    }
    file.close();
    if(found == 0)
    cout<<"\n\n Record Doesn't Exist";
    getch();
}

void product::modify(int n)
{
    int found=0;
    system("cls");
    cout<<"\n\n\t TO MODIFY ";
    file.open("Shop.txt", ios::in);
    if(!file)
    admin();
    file1.open("Shop1.txt", ios::out|ios::app);
    file>>pno>>name>>price>>dis;
    while(!file.eof())
    {
        if(pno==n)
        {
            show();
            cout<<"\n\n Please Enter The New Details of the Product : ";
            create();
            file1<<" "<<pno<<" "<<name<<" "<<price<<" "<<dis<<" ";
            cout<<"\n\n\t RECORD UPDATED";
            found=1;
        }
        else
        file1<<" "<<pno<<" "<<name<<" "<<price<<" "<<dis<<" ";
        file>>pno>>name>>price>>dis;
    }
    file.close();
    file1.close();
    remove("Shop.txt");
    rename("Shop1.txt", "Shop.txt");
    if(found==0)
        cout<<"\n\n RECORD NOT FOUND ";
    getch();
}

void product::del(int n)
{
    int found=0;
    file.open("Shop.txt", ios::in);
    if(!file)
        admin();
    file1.open("Shop1.txt", ios::out);
    file>>pno>>name>>price>>dis;
    while(!file.eof())
    {
        if(pno==n)
        {
            cout<<"\n\n\t RECORD DELETED";
            found=1;
        }
        else
        file1<<" "<<pno<<" "<<name<<" "<<price<<" "<<dis<<" ";
        file>>pno>>name>>price>>dis;
    }
    file.close();
    file1.close();
    remove("Shop.txt");
    rename("Shop1.txt", "Shop.txt");
    if(found==0)
        cout<<"\n\n RECORD NOT FOUND ";
    getch();
}

void product :: menu()
{
    system("cls");
    file.open("Shop.txt", ios::in);
    cout<<"\n\n\t\t PRODUCT MENU \n\n";
    cout<<"=================================================================";
    cout<<"P.No.\t\t NAME \t\t PRICE \n";
    cout<<"=================================================================";
    file>>pno>>name>>price;
    while(!file.eof())
    {
        cout<<pno<<"\t\t"<<name<<"\t\t"<<price<<"\n\n";
        file>>pno>>name>>price>>dis;
    }
    file.close();
}

void product :: order()
{
    int order_arr[50], quant[50], c=0;
    float amt=0, damt=0, total=0;
    char ch;
    file.open("Shop.txt", ios::in);
    if(file)
    {
        file.close();
        menu();
        cout<<"\n\n============================================";
        cout<<"\n\n          PLACE YOUR ORDER";
        cout<<"\n\n============================================\n";
        do
        {
            cout<<"\n\n Enter the Product No. of the Product";
            cin>>order_arr[c];
            cout<<"\n Quantity in Number : ";
            cin>>quant[c];
            c++;
            cout<<"\n Do You want to Order Another Product ?(Y/N)or (y/n)";
            cin>>ch;
        }while(ch=='y' || ch=='Y');
        cout<<"\n\n Thank You For Placing The Order"; getch();system("cls");
        cout<<"\n\n ****************************INVOICE****************************\n";
        cout<<"\n Pr No. \t Pr Name \t Quantity \t Price \t Amount After Discount\n";
        for(int x=0; x<=c; x++)
        {
            file.open("Shop.txt", ios::in);
            file>>pno>>name>>price>>dis;
            while(!file.eof())
            {
                if(pno == order_arr[x])
                {
                    amt=price*quant[x];
                    damt=amt-(amt/100*dis);
                    cout<<"\n"<<order_arr[x]<<"\t"<<name;
                    total+=damt;
                }
            file>>pno>>name>>price>>dis;
            }
        file.close();
        }
    cout<<"\n\n\t\t\t\t\t TOTAL = "<<total;
    getch();
    }
}

void product :: admin()
{
    system("cls");
    int choice;
    cout<<"\n\n\n\t ADMIN MENU";
    cout<<"\n\n\t 1. CREATE PRODUCT";
    cout<<"\n\n\t 2. DISPLAY ALL PRODUCTS";
    cout<<"\n\n\t 3. SEARCH PRODUCT";
    cout<<"\n\n\t 4. MODIFY PRODUCT";
    cout<<"\n\n\t 5. DELETE PRODUCT";
    cout<<"\n\n\t 6. VIEW PRODUCT MENU";
    cout<<"\n\n\t 7. BACK TO MAIN MENU";
    cout<<"\n\n\t Please Enter Your Choice (1-7): ";
    cin>>choice;
    switch(choice)
    {
    case 1: system("cls");
        write();
        break;
    case 2: display();
        break;
    case 3:
        int num;
        system("cls");
        cout<<"\n\n\t Please Enter the Product No.:";
        cin>>num;
        search(num);
        break;
    case 4:
        system("cls");


    case 5:
        system("cls");
        cout<<"\n\n\t\t\t DELETE RECORD";
        cout<<"\n\n Please Enter The Product No. ";
        cin>>num;
        del(num);
        break;
    case 6: menu();
        getch();
    case 7: break;
        default: cout<<"\a"; admin();
    }
}

main()
{
    product p;
    h:
        int choice;
        system("cls");
        cout<<"\n\n\n\t MAIN MENU";
        cout<<"\n\n\t 01. CUSTOMER";
        cout<<"\n\n\t 02. Admin";
        cout<<"\n\n\t 03. EXIT";
        cout<<"\n\n\t Please Select Your Option (1-3)";
        cin>> choice;
        switch(choice)
        {
        case 1: system("cls");
                p.order();
            getch();

        case 2: p.admin();
                break;

        case 3: exit(0);

        default: cout<<"\a";
        }
    goto h;
}
