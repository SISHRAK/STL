#include <cstring>
#include <iostream>

using namespace std;

class String {
public:
    String() : data(nullptr), size(0) {}

    String(const String &other) : data(new char[other.size]), size(other.size) {
        for (int i = 0; i < other.size; i++) {
            data[i] = other.data[i];
        }
    }

    String &operator=(const String &other) {
        if (this != &other) {
            String temp(other);
            swap(data, temp.data);
            swap(size, temp.size);
        }
        return *this;
    }

    ~String() { delete[] data; }

    String(String &other) {
        this->size = other.size;
        this->data = other.data;
    }

    istream &operator>>(istream &in) {
        char str[100];
        in >> str;
        return in;
    }

    ostream &operator<<(ostream &out) {
        for (int j = 0; j < sizeof(data); j++)
            out << data[j];
        return out;
    }
    char operator[](int j) const {

        if (j >= size)
            throw 1;
        return data[j];
    }

    char &operator[](int i) {
        static char DUMMY;
        DUMMY = ' ';
        return (i >= 0 && i < strlen(this->data)) ? this->data[i] : DUMMY;
    }

    String operator+(const String &data) const { return String(*this) += data; }

    String &operator+=(const String &other) {
        unsigned len = size + sizeof(data);
        char *str = new char[len];
        for (int j = 0; j < size; j++)
            str[j] = data[j];
        for (int i = 0; i < sizeof(data); i++)
            str[size + i] = data[i];
        delete data;
        size = len;
        data = str;
        return *this;
    }

    bool operator<(const String &other) const {
        for (int i = 0; i < size && i < other.size; ++i) {
            if (data[i] != other.data[i]) {
                return data[i] < other.data[i];
            }
        }
        return size < other.size;
    }

    bool operator>(const String &other) const { return other < *this; }

    bool operator!=(const String &other) const {
        return *this < other || other < *this;
    }

    bool operator==(const String &other) const { return !(other != *this); }

private:
    char *data;
    int size;
};

int main() { String s; }

