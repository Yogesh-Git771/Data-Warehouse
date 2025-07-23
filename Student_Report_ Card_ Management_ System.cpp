#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <windows.h>
#include <algorithm>
#include <limits>
#include <conio.h>
using namespace std;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

struct student {
    char name[80];
    char id[80];
    int roll;
    float pro, arc, writing, alg, sum, average;
    char grade;
};

void intro();
bool adminLogin();
void acceptdata();
void viewall();
void view_Specific(int);
void result(int);
void modify(int);
void deleterecord(int);
void searchStudent();
void exportToFile();
void createBackup();
void showStatistics();
void deleteAllData();
void cleanGarbageData();
char calculateGrade(float average);
int getValidatedRoll();
float getValidatedMark(const string& subject);
bool isDuplicateRoll(int roll);

int main() {
    intro();
    if (!adminLogin()) {
        SetConsoleTextAttribute(h, 12);
        cout << "Invalid login! Exiting..." << endl;
        SetConsoleTextAttribute(h, 7);
        return 0;
    }

    int choice;
    do {
        system("cls");
        SetConsoleTextAttribute(h, 11);
        cout << "\n=========== STUDENT REPORT CARD MANAGEMENT SYSTEM ===========\n";
        SetConsoleTextAttribute(h, 7);
        cout << "1. Create Student Record\n";
        cout << "2. View All Records\n";
        cout << "3. View Single Record (By Roll No)\n";
        cout << "4. Modify Record\n";
        cout << "5. Delete Record\n";
        cout << "6. Search Student (By Name/ID)\n";
        cout << "7. Export All Records to Text File\n";
        cout << "8. Backup Records\n";
        cout << "9. Show Statistics\n";
        cout << "10. Clean Garbage Records\n";
        cout << "11. Delete All Records\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

int roll;
switch (choice) {
    case 1: acceptdata(); break;
    case 2: viewall(); break;
    case 3: cout << "Enter Roll Number: "; cin >> roll; view_Specific(roll); break;
    case 4: cout << "Enter Roll Number: "; cin >> roll; modify(roll); break;
    case 5: cout << "Enter Roll Number: "; cin >> roll; deleterecord(roll); break;
    case 6: searchStudent(); break;
    case 7: exportToFile(); break;
    case 8: createBackup(); break;
    case 9: showStatistics(); break;
    case 10: cleanGarbageData(); break;
    case 11: deleteAllData(); break;
    case 0: SetConsoleTextAttribute(h, 10); cout << "\nThank you for using the system!\n"; SetConsoleTextAttribute(h, 7); break;
    default: SetConsoleTextAttribute(h, 12); cout << "Invalid choice!\n"; SetConsoleTextAttribute(h, 7); break;
}
if (choice != 0) { cout << "\nPress Enter to continue..."; cin.ignore(); cin.get(); }
} while (choice != 0);
return 0;
}
bool adminLogin() {
    string user, pass;
    char ch;

    cout << "\nEnter Admin Username: ";
    cin >> user;

    cout << "Enter Password: ";
    pass = "";

    while ((ch = _getch()) != 13) { // Enter key
        if (ch == 8 && !pass.empty()) { // Backspace
            pass.pop_back();
            cout << "\b \b";
        } else if (ch != 8) {
            pass += ch;
            cout << '*';
        }
    }
    cout << endl;

    return (user == "admin" && pass == "admin123");
}

void intro() {
    system("cls");
    SetConsoleTextAttribute(h, 14);
    cout << "\n\n\n";
    Sleep(300);
    cout << "\t\t\t\t * * *  **** *      ****  ***   ***   ****   \n";
    Sleep(300);
    cout << "\t\t\t\t * * * *     *     *     *   * * * * *        \n";
    Sleep(300);
    cout << "\t\t\t\t * * * ***** *     *     *   * * * * *****    \n";
    Sleep(300);
    cout << "\t\t\t\t * * * *     *     *     *   * * * * *         \n";
    Sleep(300);
    cout << "\t\t\t\t  ***   **** *****  ****  ***  * * *  ****     \n";
    SetConsoleTextAttribute(h, 11);
    cout << "\n\t\t\t=============================================\n";
    cout << "\t\t\tSTUDENT REPORT CARD MANAGEMENT SYSTEM\n";
    cout << "\t\t\t=============================================\n";
    SetConsoleTextAttribute(h, 10);
    cout << "\nDeveloped by: Yogesh Panigrahi" << endl;
    cout << "College: Sahyog College" << endl;
    cout << "Supervisor: Aperna Deshmukh" << endl;
    cout << "Version: Final" << endl;
    SetConsoleTextAttribute(h, 7);
    cout << "\nPress Enter to Login...";
    cin.get();
}

char calculateGrade(float avg) {
    if (avg >= 90) return 'A';
    else if (avg >= 80) return 'B';
    else if (avg >= 70) return 'C';
    else if (avg >= 60) return 'D';
    else return 'F';
}

