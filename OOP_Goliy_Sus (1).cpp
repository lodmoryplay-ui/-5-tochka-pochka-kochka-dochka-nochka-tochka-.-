#include <iostream>
#include <cmath>
#include <stdexcept>

template<typename T>
class Array {
private:
    T* data;
    size_t count;

public:
    Array() : data(nullptr), count(0) {}

    ~Array() {
        delete[] data;
    }

    T& operator[](size_t index) {
        if (index >= count) {
            throw std::out_of_range("индекс за пределами массива");
        }
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= count) {
            throw std::out_of_range("индекс за пределами массива");
        }
        return data[index];
    }

    bool operator==(const Array<T>& other) const {
        if (count != other.count) return false;
        for (size_t i = 0; i < count; i++) {
            if (data[i] != other.data[i]) return false;
        }
        return true;
    }

    bool operator!=(const Array<T>& other) const {
        return !(*this == other);
    }

    void push(const T& item) {
        T* newData = new T[count + 1];
        for (size_t i = 0; i < count; i++) {
            newData[i] = data[i];
        }
        newData[count] = item;
        delete[] data;
        data = newData;
        count++;
    }

    size_t size() const {
        return count;
    }
};


class Vector {
private:
    static double maxLength;
protected:
    double length;
public:
    Vector() : length(0) {}
    virtual ~Vector() {}

    virtual double computeLength() const = 0;
    virtual void print() const = 0;

    void setLength(double l) {
        length = l;
    }

    static void updateMaxLength(double l) {
        if (l > maxLength) maxLength = l;
    }

    static double getMaxLength() {
        return maxLength;
    }
};


class Vector2D : public Vector {
private:
    double x, y;
public:
    Vector2D(double x, double y) : x(x), y(y) {
        length = computeLength();
        updateMaxLength(length);
    }

    double computeLength() const {
        return std::sqrt(x * x + y * y);
    }

    void print() const {
        std::cout << "Вектор2D: (" << x << ", " << y << "), длина=" << length << std::endl;
    }
};

class Vector3D : public Vector {
private:
    double x, y, z;
public:
    Vector3D(double x, double y, double z) : x(x), y(y), z(z) {
        length = computeLength();
        updateMaxLength(length);
    }

    double computeLength() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    void print() const {
        std::cout << "Вектор3D: (" << x << ", " << y << ", " << z << "), длина=" << length << std::endl;
    }
};


double Vector::maxLength = 0;

int main()
{
    setlocale(LC_ALL, "");

    Array<int> a1;
    a1.push(10);
    a1.push(20);
    a1.push(30);

    std::cout << "Массив int: ";
    for (size_t i = 0; i < a1.size(); i++) {
        std::cout << a1[i] << " ";
    }
    std::cout << std::endl;

    Array<int> a2;
    a2.push(10);
    a2.push(20);
    a2.push(30);

    Array<int> a3;
    a3.push(1);
    a3.push(2);

    std::cout << "a1 == a2: " << (a1 == a2 ? "true" : "false") << std::endl;
    std::cout << "a1 != a3: " << (a1 != a3 ? "true" : "false") << std::endl;

    Vector2D v1(3.0, 4.0);
    Vector2D v2(1.0, 2.0);
    Vector3D v3(1.0, 2.0, 2.0);
    Vector3D v4(3.0, 4.0, 5.0);

    double maxLen = Vector::getMaxLength();
    std::cout << "Максимальная длина векторов: " << maxLen << std::endl;

    Array<Vector*> vectorArray;
    vectorArray.push(new Vector2D(5.0, 12.0));
    vectorArray.push(new Vector3D(2.0, 3.0, 6.0));
    vectorArray.push(new Vector2D(8.0, 6.0));

    std::cout << "Массив векторов:" << std::endl;
    for (size_t i = 0; i < vectorArray.size(); i++) {
        vectorArray[i]->print();
    }

    for (size_t i = 0; i < vectorArray.size(); i++) {
        delete vectorArray[i];
    }

    Array<double> d1;
    d1.push(1.1);
    d1.push(2.2);
    d1.push(3.3);

    Array<double> d2;
    d2.push(1.1);
    d2.push(2.2);
    d2.push(3.3);

    std::cout << "Массив double: ";
    for (size_t i = 0; i < d1.size(); i++) {
        std::cout << d1[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "d1 == d2: " << (d1 == d2 ? "true" : "false") << std::endl;

    return 0;
}