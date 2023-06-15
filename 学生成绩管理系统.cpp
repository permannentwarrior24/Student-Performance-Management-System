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
    string id;                                               // 学号
    string name;                                             // 姓名
    double usualScore;                                       // 平时成绩
    double finalScore;                                       // 期末考试成绩
    double totalScore = usualScore * 0.3 + finalScore * 0.7; // 总评

    Student(){};
    Student(string id, string n, double u, double f) : id(id), name(n), usualScore(u), finalScore(f){};

    void display()
    {
        cout << id << "\t" << name << "\t  "
             << usualScore << "\t\t      " << finalScore << "\t"
             << totalScore << endl;
    }
};

// 全局变量
vector<Student> students;

// 子函数声明
void inputStu();      // 录入学生信息
void displayAll();    // 显示学生信息
void sortStu();       // 排序总评
void findStu();       // 查找学生
void insertStu();     // 插入学生
void deleteStudent(); // 删除学生
void countStu();      // 统计数据
void saveToFile();    // 把数据保存到文件
void loadFromFile();  // 从文件加载数据
void clean();         // 清屏
void modify();        // 修改信息

int main()
{
    loadFromFile(); // 从文件加载数据

    while (true)
    {
        cout << "===================================" << endl;
        cout << "        欢迎使用成绩管理系统      " << endl;
        cout << "     1=录入学生  2=显示所有学生   " << endl;
        cout << "     3=排序总评  4=查找学生      " << endl;
        cout << "     5=插入学生  6=删除学生      " << endl;
        cout << "     7=统计数据  8=修改信息      " << endl;
        cout << "          0=保存并退出           " << endl;
        cout << "===================================" << endl;
        cout << "请输入您的选择：" << endl;
        char choice;
        cin >> choice;

        switch (choice)
        {
        case '0':         // 退出
            saveToFile(); // 保存数据到文件
            Sleep(1000);
            return 0;
        case '1': // 录入学生信息
            inputStu();
            clean();
            break;
        case '2': // 显示学生信息
            displayAll();
            clean();
            break;
        case '3': // 排序总评
            sortStu();
            clean();
            break;
        case '4': // 查找学生
            findStu();
            clean();
            break;
        case '5': // 插入学生
            insertStu();
            clean();
            break;
        case '6': // 删除学生
            deleteStudent();
            clean();
            break;
        case '7': // 统计数据
            countStu();
            clean();
            break;
        case '8': // 修改信息
            modify();
            clean();
            break;
        default:
            cout << "操作无效，请输入正确的数字!" << endl;
            clean();
        }
    }
}

void inputStu()
{
    cout << "请依次输入学生信息（学号 姓名 平时成绩 期末考试成绩）：" << endl;

    string id, name;
    double usualScore, finalScore;
    cin >> id >> name >> usualScore >> finalScore;

    // 判断学号是否重复
    for (Student &s : students)
    {
        if (s.id == id)
        {
            cout << "该学号已存在，录入失败。" << endl;
            return;
        }
    }

    // 添加学生
    Student s(id, name, usualScore, finalScore);
    students.push_back(s);

    cout << "录入成功！" << endl;
}

void displayAll()
{
    if (students.empty())
    {
        cout << "没有学生信息。" << endl;
        return;
    }

    cout << "排名\t学号\t姓名\t平时成绩\t期末考试成绩\t总评" << endl;

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
        cout << "没有学生信息。" << endl;
        return;
    }

    sort(students.begin(), students.end(), [](const Student &a, const Student &b)
         { return a.totalScore > b.totalScore; });

    cout << "排序成功！" << endl;
}

void findStu()
{
    if (students.empty())
    {
        cout << "没有学生信息。" << endl;
        return;
    }

    cout << "请输入要查找的学生的学号或姓名：" << endl;
    string x;
    cin >> x;

    for (Student &s : students)
    {
        if (s.id == x || s.name == x)
        {
            cout << "学号\t姓名\t平时成绩\t期末考试成绩\t总评" << endl;
            s.display();
            return;
        }
    }

    cout << "没有找到对应的学生。" << endl;
}

