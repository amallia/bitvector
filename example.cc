#include "bitvector.h"
#include <iostream>
#include <iomanip>

int main()
{
	stdex::bitvector v;
	std::cout << std::boolalpha;

	std::cout
		<< "sizeof:\t\t\t" << sizeof(v) << std::endl
		<< "max size:\t\t" << v.max_size() << std::endl
		<< "nothrow default ctor:\t"
		<< std::is_nothrow_default_constructible<
		    stdex::bitvector>() << std::endl
		<< "nothrow swap:\t\t" << noexcept(swap(v, v)) << std::endl
		<< "default init size:\t" << v.size() << std::endl
		;

	v = stdex::bitvector(128, true);
	v.push_back(true);

	std::cout << "all with all bit set:\t" << v.all() << std::endl;

	std::cout << std::noboolalpha;

	std::cout
		<< "size after insertion:\t" << v.size() << std::endl
		<< "last bit:\t\t" << v.test(128) << std::endl
		;

	v.set(128, false);
	std::cout << "after set to false:\t" << v[128] << std::endl;

	v.flip(128);
	std::cout << "after flipped:\t\t" << v[128] << std::endl;

	v.reset(128);
	std::cout << "after reset:\t\t" << v[128] << std::endl;

	auto r = v[128];
	r.flip();

	std::cout
		<< "after proxy flipped:\t" << v[128] << std::endl
		<< "proxy:\t\t\t" << r << std::endl
		<< "proxy inversed:\t\t" << ~r << std::endl
		;

	v[127].flip();
	stdex::bitvector v2(v);

	std::cout
		<< "popcount after a flip:\t" << v.count() << std::endl
		<< "popcount of copied:\t" << v2.count() << std::endl
		;

	stdex::bitvector v3(200);
	swap(v, v3);

	std::cout
		<< "size after swap:\t" << v.size() << std::endl
		<< "size of swapped:\t" << v3.size() << std::endl
		<< "popcount after swap:\t" << v.count() << std::endl
		;

	v.pop_back();
	std::cout << "size after popped:\t" << v.size() << std::endl;

	v.resize(277, 1);
	std::cout << "popcount after resized:\t" << v.count() << std::endl;

	v.clear();
	std::cout << "size after cleared:\t" << v.size() << std::endl;

	v.assign(64, 1);
	v.shrink_to_fit();
	std::cout << "popcount after assign:\t" << v.count() << std::endl;

	v = v2;
	std::cout << "after assignment:\t" << v.count() << std::endl;

	std::cout << std::boolalpha;

	std::cout << "all with one bit unset:\t" << v.all() << std::endl;

	v.reset();
	std::cout << "any with no bit set:\t" << v.any() << std::endl;

	v.set(128);
	std::cout << "any with last bit set:\t" << v.any() << std::endl;

	v.flip();
	std::cout << "popcount after flip:\t" << v.count() << std::endl;

	stdex::bitvector v5(std::move(v3), v2.get_allocator());
	std::cout << "size of move init'ed:\t" << v5.size() << std::endl;

	stdex::basic_bitvector<std::allocator<unsigned char>> v4;
	std::cout << "ulong of 0b(empty):\t" << v4.to_ulong() << std::endl;

	v4.push_back(1);
	v4.push_back(1);
	v4.push_back(0);
	v4.push_back(0);
	v4.push_back(1);
	std::cout << "ulong of 0b" << v4.to_string() << ":\t"
		<< v4.to_ulong() << std::endl;

	v4.push_back(0);
	v4.push_back(0);
	v4.push_back(0);
	v4.push_back(1);
	std::cout << "ulong of 0b" << v4.to_string() << ":\t"
		<< v4.to_ulong() << std::endl;
}
