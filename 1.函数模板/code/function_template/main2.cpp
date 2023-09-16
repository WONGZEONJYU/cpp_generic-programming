#include <iostream>
using namespace std;

namespace nmsp1_
{
	template<typename T>
	void myfunc(T tmpvalue) {
		auto type{ typeid(T).name() };
		cout << "template<typename T>\n" << __FUNCTION__ << 
			'<' << type << ">(" << type << " tmpvalue)" << " invoked\n\n";
	}
	
	template<typename T>
	void myfunc(T* tmpvalue){
		auto type { typeid(tmpvalue).name() };
		cout<< "template<typename T>\n" << __FUNCTION__ << 
			'<' << type << ">(" << type << " tmpvalue)" << " overload invoked\n\n";
	}

	void myfunc(int tmpvalue){
		cout << __FUNCTION__ << "(" << typeid(tmpvalue).name() << " tmpvalue)\n\n";
	}
}

namespace nmsp2_
{
	/*泛化版本*/
	template<typename T,typename U> /* void nmsp2_::tfunc<char const *,int>(char const * &,int &) */
	void tfunc(T& tmprv,U& tmprv2) {
		cout << "---------------------------begin---------------------------\n";
		auto type1 { typeid(tmprv).name() };
		auto type2 { typeid(tmprv2).name() };
		cout << "template<typename T,typename U>\n" <<
			__FUNCTION__ << '<' << type1 << "," << type2 <<
			">(" << type1 << "& tmprv," << type2 << "& tmprv2) Generalization(泛化)\n\n";

		cout << "tmprv = " << tmprv << "\ntmprv2 = " << tmprv2 << '\n';
		cout << "---------------------------end---------------------------\n\n";

	}

	/*全特化*/
	template<> /*全特化<>里面为空*/
	void tfunc<int, double>(int& tmprv, double& tmprv2)	/*<int, double>可以省略，因为根据实参可以完全推导出T和U的类型。*/
	//void tfunc(int& tmprv, double& tmprv2)
	{
		cout << "---------------------------begin---------------------------\n";
		auto type1{ typeid(tmprv).name() };
		auto type2{ typeid(tmprv2).name() };
		cout << "template<typename T,typename U>\n" <<
			__FUNCTION__ << '<' << type1 << "," << type2 <<
			">(" << type1 << "& tmprv," << type2 << "& tmprv2) full specialization(全特化)\n\n";

		cout << "tmprv = " << tmprv << "\ntmprv2 = " << tmprv2 << '\n';
		cout << "---------------------------end---------------------------\n\n";
	}

	/*重载函数*/
	void tfunc(int& tmprv, double& tmprv2)
	{
		cout << "---------------------------begin---------------------------\n";
		cout << __FUNCTION__ << '(' << typeid(tmprv).name() <<
			"& tmprv, " << typeid(tmprv2).name() << "& tmprv2)\n";
		cout << "---------------------------end---------------------------\n\n";
	}

	/*从模板参数数量上的偏特化*/
	//template< typename U>
	//void tfunc<double,U>(double& tmprv, U& tmprv2)
	//{

	//}

	/*类似于tfunc<double,U>偏特化的tfunc重载版本*/
	template<typename U>
	void tfunc(double& tmprv, U& tmprv2)
	{
		auto type{ typeid(U).name() };
		auto pram_type1{ typeid(tmprv).name() };
		auto pram_type2{ typeid(tmprv2).name() };
		cout << "---------------------------begin---------------------------\n";
		cout << "类似于tfunc<double, U>偏特化的tfunc重载版本\n";
		cout << __FUNCTION__ << '<' << type << ">(" <<
			pram_type1 << "& tmprv, " << pram_type2 << "& tmprv2)\n";
		cout << "---------------------------end---------------------------\n\n";
	}

	template<typename T, typename U>
	void tfunc(const T& tmprv, U& tmprv2)
	{
		auto type1{ typeid(T).name() };
		auto type2{ typeid(U).name() };
		auto pram_type1{ typeid(tmprv).name() };
		auto pram_type2{ typeid(tmprv2).name() };
		cout << "---------------------------begin---------------------------\n";
		cout << __FUNCTION__ << '<' << type1 << ',' << type2 << ">(const " <<
			pram_type1 << "& tmprv, " << pram_type2 << "& tmprv2)\n";
		cout << "---------------------------end---------------------------\n\n";
	}
}

int main(int argc, char* argv[])
{

#if 0
	{
		nmsp1_::myfunc(12);
		char* p{};
		nmsp1_::myfunc(p);
		nmsp1_::myfunc(12.1);
	}
#endif

#if 0
	{
		const char* p {"I Love China"};
		int i{ 12 };
		nmsp2_::tfunc(p,i);

		int k{ 12 };
		double db{ 15.8 };
		nmsp2_::tfunc<>(k, db);

		nmsp2_::tfunc(k, db);
	}
#endif

#if 1
	{
		double db1{ 18.5 };
		int i{ 12 };
		nmsp2_::tfunc(db1, i);

		const int k2{ 12 };
		double db2{ 15.8 };
		nmsp2_::tfunc(k2, db2);
	}
#endif 

	_CRT_UNUSED(getchar());
	return 0;
}


//第一节 函数模板
//4：重载
//函数（函数模板）名字相同，但是参数数量或者参数类型上不同。
//函数模板和函数也可以同时存在,此时可以把函数看成是一种重载,当普通函数和函数模板都比较合适的时候，编译器会优先选择普通函数来执行。
 //如果选择最合适（最特殊）的函数模板/函数，编译器内部有比较复杂的排序规则，规则也在不断更新。

//5：特化
//泛化（泛化版本）：大众化的，常规的。常规情况下，写的函数模板都是泛化的函数模板。
//特化（特化版本）：往往代表着从泛化版本中抽出来的一组子集。
//（5.1）全特化：就是把tfunc这个泛化版本中的所有模板参数都用具体的类型来代替构成的一个特殊的版本（全特化版本）；
 //全特化实际上等价于实例化一个函数模板，并不等价于一个函数重载。
//void tfunc<int ,double>(int& tmprv, double& tmprv2){......}  //全特化的样子
//void tfunc(int& tmprv, double& tmprv2) { ...... }  //重载函数的样子
//编译器考虑的顺序：优先选择普通函数，然后才会考虑函数模板的特化版本，最后才会考虑函数模板的泛化版本。
//（5.2）偏特化（局部特化）
//从两方面来说：一个是模板参数数量上的偏特化，一个是模板参数范围上的偏特化。
//a)模板参数数量上的偏特化：比如针对tfunc函数模板，第一个模板参数类型为double，第二个模板参数不特化；
  //实际上，从模板参数数量上来讲，函数模板不能偏特化。否则会导致编译错误。
//b)模板参数范围上的偏特化：
 //范围上：int->const int，类型变小；   T->T*，T->T&，T->T&&。针对T类型，从类型范围上都变小了。
   //实际上，对于函数模板来讲，也不存在模板参数范围上的偏特化。因为这种所谓模板参数范围上的偏特化，实际上是函数模板的重载。
//c）通过重载实现模板参数数量上的偏特化

//后续讲解类模板时，对于类模板，还是存在模板参数范围上的偏特化以及数量上的偏特化，后续会详细讲解。
