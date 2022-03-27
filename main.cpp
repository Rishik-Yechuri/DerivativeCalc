
#include <bits/stdc++.h>

using namespace std;

class AbstractTerm
{
public:
    virtual AbstractTerm* derivative() = 0;
    virtual double evaluate(double) = 0;
    virtual string toString() = 0;

};

class ConstantTerm
{
public:
    ConstantTerm(int term)
    {
        this->term = term;
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
    int term;


};

class LinearTerm
{
public:
    LinearTerm(int term)
    {
        this->term = term;
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