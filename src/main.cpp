#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

enum class STATUS
{
     YES,
     NO,
     NONE
};

struct Container
{
     int i1;
     STATUS status_1;
     STATUS status_2;
     int i2;
};

class Base
{
public:
     virtual ~Base() = default;
     
     STATUS GetStatus()
     {
          return status;
     }

     virtual STATUS GetStatus( Container& con )
     {
          return status;
     }

public:
     STATUS status;
};


class Derived1 : public Base
{
public:
     STATUS GetStatus( Container& con ) override
     {
          STATUS status = Base::GetStatus();
          con.status_1 = status;
          return status;
     }

public:
     int derived1_1;
};


class Derived2 : public Base
{
public:
     STATUS GetStatus( Container& con ) override
     {
          STATUS status = Base::GetStatus();
          con.status_2 = status;
          return status;
     }

public:
     int derived2_1;
};


int main()
{
     Derived1 d1 = Derived1();
     Base b = d1;

     STATUS status = b.GetStatus();

     Container con;
     b.GetStatus( con );
}
