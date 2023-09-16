#include <iostream>
#include <string>

using namespace std;

namespace nmsp1_
{
	//template<typename T> /*T:称为 类型 模板参数 ，代表是一个类型*/
	template<class T> /*class 可以取代typename，但这里的class并没有 “类” 的意思*/
						/*T这个名字可以任意起*/
	T Sub(T tv1, T tv2)
	{
		return tv1 - tv2;
		//return tv1 + tv2;
	}

	//template<typename T ,typename U ,typename V >
	//template<typename V ,typename T, typename U>
	template<typename T, typename U>
	//V Add(T tv1,U tv2)
	auto Add(T tv1, U tv2)	/* auto用于表达推导返回值类型的含义 */
	//auto Add(T tv1, U tv2) -> decltype(tv1 + tv2) /*返回类型后置语法,这里的auto只是返回类型后置语法的组成部分，并没有类型推导的含义*/
	{
		return tv1 + tv2;
	}
	template<typename T>
	T mydouble(T tmpvalue)
	{
		cout << __FUNCTION__ << "<" << typeid(T).name() << ">" << '\n';
		return tmpvalue * 2;
	}

	double mydouble(double tmpvalue)
	{
		cout << __FUNCTION__ << '\n';
		return tmpvalue *2;
	}
}

int main(int argc, char* argv[])
{
#if 0
	{
		int subv{ nmsp1_::Sub(3,5) };
		cout << "subv = " << subv << '\n';
		double subv2{ nmsp1_::Sub(4.7,3.1) };
		cout << "subv2 = " << subv2 << '\n';

		//string a("abc"), b("def");
		//string addresult{ nmsp1_::Sub(a,b) }; /*编译出错,模板无法推导出正确的函数*/
	}
#endif 

#if 0
	{
		//double subv0{ nmsp1_::Sub(3,4.2) }; /*编译报错,编译器无法把3(int)自动转换为double,需手动精确匹配*/
		double subv1 { nmsp1_::Sub(static_cast<double>(3), 5.9) };/*强制类型转换可以*/
		double subv2{ nmsp1_::Sub<double>(3, 5.9) };/*指定类型,编译器把 "3" 当作double类型处理*/
	}
#endif

#if 0

	{
		//cout << nmsp1_::Add(15, 17.8) << '\n'; /*编译器无法推导出 V 类型*/
		//cout << nmsp1_::Add<...,...,double>(15, 17.8) << '\n'; /*编译器不支持这种写法,必须指定T和U才能指定V*/
		//cout << nmsp1_::Add<int,double,double>(15, 17.8) << '\n';
		//cout << nmsp1_::Add<double,...,double>(15, 17.8) << '\n'; /*编译器不支持这种写法,不能跨过中间某一个或多个*/
		//cout << nmsp1_::Add<double>(15, 17.8) << '\n'; /*把 V 放前面,让 T 和 U 自动推导*/
		cout << nmsp1_::Add(15, 17.8) << '\n'; /*让编译器自动推导返回值类型*/

	}

#endif

#if 1

	{
		cout << nmsp1_::mydouble(15) << '\n'; /*可以推断出T类型是int*/
		//int result2 { nmsp1_::mydouble<int>(16.9) };
		//cout << result2 << '\n';
		//auto result3{ nmsp1_::mydouble<>(16.9) };//此种场合下，空的<>没有用处，但语法上允许
		//cout << result3 << '\n';
		auto result4{ nmsp1_::mydouble(16.9) }; //调用的是普通函数，对于编译器，模板也合适，普通也合适，编译器会优先调用普通函数
		cout << result4 << '\n';
		auto result3{ nmsp1_::mydouble<>(16.9) };//<>作用就是告诉编译器，调用mydouble函数模板。
		cout << result3 << '\n';
	}

#endif
	_CRT_UNUSED(getchar());
	return 0;
}

/*

一：基本范例
	a)模板的定义是以template关键字开头。
	b)类型模板参数T前面用typename来修饰，所以，遇到typename就该知道其后面跟的是一个类型。
			typename可以被class取代，但此处的class并没有“类”
	c)类型模板参数T（代表是一个类型）以前前面的修饰符typename/class都用<>括起来
	d)T这个名字可以换成任意其他标识符，对程序没有 影响。用T只是一种编程习惯。

*/

/*

二：实例化
	实例化：编译时，用具体的“类型”代替“类型模板参数”的过程就叫做实例化（有人也叫代码生成器）。
	 .obj文件在编译完成后就会产生
	 .obj文件的格式一般会被认为是一种COFF——通用对象文件格式（Common Object File Format）。
	int  Sub<int>(int,int)
	double Sub<double>(double,double)
	 实例化之后的函数名分别叫做Sub<int>和Sub<double>
	通过函数模板实例化之后的函数名包含三部分：
	   a)模板名；b)后面跟着一对<>；c)<>中间是一个或多个具体类型。
		 编译期间。
		在编译阶段，编译器就会查看函数模板的 函数体 部分，来确定能否针对该类型string进行Sub函数模板的实例化。
		 在编译阶段，编译器需要能够找到函数模板的函数体部分。
*/

/*

三：模板参数的推断
	（3.1）常规的参数推断
	  通过<>可以只指定一部分模板参数的类型，另外一部分模板参数的类型可以通过调用时给的实参来推断。
	  auto代替函数模板返回类型
		decltype,可以与auto结合使用来构成返回类型后置语法。这种后置语法其实也就是使用auto和decltype结合来完成返回值类型的推导。
	（3.2）各种推断的比较以及空模板参数列表的推断
		a)自动推断
		b)指定类型模板参数,优先级比自动推断高
		c)指定空模板参数列表<>：作用就是 请调用mydouble函数模板而不是调用普通的mydouble函数。
*/
