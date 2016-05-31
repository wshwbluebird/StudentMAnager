//
// Created by Macbook Pro on 16/5/30.
//

#include <iostream>
#include <fstream>
#include <Vector>
#include <iomanip>

using namespace std;

struct Scoreinfo
{
    string student_number;
    string class_number;
    string class_name;
    int credit;
    double daily_score;
    double exp_score;
    double paper_score;
    double final_score;
    double final_credit;
};

struct Studentinfo
{
    string student_number;
    string student_name;
    string gender;
    int dor_numner;
    string telephone;
    Scoreinfo curriculum[40];
    int class_amount;
    double points;//实际得到的学分

};

class Score
{

public:
    int n;
    void readfile();
    Scoreinfo scores[100];
    void ScoreInput();
    void savefile();

};

class Student
{
private:
    Studentinfo students[100];
    void saveInfo();
    void readInfo();
    void getScores();
public:
    friend class Score;
    Score score;
    int p=0;
    void sortByScore();
    void searchStudentInfoByNumber();
    void searchStudentInfoBydorm();
    void searchScore();
    void deleteInfo();

};
void Score::ScoreInput()
{
    readfile();
    cout<<"学号: ";
    cin>>scores[n].student_number;
    cout<<"课程编号: ";
    cin>>scores[n].class_number;
    cout<<"课程名称: ";
    cin>>scores[n].class_name;
    cout<<"学分: ";
    cin>>scores[n].credit;
    cout<<"平时成绩:";
    cin>>scores[n].daily_score;
    cout<<"实验成绩:";
    cin>>scores[n].exp_score;
    cout<<"卷面成绩:";
    cin>>scores[n].paper_score;
    if(scores[n].exp_score==-1)
    {
        scores[n].final_score =
        scores[n].daily_score *0.3 + scores[n].paper_score*0.7;
    }
    else{
        scores[n].final_score =
        scores[n].daily_score *0.15+ scores[n].exp_score *0.15 + scores[n].paper_score*0.7;
    }

    if(scores[n].final_score>=90)
    {
        scores[n].final_credit = scores[n].credit;
    }
    else if(scores[n].final_score>=80&&scores[n].final_score<90)
    {
        scores[n].final_credit = scores[n].credit*0.8;
    }
    else if(scores[n].final_score>=70&&scores[n].final_score<80)
    {
        scores[n].final_credit = scores[n].credit*0.75;
    }
    else if(scores[n].final_score>=60&&scores[n].final_score<70)
    {
        scores[n].final_credit = scores[n].credit*0.6;
    }
    else{
        scores[n].final_credit = 0;
    }
    n++;
    savefile();
}


void Score::readfile()
{
    ifstream fin("/Users/macbookpro/ClionProjects/StudentManager/score.dat");
    if(fin.fail()){
        cout<<"打来文件失败"<<endl;
        exit(1);
    }
    int i=0;
    string temp;
    while(fin>>temp)
    {
        scores[i].student_number = temp;
        fin>>scores[i].class_number;
        fin>>scores[i].class_name;
        fin>>scores[i].credit;
        fin>>scores[i].daily_score;
        fin>>scores[i].exp_score;
        fin>>scores[i].paper_score;
        fin>>scores[i].final_score;
        fin>>scores[i].final_credit;
        i++;
    }
    n=i;
//    cout<<n<<endl;
    fin.close();
}

void Score::savefile()
{
    ofstream fout("/Users/macbookpro/ClionProjects/StudentManager/score.dat");
    if(fout.fail()){
        cout<<"打来文件失败"<<endl;
        exit(1);
    }
    for (int i = 0; i < n ; ++i) {
        fout<<scores[i].student_number<<"    "
        <<scores[i].class_number<<"    "
        <<scores[i].class_name<<"    "
        <<scores[i].credit<<"    "
        <<scores[i].daily_score<<"    "
        <<scores[i].exp_score<<"    "
        <<scores[i].paper_score<<"    "
        <<scores[i].final_score<<"    "
        <<scores[i].final_credit<<endl;
    }
    fout.close();
    cout<<"已保存"<<endl;
}

void Student::readInfo()
{
    ifstream fin("/Users/macbookpro/ClionProjects/StudentManager/student.txt");
    if(fin.fail()){
        cout<<"打来文件失败"<<endl;
        exit(1);
    }
    int i=0;
    string temp;
    while(fin>>temp)
    {
        students[i].student_number = temp;
       // cout<<students[i].student_number<<endl;
        fin>>students[i].student_name;
        fin>>students[i].gender;
        fin>>students[i].dor_numner;
        fin>>students[i].telephone;

        i++;
    }
    p=i;
    fin.close();
}

