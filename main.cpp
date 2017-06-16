#include <iostream>
#include <functional>
#include <vector>
#include <list>

using namespace std;

template <template<typename,typename> typename C, typename T, typename A, typename U>
auto operator >> ( const C<T,A> &v, function<U(T)> f)
{
  C<U,A> result;
  for( const auto e : v )
    result.push_back( f(e) );
    
  return result;
}

int main( int argc, char *argv[] )
{
  list<int> a = {1,2,3};
  
  function<int(int)> f = [](int x) { return x+7; } ;
  function<float(int)> g = [](int x) { return x*4 + 0.5; } ;
  
  auto b = a >> f >> g;
  
  for( auto x : b )
    cout << x << endl;
#if 0    
  auto c = a >> [](int x) -> float { return (x+7)*4 - 0.5; };
  for( auto x : c )
    cout << x << endl;  
#endif  

  for( auto x: a >> f >> g )
    cout << x << endl;
}
