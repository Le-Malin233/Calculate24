#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>

using namespace std;
//----------------------------------------------------------------------------
//计算24的程序
// 验证是否有解
bool has_answer(int* arr, int oper_code, int method) {
    bool no_div_err = true;
    auto calc = [&no_div_err](double a, double b, int op) -> double {
        if (b == 0 && op == 3) {
            no_div_err = false;
            return 0;
        }
        return op == 0 ? a + b : op == 1 ? a - b : op == 2 ? a * b : a / b;
        };
    int o1 = oper_code % 4, o2 = (oper_code >> 2) % 4, o3 = (oper_code >> 4) % 4;
    if (method == 1) {	// ((AB)C)D
        return no_div_err && abs(calc(calc(calc(arr[0], arr[1], o1), arr[2], o2), arr[3], o3) - 24) < 1e-6;
    }
    else if (method == 2) { // (AB)(CD)
        return no_div_err && abs(calc(calc(arr[0], arr[1], o1), calc(arr[2], arr[3], o3), o2) - 24) < 1e-6;
    }
    else if (method == 3) { // (A(BC))D
        return no_div_err && abs(calc(calc(arr[0], calc(arr[1], arr[2], o2), o1), arr[3], o3) - 24) < 1e-6;
    }
    else if (method == 4) { // A((BC)D)
        return no_div_err && abs(calc(arr[0], calc(calc(arr[1], arr[2], o2), arr[3], o3), o1) - 24) < 1e-6;
    }
    else if (method == 5) { // A(B(CD))
        return no_div_err && abs(calc(arr[0], calc(arr[1], calc(arr[2], arr[3], o3), o2), o1) - 24) < 1e-6;
    }
    return false;
}
// 转换为 答案字符串 
string answer_to_string(int* arr, int oper_code, int method) {
    const char* op_str = "+-*/";
    string a = to_string(arr[0]), b = to_string(arr[1]), c = to_string(arr[2]), d = to_string(arr[3]);
    char o1 = op_str[oper_code % 4], o2 = op_str[(oper_code >> 2) % 4], o3 = op_str[(oper_code >> 4) % 4];
    if (method == 1) {// ((AB)C)D
        return "((" + a + o1 + b + ")" + o2 + c + ")" + o3 + d + " = 24";
    }
    else if (method == 2) {// (AB)(CD)
        return "(" + a + o1 + b + ")" + o2 + "(" + c + o3 + d + ") = 24";
    }
    else if (method == 3) {// (A(BC))D
        return "(" + a + o1 + "(" + b + o2 + c + "))" + o3 + d + " = 24";
    }
    else if (method == 4) { // A((BC)D)
        return a + o1 + "((" + b + o2 + c + ")" + o3 + d + ")" + " = 24";
    }
    else if (method == 5) {// A(B(CD))
        return a + o1 + "(" + b + o2 + "(" + c + o3 + d + "))" + " = 24";
    }
    return string("error occurred");
}
string cal24(string num) {
    for (int i = 0; i < 4; ++i) {
        if (num.find('J') != -1) {
            int tmp = num.find('J');
            num.replace(tmp, 2, "11");
            num.insert(tmp + 2, " ");
        }
        if (num.find('Q') != -1) {
            int tmp = num.find('Q');
            num.replace(tmp, 2, "12");
            num.insert(tmp + 2, " ");
        }
        if (num.find('K') != -1) {
            int tmp = num.find('K');
            num.replace(tmp, 2, "13");
            num.insert(tmp + 2, " ");
        }
    }
    for (int i = 0; i < num.size(); i++) {
        if (!((num[i] >= '0' && num[i] <= '9') || num[i] == ' ')) {
            return "Input error!";
        }
    }
    int arr[4]; // 4 个数字
    vector<string> answers;
    stringstream ss;
    ss << num;

    for (int i = 0; i < 4; i++) {
        ss >> arr[i];
        if (arr[i] <= 0 || arr[i] > 13) {
            return "Input error!";
        }
    }
    int aa;
    if (ss >> aa) return "Input error!";
    sort(arr, arr + 4);
    bool result = false;
    do {
        for (int meth = 1; meth <= 5; meth++) {
            for (int oper = 0; oper < 64; oper++) {
                result = has_answer(arr, oper, meth);
                if (result) {
                    answers.push_back(answer_to_string(arr, oper, meth));
                }
            }
        }
    } while (next_permutation(arr, arr + 4));
    if (answers.size() == 0) {
        return "No solution";
    }
    else {
        srand(time(0));
        int min = 0;
        int max = answers.size() - 1;
        int ran = rand() % (max - min + 1) + min;
        return answers[ran];
    }
}

