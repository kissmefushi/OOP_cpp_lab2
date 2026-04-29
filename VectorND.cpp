#include <iostream>
#include <windows.h>

class VectorND {
private:
    double* coords;
    int dimension;

public:
    VectorND();
    VectorND(int n);
    VectorND(int n, const double* arr);
    VectorND(const VectorND& other);
    VectorND(VectorND&& other) noexcept;
    ~VectorND();

    VectorND& operator=(const VectorND& other);
    VectorND& operator=(VectorND&& other) noexcept;

    double& operator[](int index);
    const double& operator[](int index) const;
    friend std::ostream& operator<<(std::ostream& os, const VectorND& v);
    friend std::istream& operator>>(std::istream& is, VectorND& v);

    bool operator==(const VectorND& other) const;
    bool operator!=(const VectorND& other) const;

    operator double* () const;

    VectorND operator+(const VectorND& other) const; // додавання
    VectorND operator-(const VectorND& other) const; // віднімання
    VectorND operator*(double scalar) const;         // множення на число
    double operator*(const VectorND& other) const;   // скалярний добуток
};

VectorND::VectorND() {
    coords = new double[1] {1.0};
    dimension = 1;
}
VectorND::VectorND(int n) {
    dimension = (n < 1) ? 1 : n;
    coords = new double[dimension];
    for (int i = 0; i < dimension; i++) {
        coords[i] = 0.0;
    }
}
VectorND::VectorND(int n, const double* arr) {
    dimension = (n < 1) ? 1 : n;
    coords = new double[dimension];
    for (int i = 0; i < dimension; i++) {
        coords[i] = arr[i];
    }
}
VectorND::VectorND(const VectorND& other) {
    dimension = other.dimension;
    coords = new double[dimension];
    for (int i = 0; i < dimension; i++) {
        coords[i] = other.coords[i]; 
    }
}
VectorND::VectorND(VectorND&& other) noexcept 
    : coords(other.coords), dimension(other.dimension) {
    other.coords = nullptr;
    other.dimension = 0;
}
VectorND::~VectorND() {
    delete[] coords;
}
VectorND& VectorND::operator=(const VectorND& other) {
    if (this == &other)
        return *this;
    delete[] coords;
    dimension = other.dimension;
    coords = new double[dimension];
    for (int i = 0; i < dimension; i++) {
        coords[i] = other.coords[i];
    }
    return *this;
}
VectorND& VectorND::operator=(VectorND&& other) noexcept {
    if (this == &other)
        return *this;
    delete[] coords;
    coords = other.coords;
    dimension = other.dimension;

    other.coords = nullptr;
    other.dimension = 0;
    return *this;
}
double& VectorND::operator[](int index) {
    if (index < 0 || index >= dimension)
    {
        abort();
    }
    return coords[index];
}
const double& VectorND::operator[](int index) const {
    if (index < 0 || index >= dimension)
    {
        abort();
    }
    return coords[index];
}

std::ostream& operator<<(std::ostream& os, const VectorND& v) {
    os << "(";
    for (int i = 0; i < v.dimension; i++) {
        os << v.coords[i];

        if (i < v.dimension - 1) {
            os << ", ";
        }
    }
    os << ")";

    return os;
}
std::istream& operator>>(std::istream& is, VectorND& v) {
    for (int i = 0; i < v.dimension; i++) {
        is >> v.coords[i];
    }
    return is;
}
bool VectorND::operator==(const VectorND& other) const {
    if (dimension != other.dimension) {
        return false;
    }

    for (int i = 0; i < dimension; i++) {
        if (coords[i] != other.coords[i]) {
            return false;
        }
    }
    return true;
}
bool VectorND::operator!=(const VectorND& other) const {
    return !(*this == other);
}
VectorND::operator double* () const {
    return coords;
}
VectorND VectorND::operator+(const VectorND& other) const {
    if (dimension != other.dimension)
    {
        abort();
    }
    VectorND temp(dimension);
    for (int i = 0; i < dimension; i++) {
        temp[i] = coords[i]+ other.coords[i];
    }
    return temp;
}
VectorND VectorND::operator-(const VectorND& other) const {
    if (dimension != other.dimension)
    {
        abort();
    }
    VectorND temp(dimension);
    for (int i = 0; i < dimension; i++) {
        temp[i] = coords[i] - other.coords[i];
    }
    return temp;
}
VectorND VectorND::operator*(double scalar) const {
    VectorND temp(dimension);
    
    for (int i = 0; i < dimension; i++) {
        temp[i] = coords[i]* scalar;
    }
    return temp;
}
double VectorND::operator*(const VectorND& other) const {
    if (dimension != other.dimension)
    {
        abort();
    }
    double sum = 0.0;
    for (int i = 0; i < dimension; i++) {
        sum+= coords[i] * other.coords[i];
    }
    return sum;
}
int main() {
    setlocale(LC_ALL, "Ukrainian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    double arr1[] = { 2.0, 4.0, 6.0 };
    double arr2[] = { 1.0, 3.0, 5.0 };

    VectorND v1(3, arr1);
    VectorND v2(3, arr2);
    VectorND v3(3);
    VectorND v4;

    std::cout << "v1(з масиву):" << v1 << std::endl;
    std::cout << "v2(з масиву):" << v2 << std::endl;
    std::cout << "v3(з нулів):" << v3 << std::endl;
    std::cout << "v4(за замовчуванням):" << v4 << std::endl;

    v3[0] = 10.5;
    v3[1] = 20.5;
    std::cout << "Змінений v3: " << v3 << std::endl;
    std::cout << "Другий елемент v1: " << v1[1] << std::endl;

    VectorND v_sum = v1 + v2;
    VectorND v_sub = v1 - v2;
    VectorND v_mul = v1 * 2.5;
    double scalar_product = v1 * v2;

    std::cout << "Додавання (v1 + v2): " << v_sum << std::endl;
    std::cout << "Віднімання (v1 - v2): " << v_sub << std::endl;
    std::cout << "Множення на скаляр (v1 * 2.5): " << v_mul << std::endl;
    std::cout << "Скалярний добуток (v1 * v2): " << scalar_product << std::endl;

    VectorND v_copy = v1;
    std::cout << "v_copy: " << v_copy << std::endl;
    if (v1 == v_copy)
    {
        std::cout << "v1 та v_copy рівні!" << std::endl;
    }
    if (v1 != v2)
    {
        std::cout << "v1 та v2 не рівні!" << std::endl;
    }
    double* raw_array = v1;
    std::cout << "Нульовий елемент масиву через raw_array: " << raw_array[0] << std::endl;

    VectorND v_temp(3, arr1);
    std::cout << "Створено тимчасовий v_temp: " << v_temp << std::endl;

    VectorND v_moved;
    v_moved = std::move(v_temp);
    std::cout << "Вектор v_moved після крадіжки даних: " << v_moved << std::endl;

    VectorND v_input(2);
    std::cout << "Введіть 2 координати для вектора через пробіл (наприклад, 3.5 4.1): ";
    std::cin >> v_input;
    std::cout << "Ви ввели вектор: " << v_input << std::endl;

    return 0;
}
