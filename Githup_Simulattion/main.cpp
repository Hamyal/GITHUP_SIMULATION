#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip> 
#include <windows.h>
#include <vector>
#include <cstdlib> 

#include "git_simulation.h"
using namespace std;


int main() {
    githupsimulation git;

    git.userdataread();
    git.readrepo();

    int num;
    string user_login;

    while (true) {
        system("cls");
        cout << "-----///";
        for (int i = 0; i < 50; i++) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
            cout << "*";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); 
            cout << "~";
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); 
        cout << "\\\\\\-----" << endl;

        for (int i = 0; i < 25; i++) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); 
            cout << "*";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); 
            cout << "~";
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); 
        cout << endl;

        for (int i = 0; i < 13; i++) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); 
            cout << "*";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); 
            cout << "~";
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); 
        cout << endl;

        cout << "|----->>>";

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); 
        cout << endl << endl;
        cout << " ***  ***    ***       Welcome to  Githup simulation      ***     ***    ***  " << endl;
        cout << endl;
        cout << " =========                   THE LOGIN STATUS                     =============";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); 
        cout << "<<<-----|" << endl << endl;

        for (int i = 0; i < 13; i++) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); 
            cout << "*";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
            cout << "~";
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); 
        cout << endl;

        for (int i = 0; i < 25; i++) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); 
            cout << "*";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); 
            cout << "~";
        }
        cout << endl;

        for (int i = 0; i < 50; i++) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
            cout << "*";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); 
            cout << "~";
        }

        cout << endl << endl;

        setw(40);
        cout << endl;
        if (!user_login.empty()) {
            cout << "--------------------------THE LOGGED USER: " << user_login <<"------------------------"<< endl;
        }
        else {
            cout << "    --------------                     NO USER        --------------                    " << endl;
        }

        cout << endl;

        for (int i = 0; i < 50; i++)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
            cout << "*";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
            cout << "=";
        }


        cout << endl;
        cout << setw(45) << " | 1: Registeration |" << endl;

        cout << setw(37) << " | 2: Login |" << endl;

        cout << setw(38) << " |3: Logout | " << endl;

        cout << setw(45) << " | 4:  Profile View |" << endl;

        cout << setw(52) << " | 5:  Repository Creation |" << endl;

        cout << setw(51) << " | 6: Repository Deletion |" << endl;

        cout << setw(47) << "| 7: Fork Repository |" << endl;

        cout << setw(52) << " | 8: Commit to Repository |" << endl;
        cout << setw(43) << " | 9: View  Stats |" << endl;
        cout << setw(42) << " | 10: Add Files |" << endl;
        cout << setw(44) << " | 11:Delete Files |" << endl;
        cout << setw(40) << "| 12: Follow |" << endl;
        cout << setw(41) << "| 13: Unfollow |" << endl;
        cout << setw(37) << "| 14: Exit |" << endl;



        for (int i = 0; i < 50; i++)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
            cout << "*";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
            cout << "=";
        }
        cout << endl;
        cout << "Enter your choice number : ";
        cin >> num;

        switch (num) {
        case 1:
            git.registerUser();
            break;
        case 2:
            git.login(user_login);
            break;
        case 3:
            git.logout(user_login);
            break;
        case 4: {
            string view_profile_name;
            cout << "Enter the username to view the  profile: ";
            cin >> view_profile_name;
            git.viewProfile(view_profile_name);
            break;
        }
        case 5:
            if (user_login.empty()) {
                cout << " login first username " << endl;
            }
            else {
                string name_repos;
                bool isprivate;
                cout << "Enter the  repository name: ";
                cin >> name_repos;
                cout << "Enter the   0 for private, 1 for public: ";
                cin >> isprivate;

                git.createRepository(user_login, name_repos, isprivate, 0);
            }
            break;
        case 6:
            if (user_login.empty()) {
                cout << " login first username " << endl;
            }
            else {
                string repoName;
                cout << "Enter the  repository name to delete: ";
                cin >> repoName;
                git.deleteRepository(user_login, repoName);
            }
            break;
        case 7:
            if (user_login.empty()) {
                cout << "Please login first!" << endl;
            }
            else {
                string source_name, source_repos, find_name;
                cout << "Enter the  source username: ";
                cin >> source_name;
                cout << "Enter  the source repository name: ";
                cin >> source_repos;
                cout << "Enter the  target username: ";
                cin >> find_name;
                git.Fork(source_name, source_repos, find_name);
            }
            break;
        case 8:
            if (user_login.empty()) {
                cout << " login first  username " << endl;
            }
            else {
                string name_repos, message;
                cout << "Enter the  repository name for commit: ";
                cin >> name_repos;
                cout << "Enter  the commit message: ";
                cin.ignore();
                getline(cin, message);
                git.commitToRepository(user_login, name_repos, message);
            }
            break;
        case 9:
            if (user_login.empty()) {
                cout << "login first  username" << endl;
            }
            else {
                string name_repos;
                cout << "Enter  the repository name for view the  stats: ";
                cin >> name_repos;
                git.Statsrepository(user_login, name_repos);
            }
            break;
        case 10:
            if (user_login.empty()) {
                cout << "login first  username" << endl;
            }
            else {
                string name_repos, file_name;
                cout << "Enter the  repository name: ";
                cin >> name_repos;
                cout << "Enter file name: ";
                cin >> file_name;
                git.addfile(user_login, name_repos, file_name);
            }
            break;
        case 11:
            if (user_login.empty()) {
                cout << " login first username" << endl;
            }
            else {
                string name_repos, file_name;
                cout << "Enter the  repository name: ";
                cin >> name_repos;
                cout << "Enter  the  file name: ";
                cin >> file_name;
                git.deletefile(user_login, name_repos, file_name);
            }
            break;
        case 12:
            if (user_login.empty()) {
                cout << "login first  username " << endl;
            }
            else {
                string f;
                cout << "Enter the username you want to follow: ";
                cin >> f;
                git.Folllow(user_login, f);
            }
            break;
        case 13:
            if (user_login.empty()) {
                cout << " login first  username " << endl;
            }
            else {
                string uf;
                cout << "Enter the username you want to unfollow: ";
                cin >> uf;
                git.Unfolllow(user_login, uf);
            }
            break;
        case 14:
            git.userwritedata();
            git.writerepo();
            return 0;
        default:
            cout << "incorrect choice!" << endl;
            break;
        }
        system("pause");
    }

    system("pause");
}