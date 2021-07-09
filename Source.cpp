#include<iostream>
#include<windows.h>
#include <sstream>
#include <conio.h>
#include <vector>
#include <fstream>
#include <istream>
#include<string>
#include<sstream>

using namespace std;
float stepen(int a, int b)
{
    float stepen1 = 1;
    for (int i = 1; i <= b; i++)
    {
        stepen1 = stepen1 * a;
    }
    return stepen1;
};

int countlines(const string& filename) {
    int C_LINES = 0;
    fstream parkfile; //stream for our i-file
    parkfile.open(filename, ios::in); //open a file to perform read operation using file object
    if (parkfile.is_open()) {   //checking whether the file is open
        string atr; //atribute
        while (getline(parkfile, atr)) {
            C_LINES++;
        }
    }
    return C_LINES;
};

struct curs
{
    float  kurscyfra;
    curs();
    curs(int&);

};
curs::curs() : kurscyfra(0)
{

}
curs::curs(int& kol) : kurscyfra(kol)
{

}
struct iloszcz
{
    int ilcyfra;
    iloszcz();
    iloszcz(int&);
};
iloszcz::iloszcz() :ilcyfra(0)
{
}
iloszcz::iloszcz(int& kol) : ilcyfra(kol)
{

}
class day {
public:
    int day_n;
};
class tydzien{
public:
    int tydzien_n;
};
class month {
public:
    int month_n;
};
class widoc :public day, public tydzien, public month, public curs
{
    float deference = 0;
public:
    widoc();

    void print_data(widoc[10] );
    void download_widoc(const string&, widoc[10]);
};

widoc::widoc()
{
    deference = 0;
    day_n = 1;
    tydzien_n = 1;
    month_n = 1;
    kurscyfra = 0;

}
void widoc::print_data(widoc y_2[10])
{
    

    for (int i = 0; i < 10; i++)
    {
        y_2[i + 1].deference = y_2[i + 1].kurscyfra - y_2[i].kurscyfra;
        cout << y_2[i].day_n <<"."<< y_2[i].tydzien_n<<"." << y_2[i].month_n<<" " << y_2[i].kurscyfra <<" "<<y_2[i].deference << endl;
        
    }
    
}
void widoc::download_widoc(const string& inputfile,widoc y_2[10])
{
    fstream myfile; //stream for our i-file
    myfile.open(inputfile, ios::in); //open a file to perform read operation using file object
    widoc w1;
    if (myfile.is_open())
    {   //checking whether the file is open
        string atr; //atribute
        int counterlines = 0;
        int i = 0;
       
        while (getline(myfile, atr)&& i<10)
        { //read data from file
            string word = "";
            counterlines++;
            int k = 0; //counter
            if (counterlines > 1)
            {
                for (auto x : atr)
                {
                    if (x == '|' && k < 4)
                    {
                        k++;

                        if (k == 1) {
                            w1.day_n =stoi( word);

                        }

                        if (k == 2) {
                            w1.tydzien_n = stoi(word);
                            /*cout << b.title << " | ";*/
                        }
                        if (k == 3) {
                            w1.month_n = stoi(word);

                           
                        }
                        if (k == 4) {
                            w1.kurscyfra= stof(word);
                            k = 0;
                            y_2[i] = w1;
                            i++;
                            
                         
                        }
                        word = "";
                    }
                    else
                    {
                        word = word + x;
                    }

                }
            }
            //close the file object.
        }
    }
    myfile.close();
}

class currency :iloszcz, curs
{
public:
    string nazwa;
    curs  curs1;
    iloszcz il;
    currency(std::string name);
    currency();
    void currency_out_put();
    currency(const string&, float&, int&);
    void set(const string&, float&, int&);
};