//----------------------------------------------------------------------------
//计算表达式的程序

// 运算符优先级映射
unordered_map<char, int> precedence = {
    {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}
};
// 判断是否是数字
bool isDigit(char c) {
    return c >= '0' && c <= '9';
}
// 判断是否是运算符
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}
// 运算符计算
double applyOperator(double a, double b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;
    default: return 0;
    }
}
// 中缀转后缀并计算
double evaluateExpression(const string& expr) {
    stack<double> values;        // 存储操作数
    stack<char> operators;       // 存储运算符
    int n = expr.size();

    for (int i = 0; i < n; ++i) {
        char c = expr[i];

        // 忽略空格
        if (isspace(c)) continue;

        // 如果是数字，则提取整个数字
        if (isDigit(c)) {
            double num = 0;
            while (i < n && isDigit(expr[i])) {
                num = num * 10 + (expr[i] - '0');
                ++i;
            }
            --i;  // 调整索引，因为外部循环会加1
            values.push(num);
        }
        // 如果是左括号，压入栈
        else if (c == '(') {
            operators.push(c);
        }
        // 如果是右括号，进行计算直到遇到左括号
        else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                char op = operators.top();
                operators.pop();
                double b = values.top();
                values.pop();
                double a = values.top();
                values.pop();
                values.push(applyOperator(a, b, op));
            }
            operators.pop();  // 弹出 '('
        }
        // 如果是运算符
        else if (isOperator(c)) {
            while (!operators.empty() && precedence[operators.top()] >= precedence[c]) {
                char op = operators.top();
                operators.pop();
                double b = values.top();
                values.pop();
                double a = values.top();
                values.pop();
                values.push(applyOperator(a, b, op));
            }
            operators.push(c);
        }
    }

    // 最后进行剩余的运算
    while (!operators.empty()) {
        char op = operators.top();
        operators.pop();
        double b = values.top();
        values.pop();
        double a = values.top();
        values.pop();
        values.push(applyOperator(a, b, op));
    }

    return values.top();  // 最终结果
}

//----------------------------------------------------------------------------
//生成4个随机数
vector<int> four_numbers() {
    bool flag = true;
    while (flag) {
        srand(time(0));
        // 生成四个随机数字（1到13）
        vector<int> numbers(4);
        for (int i = 0; i < 4; ++i) {
            numbers[i] = 1 + rand() % 13;  // 生成1到13之间的随机数
        }
        int arr[4];
        for (int i = 0; i < 4; ++i) {
            arr[i] = numbers[i];
        }
        sort(arr, arr + 4);
        bool result = false;

        do {
            for (int meth = 1; meth <= 5; meth++) {
                for (int oper = 0; oper < 64; oper++) {
                    result = has_answer(arr, oper, meth);
                    if (result) {
                        return numbers;
                        flag = false;
                    }
                }
            }
        } while (next_permutation(arr, arr + 4));
    }
    srand(time(0));
    // 生成四个随机数字（1到13）
    vector<int> numbers(4);
    for (int i = 0; i < 4; ++i) {
        numbers[i] = 1 + rand() % 13;  // 生成1到13之间的随机数
    }
    int arr[4];
    for (int i = 0; i < 4; ++i) {
        arr[i] = numbers[i];
    }
    sort(arr, arr + 4);
    bool result = false;

    do {
        for (int meth = 1; meth <= 5; meth++) {
            for (int oper = 0; oper < 64; oper++) {
                result = has_answer(arr, oper, meth);
                if (result) {
                    return numbers;
                }
            }
        }
    } while (next_permutation(arr, arr + 4));

}

//----------------------------------------------------------------------------
//判断输入的表达式是否都用上了生成的4个数字
bool validateExpression(const string& expression, const vector<int>& numbers) {
    // 使用set存储数字，去重
    set<int> validNumbers(numbers.begin(), numbers.end());
    map<int, int> countMap;
    map<int, int> numberMap;
    regex rgx("\\d+");
    auto words_begin = sregex_iterator(expression.begin(), expression.end(), rgx);
    auto words_end = sregex_iterator();

    for (sregex_iterator i = words_begin; i != words_end; ++i) {
        string numStr = (*i).str();
        int num = stoi(numStr);

        if (validNumbers.count(num)) {
            countMap[num]++;
        }
        else {
            return false;
        }
    }

    for (int num : numbers) {
        int counts = 0;
        if (validNumbers.count(num)) {
            numberMap[num]++;
        }
    }
    if (numberMap != countMap)return false;


    return true;
}