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
	/*�����汾*/
	template<typename T,typename U> /* void nmsp2_::tfunc<char const *,int>(char const * &,int &) */
	void tfunc(T& tmprv,U& tmprv2) {
		cout << "---------------------------begin---------------------------\n";
		auto type1 { typeid(tmprv).name() };
		auto type2 { typeid(tmprv2).name() };
		cout << "template<typename T,typename U>\n" <<
			__FUNCTION__ << '<' << type1 << "," << type2 <<
			">(" << type1 << "& tmprv," << type2 << "& tmprv2) Generalization(����)\n\n";

		cout << "tmprv = " << tmprv << "\ntmprv2 = " << tmprv2 << '\n';
		cout << "---------------------------end---------------------------\n\n";

	}

	/*ȫ�ػ�*/
	template<> /*ȫ�ػ�<>����Ϊ��*/
	void tfunc<int, double>(int& tmprv, double& tmprv2)	/*<int, double>����ʡ�ԣ���Ϊ����ʵ�ο�����ȫ�Ƶ���T��U�����͡�*/
	//void tfunc(int& tmprv, double& tmprv2)
	{
		cout << "---------------------------begin---------------------------\n";
		auto type1{ typeid(tmprv).name() };
		auto type2{ typeid(tmprv2).name() };
		cout << "template<typename T,typename U>\n" <<
			__FUNCTION__ << '<' << type1 << "," << type2 <<
			">(" << type1 << "& tmprv," << type2 << "& tmprv2) full specialization(ȫ�ػ�)\n\n";

		cout << "tmprv = " << tmprv << "\ntmprv2 = " << tmprv2 << '\n';
		cout << "---------------------------end---------------------------\n\n";
	}

	/*���غ���*/
	void tfunc(int& tmprv, double& tmprv2)
	{
		cout << "---------------------------begin---------------------------\n";
		cout << __FUNCTION__ << '(' << typeid(tmprv).name() <<
			"& tmprv, " << typeid(tmprv2).name() << "& tmprv2)\n";
		cout << "---------------------------end---------------------------\n\n";
	}

	/*��ģ����������ϵ�ƫ�ػ�*/
	//template< typename U>
	//void tfunc<double,U>(double& tmprv, U& tmprv2)
	//{

	//}

	/*������tfunc<double,U>ƫ�ػ���tfunc���ذ汾*/
	template<typename U>
	void tfunc(double& tmprv, U& tmprv2)
	{
		auto type{ typeid(U).name() };
		auto pram_type1{ typeid(tmprv).name() };
		auto pram_type2{ typeid(tmprv2).name() };
		cout << "---------------------------begin---------------------------\n";
		cout << "������tfunc<double, U>ƫ�ػ���tfunc���ذ汾\n";
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


//��һ�� ����ģ��
//4������
//����������ģ�壩������ͬ�����ǲ����������߲��������ϲ�ͬ��
//����ģ��ͺ���Ҳ����ͬʱ����,��ʱ���԰Ѻ���������һ������,����ͨ�����ͺ���ģ�嶼�ȽϺ��ʵ�ʱ�򣬱�����������ѡ����ͨ������ִ�С�
 //���ѡ������ʣ������⣩�ĺ���ģ��/�������������ڲ��бȽϸ��ӵ�������򣬹���Ҳ�ڲ��ϸ��¡�

//5���ػ�
//�����������汾�������ڻ��ģ�����ġ���������£�д�ĺ���ģ�嶼�Ƿ����ĺ���ģ�塣
//�ػ����ػ��汾�������������Ŵӷ����汾�г������һ���Ӽ���
//��5.1��ȫ�ػ������ǰ�tfunc��������汾�е�����ģ��������þ�������������湹�ɵ�һ������İ汾��ȫ�ػ��汾����
 //ȫ�ػ�ʵ���ϵȼ���ʵ����һ������ģ�壬�����ȼ���һ���������ء�
//void tfunc<int ,double>(int& tmprv, double& tmprv2){......}  //ȫ�ػ�������
//void tfunc(int& tmprv, double& tmprv2) { ...... }  //���غ���������
//���������ǵ�˳������ѡ����ͨ������Ȼ��Żῼ�Ǻ���ģ����ػ��汾�����Żῼ�Ǻ���ģ��ķ����汾��
//��5.2��ƫ�ػ����ֲ��ػ���
//����������˵��һ����ģ����������ϵ�ƫ�ػ���һ����ģ�������Χ�ϵ�ƫ�ػ���
//a)ģ����������ϵ�ƫ�ػ����������tfunc����ģ�壬��һ��ģ���������Ϊdouble���ڶ���ģ��������ػ���
  //ʵ���ϣ���ģ���������������������ģ�岻��ƫ�ػ�������ᵼ�±������
//b)ģ�������Χ�ϵ�ƫ�ػ���
 //��Χ�ϣ�int->const int�����ͱ�С��   T->T*��T->T&��T->T&&�����T���ͣ������ͷ�Χ�϶���С�ˡ�
   //ʵ���ϣ����ں���ģ��������Ҳ������ģ�������Χ�ϵ�ƫ�ػ�����Ϊ������νģ�������Χ�ϵ�ƫ�ػ���ʵ�����Ǻ���ģ������ء�
//c��ͨ������ʵ��ģ����������ϵ�ƫ�ػ�

//����������ģ��ʱ��������ģ�壬���Ǵ���ģ�������Χ�ϵ�ƫ�ػ��Լ������ϵ�ƫ�ػ�����������ϸ���⡣
