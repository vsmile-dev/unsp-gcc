// Build don't link:

template <class T>
void f(T) {} // ERROR - parameter has incomplete type

class C;

void g(const C& c)
{
  f(c); // ERROR - invalid use of undefined type
}
