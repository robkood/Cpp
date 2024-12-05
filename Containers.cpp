#include <iostream>
#include <initializer_list>
#include <memory>

class Container
{
public: //[DO NOT MODIFY/REMOVE THESE GETTERS AND SETTERS: THEY ARE USED IN THE SPECTEST]
    int GetLength() const {return length;}
    double* GetData() const {return data;}
    void SetLength(const int length) {this->length = length;}
    void SetData(double* data) {this->data = data;}

public:
    // constructors
    Container(): length(0), data(nullptr) { print("default constructor"); }
    Container(int length): length(length), data(new double[length]) {}

    Container( std::initializer_list<double> list) : Container((int)list.size())
    {
        std::uninitialized_copy(list.begin(), list.end(), data);
    }
    // copy constructor
    Container(const Container& other)
    : Container(other.length)
    {
        for (auto i=0; i<other.length; i++)
            data[i] = other.data[i];
        std::cout << __PRETTY_FUNCTION__ << " called" << std::endl;
    }

    //move constructor 
     Container(Container&& other)
    : length(other.length), data(other.data)
    {
        other.length = 0;
        other.data   = nullptr;
        std::cout << __PRETTY_FUNCTION__ << " called" << std::endl;
    }

    // destructor
    ~Container()
    {
        delete[] data;
        data = nullptr;
        length = 0;
        std::cout << __PRETTY_FUNCTION__ << " called" << std::endl;
    }

    // operators
    void print(const std::string& info) const
    {
        // print the address of this instance, the attributes `length` and
        // `data` and the `info` string
        std::cout << "  " << this << " " << length << " " << data << "  "
            << info << std::endl;
    }

    //copy assignment
    Container& operator=(const Container& other)
    {
        if (this != &other)
        {
            delete[] data;
            length = other.length;
            data   = new double[other.length];
            for (auto i=0; i<other.length; i++)
                data[i] = other.data[i];
        }
        std::cout << __PRETTY_FUNCTION__ << " called" << std::endl;
        return *this;
    }

    // move assignment
    Container& operator=(Container&& other)
    {
        if (this != &other)
        {
            delete[] data;
            length = other.length;
            data   = other.data;
            other.length = 0;
            other.data   = nullptr;
        }
        std::cout << __PRETTY_FUNCTION__ << " called" << std::endl;
        return *this;
    }

    Container operator+ (const Container& other) const {

        if (length!=other.length) throw "Vectors have different size!";

        // Create result vector
        Container result(length);

        // Add the two vectors this->data and other.data and
        // store the sum in vector result.data

        for (auto i=0; i<length; i++)
            result.data[i] = data[i] + other.data[i];

        return result;
    }

private:
    int length;
    double* data;
};

int main()
{
    Container x;
    std::cout << "x has address " << &x << std::endl;

    std::cout << "Container a({ 1, 2, 3 });" << std::endl;
    Container a({ 1, 2, 3 });
    std::cout << "  a has address " << &a << std::endl;
    std::cout << "Container b = { 4, 5, 6 };" << std::endl;
    Container b = { 4, 5, 6 };
    std::cout << "  b has address " << &b << std::endl;
    std::cout << "Container c(a);" << std::endl;
    Container c(a);
    std::cout << "  c has address " << &c << std::endl;
    std::cout << "Container d = a + b;" << std::endl;
    Container d = a + b;
    std::cout << "  d has address " << &d << std::endl;
    std::cout << "Container e;" << std::endl;
    Container e;
    std::cout << "  e has address " << &e << std::endl;
    std::cout << "e = a + b;" << std::endl;
    e = a + b;
    std::cout << "Container aPlusb = a + b; Container f(std::move(aPlusb));" << std::endl;
    Container aPlusb = a + b; Container f(std::move(aPlusb));
    std::cout << "  f has address " << &f << std::endl;
    std::cout << "Container g = a + b + c;" << std::endl;
    Container g = a + b + c;
    std::cout << "  g has address " << &g << std::endl;
    std::cout << "Container h;" << std::endl;
    Container h;
    std::cout << "  h has address " << &h << std::endl;
    std::cout << "h = a + b + c;" << std::endl;
    h = a + b + c;
    std::cout << "Container i = { a + b + c };" << std::endl;
    Container i = { a + b + c };
    std::cout << "  i has address " << &i << std::endl;
    std::cout << "end" << std::endl;

    return 0;
}