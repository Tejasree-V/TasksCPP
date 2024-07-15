#include<bits/stdc++.h>
#include<string.h>
#include <string>
using namespace std;
struct student{
    string name;
    int id;
    int math;
    int phy;
    int chem;
    int cpa;
};

void addStudent(vector<student> &grades){
    student newStu;
    cout << "Enter student name: ";
    cin.ignore();
    getline(cin, newStu.name);
    cout << "Enter id: ";
    cin >> newStu.id;
    cout << "Enter Math Grade: ";
    cin >> newStu.math;
    cout << "Enter Physics Grade: ";
    cin >> newStu.phy;
    cout << "Enter Chemistry Grade: ";
    cin >> newStu.chem;
    newStu.cpa=(newStu.math+newStu.phy+newStu.chem)/3;
    grades.push_back(newStu);
    cout << "student added successfully!" << endl;
}

void displayList(vector<student>& grades) {

    cout << "Class grades:" << endl;
    cout<< "id"<< "\t" <<"Name" << "\t" << "Math"<< "\t"<< "Phy"<< "\t"<< "chem"<< "\t" << "CPA"<< endl;
    for (int i = 0; i < grades.size(); i++) {
        const student& stu = grades[i]; 
        cout << stu.id <<"\t"<< stu.name<< "\t"<< stu.math<<"\t"<< stu.phy<< "\t"<< stu.chem<< "\t"<< stu.cpa;
        cout << endl;
    }

}

void ClassAvg (vector<student>& grades){
    double sum=0,m=0,p=0,c=0;
    for (int i = 0; i < grades.size(); i++) {
        const student& stu = grades[i]; 
        sum=sum+stu.cpa;
        m=m+stu.math;
        p=p+stu.phy;
        c=c+stu.chem;
    }
    cout<< "class average is: "<<endl;
    cout<<"math: "<< m/grades.size()<<"\t"<<"phy: "<< p/grades.size()<<"\t"<<"chem: "<< c/grades.size()<<"\t"<<"total: "<< sum/grades.size()<< endl;
}
bool comp(const student& a, const student& b) {
    return a.cpa > b.cpa;
}

void ClassTops(vector<student>& grades) {
    sort(grades.begin(), grades.end(), comp);
    int n = grades.size();
    cout << "Class Toppers:" << endl;
    for (int i = 0; i < min(3, n); i++) {
        const student& stu = grades[i];
        cout << i + 1 << ". " << stu.name << " (CPA: " << stu.cpa << ")" << endl;
    }
}
int main(){
int x;
vector<student>grades;
    do{
        cout<< "choose an action 1.enter new stu 2.Display 3.ClassAvg 4.ClassToppers 5.end"<< endl;
    cin>>x;
    switch(x){

        case 1: {
            addStudent(grades);
        } break;

        case 2: {
            displayList(grades);
        } break;
        case 3: {
            ClassAvg(grades);
        } break;
        case 4: {
            ClassTops(grades);
        } break;
        case 5:
            cout << "Exiting program...";
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
            break;
    }
    } while (x!=5);
    return 0;

}
