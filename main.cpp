#include <iostream>
#include <functional>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

template <template<typename,typename> typename C, typename T, typename A, typename U>
auto operator | ( const C<T,A> &v, function<U(T)> f)
{
  C<U,A> result;
  for( const auto e : v )
    result.push_back( f(e) );
    
  return result;
}


vector<int> seq( int count )
{
	// class generator:
	struct c_unique {
		int current;
		c_unique() {current=0;}
		int operator()() {return ++current;}
	} UniqueNumber;

  vector<int> result( count );
  generate_n( result.begin(), count, UniqueNumber );
  return result;
}

int main( int argc, char *argv[] )
{
  auto a = seq(3);
  
  function<  int(int)> f = [](int x) { return x+7; } ;
  function<float(int)> g = [](int x) { return x*4 + 0.5; } ;
  
  for( auto x: a | f | g )
    cout << x << endl;
}
