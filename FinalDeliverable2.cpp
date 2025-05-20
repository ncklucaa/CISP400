// Author: Caleb Fowler Nick Luca
// Improvements to ChatGPT
// Homework 6/Final, Deliverable 2

#include <iostream>
#include <vector>
#include <cstring>
#include <cassert>
#include <stdexcept>
#include <iomanip>
#include <sstream>
using namespace std;

void programGreetingSection() 
{
    cout << "========================================\n";
    cout << "AI Methodology - Decision Tree Predictor\n";
    cout << "             By: Nick Luca\n";
    cout << "========================================\n\n";
}

class MetaDataDescription
{
    char* description;
public:
    MetaDataDescription() : description(nullptr) {}

    MetaDataDescription(const char* desc)
    {
        description = new char[strlen(desc) + 1];
        strcpy_s(description, strlen(desc) + 1, desc);
    }

    MetaDataDescription(const MetaDataDescription& other)
    {
        description = new char[strlen(other.description) + 1];
        strcpy_s(description, strlen(other.description) + 1, other.description);
    }

    MetaDataDescription& operator=(const MetaDataDescription& other)
    {
        if (this != &other) {
            delete[] description;
            description = new char[strlen(other.description) + 1];
            strcpy_s(description, strlen(other.description) + 1, other.description);
        }
        return *this;
    }

    ~MetaDataDescription()
    {
        delete[] description;
    }

    const char* getDescription() const { return description; }
};

class AiDecisionProcess
{
public:
    virtual void evaluate() = 0;
    virtual void evaluate(int& yesCounter) { evaluate(); }
    virtual ~AiDecisionProcess() {}
    virtual AiDecisionProcess* clone() const = 0;
    virtual void print(ostream& out) const = 0;
    virtual void input(istream& in) = 0;
};

class YesNoQuestionNode : public AiDecisionProcess
{
    string question;

    AiDecisionProcess* yesB;
    AiDecisionProcess* noB;
public:
    YesNoQuestionNode(const string& q, AiDecisionProcess* yes = nullptr, AiDecisionProcess* no = nullptr)
    {
        question = q;
        yesB = yes;
        noB = no;
    }

    ~YesNoQuestionNode() { delete yesB; delete noB; }

    void evaluate(int& yesCounter) override 
    {
        string answ;

        while (true)
        {
            cout << question << " (y/n): ";
            cin >> answ;

            for (size_t i = 0; i < answ.length(); i++)
            {
                answ[i] = tolower(answ[i]);
            }

            if (answ == "y" || answ == "yes")
            {
                ++yesCounter;
                if (yesB) yesB->evaluate(yesCounter);
                break;
            }
            else if (answ == "n" || answ == "no")
            {
                if (noB) noB->evaluate(yesCounter);
                break;
            }

            cout << "enter either 'y' or 'n'\n";
        }

    }

    void evaluate() override
    {
        int temp = 0;
        evaluate(temp);
    }

    YesNoQuestionNode* clone() const override
    {
        return new YesNoQuestionNode(*this);
    }

    friend ostream& operator<<(ostream& out, const YesNoQuestionNode& qn)
    {
        out << "[Q] " << qn.question;
        return out;
    }

    friend istream& operator>>(istream& in, YesNoQuestionNode& qn)
    {
        getline(in, qn.question);
        return in;
    }

    void print(ostream& out) const override { out << *this; }
    void input(istream& in) override { in >> *this; }
};

class DecisionPathEnd : public AiDecisionProcess
{
    string result;
public:
    DecisionPathEnd() {}
    DecisionPathEnd(const string& r) : result(r) {}

    void evaluate() override
    {
        cout << "Outcome = " << result << endl;
    }

    void evaluate(int& yesCounter) override
    {
        evaluate();
    }

    DecisionPathEnd* clone() const override
    {
        return new DecisionPathEnd(*this);
    }

    friend ostream& operator<<(ostream& out, const DecisionPathEnd& rn)
    {
        out << "[R] " << rn.result;
        return out;
    }

    friend istream& operator>>(istream& in, DecisionPathEnd& rn)
    {
        getline(in, rn.result);
        return in;
    }

    void print(ostream& out) const override { out << *this; }
    void input(istream& in) override { in >> *this; }
};

class TreeEvaluation : public runtime_error
{
public:
    TreeEvaluation(const string& msg) : runtime_error(msg) {}
};

