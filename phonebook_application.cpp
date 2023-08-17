#include <iostream>
#include <fstream>
#include <string.h>
#include <iomanip>
#include <stdio.h>

using namespace std;

class PhoneBook
{
char name[20],phno[11];
public:
void Getdata();
void Showdata();
char *getname(){ return name; }
char *getphno(){ return phno; }
void update(char *times,char *phoneNumber)
{
    strcpy(name,times);
    strcpy(phno,phoneNumber);
}
    void NewContact();
    void DisplayContact();
    void DisplayContact(char *times);
    void SearchContact();
    void UpdateContactInformation();
    void DeletePhoneBook();

};

void PhoneBook :: Getdata()
{
    cout<<"\nEnter Name : ";
    cin>>name;
    repeat:
    cout<<"Enter Phone No. : ";
    cin>>phno;

    for(int i=0;i<strlen(phno);i++)
      {
           try
           {
                if(phno[i]<48 || phno[i]>57||strlen(phno)!=10)
                throw phno[i];
           }
           catch(char a)
           {
               cout<<"Enter a valid number"<<endl;
               cout<<"Try again"<<endl;
               goto repeat;
           }
      }

}

void PhoneBook :: Showdata(){
    cout<<"\n";
    cout<<setw(20)<<" Name : "<<name;
    cout<<setw(15)<<" Number : "<<phno;

}

void PhoneBook :: NewContact()
{
    int found=0;
    char rrep[11];
    char timesopi[20];

        Getdata();
          strcpy(timesopi,name);
        strcpy(rrep,phno);
    fstream file;
     file.open("phone.txt", ios::in | ios::app | ios::binary );
    while(file.read((char *) this, sizeof(*this)))
    {
        if(strcmp(rrep,getphno())==0)
        {
            found=1;
            break;
        }
    }
    file.clear();
      file.close();
    if(found==1)
        cout<<"\n\n---Contact already exist---\n";

    else
    {
        file.open("phone.txt", ios::app | ios::binary );
        update(timesopi,rrep);
        file.write((char *) this, sizeof(*this));
        cout<<"Contact Created Succesfully\n";
        file.close();
    }


}
void PhoneBook :: DisplayContact()
{

    fstream file;
    file.open("phone.txt", ios::ate | ios::in | ios::out | ios::binary );
    file.seekg(0,ios::beg);
    cout<<"\n\nRecords in Phone Book\n";
    while(file)
    {
        file.read((char *) this, sizeof(*this));
        if(!file.eof())
            Showdata();
    }
    file.clear();
    file.close();
}

void PhoneBook :: DisplayContact(char *times)
{
    char c,phoneNumber[11];
    int cnt,found=0;

    fstream file;
    file.open("phone.txt", ios::ate | ios::in | ios::out | ios::binary );
    file.seekg(0,ios::beg);
    while(file.read((char *) this, sizeof(*this)))
    {

        if(strcmp(times,getname())==0)
        {
            found=1;
            Showdata();
        }
    }
    file.clear();
    if(found==0)
        cout<<"\n\n---Record Not found---\n";
    file.close();

}

void PhoneBook :: SearchContact()
{
    char c,ch,times[20],phoneNumber[11];
    int cnt,found=0;
    cout<<"\n\nEnter Name or Phone No : ";
    cin>>phoneNumber;
    fstream file;
    file.open("phone.txt", ios::ate | ios::in | ios::out | ios::binary );
    file.seekg(0,ios::beg);
    while(file.read((char *) this, sizeof(*this)))
    {
        if(strcmp(phoneNumber,getphno())==0)
        {
            found=1;
            Showdata();
        }
    }
    file.clear();
    if(found==0)
    {
       DisplayContact(phoneNumber);
    }
    file.close();

}


    void PhoneBook :: UpdateContactInformation()
     {
               int intValue;
                fstream file;
                  file.open("phone.txt", ios::ate | ios::in | ios::out | ios::binary );
               cout<<"Enter 1 to update name"<<endl;
                 cout<<"Enter 2 to update phone number"<<endl;
                 cin>>intValue;
                 if(intValue==1)
               { char c,ch,times[20],newtimes[15],phoneNumber[15];
                 int cnt=0,found=0;
                 cout<<"\n\nEnter Name : ";
                 cin>>times;
                file.seekg(0,ios::beg);
                 while(file.read((char *) this, sizeof(*this)))
                 {
                    cnt++;
                    if(strcmp(times,getname())==0)
                    {
                        found=1;
                        break;
                    }
                 }
                 file.clear();
                 if(found==0)
                    cout<<"\n\n---Contact Not found---\n";
                 else
                 {  strcpy(phoneNumber,phno);
                    int location = (cnt-1) * sizeof(*this);
                    cin.get(ch);
                    if(file.eof())
                        file.clear();

                    cout<<"Enter New Name: ";
                    cin>>newtimes;
                    file.seekp(location);
                    update(newtimes,phoneNumber);
                    file.write((char *) this, sizeof(*this));
                    file.flush();
                 }
               }
               if(intValue==2)
               {
                   char c,ch,times[20],phoneNumber[15],newphoneNumber[15];
                 int cnt=0,found=0;
                 cout<<"\n\nEnter Phone number : ";
                 cin>>phoneNumber;
                file.seekg(0,ios::beg);
                 while(file.read((char *) this, sizeof(*this)))
                 {
                    cnt++;
                    if(strcmp(phoneNumber,getphno())==0)
                    {
                        found=1;
                        break;
                    }
                 }
                 file.clear();
                 if(found==0)
                    cout<<"\n\n---Contact Not found---\n";
                 else
                 {  strcpy(times,name);
                    int location = (cnt-1) * sizeof(*this);
                    cin.get(ch);
                    if(file.eof())
                        file.clear();

                    cout<<"Enter New Phone number: ";
                    cin>>newphoneNumber;
                    file.seekp(location);
                    update(times,newphoneNumber);
                    file.write((char *) this, sizeof(*this));
                    file.flush();
                 }
               }

                 file.close();
            }


