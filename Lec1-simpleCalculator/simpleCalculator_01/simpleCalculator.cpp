#include <iostream>
using namespace std;

int main() {
    int num1, num2;
    char op;
    cin >> num1 >> op >> num2;
    switch (op) {
    case '+':
        cout << num1 + num2 << endl;
        break;
    case '-':
        cout << num1 - num2 << endl;
        break;
    case '*':
        cout << num1*num2 << endl;
        break;
    case '/':
        if(num2 == 0)
            cout << "Invalid Divisor" << endl;
        else
            cout << num1/num2 << endl;
        break;
    case '%':
        if(num2 == 0)
            cout << "Invalid Divisor" << endl;
        else
            cout << num1%num2 << endl;
        break;
    default:
        cout << "Invalid Operator" << endl;
        break;
    }
}