class elemet_of_list_of_currency
{
public:
    currency my_currency;
    elemet_of_list_of_currency* next;
    elemet_of_list_of_currency* head;
    void write_out_element_currency();

};
class list_of_currency
{
public:
    elemet_of_list_of_currency* head;
    void add_currency(currency& said);
    void write_out_list();
    void download_file_to_list_currency(const string inputfile);
    void delete_currency_from_list(elemet_of_list_of_currency*);
    list_of_currency();
    elemet_of_list_of_currency* find_currency(const string&, list_of_currency&);
    void save_to_file(const string&);
    void change_iloszcz(string&, int&, list_of_currency&);
};
void list_of_currency::change_iloszcz(string& name_currency, int& il_ch, list_of_currency& list2)
{
    find_currency(name_currency, list2)->my_currency.il.ilcyfra = +il_ch;
}
struct operacja
{
    int id;
    bool stan;
    currency currency1, currency2;
    iloszcz il1, il2;
    curs kurs3;
    operacja();
    void oper_out();
    friend ostream& operator << (ostream& s, operacja&);

};
ostream& operator <<(ostream& s,  operacja& p)
{
    s << p.id << ' ' << p.stan;

    return s;
}

operacja::operacja()
{
    id = 0;
    stan = 0;
    currency1 = currency();
    currency2 = currency();
    il1 = il2 = iloszcz();
    kurs3 = curs();




}
void operacja::oper_out() {
    cout << id << "|";
    cout << stan << "|";
    cout << currency1.nazwa << "|";
    cout << currency2.nazwa << "|";
    cout << il1.ilcyfra << "|";
    cout << il2.ilcyfra << "|";
    cout << kurs3.kurscyfra << "|";
    cout << endl;
}

struct element_list_of_oper
{
    operacja my_oper;
    element_list_of_oper* next;
    element_list_of_oper* head;


};
class list_of_oper : element_list_of_oper
{
public:
    element_list_of_oper* head;
    list_of_oper();
    void add_operation_to_list(operacja&);
    void list_of_oper_out();
    void list_of_oper_from_file(const string&, list_of_currency&);
    element_list_of_oper* chek_oper(int&);
    void make_operation(const string&, const string&, int&, list_of_currency&);
    void safe_list_of_oper(const string&);
    void delete_oper(element_list_of_oper*);



};
list_of_oper::list_of_oper() : head(nullptr)
{}
const float spred = 0.98;
void list_of_oper::list_of_oper_out()
{
    cout << "---------------" << endl;
    element_list_of_oper* tmp = head;
    while (tmp != nullptr)
    {
        cout << tmp->my_oper.id << "|";
        cout << tmp->my_oper.stan << "|";
        cout << tmp->my_oper.currency1.nazwa << "|";
        cout << tmp->my_oper.currency2.nazwa << "|";
        cout << tmp->my_oper.il1.ilcyfra << "|";
        cout << tmp->my_oper.il2.ilcyfra << "|";
        cout << tmp->my_oper.kurs3.kurscyfra << "|";
        cout << endl;
        tmp = tmp->next;
    }
    cout << "---------------" << endl << endl;
}
void list_of_oper::add_operation_to_list(operacja& oper1)
{
    {
        element_list_of_oper* nowy = new element_list_of_oper;
        nowy->my_oper = oper1;
        if (head == nullptr)
        {
            head = nowy;
            nowy->next = nullptr;
        }
        else
        {
            element_list_of_oper* tmp = head;
            while (tmp->next)
            {
                tmp = tmp->next;
            }
            tmp->next = nowy;
            nowy->next = nullptr;
        }
    }






}

