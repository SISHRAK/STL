#include <iostream>

using namespace std;

struct RationalNumber {
public:
    static int gcd(int a, int b) {
        while (a != 0 && b != 0) {
            if (a > b) {
                swap(a, b);
            }
            b %= a;
        }
        return b + a;
    }

    RationalNumber() :
            up(0),
            down(1) {

    }

    RationalNumber(int x) :
            up(x),
            down(1) {

    }

    void print() const {
        cout << up << "/" << down;
    }

    int getUp() const {
        return up;
    }

    void setUp(int newUp) {
        up = newUp;
    }

    int getDown() const {
        return down;
    }

    void setDown(int newDown) {
        if (newDown == 0) {
            cout << "Cannot be a zero";
        }
        else {
            down = newDown;
        }
    }

    void zip() {
        int gc = gcd(up, down);
        up /= gc;
        down /= gc;
    }

    RationalNumber operator/(const RationalNumber& other)
    {
        RationalNumber res(*this);
        res /= other;
        return res;
    }

    RationalNumber operator*(const RationalNumber& other)
    {
        RationalNumber res(*this);
        res *= other;
        return res;
    }

    RationalNumber& operator+=(const RationalNumber& R)
    {
        up = (up * R.down + down * R.up);
        down *= R.down;
        zip();
        return*this;
    }

    RationalNumber operator+(const RationalNumber& a)
    {
        return RationalNumber(*this) += a;
    }

    RationalNumber& operator -= (const RationalNumber& R)
    {
        up = up * (R.down) - R.up * (down);
        down *= R.down;
        zip();
        return *this;
    }

    RationalNumber operator-(const RationalNumber& a)
    {
        return RationalNumber(*this) = RationalNumber(*this) - a;
    }

    RationalNumber& operator *= (const RationalNumber& R)
    {
        up *= R.up;
        down *= R.down;
        zip();
        return *this;
    }

    RationalNumber& operator /= (const RationalNumber& R)
    {
        if (R.up == 0) {
            cout << "cannot be a zero";
        }
        else {
            up *= (R.down);
            down *= (R.up);
            zip();
            return *this;
        }
    }

    operator double() {
        return static_cast<double>(up) / static_cast<double>(down);
    }

private:
    int up;
    int down;
    void Mistake_() {
        cout << "Mistake";
    }
};

int main()
{
    RationalNumber x, y;
    int up_;
    int down_;
    cin >> up_;
    cin >> down_;
    x.setUp(up_);
    x.setDown(down_);
    x.zip();
    x.print();
}
