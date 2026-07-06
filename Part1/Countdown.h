#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <string>
#include <sstream>
#include <vector>

// this is provided code for the last part of the README

std::string intToString(const int x) {
    std::ostringstream str;
    str << x;
    return str.str();
}

class CountdownSolution {
  
private:
    std::string solution;
    int value;
    
public:
    
    CountdownSolution() : solution(), value(0) {}
    
    CountdownSolution(const std::string & solutionIn, const int valueIn)
        : solution(solutionIn), value(valueIn) {
    }
    
    const std::string & getSolution() const {
        return solution;
    }
    
    int getValue() const {
        return value;
    }
    
};

// Do not edit above this line

// TODO: write code here:
inline bool check_Number(const std::string &token) {
    for (char ch : token) {
        if (!std::isdigit(ch) && ch != '.') {
            return false;
        }
    }
    return true;
}

int check_Presedence(const std::string &op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    return 0;
}

std::string find_Expression(std::vector<int> values, std::vector<std::string> expressions, int target) {
    for (size_t i = 0; i < values.size(); i++) {
        if (values[i] == target) {
            return expressions[i];
        }
    }

    if (values.size() == 1) {
        return "";
    }

    std::vector<std::pair<std::string, int>> operations = {
        {"*", 2},
        {"/", 2},
        {"+", 1},
        {"-", 1}
    };

    for (size_t i = 0; i < values.size(); i++) {
        for (size_t j = 0; j < values.size(); j++) {
            if (i == j) continue;

            int a = values[i];
            int b = values[j];
            std::string exprA = expressions[i];
            std::string exprB = expressions[j];

            std::vector<int> newValues;
            std::vector<std::string> newExpressions;
            for (size_t k = 0; k < values.size(); k++) {
                if (k != i && k != j) {
                    newValues.push_back(values[k]);
                    newExpressions.push_back(expressions[k]);
                }
            }

            for (const auto &op_pair : operations) {
                const std::string &op = op_pair.first;
                std::string newExpr;

                if (op == "+") {
                    newValues.push_back(a + b);
                    newExpr = "( " + exprA + " + " + exprB + " )";
                }
                else if (op == "-") {
                    newValues.push_back(a - b);
                    newExpr = "( " + exprA + " - " + exprB + " )";
                }
                else if (op == "*") {
                    newValues.push_back(a * b);
                    newExpr = "( " + exprA + " * " + exprB + " )";
                }
                else if (op == "/") {
                    if (b != 0 && a % b == 0) { 
                        newValues.push_back(a / b);
                        newExpr = "( " + exprA + " / " + exprB + " )";
                    } else {
                        continue; 
                    }
                }

                newExpressions.push_back(newExpr);

                std::string found = find_Expression(newValues, newExpressions, target);
                if (!found.empty()) return found;

                newValues.pop_back();
                newExpressions.pop_back();
            }
        }
    }

    return "";
}

std::string convert_RPN(const std::string &expression) {
    std::istringstream iss(expression);
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }

    std::vector<std::string> operatorStack; 
    std::vector<std::string> output;

    std::vector<std::pair<std::string, int>> operations = {
        {"*", 2},
        {"/", 2},
        {"+", 1},
        {"-", 1}
    };

    for (const std::string &token : tokens) {
        if (check_Number(token)) {
            output.push_back(token);
        } else if (token == "(") {
            operatorStack.push_back(token);
        } else if (token == ")") {
            while (!operatorStack.empty() && operatorStack.back() != "(") {
                output.push_back(operatorStack.back());
                operatorStack.pop_back();
            }
            if (!operatorStack.empty()) {
                operatorStack.pop_back(); 
            }
        } else {
            while (!operatorStack.empty()) {
                std::string topOp = operatorStack.back();
                if (topOp == "(") break;
                int topPrecedence = check_Presedence(topOp);
                int currentPrecedence = check_Presedence(token);
                if (topPrecedence >= currentPrecedence) {
                    output.push_back(topOp);
                    operatorStack.pop_back();
                } else {
                    break;
                }
            }
            operatorStack.push_back(token);
        }
    }

    while (!operatorStack.empty()) {
        output.push_back(operatorStack.back());
        operatorStack.pop_back();
    }

    std::ostringstream result;
    for (size_t i = 0; i < output.size(); ++i) {
        result << output[i];
        if (i != output.size() - 1) {
            result << " ";
        }
    }
    return result.str();
}

// evaluateCountdown FUNCTION
double evaluateCountdown(const std::string &expression) {
    std::istringstream iss(expression);
    std::vector<std::string> tokens;
    std::string token;

    while (iss >> token) {
        tokens.push_back(token);
    }

    std::vector<double> stack;

    for (const std::string &token : tokens) {
        if (check_Number(token)) {
            stack.push_back(std::stod(token));
        } else {
            if (stack.size() < 2) {
                return 0; 
            }

            double a = stack.back();
            stack.pop_back();
            double b = stack.back();
            stack.pop_back();

            if (token == "+") {
                stack.push_back(b + a);
            } else if (token == "-") {
                stack.push_back(b - a);
            } else if (token == "*") {
                stack.push_back(b * a);
            } else if (token == "/") {
                if (a == 0) {
                    return 0; 
                }
                stack.push_back(b / a);
            } else {
                return 0; 
            }
        }
    }

    if (stack.empty()) {
        return 0; 
    }

    double finalValue = stack.back();
    stack.pop_back();

    if (finalValue >= 0.0) {
        return static_cast<int>(finalValue + 0.5);
    } else {
        return static_cast<int>(finalValue - 0.5);
    }
}

// solveCountdownProblem FUNCTION
CountdownSolution solveCountdownProblem(const std::vector<int> &numbers, int target) {
    std::vector<int> values(numbers.begin(), numbers.end());
    std::vector<std::string> expressions;

    for (int num : numbers) {
        expressions.push_back(std::to_string(num));
    }

    std::string bestExpression = convert_RPN(find_Expression(values, expressions, target));

    int bestValue = 0;
    if (!bestExpression.empty()) {
        bestValue = evaluateCountdown(bestExpression);
    }

    return CountdownSolution(bestExpression, bestValue);
}


// Do not edit below this line


#endif