void list_of_oper::list_of_oper_from_file(const string& inputfile, list_of_currency& list)
{
    {
        fstream myfile; //stream for our i-file
        myfile.open(inputfile, ios::in); //open a file to perform read operation using file object

        if (myfile.is_open()) {   //checking whether the file is open
            string atr; //atribute
            int counterlines = 0;
            operacja oper1;
            while (getline(myfile, atr))
            { //read data from file
                string word = "";
                counterlines++;
                int k = 0; //counter
                if (counterlines > 1)
                {
                    for (auto x : atr)
                    {
                        if (x == '|' && k < 8)
                        {
                            k++;
                            if (k == 1) { oper1.id = stoi(word); }
                            if (k == 2) {
                                oper1.stan = stoi(word);


                            }
                            if (k == 3) {
                                oper1.currency1 = list.find_currency(word, list)->my_currency;
                            }

                            if (k == 4) {
                                oper1.currency2 = list.find_currency(word, list)->my_currency;
                                /*cout << b.title << " | ";*/
                            }
                            if (k == 5) {
                                oper1.il1.ilcyfra = stoi(word);



                            }
                            if (k == 6) {
                                oper1.il2.ilcyfra = stoi(word);



                            }
                            if (k == 7) {
                                oper1.kurs3.kurscyfra = stof(word);
                                add_operation_to_list(oper1);
                                k = 0;

                            }


                            word = "";
                        }
                        else
                        {
                            word = word + x;
                        }

                    }
                }
                //close the file object.
            }
        }
        myfile.close();
    }
}
void list_of_oper::delete_oper(element_list_of_oper* deleted)
{
    {
        if (head == deleted)
        {
            head = head->next;
        }
        else
        {
            element_list_of_oper* tmp = head;
            while (tmp->next != deleted)
            {
                tmp = tmp->next;
            }
            tmp->next = deleted->next;
        }
        delete deleted;

    }
}
element_list_of_oper* list_of_oper::chek_oper(int& ID)
{
    element_list_of_oper* tmp = head;
    while ((tmp->my_oper.id != ID))
    {
        if (tmp->next == nullptr)
        {
            cout << "no such oper" << endl;
            return nullptr;
        }
        tmp = tmp->next;
    }
    return tmp;
}

void list_of_oper::make_operation(const string& name_cur1, const string& name_cur2, int& il1, list_of_currency& list_c)
{
    operacja oper_tmp;
    oper_tmp.currency1 = list_c.find_currency(name_cur1, list_c)->my_currency;
    oper_tmp.currency2 = list_c.find_currency(name_cur2, list_c)->my_currency;
    oper_tmp.il1.ilcyfra = il1;
    oper_tmp.il2.ilcyfra = il1 * (oper_tmp.currency1.curs1.kurscyfra / oper_tmp.currency2.curs1.kurscyfra * spred);
    oper_tmp.kurs3.kurscyfra = float(oper_tmp.il1.ilcyfra) / float(oper_tmp.il2.ilcyfra);
    list_c.find_currency(name_cur1, list_c)->my_currency.il.ilcyfra - il1;
    list_c.find_currency(name_cur2, list_c)->my_currency.il.ilcyfra + oper_tmp.il2.ilcyfra;

    element_list_of_oper* tmp = new element_list_of_oper;
    tmp = head;
    while (tmp->next != nullptr)
    {
        tmp = tmp->next;
    }
    oper_tmp.id = tmp->my_oper.id + 1;
put_ok:
    cout << "get out " << oper_tmp.il2.ilcyfra << " of " << oper_tmp.currency2.nazwa << endl;
    cout << "end put ok";
    string otwet;
    cin >> otwet;
    if (otwet == "ok")
    {
        oper_tmp.stan = 1;
        add_operation_to_list(oper_tmp);
    }
    else {
        if (otwet == "stop")
        {
            goto end;
        }
        else goto put_ok;
    }
end:
    return;
}

void list_of_oper::safe_list_of_oper(const string& filename)
{
    ofstream fout(filename);
    fout << "\n";
    element_list_of_oper* tmp = head;
    while (tmp != nullptr)
    {
        
        fout << tmp->my_oper.id;
        fout << '|';
        fout << std::to_string(tmp->my_oper.stan);
        fout << '|';
        fout << (tmp->my_oper.currency1.nazwa);
        fout << '|';
        fout << (tmp->my_oper.currency2.nazwa);
        fout << '|';
        fout << std::to_string(tmp->my_oper.il1.ilcyfra);
        fout << '|';
        fout << std::to_string(tmp->my_oper.il2.ilcyfra);
        fout << '|';
        fout << std::to_string(tmp->my_oper.kurs3.kurscyfra);
        fout << '|';

        /* std::ostringstream ss;
         ss << tmp->my_currency.curs1.kurscyfra;
         std::string s(ss.str());
         fout << s;*/
        fout << '\n';
        tmp = tmp->next;
    }
    fout.close();
}

