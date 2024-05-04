#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

int generateRandomNumber(int maxNum) {
    return rand() % maxNum + 1;
}

char generateRandomOperator() {
    char operators[] = { '+', '-', '*', '/' };
    return operators[rand() % 4];
}

void generateExpression(int numQuestions, char operation, int maxNum, bool withBracket, bool withDecimal, ostream& output) {
    for (int i = 0; i < numQuestions; i++) {
        int num1 = generateRandomNumber(maxNum);
        int num2 = generateRandomNumber(maxNum);
        char op = operation == 'r' ? generateRandomOperator() : operation;

        if (withDecimal) {
            double result;
            switch (op) {
            case '+':
                result = num1 + num2;
                break;
            case '-':
                result = num1 - num2;
                break;
            case '*':
                result = num1 * num2;
                break;
            case '/':
                result = (double)num1 / num2;
                break;
            }
            output << num1 << " " << op << " " << num2 << " = " << result << endl;
        }
        else {
            if (withBracket) {
                output << "(" << num1 << " " << op << " " << num2 << ")" << endl;
            }
            else {
                output << num1 << " " << op << " " << num2 << endl;
            }
        }

        if (&output == &cout) {
            cout << endl;
        }
    }
}

int main() {
    srand(time(0));

    int numQuestions;
    char operation;
    int maxNum;
    bool withBracket;
    bool withDecimal;

    // 用户输入参数
    cout << "输出生成表达式的数量: ";
    cin >> numQuestions;
    cout << "选择运算符 (+, -, *, /, r 表示随机): ";
    cin >> operation;
    cout << "输入最大数的上限: ";
    cin >> maxNum;
    cout << "包括括号吗? (1 for yes, 0 for no): ";
    cin >> withBracket;
    cout << "包含小数吗? (1 for yes, 0 for no): ";
    cin >> withDecimal;

    // 输出到文件或控制台
    char outputChoice;
    cout << "选择输出 (f 输出到文件, c输出到控制台): ";
    cin >> outputChoice;

    if (outputChoice == 'f') {
        ofstream outputFile("questions.txt");
        if (outputFile.is_open()) {
            generateExpression(numQuestions, operation, maxNum, withBracket, withDecimal, outputFile);
            outputFile.close();
            cout << "Questions generated successfully and saved in questions.txt" << endl;
        }
        else {
            cout << "Error opening file." << endl;
        }
    }
    else if (outputChoice == 'c') {
        generateExpression(numQuestions, operation, maxNum, withBracket, withDecimal, cout);
    }
    else {
        cout << "Invalid output choice." << endl;
    }

    return 0;
}