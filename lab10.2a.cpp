#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <Windows.h>

using namespace std;

// ������ ��������������
enum Specialization { COMPUTER_SCIENCE, MATHEMATICS, PHYSICS, ENGINEERING, BIOLOGY };
string specializationStr[] = { "����'����� �����", "����������", "Գ����", "��������", "�������" };

// ��������� ��� ������������� ��������
struct Student {
    string surname;
    unsigned course;
    Specialization specialization;
    int physics;
    int mathematics;
    int informatics;
};

// ������� ��� ��������, ���������, ���������� �� ���������� ���������� ����
void InputStudents(Student* students, int N);
void PrintStudents(const Student* students, int N);
double CalculateAverage(const Student& student);
void SortStudents(Student* students, int N);
int BinarySearch(Student* students, int N, const string& surname, double average, int mathGrade);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int numStudents;
    cout << "������ ������� ��������: ";
    cin >> numStudents;

    Student* students = new Student[numStudents];

    int menuItem;
    do {
        cout << "\n����:\n";
        cout << "1 - �������� ����� ��������\n";
        cout << "2 - ���� ����� ��������\n";
        cout << "3 - Գ����� ���������� ��������\n";
        cout << "4 - ����� �������� �� ��������, ������� ����� � ������� � ����������\n";
        cout << "0 - �����\n";
        cout << "������� ��: ";
        cin >> menuItem;

        switch (menuItem) {
        case 1:
            InputStudents(students, numStudents);
            break;
        case 2:
            PrintStudents(students, numStudents);
            break;
        case 3:
            SortStudents(students, numStudents);
            cout << "������ �������� �����������.\n";
            break;
        case 4: {
            string surname;
            double avg;
            int mathGrade;
            cout << "������ ������� ��� ������: ";
            cin >> surname;
            cout << "������ ������� ��� ��� ������: ";
            cin >> avg;
            cout << "������ ������ � ���������� ��� ������: ";
            cin >> mathGrade;

            int index = BinarySearch(students, numStudents, surname, avg, mathGrade);
            if (index != -1) {
                cout << "�������� ��������: " << students[index].surname << endl;
            }
            else {
                cout << "�������� �� ��������.\n";
            }
            break;
        }
        case 0:
            break;
        default:
            cout << "������������ ����. ��������� �� ���.\n";
        }
    } while (menuItem != 0);

    delete[] students;
    return 0;
}

void InputStudents(Student* students, int N) {
    int spec;
    for (int i = 0; i < N; i++) {
        cout << "������� � " << i + 1 << ":\n";
        cin.ignore();
        cout << " �������: "; getline(cin, students[i].surname);
        cout << " ����: "; cin >> students[i].course;
        cout << " ������������ (0 - ����'����� �����, 1 - ����������, 2 - Գ����, 3 - ��������, 4 - �������): ";
        cin >> spec;
        students[i].specialization = static_cast<Specialization>(spec);
        cout << " ������ � ������: "; cin >> students[i].physics;
        cout << " ������ � ����������: "; cin >> students[i].mathematics;
        cout << " ������ � �����������: "; cin >> students[i].informatics;
    }
}

void PrintStudents(const Student* students, int N) {
    cout << "=============================================================================================\n";
    cout << "| � | �������         | ���� | ������������           | Գ���� | ���������� | ����������� |\n";
    cout << "---------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < N; i++) {
        cout << "| " << setw(2) << i + 1 << "| ";
        cout << setw(15) << left << students[i].surname;
        cout << "  | " << setw(4) << right << students[i].course;
        cout << " | " << setw(21) << left << specializationStr[students[i].specialization];
        cout << "   | " << setw(6) << right << students[i].physics;
        cout << " | " << setw(10) << right << students[i].mathematics;
        cout << " | " << setw(11) << right << students[i].informatics << " |\n";
    }

    cout << "=============================================================================================\n";
}

double CalculateAverage(const Student& student) {
    return (student.physics + student.mathematics + student.informatics) / 3.0;
}

void SortStudents(Student* students, int N) {
    sort(students, students + N, [](const Student& a, const Student& b) {
        double avgA = CalculateAverage(a);
        double avgB = CalculateAverage(b);
        if (avgA != avgB)
            return avgA > avgB;
        if (a.mathematics != b.mathematics)
            return a.mathematics > b.mathematics;
        return a.surname < b.surname;
        });
}

int BinarySearch(Student* students, int N, const string& surname, double average, int mathGrade) {
    int left = 0, right = N - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        double avgMid = CalculateAverage(students[mid]);

        if (students[mid].surname == surname && avgMid == average && students[mid].mathematics == mathGrade) {
            return mid;
        }

        if (avgMid > average || (avgMid == average && students[mid].mathematics > mathGrade) ||
            (avgMid == average && students[mid].mathematics == mathGrade && students[mid].surname > surname)) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return -1; // �� ��������
}