class DecisionMakingTree
{
    AiDecisionProcess** nodes;
    int size;
    int capacity;
    int added;
    int removed;
    int peak;
public:
    DecisionMakingTree(int cap = 2) : size(0), added(0), removed(0), peak(0)
    {
        capacity = cap;
        nodes = new AiDecisionProcess* [capacity];
    }

    DecisionMakingTree(const DecisionMakingTree& other) : size(other.size), capacity(other.capacity), added(other.added), removed(other.removed), peak(other.peak)
    {
        nodes = new AiDecisionProcess* [capacity];

        for (int i = 0; i < size; ++i) 
        {
            nodes[i] = other.nodes[i]->clone();
        }
    }

    DecisionMakingTree(DecisionMakingTree&& other) noexcept : nodes(other.nodes), size(other.size), capacity(other.capacity), added(other.added), removed(other.removed), peak(other.peak)
    {
        other.nodes = nullptr;
        other.size = 0;
    }

    DecisionMakingTree& operator=(const DecisionMakingTree& other)
    {
        if (this != &other) 
        {
            for (int i = 0; i < size; ++i) delete nodes[i];
            delete[] nodes;
            capacity = other.capacity;
            size = other.size;
            added = other.added;
            removed = other.removed;
            peak = other.peak;
            nodes = new AiDecisionProcess* [capacity];
            for (int i = 0; i < size; ++i) nodes[i] = other.nodes[i]->clone();
        }
        return *this;
    }

    DecisionMakingTree& operator=(DecisionMakingTree&& other) noexcept
    {
        if (this != &other) 
        {
            for (int i = 0; i < size; ++i) delete nodes[i];
            delete[] nodes;
            nodes = other.nodes;
            size = other.size;
            capacity = other.capacity;
            added = other.added;
            removed = other.removed;
            peak = other.peak;
            other.nodes = nullptr;
            other.size = 0;
        }
        return *this;
    }

    ~DecisionMakingTree()
    {
        for (int i = 0; i < size; ++i) delete nodes[i];
        delete[] nodes;
    }

    void grow() 
    {
        capacity *= 2;
        AiDecisionProcess** newArr = new AiDecisionProcess* [capacity];
        for (int i = 0; i < size; ++i) newArr[i] = nodes[i];
        delete[] nodes;
        nodes = newArr;
    }

    void add(AiDecisionProcess* node)
    {
        if (size >= capacity) grow();
        nodes[size++] = node;
        added++;
        if (size > peak) peak = size;
    }

    void removeLast() 
    {
        if (size == 0) return;
        delete nodes[--size];
        removed++;
    }

    void evaluateAll(int& yesCounter) 
    {
        if (size == 0) throw TreeEvaluation("No nodes to evaluate!");

        for (int i = 0; i < size; i++)
        {
            nodes[i]->evaluate(yesCounter);
        }
    }

    void displayTable() const 
    {
        cout << "\n----------------------------------\n";
        cout << "|     Decision Tree Summary      |\n";
        cout << "----------------------------------\n";
        cout << "| Current Nodes:      " << setw(10) << size << " |\n";
        cout << "| Nodes Added:        " << setw(10) << added << " |\n";
        cout << "| Nodes Removed:      " << setw(10) << removed << " |\n";
        cout << "| Peak Size:          " << setw(10) << peak << " |\n";
        cout << "----------------------------------\n";
    }
};

class TypeConversionD
{
    string name;
public:
    TypeConversionD(const string& n) : name(n) {}
    operator string() const { return name; }
};

int main() 
{
    programGreetingSection();

    DecisionMakingTree tree;
    assert(true && "Tree should be initialized.");
    
    try 
    {
        int yesCounter = 0;

        auto* nnNode = new DecisionPathEnd("take a nap");
        auto* ggNode = new DecisionPathEnd("you good no nap needed");

        auto* ttNode = new YesNoQuestionNode("are you feeling tired?", nnNode, ggNode);

        ttNode->evaluate(yesCounter);

        auto repYes = [](int count)
            {
                cout << "\nyou answered yes " << count << " times\n";
            };

        repYes(yesCounter);

        delete ttNode;
    }
    catch (const TreeEvaluation& e)
    {
        cout << "Evaluation Error: " << e.what() << '\n';
    }

    tree.displayTable();
    return 0;
}