void PhoneBook :: DeletePhoneBook()
{
    char conctName[20],phoneNumber[11];
    cout<<"Enter the name of the contact which is to be deleted:";
    cin>>conctName;
    fstream file;
    file.open("phone.txt",  ios::in | ios::binary );
    fstream fout;
    fout.open("tempfile.txt",ios::out | ios::binary);
    int i=0,j=0,found=0;
    file.read((char *) this, sizeof(*this));
    while(!file.eof())
    {
        i++;
        if(strcmp(conctName,getname()))
        {
            fout.write((char*)this,sizeof(*this));
            j++;
        }
//        found++
        file.read((char*)this,sizeof(*this));


    }
    fout.close();
    file.close();
    if(i-j<=1)
    {

        file.close();
        remove("phone.txt");
        rename("tempfile.txt","phone.txt");
        if(j<i)
        cout<<"CONTACT DELETED"<<endl;


        if(j==i)
        cout<<"CONTACT NOT FOUND"<<endl;

    }
    else
    {
        cout<<"\n\nTWO SAME CONTACT NAMES EXIST\n"<<endl;
        file.open("phone.txt", ios::ate | ios::in | ios::out | ios::binary );
        file.seekg(0,ios::beg);
    while(file.read((char *) this, sizeof(*this)))
    {
        if(strcmp(conctName,getname())==0)
        {
            found=1;
            Showdata();
            cout<<endl;
        }
    }
        file.clear();
        file.close();
        cout<<"\n\n NOW ENTER THE CONTACT NUMBER YOU WANT TO DELETE :  "<<endl;
        cin>>phoneNumber;
        //fstream file;
        file.open("phone.txt",  ios::in | ios::binary );
    //    fstream fout;
        fout.open("tempfileph.txt",ios::out | ios::binary);
    //  int i=0,j=0,found=0;
        file.read((char *) this, sizeof(*this));
        i=0;
        j=0;
        while(!file.eof())
        {
            i++;
            if(strcmp(phoneNumber,getphno()))
            {
                fout.write((char*)this,sizeof(*this));
                j++;
            }
    //        found++
            file.read((char*)this,sizeof(*this));
        }
        fout.close();
        file.close();
        remove("phone.txt");
        rename("tempfileph.txt","phone.txt");
        if(j<i)cout<<"\n\nCONTACT DELETED\n\n"<<endl;
        else cout<<"CONTACT NOT FOUND"<<endl;
    }


}

int main()
{
    PhoneBook book;
    int selectOption;

    while(1)
    {
                char times[20];
        cout<<"\n*****Phone Book -Developed by Shadrack  *****\n";
        cout<<"1) Search Contact\n";
        cout<<"2) Create a new Contact\n";
        cout<<"3) Display All Contacts\n";
        cout<<"4) Edit Contact \n";
        cout<<"5) Delete a Contact \n";
        cout<<"6) Exit Application\n";
        cout<<"Choose your Choice : ";
        cin>>selectOption;
        switch(selectOption)
        {
            case 1 :
                book.SearchContact();

                 break;

            case 2 :
                book.NewContact();
              break;

            case 3 :book.DisplayContact();
            break;

            case 4 :book.UpdateContactInformation();
                 break;

           case 5:   book.DeletePhoneBook();
                    break;

           case 6:  exit(1);

           default:
                cout<<"Please enter a valid option!!"<<endl;

        }

    


return 0;
}