void Student::saveInfo()
{
    ofstream fout("/Users/macbookpro/ClionProjects/StudentManager/student.txt");
    if(fout.fail())
    {
        cout<<"打来文件失败"<<endl;
        exit(1);
    }
    for (int i = 0; i < p ; ++i)
    {
        fout<<students[i].student_number<<"    "
        <<students[i].student_name<<"    "
        <<students[i].gender<<"    "
        <<students[i].dor_numner<<"    "
        <<students[i].telephone<<endl;
    }
    fout.close();
    cout<<"已保存"<<endl;
}
void Student::searchStudentInfoByNumber()
{
    readInfo();
    cout<<"请输入要查找的姓名或学号: ";
    string temp;
    cin>>temp;
    bool flag = true;
    for (int i = 0; i < p ; ++i) {
        if(temp==students[i].student_number||temp==students[i].student_name)
        {
            flag = false;
            cout<<students[i].student_number<<"    "
            <<students[i].student_name<<"    "
            <<students[i].gender<<"    "
            <<students[i].dor_numner<<"    "
            <<students[i].telephone<<endl;
            break;
        }
    }
    if(flag)
    {
        cout<<"未找到该学生!";
    }

}
void Student::searchStudentInfoBydorm()
{
    readInfo();
    cout<<"请输入要查找的宿舍号: ";
    int temp;
    cin>>temp;
    bool flag = true;
    for (int i = 0; i < p ; ++i) {
        if(temp==students[i].dor_numner)
        {
            flag = false;
            cout<<students[i].student_number<<"    "
            <<students[i].student_name<<"    "
            <<students[i].gender<<"    "
            <<students[i].dor_numner<<"    "
            <<students[i].telephone<<endl;
        }
    }
    if(flag)
    {
        cout<<"未找到该学生!";
    }
    saveInfo();
}
void Student::getScores()
{
    readInfo();
    score.readfile();
    for (int i = 0; i < p ; ++i) {
        students[i].class_amount=0;
        students[i].points = 0;
        cout<<score.n<<endl;
        for (int j = 0; j < score.n; ++j) {
            if(students[i].student_number==score.scores[j].student_number)
            {
                students[i].curriculum[students[i].class_amount].class_number = score.scores[j].class_number;
                students[i].curriculum[students[i].class_amount].class_name = score.scores[j].class_name;
                students[i].curriculum[students[i].class_amount].daily_score = score.scores[j].daily_score;
                students[i].curriculum[students[i].class_amount].exp_score = score.scores[j].exp_score;
                students[i].curriculum[students[i].class_amount].paper_score = score.scores[j].paper_score;
                students[i].curriculum[students[i].class_amount].final_score = score.scores[j].final_score;
                students[i].curriculum[students[i].class_amount].credit = score.scores[j].credit;
                students[i].curriculum[students[i].class_amount++].final_credit = score.scores[j].final_credit;
                students[i].points+=score.scores[j].final_credit;
            }
        }
    }
}
void Student::searchScore()
{
    getScores();
    string temp;
    cout<<"请输入要查询的学号: ";
    cin>>temp;
    for (int i = 0; i < p ; ++i) {
        if(temp == students[i].student_number)
        {
            cout<<"    "<<"学号:  "<<students[i].student_number<<"    姓名: "<<students[i].student_name<<endl;
            for (int j = 0; j < students[i].class_amount; ++j) {
                cout<<"课程编号:  "<<students[i].curriculum[j].class_number<<"    课程名称:  "
                <<students[i].curriculum[j].class_name<<"     综合成绩:  "<< students[i].curriculum[j].final_score
                        <<"    实得学分:  "<< students[i].curriculum[j].final_credit<<endl;
            }
            cout<<"共修: "<<students[i].class_amount<<"科"<<"     "<<"实得总学分为:  "<<students[i].points;
            break;
        }

    }
}

void Student::sortByScore()
{
    getScores();
    for (int i = 0; i < p ; ++i) {
        for (int j = i; j < p ; ++j) {
            if(students[i].points < students[j].points)
            {
                Studentinfo temp;
                temp =  students[i];
                students[i] = students[j];
                students[j] = temp;

            }
        }
    }

    for (int k = 0; k < p; ++k) {
        cout<<"    "<<"学号:  "<<students[k].student_number<<"    姓名: "<<students[k].student_name
            <<"      共修: "<<students[k].class_amount<<"科"<<"     "<<"实得总学分为:  "<<students[k].points<<endl;
    }
}

void  Student::deleteInfo()
{
    readInfo();
    string temp;
    cout<<"请输入要删除的学号:  ";
    cin>>temp;
    for (int i = 0; i < p; ++i) {
       if(temp==students[i].student_number)
       {
           while(i<p-1)
           {
               students[i] = students[i+1];
               i++;
           }
           p--;
           //break;
       }
    }
    cout<<"delete1"<<endl;
    saveInfo();
    score.readfile();
    //cout<<score.n<<endl;
    for (int j = 0; j < score.n ; ++j) {
        //cout<<"df"<<endl;
        if(temp==score.scores[j].student_number)
        {
            int cp = j;
           // cout<<cp<<endl;
            while(cp<score.n-1)
            {
                score.scores[cp] = score.scores[cp+1];
                cp++;
            }
            j--;
            score.n--;
        }
    }
    score.savefile();
}

int main()
{
//    cout<<"Sefd";
//    Score t;
//    Score t;
//    t.n=0;
//    cout<<"SDfd"<<endl;
//    t.ScoreInput();
//    t.searchScore();
    Student t;
//    t.score.ScoreInput();
//    t.score.ScoreInput();
//    t.score.ScoreInput();
    //t.searchScore();
     t.deleteInfo();
    return 0;
}