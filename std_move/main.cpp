#include <iostream>
#include <vector>

using std::string;

int main() {
    // 左值引用测试
    {
        int lvalue = 5;
        int& lref = lvalue;
        // int& lref2 = 5;       // Error，左值引用不能指向右值
        const double& lref2 = 5; // OK，常量左值可以指向右值
    }

    // 右值引用测试
    {
        int&& rref = 5;         // OK
        int lvalue = 5;
        // int&& rref2 = lvalue;// Error，右值引用不能指向左值
        rref = 10;              // 右值引用的用途：可以修改右值
    }

    // std::move：实现右值引用指向左值
    {
        int lvalue = 5;
        int& lref = lvalue;
        int&& rref = std::move(lvalue); // 通过std::move将左值强制转换为右值(功能等同于static_cast<T&&>(lvalue)， 单纯的std::move(xxx)不会有性能提升)，可以被右值引用指向
        rref = 10;
        std::cout << __LINE__ << ": "<< lvalue << std::endl;
        std::cout << __LINE__ << ": "<< rref << std::endl;
    }
    
    // 右值引用能指向右值，本质上也是把右值提升为一个左值
    {
        {
            int &&ref_a = 5;
            ref_a = 6; 
        }
        // ====
        {
            int temp = 5;
            int &&ref_a = std::move(temp);
            ref_a = 6;
        }
    }

    // 被声明出来的左、右值引用都是左值
    // 右值引用既可以是左值也可以是右值，如果有名称则为左值，否则是右值;作为函数返回值的 && 是右值，直接声明出来的 && 是左值
    // 实现移动语义，避免拷贝，从而提升程序性能

    // 1. 从性能上讲，左右值引用没有区别，传参使用左右值引用都可以避免拷贝
    // 2. 右值引用可以直接指向右值，也可以通过std::move指向左值；而左值引用只能指向左值(const左值引用也能指向右值)
    // 3. 作为函数形参时，右值引用更灵活。虽然const左值引用也可以做到左右值都接受，但它无法修改，有一定局限性
    // 4. 可移动对象在<需要拷贝且被拷贝者之后不再被需要>的场景，建议使用std::move触发移动语义，提升性能
    // 5. std::move本身只做类型转换，对性能无影响。 我们可以在自己的类中实现移动语义，避免深拷贝，充分利用右值引用和std::move的语言特性

    {
        std::string str1 = "aacasxs";
        std::vector<std::string> vec;
        
        vec.push_back(str1); // 传统方法，copy
        std::cout << __LINE__ << ": "<< str1 << std::endl;
        vec.push_back(std::move(str1)); // 调用移动语义的push_back方法，避免拷贝，str1会失去原有值，变成空字符串
        std::cout << __LINE__ << ": "<< str1 << std::endl;
        vec.emplace_back(std::move(str1)); // emplace_back效果相同，str1会失去原有值
        vec.emplace_back("axcsddcas"); // 当然可以直接接右值

        std::cout << __LINE__ << ": "<< vec.size() << std::endl;
        for (auto &v : vec) {
            std::cout << __LINE__ << ": "<< v << std::endl;
        }
    }

    // std::forward<T>(u)
    // 当T为左值引用类型时，u将被转换为T类型的左值; 否则u将被转换为T类型右值
    {
        int a = 5;
        int rref = std::move(a); 
        std::forward<int &>(rref);  // 转换为左值
        std::forward<int &&>(rref); // 转换为右值
        std::forward<int>(rref);    // 转换为右值    
    }
}
