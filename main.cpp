
#include <bits/stdc++.h>

using namespace std;

static class AbstractTerm {
public:
    string derivativeNum ;

    virtual AbstractTerm *derivative();

    virtual double evaluate(double);

    virtual string toString();

    //https://www.educative.io/edpresso/what-is-a-cpp-abstract-class
    virtual int getPriority();

 /*   void setDerivative(int derivative) {
        derivativeNum = derivative;
    };
*/
};

class ConstantTerm : public AbstractTerm {
public:
    ConstantTerm(int term) {
        this->term = term;
    }

     AbstractTerm *derivative() {
        AbstractTerm *newTerm = new AbstractTerm();
        string stringToSet = " ";
        if (term > 0) {
            stringToSet += "+ ";
        }
        stringToSet += std::to_string(term);

        newTerm->derivativeNum = stringToSet;
        return newTerm;
    }

    double evaluate(double t) {
        return term;
    }

    int getPriority() {
        return 3;
    }

    string toString() {
        string stringToSet = " ";
        if (term > 0) {
            stringToSet += "+ ";
        }
        stringToSet += std::to_string(term);
        return stringToSet;
    }

private:
    int term;


};

class LinearTerm :public ConstantTerm {
public:
    LinearTerm(int term) : ConstantTerm(term) {
        this->term = term;
    }

    ::AbstractTerm *derivative() {
        ::AbstractTerm *newTerm = new ::AbstractTerm();
        string stringToSet = " ";
        if (term > 0) {
            stringToSet += "+ ";
        }
        stringToSet += std::to_string(term) + "x";
        newTerm->derivativeNum = stringToSet;
        return newTerm;
    }

    double evaluate(double t) {
        return t * term;
    }

    string toString() {
        string stringToSet = " ";
        if (term > 0) {
            stringToSet += "+ ";
        }
        stringToSet += std::to_string(term) + "x";
        return stringToSet;
    }

    int getPriority() {
        return 4;
    }

private:
    int term;
};

struct ProjNode {
    AbstractTerm *heldObject;
    ProjNode *nextNode;
};

class ProjLinkedList {
    int length = 0;

public:
    ProjLinkedList() {
    }

    ProjNode *head;

    int returnLength() {
        return length;
    }

    AbstractTerm *getAt(int location) {
        ProjNode *currNode = head;
        for (int x = 1; x < location; x++) {
            currNode = head->nextNode;
        }
        return currNode->heldObject;
    }

    void add(ProjNode *newNode) {
        newNode->nextNode = head;
        head = newNode;
        length++;
    }
};

class PolynomialTerm : public LinearTerm {
public:
    PolynomialTerm( int term1, int term2) : LinearTerm(term1) {
        this->term1 = term1;
        this->term2 = term2;
    }

    ::AbstractTerm *derivative() {
        ::AbstractTerm *newTerm = new ::AbstractTerm();
        string stringToSet = " ";
        if (term1 >= 0) {
            stringToSet += "+ ";
        } else {
            stringToSet += "- ";
        }
        if (term2 > 2) {
            stringToSet +=
                    "(" + std::to_string(term1) + std::to_string(term2) + ")" + "x^(" + std::to_string(term2) + "-1)";
        } else if (term2 == 2) {
            stringToSet += "2" + std::to_string(term1) + "x";
        }
        newTerm->derivativeNum = stringToSet;
        return newTerm;
    }

    double evaluate(double t) {
        return term1 * pow(t, term2);
    }

    string toString() {
        string stringToSet = " ";
        if (term1 >= 0) {
            stringToSet += "+ ";
        } else {
            stringToSet += "- ";
        }
        if (term2 > 2) {
            stringToSet +=
                    "(" + std::to_string(term1) + std::to_string(term2) + ")" + "x^(" + std::to_string(term2) + "-1)";
        } else if (term2 == 2) {
            stringToSet += "2" + std::to_string(term1) + "x";
        }
        return stringToSet;
    }

    int getPriority() {
        return 5;
    }

    int getExponent() {
        return term2;
    }

private:
    int term1;
    int term2;
};

enum TrigType {
    COSINE = 0,
    SINE = 1
};

class TrigTerm : public LinearTerm {
public:
    TrigTerm( int term, TrigType trigType) : LinearTerm(term) {
        this->term = term;
        this->trigType = trigType;
    }

    ::AbstractTerm *derivative() {
        ::AbstractTerm *newTerm = new ::AbstractTerm();

        string stringToSet;
        if (term >= 0) {
            stringToSet += "+";
        }
        stringToSet += " " + std::to_string(term) + " ";
        if (trigType == COSINE) {
            stringToSet += "sin(x)";
        } else if (trigType == SINE) {
            stringToSet += "cos(x)";
        }
        newTerm->derivativeNum = stringToSet;
        return newTerm;
    }

