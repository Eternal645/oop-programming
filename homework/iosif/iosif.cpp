#include <iostream>
#include <vector>
#include <locale.h>

using namespace std;

class Array
{
private:
    vector<int> data;

public:
    Array(size_t n)
    {
        data.resize(n);
        for (size_t i = 0; i < n; ++i)
            data[i] = i + 1;
    }

    size_t size() const
    {
        return data.size();
    }

    void removeAt(size_t index)
    {
        data.erase(data.begin() + index);
    }

    int get(size_t index) const
    {
        return data[index];
    }
};

size_t josephus(size_t n, size_t k)
{
    Array arr(n);
    size_t current = 0;

    while (arr.size() > 1)
    {
        current = (current + k - 1) % arr.size();
        arr.removeAt(current);
    }

    return arr.get(0);
}

int main()
{
    setlocale(LC_ALL, "Russian");
    const size_t k = 3;
    vector<size_t> n_values = {1000, 5000, 10000, 50000, 100000, 500000, 1000000};

    cout << "N---------------Ответ" << endl;

    for (size_t n : n_values)
    {
        size_t result = josephus(n, k);
        cout << n << "------------" << result << endl;
    }

    return 0;
}