void insertStu()
{
    if (students.empty())
    {
        cout << "没有学生信息。" << endl;
        return;
    }

    cout << "请输入要插入的学生信息：（学号 姓名 平时成绩 期末考试成绩）" << endl;

    string id, name;
    double usualScore, finalScore;
    cin >> id >> name >> usualScore >> finalScore;
    // 判断学号是否重复
    for (Student &s : students)
    {
        if (s.id == id)
        {
            cout << "学号已经存在，请重新输入。" << endl;
            return;
        }
    }

    // 添加学生
    Student student(id, name, usualScore, finalScore);

    for (unsigned int i = 0; i < students.size(); i++)
    {
        if (student.totalScore >= students[i].totalScore)
        {
            students.emplace(students.begin() + i, student);
            cout << "插入成功！" << endl;
            return;
        }
    }

    students.push_back(student);
    cout << "插入成功！" << endl;
}

void deleteStudent()
{
    if (students.empty())
    {
        cout << "没有学生信息。" << endl;
        return;
    }

    cout << "请输入要删除的学生的学号或姓名：" << endl;
    string x;
    cin >> x;

    for (unsigned int i = 0; i < students.size(); i++)
    {
        if (students[i].id == x || students[i].name == x)
        {
            cout << "确定要删除学生信息吗？(Y确认/N取消):" << endl;
            char choice;
            cin >> choice;
            if (choice == 'Y' || choice == 'y')
            {
                students.erase(students.begin() + i);
                cout << "删除成功！" << endl;
            }
            else
                cout << "已取消" << endl;
            return;
        }
    }

    cout << "没有找到对应的学生。" << endl;
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

    cout << "共有" << number << "名学生。" << endl;
    cout << "平时成绩的平均分为：" << averageUsualScore << endl;
    cout << "期末考试成绩的平均分为：" << averageFinalScore << endl;
    cout << "总评的平均分为：" << averageTotalScore << endl;
    cout << "有" << failNumber << "人不及格！" << endl;
    cout << "及格率为" << passRate << '%' << endl;
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
    cout << "文件保存成功!";
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
    cout << "文件载入成功!" << endl;
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
        cout << "没有学生信息。" << endl;
        return;
    }

    cout << "请输入要修改的学生的学号或姓名：" << endl;
    string x;
    cin >> x;

    for (Student &s : students)
    {
        if (s.id == x || s.name == x)
        {
            cout << "该学生的信息如下：\n学号\t姓名\t平时成绩\t期末考试成绩\t总评" << endl;
            s.display();
            cout << "请输入要修改的项目的编号（1.学号，2.姓名，3.平时成绩，4.期末考试成绩）：" << endl;

            string content;
            double score;
            char option;
            cin >> option;
            switch (option)
            {
            case '1':
                cout << "请输入学号：" << endl;
                cin >> content;
                s.id = content;
                cout << "修改成功！" << endl;
                break;
            case '2':
                cout << "请输入姓名：" << endl;
                cin >> content;
                s.name = content;
                cout << "修改成功！" << endl;
                break;
            case '3':
                cout << "请输入平时成绩：" << endl;
                cin >> score;
                s.usualScore = score;
                cout << "修改成功！" << endl;
                break;
            case '4':
                cout << "请输入期末考试成绩：" << endl;
                cin >> score;
                s.finalScore = score;
                cout << "修改成功！" << endl;
                break;
            default:
                cout << "编号输入错误，修改失败！" << endl;
            }
            cout << "修改后的信息如下：\n学号\t姓名\t平时成绩\t期末考试成绩\t总评" << endl;
            s.display();
            return;
        }
    }

    cout << "没有找到对应的学生。" << endl;
}