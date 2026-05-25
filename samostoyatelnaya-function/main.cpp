#include "Function.h"

int main() {
    Hiperbola hyp(2.0);
    hyp.print(3.0);
    std::cout << "min на [1, 5] = " << hyp.findMin(1.0, 5.0) << "\n";
    std::cout << "max на [1, 5] = " << hyp.findMax(1.0, 5.0) << "\n";

    Parabola par(1.0, -2.0, 1.0);
    par.print(3.0);
    std::cout << "min на [-3, 3] = " << par.findMin(-3.0, 3.0) << "\n";
    std::cout << "max на [-3, 3] = " << par.findMax(-3.0, 3.0) << "\n";

    Exponenta expf(1.0, 0.5);
    expf.print(2.0);
    std::cout << "min на [0, 4] = " << expf.findMin(0.0, 4.0) << "\n";
    std::cout << "max на [0, 4] = " << expf.findMax(0.0, 4.0) << "\n";

    std::vector<double> c = {1.0, -2.0, 1.0, 0.5};
    Polinom poly(c);
    poly.print(2.0);
    std::cout << "min на [-2, 3] = " << poly.findMin(-2.0, 3.0) << "\n";
    std::cout << "max на [-2, 3] = " << poly.findMax(-2.0, 3.0) << "\n";

    return 0;
}
