
#include <bits/stdc++.h>

using namespace std;

class AbstractTerm
{
public:
    int derivativeNum = 0;
    virtual AbstractTerm* derivative();
    virtual double evaluate(double);
    virtual string toString();
    void setDerivative(int derivative){
        derivativeNum = derivative;
    };

};

class ConstantTerm:AbstractTerm
{
public:
    ConstantTerm(int term)
    {
        this->term = term;
    }
    AbstractTerm* derivative()
    {
        AbstractTerm* newTerm = new AbstractTerm();
        newTerm->derivativeNum = 0;
        return newTerm;
    }

    double evaluate(double t)
    {
        return term;
    }

    string toString()
    {
        return  std::to_string(term);
    }

private:
    int term;


};

class LinearTerm:AbstractTerm
{
public:
    LinearTerm(int term)
    {
        this->term = term;
    }

    AbstractTerm* derivative()
    {
        AbstractTerm* newTerm = new AbstractTerm();
        newTerm->derivativeNum = term;
        return newTerm;
    }

    double evaluate(double t)
    {
        return t * term;
    }

    string toString()
    {
        return  (std::to_string(term) + "x");
    }

private:
    int term;
};

class PolynomialTerm
{
public:
    PolynomialTerm(int term1, int term2)
    {
        this->term1 = term1;
        this->term2 = term2;
    }

    AbstractTerm* derivitive()
    {

    }

    double evaluate(double t)
    {

    }

    string toString()
    {

    }

private:
    int term1;
    int term2;
};

enum TrigType
{
    COSINE,
    SINE
};

class TrigTerm
{
public:
    TrigTerm(int term, TrigType trigType)
    {
        this->term = term;
        this->trigType = trigType;
    }
private:
    int term;
    TrigType trigType;
};

class Expression
{
public:
    Expression()
    {

    }
    Expression* getDerivative()
    {

    }

    double getEvaluation(double)
    {

    }

    string toString()
    {

    }

    Expression operator+=(AbstractTerm*)
    {

    }
};
int main()
{
    AbstractTerm* t1 = reinterpret_cast<AbstractTerm *>(new LinearTerm(5));
    AbstractTerm* t2 = reinterpret_cast<AbstractTerm *>(new PolynomialTerm(-4, 3));
    AbstractTerm* t3 = reinterpret_cast<AbstractTerm *>(new TrigTerm(-6, TrigType::COSINE));
    cout << t1->toString() << endl; // + 5x
    cout << t1->evaluate(5) << endl; // 25
    cout << t2->toString() << endl; // - 4x^3
    cout << t2->evaluate(2) << endl; // -32
    cout << t3->toString() << endl; // - 6cos(x)
    cout << t3->evaluate(45) << endl; // -4.24
    Expression* e1 = new Expression();
    e1->getDerivative();
    (*e1) += t1;
    (*e1) += t2;
    (*e1) += t3;
    Expression* e2 = e1->getDerivative();
    cout << e1->toString() << endl; // - 4x^3 + 5x - 6cos(x)
    cout << e2->toString() << endl; // - 12x^2 + 5 + 6sin(x)
    cout << e1->getEvaluation(0) << endl; // -6
    cout << e2->getEvaluation(0) << endl; // 5
    delete e2;
    delete e1;

}