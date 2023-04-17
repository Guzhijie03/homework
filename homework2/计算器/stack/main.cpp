#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <map>
#include <cmath>

// ����һ��������������������һ��������Ľ��
double calculate(double a, double b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;
    case '^': return pow(a, b);
    default: return 0;
    }
}

// ����һ��������ʵ���ַ���������
double string_calculator(const std::string& expression) {
    // ��������ջ�ֱ�洢�������������
    std::stack<char> op_stack;
    std::stack<double> num_stack;

    // ����һ�����ȼ���
    std::map<char, int> priority = {
      {'+', 1},
      {'-', 1},
      {'*', 2},
      {'/', 2},
      {'^', 3}
    };

    // ����һ���ַ�������������ȡ���ʽ�е��ַ�������
    std::istringstream iss(expression);

    // ����һ���ַ�������һ�����ֱ���
    char ch;
    double num;

    // �������ʽ�е�ÿ���ַ�
    while (iss >> ch) {
        // ��������֣��Ͷ�ȡ���������֣�������ѹ��������ջ��
        if (std::isdigit(ch)) {
            iss.putback(ch); // ���ַ��Ż��ַ�������
            iss >> num; // ��ȡ����������
            num_stack.push(num); // ������ѹ��������ջ��
        }
        // ����������ţ��ͽ���ѹ�������ջ��
        else if (ch == '(') {
            op_stack.push(ch);
        }
        // ����������ţ��Ͳ��ϵ�����������������������м��㣬ֱ������������Ϊֹ
        else if (ch == ')') {
            while (!op_stack.empty() && op_stack.top() != '(') {
                char op = op_stack.top(); // ���������
                op_stack.pop();
                double b = num_stack.top(); // �����Ҳ�����
                num_stack.pop();
                double a = num_stack.top(); // �����������
                num_stack.pop();
                double res = calculate(a, b, op); // ������
                num_stack.push(res); // �����ѹ��������ջ��
            }
            if (!op_stack.empty() && op_stack.top() == '(') {
                op_stack.pop(); // ����������
            }
        }
        // �����������������ͱȽ�����ջ������������ȼ�����������Ӧ�Ĳ���
        else {
            while (!op_stack.empty() && priority[ch] <= priority[op_stack.top()]) {
                char op = op_stack.top(); // ���������
                op_stack.pop();
                double b = num_stack.top(); // �����Ҳ�����
                num_stack.pop();
                double a = num_stack.top(); // �����������
                num_stack.pop();
                double res = calculate(a, b, op); // ������
                num_stack.push(res); // �����ѹ��������ջ��
            }
            op_stack.push(ch); // ����ǰ�����ѹ�������ջ��
        }
    }

    // ����������ʽ����������ջ��Ϊ�գ��ͼ���������������������������м��㣬ֱ�������ջΪ��Ϊֹ
    while (!op_stack.empty()) {
        char op = op_stack.top(); // ���������
        op_stack.pop();
        double b = num_stack.top(); // �����Ҳ�����
        num_stack.pop();
        double a = num_stack.top(); // �����������
        num_stack.pop();
        double res = calculate(a, b, op); // ������
        num_stack.push(res); // �����ѹ��������ջ��
    }

    // ��ʱ��������ջ��ֻʣ��һ��Ԫ�أ��������յļ�����������������
    return num_stack.top();
}

int main() {
    std::string expression; // ����һ���ַ����������洢���ʽ
    std::cout << "������һ����ʽ��"; // �����ʾ��Ϣ
    std::cin >> expression; // �ӱ�׼�����ȡ���ʽ
    double result = string_calculator(expression); // ���ú���������
    std::cout << "��ʽ�������ǣ�" << result << "\n"; // ������
    return 0; // ����0��ʾ������������
}