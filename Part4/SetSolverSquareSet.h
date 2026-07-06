#ifndef SetSolverSquareSet_h
#define SetSolverSquareSet_h

// Do not add any additional class.
#include <vector>


class SetSolverSquareSet
{
public:
    std::vector<int> set; 
    int value;            
    bool isBlack;         
    bool isClue;          

    SetSolverSquareSet(){
        value = 99;     
        isBlack = false;
        isClue = false;
        set.clear();
    }
};

#endif /* SetSolverSquareSet_h */