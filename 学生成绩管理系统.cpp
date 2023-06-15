#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>

using namespace std;

class Student
{

public:
    string id;                                               // ѧ��
    string name;                                             // ����
    double usualScore;                                       // ƽʱ�ɼ�
    double finalScore;                                       // ��ĩ���Գɼ�
    double totalScore = usualScore * 0.3 + finalScore * 0.7; // ����

    Student(){};
    Student(string id, string n, double u, double f) : id(id), name(n), usualScore(u), finalScore(f){};

    void display()
    {
        cout << id << "\t" << name << "\t  "
             << usualScore << "\t\t      " << finalScore << "\t"
             << totalScore << endl;
    }
};

// ȫ�ֱ���
vector<Student> students;

// �Ӻ�������
void inputStu();      // ¼��ѧ����Ϣ
void displayAll();    // ��ʾѧ����Ϣ
void sortStu();       // ��������
void findStu();       // ����ѧ��
void insertStu();     // ����ѧ��
void deleteStudent(); // ɾ��ѧ��
void countStu();      // ͳ������
void saveToFile();    // �����ݱ��浽�ļ�
void loadFromFile();  // ���ļ���������
void clean();         // ����
void modify();        // �޸���Ϣ

int main()
{
    loadFromFile(); // ���ļ���������

    while (true)
    {
        cout << "===================================" << endl;
        cout << "        ��ӭʹ�óɼ�����ϵͳ      " << endl;
        cout << "     1=¼��ѧ��  2=��ʾ����ѧ��   " << endl;
        cout << "     3=��������  4=����ѧ��      " << endl;
        cout << "     5=����ѧ��  6=ɾ��ѧ��      " << endl;
        cout << "     7=ͳ������  8=�޸���Ϣ      " << endl;
        cout << "          0=���沢�˳�           " << endl;
        cout << "===================================" << endl;
        cout << "����������ѡ��" << endl;
        char choice;
        cin >> choice;

        switch (choice)
        {
        case '0':         // �˳�
            saveToFile(); // �������ݵ��ļ�
            Sleep(1000);
            return 0;
        case '1': // ¼��ѧ����Ϣ
            inputStu();
            clean();
            break;
        case '2': // ��ʾѧ����Ϣ
            displayAll();
            clean();
            break;
        case '3': // ��������
            sortStu();
            clean();
            break;
        case '4': // ����ѧ��
            findStu();
            clean();
            break;
        case '5': // ����ѧ��
            insertStu();
            clean();
            break;
        case '6': // ɾ��ѧ��
            deleteStudent();
            clean();
            break;
        case '7': // ͳ������
            countStu();
            clean();
            break;
        case '8': // �޸���Ϣ
            modify();
            clean();
            break;
        default:
            cout << "������Ч����������ȷ������!" << endl;
            clean();
        }
    }
}

void inputStu()
{
    cout << "����������ѧ����Ϣ��ѧ�� ���� ƽʱ�ɼ� ��ĩ���Գɼ�����" << endl;

    string id, name;
    double usualScore, finalScore;
    cin >> id >> name >> usualScore >> finalScore;

    // �ж�ѧ���Ƿ��ظ�
    for (Student &s : students)
    {
        if (s.id == id)
        {
            cout << "��ѧ���Ѵ��ڣ�¼��ʧ�ܡ�" << endl;
            return;
        }
    }

    // ���ѧ��
    Student s(id, name, usualScore, finalScore);
    students.push_back(s);

    cout << "¼��ɹ���" << endl;
}

void displayAll()
{
    if (students.empty())
    {
        cout << "û��ѧ����Ϣ��" << endl;
        return;
    }

    cout << "����\tѧ��\t����\tƽʱ�ɼ�\t��ĩ���Գɼ�\t����" << endl;

    // for (Student &s : students)
    // {
    //     s.display();
    // }
    for (unsigned int i = 0; i < students.size(); i++)
    {
        cout << i + 1 << '\t';
        students[i].display();
    }
}

void sortStu()
{
    if (students.empty())
    {
        cout << "û��ѧ����Ϣ��" << endl;
        return;
    }

    sort(students.begin(), students.end(), [](const Student &a, const Student &b)
         { return a.totalScore > b.totalScore; });

    cout << "����ɹ���" << endl;
}

void findStu()
{
    if (students.empty())
    {
        cout << "û��ѧ����Ϣ��" << endl;
        return;
    }

    cout << "������Ҫ���ҵ�ѧ����ѧ�Ż�������" << endl;
    string x;
    cin >> x;

    for (Student &s : students)
    {
        if (s.id == x || s.name == x)
        {
            cout << "ѧ��\t����\tƽʱ�ɼ�\t��ĩ���Գɼ�\t����" << endl;
            s.display();
            return;
        }
    }

    cout << "û���ҵ���Ӧ��ѧ����" << endl;
}

