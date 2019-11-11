#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define DEBUG 1

// Struct defining our evaluator and the allowable set of operators
template <typename T>
struct FMathExpr final
{
    // Access to the evaluator
    static T Evaluate(const std::vector<T>& Args, const std::vector<void (FMathExpr<T>::*)()>& Ops)
    {
        FMathExpr<T> Expr(Args);
        
        for (void (FMathExpr<T>::*Op)() : Ops)
        {
            (Expr.*Op)();
        }
    #if DEBUG  
        std::cout << "Evaluation complete" << std::endl;
    #endif // #if DEBUG  
    
        return Expr.GetResult();
    }
    
    // The allowable set of operators
    // ~Begin
    void Add() 
    { 
        T Second = ExecutionStack.back(); ExecutionStack.pop_back(); 
        T First = ExecutionStack.back(); ExecutionStack.pop_back(); 
        T Result = First + Second;
        ExecutionStack.push_back(Result);
#if DEBUG  
        std::cout << "Executing " << First << " + " << Second << " to get: " << Result << std::endl;
#endif // #if DEBUG  
    }
    void Subtract() 
    { 
        T Second = ExecutionStack.back(); ExecutionStack.pop_back(); 
        T First = ExecutionStack.back(); ExecutionStack.pop_back(); 
        T Result = First - Second;
        ExecutionStack.push_back(Result);
#if DEBUG  
        std::cout << "Executing " << First << " - " << Second << " to get: " << Result << std::endl; 
#endif // #if DEBUG  
    }
    void UnaryMinus() 
    { 
        T Operand = ExecutionStack.back(); ExecutionStack.pop_back();
        ExecutionStack.push_back(-Operand);
#if DEBUG  
        std::cout << "Executing -(" << Operand << ") to get: " << -Operand << std::endl; 
#endif // #if DEBUG  
    }
    
    // "Operator" that just gets the next bit of input and places it on top of the 
    // execution stack
    void GetInput() 
    { 
        ExecutionStack.push_back(Inputs.back());
#if DEBUG  
        std::cout << "Input: " << Inputs.back() << std::endl;  
#endif // #if DEBUG
        Inputs.pop_back(); 
    }
    // ~End
    
private:
    // Constructor only used by the static Evaluate
    FMathExpr(const std::vector<T>& Args) 
        : Inputs(Args) 
    { 
        // Reverse so that GetInput adds the correct input to the stack
        std::reverse(Inputs.begin(), Inputs.end()); 
    }
    
    // Helper to make this line's purpose explicit
    T GetResult() const
    {
        return ExecutionStack.back();
    }
    
    std::vector<T> Inputs;
    std::vector<T> ExecutionStack;
};

// Defining freindly names for our member functions
namespace FloatRpnExpr
{
    using MemberFunctionPtr = void (FMathExpr<float>::*)();
    MemberFunctionPtr GetInput = &FMathExpr<float>::GetInput;
    MemberFunctionPtr Add = &FMathExpr<float>::Add;
    MemberFunctionPtr Sub = &FMathExpr<float>::Subtract;
    MemberFunctionPtr Minus = &FMathExpr<float>::UnaryMinus;
}

int main()
{
    using namespace FloatRpnExpr;
    
    std::cout << "Test ptr to member solution \n";
    
    float Result = FMathExpr<float>::Evaluate(
        /* Inputs*/ {1.f, 2.f}, 
        /* RPNExpr*/{GetInput, GetInput, Add});
    std::cout << "Result: " << Result << "\n\n";
        
    Result = FMathExpr<float>::Evaluate(
        {1.f, 6.f, 2.f, 3.f},
        {GetInput, Minus, GetInput, Add, GetInput, GetInput, Add, Sub});
    std::cout << "Result: " << Result << "\n\n";
    
    return 0;
}
