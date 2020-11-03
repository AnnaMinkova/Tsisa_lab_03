#include <cmath>
#include <ctime>
#include <iomanip>
#include <iostream>

using std::cout;

double randomInRange(const double a, const double b)
{
    return a + rand() * 1./RAND_MAX * (b - a);
}

void printTableHead()
{
    cout << std::left << std::string(47, '-') << '\n'
         << "| " << std::setw(4) << "N"
         << "| " << std::setw(10) << "T"
         << "| " << std::setw(11) << "x"
         << "| " << std::setw(13) << "f(x)" << "|\n"
         << std::string(47, '-') << '\n';
}

void printLine(const int iteration, const double T, const double value, const double functionValue)
{
    cout << "| " << std::setw(4) << iteration
         << "| " << std::setw(10) << T
         << "| " << std::setw(11) << value
         << "| " << std::setw(13) << functionValue << "|\n";
}

template<class Function>
auto SAMethod(const double a, const double b, Function func)
{
    printTableHead();

    const double T_min = .01;
    double T_i = 10000.;
    double x_i = randomInRange(a,b);
    int i = 0;
    while (T_i > T_min) {
        ++i;
        double x_new = randomInRange(a, b);
        double delta_f = func(x_new) - func(x_i);
        if (delta_f <= 0) {
            x_i = x_new;
        } else {
            double randomProb = randomInRange(0, 1);
            double probability = exp(-delta_f/T_i);
            if (randomProb < probability) {
                x_i = x_new;
            }
        }
        printLine(i, T_i, x_i, func(x_i));
        T_i *= .95;
    }

    cout << std::string(47, '-') << '\n';
    return std::pair{x_i, func(x_i)};
}

double MyFunction(const double x)
{
    return pow((1-x),2)+exp(x);
}

double MyFunctionSin(const double x) {
    return MyFunction(x) * sin(5*x);
}

const double A = -2.;
const double B = 4.;

int main()
{
    cout << "Variant 10\nFunction 1:" <<std::endl;
    srand(time(nullptr));
    auto result_1 = SAMethod(A, B, MyFunction);
    cout << "Result: Xmin = " << result_1.first
         << ", Fmin = " << result_1.second << '\n';

    cout << "\nFunction 2:"<<std::endl;
    auto result_2 = SAMethod(A, B, MyFunctionSin);
    cout << "Result: Xmin = " << result_2.first
         << ", Fmin = " << result_2.second << '\n';

    return 0;
}