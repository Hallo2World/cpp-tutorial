#include <cstddef>
#include <iostream>
#include <typeinfo>

using namespace std;

class Person {};
class Student : public Person {
public:
    // object for class needs vtable for RTTI
    ~Student() {}
};
struct Struct {};

/// RTTI typdeid 获取类型信息
/// 编译器不会为所有的类型创建 type_info 对象，只会为使用了 typeid 运算符的类型创建。不过有一种特殊情况，就是带虚函数的类（包括继承来的），不管有没有使用 typeid 运算符，编译器都会为带虚函数的类创建 type_info 对象

int main(int argc, char **argv)
{
    cout << "Hello World" << endl;

    // int
    {
        int i = 10;
        const type_info& info = typeid(i);
        cout << info.name() <<" | "<<info.hash_code()<<endl;

        int32_t i2 = 10;
        const type_info& info2 = typeid(i2);
        cout << (info == info2) << endl;    ///< bool operator==(const type_info& rhs) const
        cout << (info != info2) << endl;
        cout << (info == typeid(int)) << endl;
    }

    // long
    {
        long i = 10;
        const type_info& info = typeid(i);
        cout << info.name() <<" | "<<info.hash_code()<<endl;
    }

    // int8_t
    {
        int8_t i = 10;
        const type_info& info = typeid(i);
        cout << info.name() <<" | "<<info.hash_code()<<endl;
    }

    // uint8_t
    {
        uint8_t i = 10;
        const type_info& info = typeid(i);
        cout << info.name() <<" | "<<info.hash_code()<<endl;
    }

    // int64_t
    {
        int64_t i = 10;
        const type_info& info = typeid(i);
        cout << info.name() <<" | "<<info.hash_code()<<endl;
    }

    // float
    {
        const type_info& info = typeid(0.f);
        cout << info.name() <<" | "<<info.hash_code()<<endl;
    }

    // double
    {
        const type_info& info = typeid(0.);
        cout << info.name() <<" | "<<info.hash_code()<<endl;
    }

    // C-Style string
    {
        const type_info& info = typeid("ABC");
        cout << info.name() <<" | "<<info.hash_code()<<endl;
    }

    // std::string
    {
        string str = "ABC";
        const type_info& info = typeid(str);
        cout << info.name() <<" | "<<info.hash_code()<<endl;
    }

    // std::string
    {
        string str = "ABC";
        const type_info& info = typeid(str);
        cout << info.name() <<" | "<<info.hash_code()<<endl;
    }

    // Class
    {
        Person p;
        const type_info& info = typeid(p);
        cout << info.name() <<" | "<<info.hash_code()<<endl;
    
        Student p2;
        const type_info& info2 = typeid(p2);
        cout << info2.name() <<" | "<<info2.hash_code()<<endl;
        cout << info.before(info2) << endl; ///< bool before(const type_info& rhs) const; 判断一个类型是否位于另一个类型的前面
    }

    // Struct    
    {
        struct Struct p;
        const type_info& info = typeid(p);
        cout << info.name() <<" | "<<info.hash_code()<<endl;
    }

    return 0;
}