    double evaluate(double t) {
        if (trigType == COSINE) {
            return term * cos(t);
        } else if (trigType == SINE) {
            return term * sin(t);
        }
    }

    string toString() {
        string stringToSet;
        if (term >= 0) {
            stringToSet += "+";
        }
        stringToSet += " " + std::to_string(term) + " ";
        if (trigType == COSINE) {
            stringToSet += "sin(x)";
        } else if (trigType == SINE) {
            stringToSet += "cos(x)";
        }
        return stringToSet;
    }

    int returnPriority() {
        if (trigType == SINE) {
            return 2;
        } else if (trigType == COSINE) {
            return 1;
        }
    }

private:
    int term;
    TrigType trigType;
};

enum PriorityVals {
    COS = 1,
    SIN = 2,
    CONSTANT = 3,
    LINEAR = 4,
    POLYNOMIAL = 5

};

class Expression {
public:
    ProjLinkedList *holdThings;

    Expression() {
        //ProjNode* newHead = new ProjNode();
        holdThings = new ProjLinkedList();
    }
    void setLinkedList(ProjLinkedList *holdItems){
        *holdThings = *holdItems;
    }
    Expression *getDerivative() {
        Expression *newExpression = new Expression();
        for (int x = 0; x < holdThings->returnLength(); x++) {
            AbstractTerm *newDerivativeObject = holdThings->getAt(x);
            AbstractTerm *newDerValue = newDerivativeObject->derivative();
            /* string extractedVal = newDerValue->derivativeNum;
             AbstractTerm* thingToInject = new AbstractTerm();
             thingToInject->derivativeNum = extractedVal;*/
            *newExpression += newDerValue;
        }
        return newExpression;
    }

    double getEvaluation(double input) {
        double sum = 0;
        for (int x = 0; x < holdThings->returnLength(); x++) {
            AbstractTerm *newDerivativeObject = holdThings->getAt(x);
            sum += newDerivativeObject->evaluate(input);
        }
        return sum;
    }

    string toString() {
        /*int size = holdThings->returnLength();
        string holdStrings[size];
        for (int x = 0; x < size; x++) {
            AbstractTerm *tempTerm = holdThings->getAt(x);
            string tempText = tempTerm->derivativeNum;//3x^2 4x 76
            holdStrings[x] = tempText;
        }*/
        int size = holdThings->returnLength();
        string finalString = "";
        for(int x=0;x<size;x++){
            AbstractTerm* tempTerm = holdThings->getAt(x);
            finalString+=tempTerm->toString();
        }
        //sort it by assigning priority vals
        //sort thing based on priority

        //Get priority val from function
        //sort(holdStrings)
    }

    Expression operator+=(AbstractTerm *newTerm) {
        //Sort based on priority value
        //if polynomial compare exponents
        bool keepGoing = true;
        ProjNode *prevNode = nullptr;
        ProjNode *afterNode = holdThings->head;
        ProjNode *newNode = new ProjNode();
        newNode->heldObject = newTerm;
        int currPriority = newTerm->getPriority();
        while (keepGoing) {
            AbstractTerm *currentNodeTerm = afterNode->heldObject;
            AbstractTerm *prevNodeTerm = prevNode->heldObject;
            int prevNodeVal = prevNodeTerm->getPriority();
            int currentNodeVal = currentNodeTerm->getPriority();
            if ((currPriority == currentNodeVal || currPriority == prevNodeVal) && newTerm->getPriority() == 5) {
                PolynomialTerm *tempTerm = dynamic_cast<PolynomialTerm *>(newTerm);
                PolynomialTerm *currNodeTerm = dynamic_cast<PolynomialTerm *>(currentNodeTerm);
                PolynomialTerm *prevNodeTerm = dynamic_cast<PolynomialTerm *>(prevNodeTerm);
                if ((currentNodeTerm != nullptr && tempTerm->getExponent() > currNodeTerm->getExponent()) && (prevNodeTerm !=nullptr && tempTerm->getExponent() <= prevNodeTerm->getExponent())) {
                    keepGoing = false;
                }
            } else if (currPriority > currentNodeVal && currPriority < prevNodeVal) {
                keepGoing = false;
            } else {
                prevNode = afterNode;
                afterNode = afterNode->nextNode;
            }

        }
        if (prevNode != nullptr) {
            prevNode->nextNode = newNode;
        }
        newNode->nextNode = afterNode;
        Expression expressionToReturn = *new Expression();
        expressionToReturn.setLinkedList(holdThings);
        return expressionToReturn;
    }

    ~Expression() {}
};

int main() {
    AbstractTerm* t1 = new LinearTerm(5);
    AbstractTerm* t2 = new PolynomialTerm(-4,3);
    AbstractTerm* t3 = new TrigTerm(-6, TrigType::COSINE);
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