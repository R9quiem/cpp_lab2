#include <iostream> 
#include <fstream>
#include <vector> 
#include <string>
#include <sstream>
#include <map>
#include <optional>
#include <cstdio>

class Student {
    
public:
    enum Type{ Good, Average, Poor };
    Student(Type type, const std::string& name) {
        this->type = type;
        this->name = name;
    }

    void solveTest(const std::string& equationsFile, const std::string& solutionsFile) const {
            std::ifstream inFile(equationsFile);
            std::ofstream outFile(solutionsFile, std::ios::app); 

            if (!inFile.is_open()) {
                std::cerr << "Ошибка открытия файла с уравнениями\n\n";
                return;
            }

            if (!outFile.is_open()) {
                std::cerr << "Ошибка открытия файла для записи решений\n\n";
                return;
            }
            std::string line;
        while (std::getline(inFile, line)) {
            std::istringstream iss(line);
            double a, b, c;
            if (!(iss >> a >> b >> c)) {
                std::cerr << "Неккоректный формат уравнения: " << line << "\n\n";
                continue; // Пропускаем некорректные уравнения
            }
            auto answer = solveEquation(a, b, c);
            if (answer.has_value()) {
                outFile << line << " | " << answer.value().first << " " << answer.value().second << " | " << this->name << "\n";
            }
            else {
                outFile << line << " | none | " << this->name << "\n";
            }
        }
        outFile << std::endl;
        inFile.close();
        outFile.close();
    }
    std::optional<std::pair<double, double>> solveEquation(double a, double b, double c) const {
        double D = b * b - 4 * a * c;
        if (D < 0) {
            return std::nullopt;
        }
        else {
            double root1 = (-b + std::sqrt(D)) / (2 * a);
            double root2 = (-b - std::sqrt(D)) / (2 * a);
            return std::make_pair(root1, root2);
        }
    }
private:
    Type type;
    std::string name;
};

class Teacher {
    bool isChecked = false;
    std::map<std::string, int> results;
public:
    Teacher* checkSolutions(std::string solutionsFile) {
        std::ifstream inFile(solutionsFile);

        if (!inFile.is_open()) {
            std::cerr << "Ошибка открытия файла с решениями\n\n";
            return this;
        }

        std::string line;
        while (std::getline(inFile, line)) {
            std::istringstream iss(line);
            std::string equation;
            std::string answer;
            std::string student;

            // Используем разделитель ':' для разделения на три части
            if (std::getline(iss, equation, '|') && std::getline(iss, answer, '|') && std::getline(iss, student)) {
                std::istringstream issEquation(equation);
                double a, b, c;
                if (!(issEquation >> a >> b >> c)) {
                    std::cerr << "Неккоректный формат уравнения: " << line << "\n\n";
                    continue; // Пропускаем некорректные уравнения
                }
                answer.erase(std::remove(answer.begin(), answer.end(), ' '), answer.end());
                student.erase(std::remove(student.begin(), student.end(), ' '), student.end());
                std::string rightAnswer = solveEquation(a, b, c);
                if (rightAnswer == answer) {
                    results[student]++;
                }
                std::istringstream issAnswer(answer);
            }
        }
        inFile.close();
        this->isChecked = true;
        return this;
       
    };
    
    
    Teacher* writeResults(std::string resultsFile) {
        if (!isChecked) {
            std::cout << "Нельзя записать результаты не проверив ответы\n\n";
            return this;
        }
        std::ofstream outFile(resultsFile);
        if (!outFile.is_open()) {
            std::cerr << "Ошибка открытия файла с результатами\n\n";
            return this;
        }
        outFile << "Таблица успеваемости:\n";
        for (auto student : results) {
            outFile << student.first << ": " << student.second << "\n";
        }
        outFile.close();
        
    };
    Teacher* showResults(std::string resultsFile) {
        if (!isChecked) {
            std::cout << "Нельзя показать результаты не проверив ответы\n\n";
            return this;
        }
        std::ifstream inFile(resultsFile);
        if (!inFile.is_open()) {
            std::cerr << "Ошибка открытия файла с результатами\n\n";
            return this;
        }

        inFile.close();
    };
    std::string solveEquation(double a, double b, double c) const { 
        double D = b * b - 4 * a * c;
        if (D < 0) {
            return "none"; 
        }
        else {
            double root1 = (-b + std::sqrt(D)) / (2 * a);
            double root2 = (-b - std::sqrt(D)) / (2 * a);
            std::ostringstream oss;
            oss << std::noshowpoint << root1 << root2;
            return oss.str();
        }
    }
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
        student.solveTest(equationsFile, solutionsFile);
    }

    //учитель все проверяет и записывает
    //очистка файла
    //std::ofstream file(resultsFile, std::ios::trunc);
    teacher.checkSolutions(solutionsFile);

    //записывает в файл результаты
    teacher.writeResults(resultsFile);

    //учитель показывает результаты
    teacher.showResults(resultsFile);


}