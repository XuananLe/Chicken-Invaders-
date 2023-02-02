#include "CommonFunc.h"
#include "BaseObject.h"
#define NONE 1
#define ION 2
#define DOUBLE_ION 3
#define LASER 4
class AmmoObject : public BaseObject
{
protected:
    bool Can_Move = false;
    int AMMO_VEL;
    int Ammo_Type;
public:
    AmmoObject();
    ~AmmoObject();

    void Set_AMMO_VEL(const int &AMMO_VEL) { this->AMMO_VEL = AMMO_VEL; }
    int Get_AMMO_VEL() const { return AMMO_VEL; }

    void Set_AmmoType(const int &Ammo_Type) { this->Ammo_Type = Ammo_Type; }
    int Get_AmmoType() const { return Ammo_Type;}

    void Set_Can_Move(bool Can_Move) { this->Can_Move = Can_Move; }
    bool Get_Can_Move() const { return Can_Move; }
    // handle input from user down to up
    void Handle_Input_Action_BTU(const int &WIDTH_BORDER, const int &HEIGHT_BORDER);
};
AmmoObject::AmmoObject()
{
    AMMO_VEL = 0;
    Can_Move = false;
    Ammo_Type  = NONE;
}

AmmoObject::~AmmoObject() {}

void AmmoObject::Handle_Input_Action_BTU(const int &WIDTH_BORDER, const int &HEIGHT_BORDER)
{
    rect_.y -= AMMO_VEL;
    if (rect_.y <= 0)
    {
        Can_Move = false;
    }
}
