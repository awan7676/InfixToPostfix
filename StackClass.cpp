#include <iostream>
#include <cstring>
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
