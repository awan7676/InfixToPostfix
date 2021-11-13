#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

class Stack{
    private:
        const static int size = 100;
        char * stack_array = new char[size];
        int top = -1;
    
    public:

    //check if stack is empty
    bool isEmpty(){
        if(top <= -1){
            return true;
        }
        else{
            return false;
        }
    }

    //check if stack is full
    bool isFull(){
        if(top == size -1){
            return true;
        }
        else{
            return false;
        }
    }

    //push an element on top of the stack
    void Push(char e){
        if(!isFull()){
            top++;
            stack_array[top] = e;
        }
        else{
            cout<<"Stack overflow!!"<<endl;
        }
    }

    //removes and display an element on top of the stack
    char Pop(){
        char popped;
        if(!isEmpty()){
            popped = stack_array[top];
            top--;
        }
        else{
            cout<<"Stack underflow!!"<<endl;
        }
        return popped;
    }

    //displays the content on top of the stack
    char Peak(){
        char top_element;
        if(!isEmpty()){
            top_element = stack_array[top];
        }
        else{
            cout<<"Stack empty!!"<<endl;
        }
        return top_element;
    }

    //release all the memory allocated by stack
    void clear(){
        delete [] stack_array;
    }

};

//to check if entered expression is operand
bool isOperand(char op){
    if(op >= 'A' &&  op<= 'Z'){
        return true;
    }
    if(op >= 'a' && op <= 'z'){
        return true;
    }
    if(op >= '0' && op <= '9'){
        return true;
    }
    return false;
}

//to check if entered expression is operator
bool isOperator(char op){
    if (op == '+' || op == '-' || op == '/' || op == '*' || op == '^'){
        return true;
    }
    return false;
}

//to check precedence of the operator
int precedence(char op){
    if(op == '+' || op == '-'){
        return 1;
    }
    else if(op == '/' || op == '*'){
        return 2;
    }
    else if(op == '^'){
        return 3;
    }
    return 0;
}

//to compare precedence of two operators
bool comparePrecedence(char op1, char op2){
    int operator_1 = precedence(op1);
    int operator_2 = precedence(op2);
    if(operator_1 == operator_2){
        if(operator_1 == '^'){
            return false;
        }
        return true;
    }
    return (operator_1 > operator_2 ? true:false);
}

bool areBracesBalanced(string expr){
    Stack s;
    char ch;
    for (int i=0; i<expr.length(); i++) {    //for each character in the expression, check conditions
        if (expr[i]=='('||expr[i]=='['||expr[i]=='{') {    //when it is opening bracket, push into     stack
            s.Push(expr[i]);
            continue;
        }
        if(!s.isEmpty()){
            switch (expr[i]) {
            case ')':    //for closing parenthesis, pop it and check for braces and square brackets
                ch = s.Peak();
                s.Pop();
                if (ch=='{' || ch=='[')
                    return false;
                    break;
            case '}': //for closing braces, pop it and check for parenthesis and square brackets
                ch = s.Peak();
                s.Pop();
                if (ch=='(' || ch=='[')
                    return false;
                    break;
            case ']': //for closing square bracket, pop it and check for braces and parenthesis
                ch = s.Peak();
                s.Pop();
                if (ch =='(' || ch == '{')
                    return false;
                    break;
            }
        }
    }
    return (s.isEmpty());
}

string PostfixConversion(string Infix){
    Stack s;
    string postfix = "";
    if(areBracesBalanced(Infix)){
        s.Push('(');
        Infix += ')';
        char p;
        for (int i=0; i<Infix.length(); ++i){
            p = Infix[i];
            
            if (p == ' '){
                continue;
            }

            else if(p == '(' || p == '[' || p == '{'){
                s.Push(p);
            }

            else if(isOperand(p)){
                int j=i;
                int counter = 0;
                while (isOperand(Infix[j])){
                    postfix += Infix[j];
                    counter ++;
                    j++;
                }
                if(counter>1){
                    postfix += '$';
                }
                i = j-1;
            }

            else if(isOperator(p)){
                while (!s.isEmpty() && comparePrecedence(s.Peak(), p)){
                    postfix += s.Peak();
                    s.Pop();
                }
                s.Push(p);
            }

            else if(p == ')'){
                while (!s.isEmpty() && s.Peak() != '(' ){
                    postfix += s.Peak();
                    s.Pop();
                }
                s.Pop();
            }

            else if(p == ']'){
                while (!s.isEmpty() && s.Peak() != '[' ){
                    postfix += s.Peak();
                    s.Pop();
                }
                s.Pop();
            }

            else if(p == '}'){
                while (!s.isEmpty() && s.Peak() != '{' ){
                    postfix += s.Peak();
                    s.Pop();
                }
                s.Pop();
            }

        }

        return postfix;
    }else{
        cout<<"Invalid Expression!!"<<endl;
        postfix = "NULL";
        return postfix;
    }
}


void evaluatePostfix(string postfix){
    if(postfix != "NULL"){
        Stack s;
        char ch;
        int result;
        int a,b;
        postfix += ')';
        for (int i=0; postfix[i] != ')'; ++i){
            ch = postfix[i];

            if(ch == ' '){
                continue;
            }

            if(isOperand(ch) || ch == '$'){
                s.Push(ch);
            }
            else if(isOperator(ch)){
                int x,y;
                if(s.Peak() == '$'){
                    s.Pop(); //pop $ operator
                    x = s.Pop() - '0';
                    y = s.Pop() - '0';
                    y *= 10;
                    a = x + y;
                    if(s.Peak() == '$'){
                        s.Pop(); //pop $ opeartor
                        x = s.Pop() - '0';
                        y = s.Pop() - '0';
                        y *= 10;
                        a = x + y;
                    }else{
                        b = s.Pop() - '0';
                    }
                }
                else{
                    a = s.Pop() - '0';
                    if(s.Peak() == '$'){
                        s.Pop();    //remove $ operator
                        x = s.Pop() - '0';
                        y = s.Pop() - '0';
                        y *= 10;
                        b = x + y;
                    }else{
                        b = s.Pop() - '0';
                    }
                }

                switch (ch){
                    case '+':
                        result = b + a;
                        break;
                    case '-':
                        result = b - a;
                        break;
                    case '*':
                        result = b * a;
                        break;
                    case '/':
                        result = b / a;
                        break;
                    case '^':
                        result = pow(b,a);
                        break;
                }
                s.Push('0' + result);
            }
        }
        cout<<"VALUE OF POSTFIX: "<<s.Pop()-48<<endl;
    }
}

int main(){
    int choice = 0;
    string infix;
    string postfix;
    while (choice != -1){
        cout<<"Press 1 -> To enter an expression!"<<endl;
        cout<<"press -1 -> To exit the program!"<<endl;
        cout<<"Choose an option: ";
        cin>>choice;
        switch (choice){
            case 1:
                cout<<"Enter an expression without spaces. Only 2 digit numbers are allowed: ";
                cin>>infix;
                postfix = PostfixConversion(infix);
                cout<<"POSTFIX: "<<postfix<<endl;
                evaluatePostfix(postfix);
                break;
            
            case -1:
                cout<<"The Program has ended!!"<<endl;
                break;

            default:
                cout<<"Choose valid option!"<<endl;
        }
    }
}