list_of_currency::list_of_currency()
{
    head = nullptr;
}
currency::currency(string name)
{
    nazwa = name;

    curs1.kurscyfra = 0;
    il.ilcyfra = 0;
}
currency::currency()
{
    nazwa = "nazwa";

    curs1.kurscyfra = 0;
    il.ilcyfra = 0;
}
currency::currency(const string& name, float& kurks, int& kolicz)
{
    nazwa = name;
    curs1.kurscyfra = kurks;
    il.ilcyfra = kolicz;
}
void currency::set(const string& name, float& kurks, int& kolicz)
{
    nazwa = name;
    curs1.kurscyfra = kurks;
    il.ilcyfra = kolicz;
}
void list_of_currency::save_to_file(const string& filename)
{
    ofstream fout(filename);
    fout << "\n";
    elemet_of_list_of_currency* tmp = head;
    while (tmp != nullptr)
    {
       
        fout << tmp->my_currency.nazwa;
        fout << '|';
        fout << std::to_string(tmp->my_currency.il.ilcyfra);
        fout << '|';
        fout << std::to_string(tmp->my_currency.curs1.kurscyfra);
        fout << '|';
        /* std::ostringstream ss;
         ss << tmp->my_currency.curs1.kurscyfra;
         std::string s(ss.str());
         fout << s;*/
        fout << '\n';
        tmp = tmp->next;
    }
    fout.close();
}



void currency::currency_out_put()
{
    cout << nazwa << '|';
    cout << il.ilcyfra << '|';
    cout << curs1.kurscyfra << endl;
    return;
}
void list_of_currency::download_file_to_list_currency(const string inputfile)

{
    fstream myfile; //stream for our i-file
    myfile.open(inputfile, ios::in); //open a file to perform read operation using file object

    if (myfile.is_open()) 
    {   //checking whether the file is open
        string atr; //atribute
        int counterlines = 0;
        currency cur2;
        while (getline(myfile, atr))
        { //read data from file
            string word = "";
            counterlines++;
            int k = 0; //counter
            if (counterlines > 1)
            {
                for (auto x : atr)
                {
                    if (x == '|' && k < 4)
                    {
                        k++;

                        if (k == 1) {
                            cur2.nazwa = word;

                        }

                        if (k == 2) {
                            cur2.il.ilcyfra = stoi(word);
                            /*cout << b.title << " | ";*/
                        }
                        if (k == 3) {
                            cur2.curs1.kurscyfra = stof(word);

                            k = 0;
                            add_currency(cur2);
                        }
                        word = "";
                    }
                    else
                    {
                        word = word + x;
                    }

                }
            }
            //close the file object.
        }
    }
    myfile.close();
}

void list_of_currency::add_currency(currency& said)
{
    elemet_of_list_of_currency* nowy = new elemet_of_list_of_currency;
    nowy->my_currency = said;
    if (head == nullptr)
    {
        head = nowy;
        nowy->next = nullptr;
    }
    else
    {
        elemet_of_list_of_currency* tmp = head;
        while (tmp->next)
        {
            tmp = tmp->next;
        }
        tmp->next = nowy;
        nowy->next = nullptr;
    }
}

void list_of_currency::write_out_list()
{
    cout << "---------------" << endl;
    elemet_of_list_of_currency* tmp = head;
    while (tmp != nullptr)
    {
        cout << tmp->my_currency.nazwa << "|";
        cout << tmp->my_currency.il.ilcyfra << "|";
        cout << tmp->my_currency.curs1.kurscyfra << endl;
        tmp = tmp->next;
    }
    cout << "---------------" << endl << endl;
}

void list_of_currency::delete_currency_from_list(elemet_of_list_of_currency* deleted)
{
    {
        if (head == deleted)
        {
            head = head->next;
        }
        else
        {
            elemet_of_list_of_currency* tmp = head;
            while (tmp->next != deleted)
            {
                tmp = tmp->next;
            }
            tmp->next = deleted->next;
        }
        delete deleted;

    }
}
elemet_of_list_of_currency* list_of_currency::find_currency(const string& said_name, list_of_currency& list)
{
    elemet_of_list_of_currency* tmp = list.head;
    while ((tmp->my_currency.nazwa != said_name))
    {
        if (tmp->next == nullptr)
        {
            cout << "no such currency" << endl;
            return nullptr;
        }
        tmp = tmp->next;
    }
    return tmp;
}
void elemet_of_list_of_currency::write_out_element_currency()
{
    my_currency.currency_out_put();
}
class menu
{
public:
        
