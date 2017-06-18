#include <iostream>
#include <functional>
#include <vector>
#include <list>
#include <algorithm>

#include "date.h"

using namespace std;
using namespace std::chrono;
using namespace date;

template <template<typename T,typename ... A> typename C, typename T, typename ... A, typename U>
auto operator | ( const C<T,A...> &v, function<U(T)> f)
{
  C<U,A...> result;
  for( const auto e : v )
    result.push_back( f(e) );
    
  return result;
}

vector<int> seq( int from, int to )
{
	// class generator:
	struct UniqueNumber {
		int current;
		UniqueNumber( int from=1 ) {current=from-1;}
		int operator()() {return ++current;}
	};

  vector<int> result( to-from+1 );
  generate_n( result.begin(), to-from+1, UniqueNumber(from) );
  return result;
}

vector<int> seq( int count ) { return seq(1,count); }

days days_in_year( unsigned short y )
{
  auto next = sys_days{year{y+1}/1/1};
  auto curr = sys_days{year{ y }/1/1};

  return next - curr;
}

days days_in_month( unsigned short y, unsigned char m )
{
  auto next = sys_days{year{y}/month{m}/last};
  auto curr = sys_days{year{y}/month{m}/0};

  return next - curr;
}







int main( int argc, char *argv[] )
{
  auto a = seq(3);
  
  function<  int(int)> f = [](int x) { return x+7; } ;
  function<float(int)> g = [](int x) { return x*4 + 0.5; } ;
  
  for( auto x: a | f | g )
    cout << x << endl;

	auto today = floor<days>(system_clock::now());
	cout << today << '\n';

  cout << days_in_year(  2016  ) << endl;
  cout << days_in_month(2016, 2) << endl;
  cout << days_in_month(2016, 1) << endl;
  cout << days_in_month(2017, 2) << endl;
}

