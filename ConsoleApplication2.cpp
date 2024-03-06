#include <iostream> 
#include <vector> 

class Student {

public:
    enum class Type
    {
        Good,
        Average,
        Poor

    };

    Student(Type type) {

        this->type = type;
    }
private:
    Type type;
};

class Teacher {
    void print() {};
};

class QuadEquation {
    double a, b, c;
};

int main()
{
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

        std::cout << "Студент " << std::endl;
    }
    //студенты отправляют задачи teacher 

    //учитель все проверяет и записывает в другой файлик успеваемость 

    //учитель пишет статистику 
}