#ifndef PRESENT_H
#define PRESENT_H
#include "MainObject.h"
#include "BaseObject.h"
#include "CommonFunc.h"


enum Present_Type
{
    GREEN = 1,
    RED = 2    
};

class Present : public BaseObject
{
protected:
    Present_Type present;
    bool Can_Move;
public:
    
    ~Present(){};
    Present()
    {
        Can_Move = true;
        present = GREEN;
    }
    
    void Move()
    {
        if(Can_Move == true && rect_.y < SCREEN_HEIGHT)
        {
            rect_.y += PRESENT_VEL;
        } else 
        {
            rect_.y = 0;
        }
    }


    void Set_Present_Type(const Present_Type &present) { this->present = present;}
    Present_Type Get_Present_Type() const { return present; }

    void Set_Can_Move(bool Can_Move) { this->Can_Move = Can_Move; }
    bool Get_Can_Move() const { return Can_Move; }
};


#endif