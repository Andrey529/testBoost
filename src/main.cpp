#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Base
{
public:
     virtual ~Base() = default;
     int base_1;
};

class Derived : public Base
{
public:
     int derived_1;
};

std::shared_ptr< Base > Make()
{
     auto elem = std::make_shared< Derived >();
     std::cout << "Make() elem = " << typeid( elem ).name() << std::endl;
     return elem;
}

void fun( std::shared_ptr< Base >& elem )
{
     std::cout << "fun() elem typeid.name = " << typeid( elem ).name() << std::endl;
}

// Base* Make()
// {
//      auto elem = new Derived();
//      std::cout << "Make() elem = " << typeid( *elem ).name() << std::endl;
//      return elem;
// }

// void fun( Base* elem )
// {
//      std::cout << "fun() elem typeid.name = " << typeid( *elem ).name() << std::endl;
// }

int main()
{
     // auto elem = Make();
     auto elem = std::make_shared< Derived >();
     std::cout << "main() elem typeid.name = " << typeid( elem ).name() << std::endl;
     fun( elem );
     std::cout << "main() elem typeid.name = " << typeid( elem ).name() << std::endl;


     // auto d = Derived();
     // std::cout << "d typeid.name = " << typeid( d ).name() << std::endl;

     // auto b = d;
     // std::cout << "b typeid.name = " << typeid( b ).name() << std::endl;
}
