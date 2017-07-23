#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string add(string x, string y) {
    string answer;
    const int x_length = x.length(), y_length = y.length();
    const int max_length = max(x_length, y_length);

    for (int i = 0, carry = 0; i < max_length || carry > 0; ++i) {
        int d = carry;
        if (i < x_length) d += x.at(x_length - i - 1) - 48;
        if (i < y_length) d += y.at(y_length - i - 1) - 48;
        carry = d / 10;
        d %= 10;
        answer.insert(0, 1, d + 48);
    }

    return answer;
}

string karatsuba_multiplication(string x, string y) {
    const int x_length = x.length(), y_length = y.length();

    if (x_length == 1 && y_length == 1) {
        return to_string((x.at(0) - 48) * (y.at(0) - 48));
    } else {
        int split_position = max(x_length, y_length) / 2;
        string x1 = x.substr(0, max(x_length - split_position, 0));
        string x0 = x.substr(max(x_length - split_position, 0), min(split_position, x_length));
        string y1 = y.substr(0, max(y_length - split_position, 0));
        string y0 = y.substr(max(y_length - split_position, 0), min(split_position, y_length));
        if (x1.length() == 0) x1.push_back('0');
        if (y1.length() == 0) y1.push_back('0');
        string z2 = karatsuba_multiplication(x1, y1);
        string z1 = add(karatsuba_multiplication(x1, y0), karatsuba_multiplication(x0, y1));
        string z0 = karatsuba_multiplication(x0, y0);
        string answer = z2;
        answer.append(string(split_position, '0'));
        answer = add(answer, z1);
        answer.append(string(split_position, '0'));
        answer = add(answer, z0);
        while (answer.length() > 1 && answer.at(0) == '0') {
            answer.erase(0, 1);
        }
        return answer;
    }
}

int main(int argc, char const *argv[]) {
    string a, b;
    cin >> a;
    cin >> b;
    cout << karatsuba_multiplication(a, b);
    return 0;
}
