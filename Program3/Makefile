all: test_multiset prime_factor

test_multiset: multiset.h test_multiset.cc
	g++ -Wall -Werror -o test_multiset test_multiset.cc -pthread -lgtest

prime_factors: multiset.h prime_factors.cc
	g++ -Wall -Werror -o prime_factors prime_factors.cc

cpplint:
	/home/cs36cjp/public/cpplint/cpplint prime_factor.cc

clean:
	rm -rf *o test_multiset prime_factors
