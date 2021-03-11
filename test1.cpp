#include<iostream>
#include<cstdio>
#include<string>
#include<fstream>
#include<Windows.h>
using namespace std;


class Student{
    public:
        string no;
        string name;
        string gender;
        int age;
        string department;

        void Insert(string n,string na,string gd,int a,string dpm);
        void Update();
        void Delete(string n);
        void SelectNo(string n);
};

class Course{
    public:
        int no;
        string name;
        int before;
        int credit;

        void Insert(int n,string na,int bf,int c);
        void SelectName(string na);
};

class Sc{
    public:
        string stuno;
        int courno;
        int score;

        void Insert(string sn,int cn,int c);
        void SelectCourno(int courno);
};

void print(string filename)
{
        fstream openfile;
        openfile.open(filename,ios::in);
        char str[100];
        while(openfile.getline(str,100))
        {
                cout<<left<<str<<endl;
        }
        return ;

}
void Student::Insert(string n,string na,string gd,int a,string dpm)
{
        no=n;
        name=na;
        gender=gd;
        age=a;
        department=dpm;

        fstream openfile;
        openfile.open("student.txt",ios::in|ios::out|ios::ate);
        if(openfile.fail())
        {
                openfile.open("student.txt",ios::out);  //新建文件
                openfile.close();
                openfile.open("student.txt",ios::in|ios::out); 
        }
        openfile<<no<<' '<<name<<' '<<gender<<' '<<age<<' '<<department<<endl;
        openfile.close();

}
void Student::Update()
{
        CopyFile("student.txt","tmp.txt",FALSE);  //复制文件
        fstream tmpfile("tmp.txt");
        if(tmpfile.fail())
        {
                cout<<"打开文件错误"<<endl;
                return ;
        }
        fstream openfile;
        openfile.open("student.txt",ios::out|ios::trunc);  //清空原文件
        while(tmpfile>>no>>name>>gender>>age>>department)  //逐条修改添加
        {
                age+=1;
                openfile<<no<<' '<<name<<' '<<gender<<' '<<age<<' '<<department<<endl;
        }
        tmpfile.close();
        openfile.close();
        DeleteFile("tmp.txt");  //删除副本
}
void Student::Delete(string n)
{
        CopyFile("student.txt","tmp.txt",FALSE);  //复制文件
        fstream tmpfile("tmp.txt");
        if(tmpfile.fail())
        {
                cout<<"打开文件错误"<<endl;
                return ;
        }
        fstream openfile;
        openfile.open("student.txt",ios::out|ios::trunc);  //清空原文件
        while(tmpfile>>no>>name>>gender>>age>>department)  //逐项添加
        {
                if(no==n) continue;  //不添加删除项
                openfile<<no<<' '<<name<<' '<<gender<<' '<<age<<' '<<department<<endl;
        }
        tmpfile.close();
        openfile.close();
        DeleteFile("tmp.txt");  //删除副本
}
void Student::SelectNo(string n)
{
        fstream openfile("student.txt");
        if(openfile.fail())
        {
                cout<<"打开文件错误"<<endl;
                return ;
        }
        while(openfile>>no>>name>>gender>>age>>department)  //逐项添加
        {
                if(no==n)  //查找成功
                {
                        cout<<no<<' '<<name<<endl;
                }
        }
        openfile.close();
        return ;
}
void Course::Insert(int n,string na,int bf,int c)
{
        no=n;
        name=na;
        before=bf;
        credit=c;

        fstream openfile;
        openfile.open("course.txt",ios::in|ios::out|ios::ate);
        if(openfile.fail())
        {
                openfile.open("course.txt",ios::out);  //新建文件
                openfile.close();
                openfile.open("course.txt",ios::in|ios::out); 
        }
        openfile<<no<<' '<<name<<' '<<before<<' '<<credit<<' '<<endl;
        openfile.close();
}

void Course::SelectName(string na)
{
        fstream openfile("course.txt");
        if(openfile.fail())
        {
                cout<<"打开文件错误"<<endl;
                return ;
        }
        while(openfile>>no>>name>>before>>credit)  //逐项读入查找
        {
                if(name==na) //查找成功
                {
                        Sc scselect;
                        scselect.SelectCourno(no);
                }
        }
        openfile.close();
        return ;
}
void Sc::Insert(string sn,int cn,int c)
{
        stuno=sn;
        courno=cn;
        score=c;

        fstream openfile;
        openfile.open("sc.txt",ios::in|ios::out|ios::ate);
        if(openfile.fail())
        {
                openfile.open("sc.txt",ios::out);  //新建文件
                openfile.close();
                openfile.open("sc.txt",ios::in|ios::out); 
        }
        openfile<<stuno<<' '<<courno<<' '<<score<<' '<<endl;
        openfile.close();

}

void Sc::SelectCourno(int cn)
{
        fstream openfile("sc.txt");
        if(openfile.fail())
        {
                cout<<"打开文件错误"<<endl;
                return ;
        }
        while(openfile>>stuno>>courno>>score)  //逐项读入查找
        {
                if(courno==cn)   //查找成功，返回信息
                {
                        Student stu;
                        stu.SelectNo(stuno);
                }
        }
        openfile.close();
        return ;
}

int main()
{
/**************************** task1 *****************************
 *    编写数据插入功能模块，将各个数据表的数据分别插入到对应    *
 *    的数据文件中，并显示输出各个数据表的数据信息；            *
 ****************************************************************/


        cout<<"---------task1----------"<<endl;

        Student s;
        s.Insert("95001","李勇","男",20,"CS");
        s.Insert("95002","刘晨","女",19,"IS");
        s.Insert("95003","王敏","女",18,"MA");
        s.Insert("95004","张立","男",19,"IS");
        print("student.txt");
        cout<<endl;

        Course c;
        c.Insert(1,"数据库",5,4);
        c.Insert(2,"数学",0,2);
        c.Insert(3,"信息系统",1,4);
        c.Insert(4,"操作系统",6,3);
        c.Insert(5,"数据结构",7,4);
        c.Insert(6,"数据处理",0,2);
        c.Insert(7,"PASCAL语言",6,4);
        print("course.txt");
        cout<<endl;

        Sc sc;
        sc.Insert("95001",1,92);
        sc.Insert("95001",2,85);
        sc.Insert("95001",3,88);
        sc.Insert("95002",2,90);
        sc.Insert("95002",3,80);
        print("sc.txt");
        cout<<endl;

/**************************** task2 *****************************
 *   编写数据修改功能模块，将所有学生的年龄增加1岁，并显示输    *
 *   出所有学生的信息；                                         *
 ****************************************************************/

        cout<<"---------task2----------"<<endl;
        s.Update();
        print("student.txt");
        cout<<endl;

/**************************** task3 *****************************
 *   编写数据删除功能模块，删除学号为95004的学生记录，并显示    *
 *   输出所有学生的信息                                         *
 ****************************************************************/

        cout<<"---------task3----------"<<endl;
        s.Delete("95004");
        print("student.txt");
        cout<<endl;
        

/**************************** task4 *****************************
 *   编写数据查询功能模块，查询选修了课程名为“信息系统”的学     *
 *   生学号和姓名                                               *
 ****************************************************************/

        cout<<"---------task4----------"<<endl;
        Course cs;
        cs.SelectName("信息系统");
        cout<<endl;

        return 0;
}
