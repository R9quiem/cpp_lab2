#include <iostream> 
#include <vector> 

class Student {

public:
    enum Type
    {
        Good,
        Average,
        Poor

    };

    Student(Type type) {

        this->type = type;
    }
    Type type;
    void solve(const QuadEquation &equation){}
private:
};

class Teacher {
    void print() {};
};

class QuadEquation {
    double a, b, c;
};

int main()
{
    setlocale(LC_ALL, "ru");
    //инициализация студентов и учителя 
    std::vector<Student> students;
    Teacher teacher;

    students.push_back(Student(Student::Type::Good));
    students.push_back(Student(Student::Type::Average));
    students.push_back(Student(Student::Type::Good));
    students.push_back(Student(Student::Type::Good));
    students.push_back(Student(Student::Type::Average));
    students.push_back(Student(Student::Type::Poor));
    
    //студенты получают задачи и решают (записывая в файлик с решениями) 
    for (const auto& student : students) {

        std::cout << "Студент " << student.type <<  std::endl;

    }
    //студенты отправляют задачи teacher 

    //учитель все проверяет и записывает в другой файлик успеваемость 

    //учитель пишет статистику 
}