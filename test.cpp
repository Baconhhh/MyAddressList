#include "hash.h"
#include <iostream>
void insert ();
void find ();
void del ();
void print ();
HashMap<string, AddressList, HashFunc, EqualKey> hashmap ( 100 );
string name, college;
d_long tel, stu_Id;
int choice;
int main ( void ) {
	system("sl");

        cout << "1.增加联系人\n";
        cout << "2.查找联系人\n";
        cout << "3.删除联系人\n";
        cout << "4.打印通讯录\n";
        cout << "请输入对应数字进行相关操作(q 代表退出)\n";

        while ( scanf ( "%d", &choice ) == 1 ) {
                switch ( choice ) {
                case 1:
                        insert ();
                       
                        system ( "clear" );
                        cout << "1.增加联系人\n";
                        cout << "2.查找联系人\n";
                        cout << "3.删除联系人\n";
                        cout << "4.打印通讯录\n";
                        cout << "请输入对应数字进行相关操作(q 代表退出)\n";
                         break;
                case 2: find (); break;

                case 3:
                        del ();

                        system ( "clear" );
                        cout << "1.增加联系人\n";
                        cout << "2.查找联系人\n";
                        cout << "3.删除联系人\n";
                        cout << "4.打印通讯录\n";
                        cout << "请输入对应数字进行相关操作(q 代表退出)\n";

                        break;
                case 4: print (); break;
                }
        }

        return 0;
}
void print () { hashmap.print (); }

void insert () {
        cout << "请输入姓名：";
        cin >> name;
        cout << "请输入学号：";
        cin >> stu_Id;
        cout << "请输入学院：";
        cin >> college;
        cout << "请输入电话：";
        cin >> tel;

        AddressList t ( name, stu_Id, college, tel );
        hashmap.insert ( name, t );
}

void find () {
        cout << "请输入你要查找的联系人的姓名：";
        cin >> name;
        cout << hashmap.find ( name );
}

void del () {
        cout << "请输入你要删除的联系人的姓名：";
        cin >> name;
        hashmap.del ( name );
}
