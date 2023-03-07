#include <iostream>
#include <cstdlib>

using namespace std;
int arithmetic(int num1, int num2, char op){
    switch (op) {
    case '+':
        return num1 + num2;
    case '-':
        return num1 - num2;
    case 'x':
        return num1 * num2;
    case '/':
        if(num2 == 0){
            cout << "Invalid Divisor" << endl;
            exit(0);
        }
        else
            return num1/num2;
    case '%':
        if(num2 == 0){
            cout << "Invalid Divisor" << endl;
            exit(0);
        }
        else
            return num1%num2;
    default:
        cout << "Invalid Operator" << endl;
        exit(0);
    }
}
int main(int argc, char* argv[]){ // Run with command line
    int num1, num2;
    char op;

    num1 = atoi(argv[1]);
    op = argv[2][0];
    num2 = atoi(argv[3]);

    cout << arithmetic(num1, num2, op) << endl;
    return 0;
}