    {

        cout << "\nEnter number of the operation: ";
        cout << "\n\n =============================================================================" << endl;
        cout << "(1)        currency menu" << endl;
        cout << "(2)        operations menu" << endl;
        cout << " =============================================================================" << endl;
    };
    void show_menu_currency()
    {

        cout << "\nEnter number of the operation: ";
        cout << "\n\n =============================================================================" << endl;
        cout << "(1)        write list of currency" << endl;
        cout << "(2)        check currency from list" << endl;
        cout << "(3)        add currency to list" << endl;
        cout << "(4)        delete currency from list" << endl;
        cout << "(5)        save list" << endl;
        cout<< "(6)        show widoc" << endl;
        cout << " =============================================================================" << endl;
        cout << "Enter 0 to go back to  main menu | Enter [D] or [d] to exit - > ";


    };
    void show_menu_operations()
    {

        cout << "\nEnter number of the operation: ";
        cout << "\n\n =============================================================================" << endl;
        cout << "(1)        write list of opperations" << endl;
        cout << "(2)        make opperation" << endl;
        cout << "(3)        find oper " << endl;
        cout << "(4)        delete oper from list" << endl;
        cout << "(5)        save list of operations" << endl;
        cout << " =============================================================================" << endl;
        cout << "Enter 0 to go back to  main menu | Enter [D] or [d] to exit - > ";


    };


};
bool is_number(string s)
{
    string chars = "-";

    for (char c : chars) {
        s.erase(remove(s.begin(), s.end(), c), s.end());
    }

    string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}
;

