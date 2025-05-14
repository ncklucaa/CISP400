// Author: ChatGPT
// For: Caleb Fowler Nick Luca
// Homework 6/Final, Deliverable 1

#include <iostream>
#include <vector>
#include <cstring>
#include <cassert>
#include <stdexcept>
#include <iomanip>
#include <sstream>
using namespace std;

// ===================== PROGRAM GREETING =====================
void greeting() {
    cout << "======================================\n";
    cout << "  Author: Nick and ChatGPT\n";
    cout << "  Theme: AI Methodology - Decision Tree Predictor\n";
    cout << "======================================\n\n";
}

// ===================== METADATA (Composition) =====================
class NodeData {
    char* description;
public:
    NodeData() : description(nullptr) {}

    NodeData(const char* desc) {
        description = new char[strlen(desc) + 1];
        strcpy_s(description, strlen(desc) + 1, desc);
    }

    NodeData(const NodeData& other) {
        description = new char[strlen(other.description) + 1];
        strcpy_s(description, strlen(other.description) + 1, other.description);
    }

    NodeData& operator=(const NodeData& other) {
        if (this != &other) {
            delete[] description;
            description = new char[strlen(other.description) + 1];
            strcpy_s(description, strlen(other.description) + 1, other.description);
        }
        return *this;
    }

    ~NodeData() {
        delete[] description;
    }

    const char* getDescription() const { return description; }
};

// ===================== ABSTRACT BASE CLASS =====================
class DecisionNode {
public:
    virtual void evaluate() = 0;
    virtual ~DecisionNode() {}
    virtual DecisionNode* clone() const = 0; // For deep copying
    virtual void print(ostream& out) const = 0;
    virtual void input(istream& in) = 0;
};

// ===================== DERIVED CLASSES =====================
class QuestionNode : public DecisionNode {
    string question;
public:
    QuestionNode() {}
    QuestionNode(const string& q) : question(q) {}

    void evaluate() override {
        string answer;
        cout << question << " (yes/no): ";
        cin >> answer;
    }

    QuestionNode* clone() const override {
        return new QuestionNode(*this);
    }

    friend ostream& operator<<(ostream& out, const QuestionNode& qn) {
        out << "[Q] " << qn.question;
        return out;
    }

    friend istream& operator>>(istream& in, QuestionNode& qn) {
        getline(in, qn.question);
        return in;
    }

    void print(ostream& out) const override { out << *this; }
    void input(istream& in) override { in >> *this; }
};

class ResultNode : public DecisionNode {
    string result;
public:
    ResultNode() {}
    ResultNode(const string& r) : result(r) {}

    void evaluate() override {
        cout << "Result: " << result << endl;
    }

    ResultNode* clone() const override {
        return new ResultNode(*this);
    }

    friend ostream& operator<<(ostream& out, const ResultNode& rn) {
        out << "[R] " << rn.result;
        return out;
    }

    friend istream& operator>>(istream& in, ResultNode& rn) {
        getline(in, rn.result);
        return in;
    }

    void print(ostream& out) const override { out << *this; }
    void input(istream& in) override { in >> *this; }
};

// ===================== EXCEPTION CLASS =====================
class EvaluationError : public runtime_error {
public:
    EvaluationError(const string& msg) : runtime_error(msg) {}
};

// ===================== DECISION TREE CLASS =====================
class DecisionTree {
    DecisionNode** nodes;
    int size;
    int capacity;
    int added;
    int removed;
    int peak;
public:
    DecisionTree(int cap = 2) : size(0), added(0), removed(0), peak(0) {
        capacity = cap;
        nodes = new DecisionNode * [capacity];
    }

    // Copy constructor (deep copy)
    DecisionTree(const DecisionTree& other) : size(other.size), capacity(other.capacity), added(other.added), removed(other.removed), peak(other.peak) {
        nodes = new DecisionNode * [capacity];
        for (int i = 0; i < size; ++i) {
            nodes[i] = other.nodes[i]->clone();
        }
    }

    // Move constructor
    DecisionTree(DecisionTree&& other) noexcept : nodes(other.nodes), size(other.size), capacity(other.capacity), added(other.added), removed(other.removed), peak(other.peak) {
        other.nodes = nullptr;
        other.size = 0;
    }

    // Assignment operator (deep copy)
    DecisionTree& operator=(const DecisionTree& other) {
        if (this != &other) {
            for (int i = 0; i < size; ++i) delete nodes[i];
            delete[] nodes;
            capacity = other.capacity;
            size = other.size;
            added = other.added;
            removed = other.removed;
            peak = other.peak;
            nodes = new DecisionNode * [capacity];
            for (int i = 0; i < size; ++i) nodes[i] = other.nodes[i]->clone();
        }
        return *this;
    }

    // Move assignment
    DecisionTree& operator=(DecisionTree&& other) noexcept {
        if (this != &other) {
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

    ~DecisionTree() {
        for (int i = 0; i < size; ++i) delete nodes[i];
        delete[] nodes;
    }

    void grow() {
        capacity *= 2;
        DecisionNode** newArr = new DecisionNode * [capacity];
        for (int i = 0; i < size; ++i) newArr[i] = nodes[i];
        delete[] nodes;
        nodes = newArr;
    }

    void add(DecisionNode* node) {
        if (size >= capacity) grow();
        nodes[size++] = node;
        added++;
        if (size > peak) peak = size;
    }

    void removeLast() {
        if (size == 0) return;
        delete nodes[--size];
        removed++;
    }

    void evaluateAll() {
        if (size == 0) throw EvaluationError("No nodes to evaluate!");
        for (int i = 0; i < size; ++i) nodes[i]->evaluate();
    }

    void displayTable() const {
        cout << "\n+-------------------------------+\n";
        cout << "|     Decision Tree Summary     |\n";
        cout << "+-------------------------------+\n";
        cout << "| Current Nodes:      " << setw(10) << size << " |\n";
        cout << "| Nodes Added:        " << setw(10) << added << " |\n";
        cout << "| Nodes Removed:      " << setw(10) << removed << " |\n";
        cout << "| Peak Size:          " << setw(10) << peak << " |\n";
        cout << "+-------------------------------+\n";
    }
};

// ===================== CONVERT CONSTRUCTOR =====================
class Label {
    string name;
public:
    Label(const string& n) : name(n) {}
    operator string() const { return name; }
};

// ===================== MAIN =====================
int main() {
    greeting();

    DecisionTree tree;
    assert(true && "Tree should be initialized.");

    try {
        tree.add(new QuestionNode("Is it raining?"));
        tree.add(new QuestionNode("Do you have an umbrella?"));
        tree.add(new ResultNode("Go outside."));
        tree.add(new ResultNode("Stay inside."));

        auto countYes = [](int count) {
            cout << "\nYou answered 'yes' " << count << " times.\n";
            };
        tree.evaluateAll();
        countYes(2); // dummy value
    }
    catch (const EvaluationError& e) {
        cerr << "Evaluation Error: " << e.what() << endl;
    }

    tree.displayTable();
    return 0;
}
