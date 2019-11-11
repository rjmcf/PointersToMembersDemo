#include <iostream>
#include <vector>

template<typename T>
class BaseExpr
{
public:
    virtual void Eval(std::vector<T>& Stack) const = 0;
};

template<typename T>
class Symbol : public BaseExpr<T>
{
public:
    virtual void Eval(std::vector<T>& Stack) const override { Stack.push_back(Value); }  
    Symbol(T InValue) : Value(InValue) {}
    
private:
    T Value;
};

template<typename T>
class AddExpr : public BaseExpr<T>
{
public:
    virtual void Eval(std::vector<T>& Stack) const override 
    { 
        T Second = Stack.back(); Stack.pop_back();
        T First = Stack.back(); Stack.pop_back();
        Stack.push_back(First + Second);
    }
};

template<typename T>
float Evaluate(std::vector<BaseExpr<T>*> RpnExpr)
{
    std::vector<T> Stack;
    for (const BaseExpr<T>* const Expr : RpnExpr)
    {
        Expr->Eval(Stack);
    }
    
    std::cout << Stack.back() << '\n';
    return Stack.back();
}


int main()
{
    std::cout << "Testing OOP solution\n";
    
    Symbol<float> One(1.f);
    Symbol<float> Two(2.f);
    AddExpr<float> Add;
    Evaluate<float>({&One, &Two, &Add});
    
    return 0;
}
