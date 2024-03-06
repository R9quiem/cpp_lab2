#include <iostream> 
#include <fstream>
#include <vector> 
#include <string>
#include <sstream>
#include <optional>

class Student {
    
public:
    enum Type{ Good, Average, Poor };
    Student(Type type, const std::string& name) {
        this->type = type;
        this->name = name;
    }

    void solveEquations(const std::string& equationsFile, const std::string& solutionsFile) const {
            std::ifstream inFile(equationsFile);
            std::ofstream outFile(solutionsFile, std::ios::app); 

            if (!inFile.is_open()) {
                std::cerr << "Ошибка открытия файла с уравнениями\n";
                return;
            }

            if (!outFile.is_open()) {
                std::cerr << "Ошибка открытия файла для записи решений\n";
                return;
            }
            std::string line;
        while (std::getline(inFile, line)) {
            std::istringstream iss(line);
            double a, b, c;
            if (!(iss >> a >> b >> c)) {
                std::cerr << "Неккоректный формат уравнения: " << line << std::endl;
                continue; // Пропускаем некорректные уравнения
            }
            
            double D = b * b - 4 * a * c;

            if (D < 0) {
                outFile << line << " | none | " << this->name << " " << std::endl;
            } else {
                double root1 = (-b + sqrt(D)) / (2 * a);
                double root2 = (-b - sqrt(D)) / (2 * a);
                outFile << line << " | " << root1 << " " << root2 << " | " << this->name << " " << std::endl;
            }
        }
        outFile << std::endl;
        inFile.close();
        outFile.close();
    }
private:
    Type type;
    std::string name;
};

class Teacher {
    bool isChecked = false;
public:
    void checkSolutions(std::string solutionsFile, std::string resultsFile) {
        std::ifstream inFile(solutionsFile);
        std::ofstream outFile(resultsFile, std::ios::app);

        if (!inFile.is_open()) {
            std::cerr << "Ошибка открытия файла с уравнениями\n";
            return;
        }

        if (!outFile.is_open()) {
            std::cerr << "Ошибка открытия файла для записи решений\n";
            return;
        }
        std::string line;
        while (std::getline(inFile, line)) {
            std::istringstream iss(line);
            std::string equation;
            std::string answer;
            std::string student;

            // Используем разделитель ':' для разделения на три части
            if (std::getline(iss, equation, '|') && std::getline(iss, answer, '|') && std::getline(iss, student)) {
                // Теперь equation содержит уравнение, answer - ответ, student - имя студента
                std::cout << "Equation: " << equation << std::endl;
                std::cout << "Answer: " << answer << std::endl;
                std::cout << "Student: " << student << std::endl;
            }
        }
        outFile << std::endl;
        inFile.close();
        outFile.close();
        this->isChecked = true;
    };
    void showResults(std::string resultsFile) {
        if (!isChecked) {
            std::cout << "Нельзя показать результаты не проверив ответы" << std::endl;
            return;
        }
    };
};

int main()
{
    setlocale(LC_ALL, "ru");
    //инициализация студентов и учителя 
    std::vector<Student> students = {
        Student(Student::Type::Good, "Иван"),
        Student(Student::Type::Average, "Петр"),
        Student(Student::Type::Good, "Мария"),
        Student(Student::Type::Good, "Татьяна"),
        Student(Student::Type::Average, "Алексей"),
        Student(Student::Type::Poor, "Андрей")
    };

    Teacher teacher;

    std::string equationsFile = "equations.txt";
    std::string solutionsFile = "solutions.txt";
    std::string resultsFile = "results.txt";

    //студенты получают задачи и решают (записывая в файлик с решениями) 
    //очистка файла
    std::ofstream file(solutionsFile, std::ios::trunc);
    for (const auto& student : students) {
        student.solveEquations(equationsFile, solutionsFile);
    }

    //учитель все проверяет и записывает
    //очистка файла
    //std::ofstream file(resultsFile, std::ios::trunc);
    teacher.checkSolutions(solutionsFile, resultsFile);

    //учитель пишет статистику 

    teacher.showResults(resultsFile);


}