#include <cstdlib>
#include <iostream>

#include "A.hpp"
#include "B.hpp"
#include "Base.hpp"
#include "C.hpp"

Base *generate(void) {
    int randomNum = rand() % 3;
    Base *random = NULL;

    switch (randomNum) {
    case 0:
        random = new A;
        std::cout << "Generated type: A" << std::endl;
        break;
    case 1:
        random = new B;
        std::cout << "Generated type: B" << std::endl;
        break;
    case 2:
        random = new C;
        std::cout << "Generated type: C" << std::endl;
        break;
    }
    return random;
}

void identify(Base *p) {
    if (p == NULL) {
        std::cout << "Actual type: Unknown (NULL pointer)" << std::endl;
        return;
    }

    A *a_ptr = dynamic_cast<A *>(p);
    if (a_ptr != NULL) {
        std::cout << "Actual type: A" << std::endl;
        return;
    }

    B *b_ptr = dynamic_cast<B *>(p);
    if (b_ptr != NULL) {
        std::cout << "Actual type: B" << std::endl;
        return;
    }

    C *c_ptr = dynamic_cast<C *>(p);
    if (c_ptr != NULL) {
        std::cout << "Actual type: C" << std::endl;
        return;
    }

    std::cout << "Actual type: Unknown" << std::endl;
}

void identify(Base &p) {
    try {
        A &a_ref = dynamic_cast<A &>(p);
        (void)a_ref;
        std::cout << "Actual type: A" << std::endl;
        return;
    } catch (const std::exception &e) {
    }

    try {
        B &b_ref = dynamic_cast<B &>(p);
        (void)b_ref;
        std::cout << "Actual type: B" << std::endl;
        return;
    } catch (const std::exception &e) {
    }

    try {
        C &c_ref = dynamic_cast<C &>(p);
        (void)c_ref;
        std::cout << "Actual type: C" << std::endl;
        return;
    } catch (const std::exception &e) {
        std::cout << "Actual type: Unknown" << std::endl;
    }
}

void run_tests(int count) {
    std::cout << "--- Running testing " << count << "x ---" << std::endl;

    for (int i = 0; i < count; ++i) {
        std::cout << "\n[Test " << i + 1 << "]: ";

        Base *p = generate();

        std::cout << "Pointer identification: ";
        identify(p);

        std::cout << "Reference identification: ";
        identify(*p);

        delete p;
        std::cout << "Object destroyed." << std::endl;
    }
}

int main() {
    srand(time(NULL));
    run_tests(5);
    std::cout << "\n[Test NULL Pointer]: ";
    Base *nullPtr = NULL;
    std::cout << "Pointer identification: ";
    identify(nullPtr);
    return 0;
}
