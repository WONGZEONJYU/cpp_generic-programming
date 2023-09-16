#include <iostream>
#include <string>

using namespace std;

namespace _nmsp1
{
	int mf(int tmp1, int tmp2){
		cout << __FUNCTION__ << "(int tmp1, int tmp2)\n" ;
		return 1;
	}

	int mf2(int tmp1, int tmp2) {
		cout << __FUNCTION__ << "(int tmp1, int tmp2)\n";
		return 10;
	}

	using FunType = int(*)(int, int); /*函数指针类型定义*/

	template<typename T,typename F = FunType>
	void testfunc(T i,T j,F funcpoint = mf) {
		cout << funcpoint(i, j) << '\n';
	}

	template <typename T = int, typename U>
	void testfunc2(U m) {

		T tmpvalue{ m };
		cout << __FUNCTION__ << " template<typename T = int, typename U>(U m)\n tmpvalue = " <<
		tmpvalue << '\n';
	}

	template <typename T,typename R = int, typename U>
	R testfunc3(U m) {

		T tmpvalue{ m };
		cout << "template<typename T, typename R = int, typename U>(U m)\n";

		cout << typeid(R).name() << " " << __FUNCTION__ << " (U m) tmpvalue = " << tmpvalue << '\n';
		return tmpvalue;
	}
}

struct MyStruct_
{
	float aa;
};

struct MyStruct
{
	MyStruct_ s;
	int a;
	static void f(){cout << __FUNCTION__ << '\n';}
};

class MyClass : public MyStruct
{
public:
	char b;
	double c;
	static void f1() { cout << __FUNCTION__ << '\n'; }
};

namespace _nmsp2
{
	template < typename T, typename U, int val = 100 >
	//template < typename T, typename U, auto val = 100 > 
	auto Add(T tv1, U tv2) {
		return tv1 + tv2 + val;
	}

	template < typename T, typename U, double val = 100.0 >
	auto Add(T tv1, U tv2) {
		cout << "template < typename T, typename U, double val = 100.0 >\n";
		return tv1 + tv2 + val;
	}

	template < typename T, typename U, MyClass val = MyClass{} >
	auto Add(T tv1, U tv2) {
		cout << "template < typename T, typename U, MyClass val = MyClass{100.0f,200,'a',12.5} >\n" <<
			"val.s.aa = " << val.s.aa <<
			" val.a = " << val.a <<
			" val.b = " << val.b <<
			" val.c = " << val.c << '\n';
		val.f();
		val.f1();
		return tv1 + tv2 + val.s.aa + val.a + val.b + val.c;
	}
}

namespace _nmsp3 {

	template <double* p>
	void mft()
	{
		cout << __FUNCTION__ << " template <double* p>\n";
	}
	double g_d{ 1.3 };
}


int main(int argc, char* argv[])
{
	//_nmsp1::testfunc(15, 16);
	//_nmsp1::testfunc(15, 16, _nmsp1::mf2);
	//_nmsp1::testfunc2(12);
	//_nmsp1::testfunc3<int>(100);
	
	//cout << _nmsp2::Add<float, float>(22.3f, 11.8f) << '\n';
	//cout << _nmsp2::Add<float, float,800>(22.3f, 11.8f) << '\n';
	
	{
		/*
		int k = 1000;
		cout << _nmsp2::Add<float, float, k>(22.3f, 11.8f) << '\n';
		*/

		/*
		constexpr int v{ 900 };
		cout << _nmsp2::Add<float, float,v>(22.3f, 11.8f) << '\n';
		*/
	}

	{
		/*
		cout << _nmsp2::Add<float, float, 12.5>(22.3f, 11.8f) << '\n'; //46.6
		constexpr double d{ 13.5 };
		cout << _nmsp2::Add<float, float, d>(22.3f, 11.8f) << '\n'; //47.6
		*/
	}


	{
		/*
		constexpr MyClass a { 100.0f,200,'a',12.5 };
		cout << _nmsp2::Add<float, float,a>(22.3f, 11.8f) << '\n';
		*/
	}
	
	{
		_nmsp3::mft<&_nmsp3::g_d>();


	}

	_CRT_UNUSED(getchar());
	return 0;
}