int getValidatedRoll() {
    int roll;
    while (true) {
        cout << "Enter Roll No: ";
        cin >> roll;
        if (cin.fail() || roll <= 0) {
            cout << "Invalid input. Please enter a valid positive number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else if (isDuplicateRoll(roll)) {
            cout << "This roll number already exists. Please enter a different one.\n";
        } else {
            break;
        }
    }
    return roll;
}

float getValidatedMark(const string& subject) {
    float mark;
    while (true) {
        cout << subject << " Marks (0-100): ";
        cin >> mark;
        if (cin.fail() || mark < 0 || mark > 100) {
            cout << "Invalid input. Please enter marks between 0 and 100.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    return mark;
}

bool isDuplicateRoll(int roll) {
    student s;
    ifstream infile("Report.txt", ios::binary);
    while (infile.read(reinterpret_cast<char*>(&s), sizeof(student))) {
        if (s.roll == roll) {
            infile.close();
            return true;
        }
    }
    infile.close();
    return false;
}

void deleteAllData() {
    ofstream file("Report.txt", ios::trunc | ios::binary);
    file.close();
    cout << "\nAll data deleted successfully!\n";
}

void cleanGarbageData() {
    ifstream infile("Report.txt", ios::binary);
    ofstream outfile("Cleaned.txt", ios::binary);
    student s;
    int removed = 0;
    while (infile.read(reinterpret_cast<char*>(&s), sizeof(student))) {
        s.grade = calculateGrade(s.average);
        if (s.roll > 0 && s.pro >= 0 && s.arc >= 0 && s.writing >= 0 && s.alg >= 0 && s.average >= 0 && isalpha(s.grade)) {
            outfile.write(reinterpret_cast<char*>(&s), sizeof(student));
        } else {
            removed++;
        }
    }
    infile.close();
    outfile.close();
    remove("Report.txt");
    rename("Cleaned.txt", "Report.txt");
    cout << "\nCleaned " << removed << " invalid record(s).\n";
}

void acceptdata() {
    system("cls");
    student s;
    ofstream outfile("Report.txt", ios::app | ios::binary);
    if (!outfile) { cout << "File Error!"; return; }

    cout << "\nEnter Full Name: "; cin.ignore(); cin.getline(s.name, 80);
    cout << "Enter ID (without prefix GUE/): "; cin >> s.id;
    s.roll = getValidatedRoll();
    s.pro = getValidatedMark("Programming");
    s.arc = getValidatedMark("Architecture");
    s.writing = getValidatedMark("Writing Skill");
    s.alg = getValidatedMark("Algebra");

    s.sum = s.pro + s.arc + s.writing + s.alg;
    s.average = s.sum / 4.0;
    s.grade = calculateGrade(s.average);

    outfile.write(reinterpret_cast<char*>(&s), sizeof(student));
    outfile.close();
    cout << "\nRecord Saved Successfully!\n";
}

void viewall() {
    system("cls");
    student s;
    ifstream infile("Report.txt", ios::binary);
    if (!infile) { cout << "File Error!\n"; return; }

    SetConsoleTextAttribute(h, 11);
    cout << "+----------+--------------------+---------------+--------+--------+--------+--------+--------+--------+-------+\n";
    cout << "| Roll No  | Name               | GUE ID        | Prog   | Arch   | Write  | Alg    | Total  | Avg    | Grade |\n";
    cout << "+----------+--------------------+---------------+--------+--------+--------+--------+--------+--------+-------+\n";
    SetConsoleTextAttribute(h,7);
    while (infile.read(reinterpret_cast<char*>(&s), sizeof(student))) {
        string fullID = "GUE/" + string(s.id);
        SetConsoleTextAttribute(h, 14);
        cout << "| " << setw(9) << left << s.roll;
        SetConsoleTextAttribute(h, 7);
         cout << "| " << setw(19) << left << s.name;
         SetConsoleTextAttribute(h, 13);
         cout << "| " << setw(14) << left << fullID;
         SetConsoleTextAttribute(h, 7);
          cout   << "| " << setw(7) << left << s.pro
             << "| " << setw(7) << left << s.arc
             << "| " << setw(7) << left << s.writing
             << "| " << setw(7) << left << s.alg
             << "| " << setw(7) << left << s.sum
             << "| " << setw(7) << left << s.average
             << "| " << setw(6) << left << s.grade << "|\n";
    }
    SetConsoleTextAttribute(h, 11);
    cout << "+----------+--------------------+---------------+--------+--------+--------+--------+--------+--------+-------+\n";
    SetConsoleTextAttribute(h, 7);
    infile.close();
}
void view_Specific(int n) {
    system("cls");
    student s; bool found = false;
    ifstream infile("Report.txt", ios::binary);
    while (infile.read(reinterpret_cast<char*>(&s), sizeof(student))) {
        if (s.roll == n) {
            cout << "\nRecord Found:\n";
            cout << "Name: " << s.name << "\nID: GUE/" << s.id << "\nRoll: " << s.roll << endl;
            cout << "Marks => Programming: " << s.pro << ", Architecture: " << s.arc << ", Writing: " << s.writing << ", Algebra: " << s.alg << endl;
            cout << "Total: " << s.sum << ", Average: " << s.average << ", Grade: " << s.grade << endl;
            found = true;
        }
    }
    infile.close();
    if (!found) cout << "\nRecord Not Found!\n";
}

void result(int n) { view_Specific(n); }

void modify(int n) {
    system("cls");
    student s; bool found = false;
    fstream file("Report.txt", ios::binary | ios::in | ios::out);
    while (file.read(reinterpret_cast<char*>(&s), sizeof(student))) {
        if (s.roll == n) {
            cout << "Enter New Data:\n";
            cout << "Full Name: "; cin.ignore(); cin.getline(s.name, 80);
            cout << "ID (without GUE/): "; cin >> s.id;
            cout << "Programming: "; cin >> s.pro;
            cout << "Architecture: "; cin >> s.arc;
            cout << "Writing: "; cin >> s.writing;
            cout << "Algebra: "; cin >> s.alg;
            s.sum = s.pro + s.arc + s.writing + s.alg;
            s.average = s.sum / 4;
            s.grade = calculateGrade(s.average);
            file.seekp(-static_cast<int>(sizeof(student)), ios::cur);
            file.write(reinterpret_cast<char*>(&s), sizeof(student));
            found = true;
            cout << "\nRecord Updated Successfully!\n";
            break;
        }
    }
    file.close();
    if (!found) cout << "\nRecord Not Found!\n";
}

void deleterecord(int n) {
    system("cls");
    student s;
    ifstream infile("Report.txt", ios::binary);
    ofstream outfile("Temp.txt", ios::binary);
    bool deleted = false;
    while (infile.read(reinterpret_cast<char*>(&s), sizeof(student))) {
        if (s.roll != n)
            outfile.write(reinterpret_cast<char*>(&s), sizeof(student));
        else deleted = true;
    }
    infile.close(); outfile.close();
    remove("Report.txt"); rename("Temp.txt", "Report.txt");
    if (deleted) cout << "\nRecord Deleted!\n";
    else cout << "\nRecord Not Found!\n";
}

void searchStudent() {
    system("cls");
    student s; bool found = false;
    string key;
    cout << "\nSearch by Name or ID (partial allowed): "; cin.ignore(); getline(cin, key);
    transform(key.begin(), key.end(), key.begin(), ::tolower);

    ifstream infile("Report.txt", ios::binary);
    while (infile.read(reinterpret_cast<char*>(&s), sizeof(student))) {
        string nameLower(s.name), idLower(s.id);
        transform(nameLower.begin(), nameLower.end(), nameLower.begin(), ::tolower);
        transform(idLower.begin(), idLower.end(), idLower.begin(), ::tolower);

        if (nameLower.find(key) != string::npos || idLower.find(key) != string::npos) {
            cout << "\nMatch Found: " << s.name << " (Roll: " << s.roll << ", ID: GUE/" << s.id << ")" << endl;
            found = true;
        }
    }
    infile.close();
    if (!found) cout << "\nNo matching record found!\n";
}

void exportToFile() {
    system("cls");
    student s;
    ifstream infile("Report.txt", ios::binary);
    ofstream out("Export.txt");

    out << left << setw(10) << "Roll" << setw(20) << "Name" << setw(12) << "ID" << setw(8) << "Prog" << setw(8)
        << "Arch" << setw(8) << "Write" << setw(8) << "Alg" << setw(8) << "Sum" << setw(8) << "Avg" << "Grade" << endl;
    out << string(80, '=') << endl;

    while (infile.read(reinterpret_cast<char*>(&s), sizeof(student))) {
        out << left << setw(10) << s.roll << setw(20) << s.name << setw(12) << (string("GUE/") + s.id)
            << setw(8) << s.pro << setw(8) << s.arc << setw(8) << s.writing << setw(8) << s.alg
            << setw(8) << s.sum << setw(8) << s.average << s.grade << endl;
    }
    infile.close(); out.close();
    cout << "\nExport completed to Export.txt\n";
}

void createBackup() {
    system("cls");
    ifstream src("Report.txt", ios::binary);
    ofstream dst("Backup.txt", ios::binary);
    dst << src.rdbuf();
    src.close(); dst.close();
    cout << "\nBackup created as Backup.txt\n";
}

void showStatistics() {
    system("cls");
    student s;
    int total = 0, a=0,b=0,c=0,d=0,f=0;
    float sum_avg = 0, max_avg = 0;

    ifstream infile("Report.txt", ios::binary);
    while (infile.read(reinterpret_cast<char*>(&s), sizeof(student))) {
        total++;
        sum_avg += s.average;
        if (s.average > max_avg) max_avg = s.average;
        switch (s.grade) {
            case 'A': a++; break; case 'B': b++; break; case 'C': c++; break; case 'D': d++; break; case 'F': f++; break;
        }
    }
    infile.close();

    if (total == 0) { cout << "No records found!\n"; return; }
    cout << "\nTotal Students: " << total << endl;
    cout << "Class Average: " << (sum_avg / total) << endl;
    cout << "Highest Average: " << max_avg << endl;
    cout << "Grade Distribution => A: " << a << ", B: " << b << ", C: " << c << ", D: " << d << ", F: " << f << endl;
}