void insertStu()
{
    if (students.empty())
    {
        cout << "û��ѧ����Ϣ��" << endl;
        return;
    }

    cout << "������Ҫ�����ѧ����Ϣ����ѧ�� ���� ƽʱ�ɼ� ��ĩ���Գɼ���" << endl;

    string id, name;
    double usualScore, finalScore;
    cin >> id >> name >> usualScore >> finalScore;
    // �ж�ѧ���Ƿ��ظ�
    for (Student &s : students)
    {
        if (s.id == id)
        {
            cout << "ѧ���Ѿ����ڣ����������롣" << endl;
            return;
        }
    }

    // ���ѧ��
    Student student(id, name, usualScore, finalScore);

    for (unsigned int i = 0; i < students.size(); i++)
    {
        if (student.totalScore >= students[i].totalScore)
        {
            students.emplace(students.begin() + i, student);
            cout << "����ɹ���" << endl;
            return;
        }
    }

    students.push_back(student);
    cout << "����ɹ���" << endl;
}

void deleteStudent()
{
    if (students.empty())
    {
        cout << "û��ѧ����Ϣ��" << endl;
        return;
    }

    cout << "������Ҫɾ����ѧ����ѧ�Ż�������" << endl;
    string x;
    cin >> x;

    for (unsigned int i = 0; i < students.size(); i++)
    {
        if (students[i].id == x || students[i].name == x)
        {
            cout << "ȷ��Ҫɾ��ѧ����Ϣ��(Yȷ��/Nȡ��):" << endl;
            char choice;
            cin >> choice;
            if (choice == 'Y' || choice == 'y')
            {
                students.erase(students.begin() + i);
                cout << "ɾ���ɹ���" << endl;
            }
            else
                cout << "��ȡ��" << endl;
            return;
        }
    }

    cout << "û���ҵ���Ӧ��ѧ����" << endl;
}

void countStu()
{
    int number = students.size(), failNumber = 0;
    double averageUsualScore = 0, averageFinalScore = 0, averageTotalScore = 0, passRate;
    for (auto &student : students)
    {
        averageUsualScore += student.usualScore;
        averageFinalScore += student.finalScore;
        averageTotalScore += student.totalScore;

        if (student.totalScore < 60)
            failNumber++;
    }
    averageUsualScore /= number;
    averageFinalScore /= number;
    averageTotalScore /= number;
    passRate = 100 * (number - failNumber) / number;

    cout << "����" << number << "��ѧ����" << endl;
    cout << "ƽʱ�ɼ���ƽ����Ϊ��" << averageUsualScore << endl;
    cout << "��ĩ���Գɼ���ƽ����Ϊ��" << averageFinalScore << endl;
    cout << "������ƽ����Ϊ��" << averageTotalScore << endl;
    cout << "��" << failNumber << "�˲�����" << endl;
    cout << "������Ϊ" << passRate << '%' << endl;
}

void saveToFile()
{
    ofstream outfile("students.txt");

    for (Student &s : students)
    {
        outfile << s.id << " " << s.name << " "
                << s.usualScore << " " << s.finalScore << endl;
    }

    outfile.close();
    cout << "�ļ�����ɹ�!";
}

void loadFromFile()
{
    ifstream infile("students.txt");
    if (!infile.is_open())
    {
        cout << "Failed to open file!" << endl;
        return;
    }
    if (infile.is_open())
    {
        string id, name;
        double usualScore, finalScore;
        while (infile >> id >> name >> usualScore >> finalScore)
        {
            Student student(id, name, usualScore, finalScore);
            students.push_back(student);
        }
    }

    infile.close();
    cout << "�ļ�����ɹ�!" << endl;
}

void clean()
{
    system("pause");
    system("cls");
}

void modify()
{
    if (students.empty())
    {
        cout << "û��ѧ����Ϣ��" << endl;
        return;
    }

    cout << "������Ҫ�޸ĵ�ѧ����ѧ�Ż�������" << endl;
    string x;
    cin >> x;

    for (Student &s : students)
    {
        if (s.id == x || s.name == x)
        {
            cout << "��ѧ������Ϣ���£�\nѧ��\t����\tƽʱ�ɼ�\t��ĩ���Գɼ�\t����" << endl;
            s.display();
            cout << "������Ҫ�޸ĵ���Ŀ�ı�ţ�1.ѧ�ţ�2.������3.ƽʱ�ɼ���4.��ĩ���Գɼ�����" << endl;

            string content;
            double score;
            char option;
            cin >> option;
            switch (option)
            {
            case '1':
                cout << "������ѧ�ţ�" << endl;
                cin >> content;
                s.id = content;
                cout << "�޸ĳɹ���" << endl;
                break;
            case '2':
                cout << "������������" << endl;
                cin >> content;
                s.name = content;
                cout << "�޸ĳɹ���" << endl;
                break;
            case '3':
                cout << "������ƽʱ�ɼ���" << endl;
                cin >> score;
                s.usualScore = score;
                cout << "�޸ĳɹ���" << endl;
                break;
            case '4':
                cout << "��������ĩ���Գɼ���" << endl;
                cin >> score;
                s.finalScore = score;
                cout << "�޸ĳɹ���" << endl;
                break;
            default:
                cout << "�����������޸�ʧ�ܣ�" << endl;
            }
            cout << "�޸ĺ����Ϣ���£�\nѧ��\t����\tƽʱ�ɼ�\t��ĩ���Գɼ�\t����" << endl;
            s.display();
            return;
        }
    }

    cout << "û���ҵ���Ӧ��ѧ����" << endl;
}