int main()
{
    widoc wid1;
    widoc u[10];
   
    string name;
    elemet_of_list_of_currency el_cur;

    int cyfra = 0;
    float czislo = 0;
    string filename = "currency.txt";
    string filenameop = "operations.txt";
    list_of_currency list1;
    list1.download_file_to_list_currency(filename);
    menu main_menu;
    char Stop_Programm = 'y';
    int stan_menu = 0;
    string name1;
    string name2;
    currency cur_main;
    operacja my_212;
    list_of_oper listo;
    string file_out;
    listo.list_of_oper_from_file(filenameop, list1);

    /*
    * listo.list_of_oper_out();
    string name12="dollar";
    string name2="euro";
    int li = 100;
    listo.make_operation(name12, name2, li, list1);
    listo.list_of_oper_out();*/
    while (Stop_Programm != 'd' || Stop_Programm == 'D')
    {
    Main_menu:
        main_menu.set_menu();
        cout << endl;
        string s_User_Choice;//checking if user entered right command
        cin >> s_User_Choice;
        if (is_number(s_User_Choice) && stoi(s_User_Choice) < 3 && stoi(s_User_Choice) > 0)
        {
            int User_Choice = stoi(s_User_Choice);
            switch (User_Choice)
            {
            case 1:

                while (Stop_Programm != 'd' || Stop_Programm == 'D')
                {
                    main_menu.show_menu_currency();
                    cout << endl;
                    string s_User_Choice;//checking if user entered right command
                    cin >> s_User_Choice;
                    if (is_number(s_User_Choice) && stoi(s_User_Choice) < 7 && stoi(s_User_Choice) > -1)
                    {
                        int User_Choice = stoi(s_User_Choice);
                        switch (User_Choice)
                        {
                        case 0:
                            goto Main_menu;
                            break;
                        case 1:
                            list1.write_out_list();
                            break;

                        case 2:
                            cout << "Enter name of currency";
                            cin >> name;

                            list1.find_currency(name, list1)->my_currency.currency_out_put();
                            break;
                        case 3:
                            cout << "enter information about currency" << endl;
                            cout << "Name of currency" << endl;
                            cin >> name;
                            cout << "Kurs of currency k dollaru";
                            cin >> czislo;
                            cout << "koliczestwo of currency";
                            cin >> cyfra;
                            cur_main.set(name, czislo, cyfra);
                            list1.add_currency(cur_main);
                            break;
                        case 4:
                            cout << "Enter name of currency to delit";
                            cin >> name1;
                            list1.delete_currency_from_list(list1.find_currency(name1, list1));
                            break;
                        case 5:
                            cout << "Enter name of file";
                            
                            cin >> file_out;

                            list1.save_to_file(file_out);
                            break;
                        case 6:
                            wid1.download_widoc("wid.txt", u);
                            wid1.print_data(u);
                            break;

                        }
                    }
                    else
                    {
                        if (s_User_Choice == "D" || s_User_Choice == "d")
                        {
                            goto stopp_program;
                        }
                    }

                }



                break;


            case 2:



                while (Stop_Programm != 'd' || Stop_Programm == 'D')
                {
                    main_menu.show_menu_operations();
                    cout << endl;
                    string s_User_Choice;//checking if user entered right command
                    cin >> s_User_Choice;
                    if (is_number(s_User_Choice) && stoi(s_User_Choice) < 6 && stoi(s_User_Choice) > -1)
                    {
                        int User_Choice = stoi(s_User_Choice);

                        switch (User_Choice)
                        {
                        case 0:
                            goto Main_menu;
                            break;
                        case 1:

                            listo.list_of_oper_out();
                            break;

                        case 2:
                            cout << endl << "Enter currency 1 ";
                            cin >> name1;
                            cout << endl << "Enter currency 2 ";
                            cin >> name2;
                            cout << endl << "enter iloszcz ";
                            cin >> cyfra;
                            listo.make_operation(name1, name2, cyfra, list1);
                            listo.safe_list_of_oper(filenameop);
                            break;
                        case 3:
                            cin >> cyfra;
                            my_212=listo.chek_oper(cyfra)->my_oper;
                            cout << my_212;

                            break;
                        case 4:
                            cin >> cyfra;
                            listo.delete_oper(listo.chek_oper(cyfra));
                            break;
                        case 5:
                            cout << "Enter name of file";
                            string file_out;
                            cin >> file_out;

                            listo.safe_list_of_oper(file_out);



                        }
                    }
                    else
                    {
                        if (s_User_Choice == "D" || s_User_Choice == "d")
                        {
                            goto stopp_program;
                        }
                    }

                }








            }
        }
        else {
            cout << "You must enter an existing operation !";
        }
        cout << endl << "=====================================================================================" << endl;
        cout << "Enter [ANY BUTTON] to go back to  main menu | Enter [D] or [d] to exit - > ";
        cin >> Stop_Programm;
    };
stopp_program:




    ///*currency* cur_test = new currency[countlines(filename) - 1];
    //currency cut;

    //cut.currency_download_from_file(filename, cur_test);

    //for (int i = 0; i < countlines(filename) - 1; i++)
    //{
    //    cout << cur_test[i].nazwa << " | " << cur_test[i].il.ilcyfra << " | " << cur_test[i].curs1.kurscyfra << endl;
    //}

    //delete[]cur_test;
    //*/
    //list_of_currency list1;
    //list1.download_file_to_list_currency(filename);
    //list1.write_out_list();

    //list1.write_out_list();
    //list1.delete_currency_from_list(list1.find_currency("dollar2",list1));
    //list1.write_out_list();
    //operacja oper1;
    //currency dollar;
    //dollar.curs1.kurscyfra = 1;
    //currency frank;
    //frank.curs1.kurscyfra = 1.2;
    //oper1.currency1 = list1.find_currency("dollar",list1)->my_currency;
    //oper1.currency2 = list1.find_currency("euro", list1)->my_currency;
    //oper1.il1.ilcyfra = 100;
    //oper1.il2.ilcyfra = (oper1.il1.ilcyfra) *( (oper1.currency2.curs1.kurscyfra)/ (oper1.currency1.curs1.kurscyfra)*spred);
    //oper1.stan = 0;
    //oper1.kurs3.kurscyfra = oper1.il2.ilcyfra / oper1.il2.ilcyfra;



    //
    //list_of_oper list2;
    //list2.add_to_list_of_oper(oper1);
    //list2.list_of_oper_out();



    return 0;
}