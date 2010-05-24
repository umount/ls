/*
 * Шаблон, который превращает двоичную запись, в десятичную
 * Bin <101110>::Value
 * @author Denis Sobolev <dns.sobol@gmail.com>
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

template<int bin> class Bin {
public:
 enum { Value = 2*Bin<bin/10>::Value + bin%10 };
};

template<>
class Bin<0> {
public:
 enum{Value=0};
};

template<>
class Bin<1> {
public:
 enum{Value=1};
};

int main() {
   int my_value= Bin<1010>::Value;
}
