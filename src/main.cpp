#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Base
{
public:
     virtual ~Base() = default;
     
     virtual void increment()
     {
          ++base_1;
     }

     virtual void hello()
     {
          std::cout << "Hello from Base" << std::endl;
     }

public:
     int base_1;
};

std::ofstream& operator<<( std::ofstream& out, const Base& b )
{
     out << "base_1 = " << b.base_1;
     return out;
}

class Derived : public Base
{
public:
     void increment() override
     {
          ++derived_1;
     }

     void hello() override
     {
          std::cout << "Hello from Derived" << std::endl;
     }

public:
     int derived_1;
};

std::ofstream& operator<<( std::ofstream& out, const Derived& d )
{
     out << "base_1 = " << d.base_1 << ", derived_1 = " << d.derived_1;
     return out;
}


std::shared_ptr< Base > Make()
{
     auto elem = std::make_shared< Derived >();
     std::cout << "Make() elem typeid.name = " << typeid( elem ).name() << std::endl;
     elem->hello();
     return elem;
}

void fun( const std::shared_ptr< Base >& elem )
{
     std::cout << "fun() elem typeid.name = " << typeid( elem ).name() << std::endl;
     std::cout << "fun() *elem typeid.name = " << typeid( *elem ).name() << std::endl;
     std::cout << "fun() elem address = " << &(*elem) << std::endl;
     elem->hello();
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
     auto elem = Make();
     std::cout << "main() elem typeid.name = " << typeid( elem ).name() << std::endl;
     std::cout << "main() *elem typeid.name = " << typeid( *elem ).name() << std::endl;
     std::cout << "main() elem address = " << &(*elem) << std::endl;
     elem->hello();
     fun( elem );
     std::cout << "main() elem typeid.name = " << typeid( elem ).name() << std::endl;


     // auto d = Derived();
     // std::cout << "d typeid.name = " << typeid( d ).name() << std::endl;

     // auto b = d;
     // std::cout << "b typeid.name = " << typeid( b ).name() << std::endl;
}
