#include <iostream>
#include <string>

using namespace std;

namespace nmsp1_
{
	//template<typename T> /*T:��Ϊ ���� ģ����� ��������һ������*/
	template<class T> /*class ����ȡ��typename���������class��û�� ���ࡱ ����˼*/
						/*T������ֿ���������*/
	T Sub(T tv1, T tv2)
	{
		return tv1 - tv2;
		//return tv1 + tv2;
	}

	//template<typename T ,typename U ,typename V >
	//template<typename V ,typename T, typename U>
	template<typename T, typename U>
	//V Add(T tv1,U tv2)
	auto Add(T tv1, U tv2)	/* auto���ڱ���Ƶ�����ֵ���͵ĺ��� */
	//auto Add(T tv1, U tv2) -> decltype(tv1 + tv2) /*�������ͺ����﷨,�����autoֻ�Ƿ������ͺ����﷨����ɲ��֣���û�������Ƶ��ĺ���*/
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
		//string addresult{ nmsp1_::Sub(a,b) }; /*�������,ģ���޷��Ƶ�����ȷ�ĺ���*/
	}
#endif 

#if 0
	{
		//double subv0{ nmsp1_::Sub(3,4.2) }; /*���뱨��,�������޷���3(int)�Զ�ת��Ϊdouble,���ֶ���ȷƥ��*/
		double subv1 { nmsp1_::Sub(static_cast<double>(3), 5.9) };/*ǿ������ת������*/
		double subv2{ nmsp1_::Sub<double>(3, 5.9) };/*ָ������,�������� "3" ����double���ʹ���*/
	}
#endif

#if 0

	{
		//cout << nmsp1_::Add(15, 17.8) << '\n'; /*�������޷��Ƶ��� V ����*/
		//cout << nmsp1_::Add<...,...,double>(15, 17.8) << '\n'; /*��������֧������д��,����ָ��T��U����ָ��V*/
		//cout << nmsp1_::Add<int,double,double>(15, 17.8) << '\n';
		//cout << nmsp1_::Add<double,...,double>(15, 17.8) << '\n'; /*��������֧������д��,���ܿ���м�ĳһ������*/
		//cout << nmsp1_::Add<double>(15, 17.8) << '\n'; /*�� V ��ǰ��,�� T �� U �Զ��Ƶ�*/
		cout << nmsp1_::Add(15, 17.8) << '\n'; /*�ñ������Զ��Ƶ�����ֵ����*/

	}

#endif

#if 1

	{
		cout << nmsp1_::mydouble(15) << '\n'; /*�����ƶϳ�T������int*/
		//int result2 { nmsp1_::mydouble<int>(16.9) };
		//cout << result2 << '\n';
		//auto result3{ nmsp1_::mydouble<>(16.9) };//���ֳ����£��յ�<>û���ô������﷨������
		//cout << result3 << '\n';
		auto result4{ nmsp1_::mydouble(16.9) }; //���õ�����ͨ���������ڱ�������ģ��Ҳ���ʣ���ͨҲ���ʣ������������ȵ�����ͨ����
		cout << result4 << '\n';
		auto result3{ nmsp1_::mydouble<>(16.9) };//<>���þ��Ǹ��߱�����������mydouble����ģ�塣
		cout << result3 << '\n';
	}

#endif
	_CRT_UNUSED(getchar());
	return 0;
}

/*

һ����������
	a)ģ��Ķ�������template�ؼ��ֿ�ͷ��
	b)����ģ�����Tǰ����typename�����Σ����ԣ�����typename�͸�֪������������һ�����͡�
			typename���Ա�classȡ�������˴���class��û�С��ࡱ
	c)����ģ�����T��������һ�����ͣ���ǰǰ������η�typename/class����<>������
	d)T������ֿ��Ի�������������ʶ�����Գ���û�� Ӱ�졣��Tֻ��һ�ֱ��ϰ�ߡ�

*/

/*

����ʵ����
	ʵ����������ʱ���þ���ġ����͡����桰����ģ��������Ĺ��̾ͽ���ʵ����������Ҳ�д�������������
	 .obj�ļ��ڱ�����ɺ�ͻ����
	 .obj�ļ��ĸ�ʽһ��ᱻ��Ϊ��һ��COFF����ͨ�ö����ļ���ʽ��Common Object File Format����
	int  Sub<int>(int,int)
	double Sub<double>(double,double)
	 ʵ����֮��ĺ������ֱ����Sub<int>��Sub<double>
	ͨ������ģ��ʵ����֮��ĺ��������������֣�
	   a)ģ������b)�������һ��<>��c)<>�м���һ�������������͡�
		 �����ڼ䡣
		�ڱ���׶Σ��������ͻ�鿴����ģ��� ������ ���֣���ȷ���ܷ���Ը�����string����Sub����ģ���ʵ������
		 �ڱ���׶Σ���������Ҫ�ܹ��ҵ�����ģ��ĺ����岿�֡�
*/

/*

����ģ��������ƶ�
	��3.1������Ĳ����ƶ�
	  ͨ��<>����ָֻ��һ����ģ����������ͣ�����һ����ģ����������Ϳ���ͨ������ʱ����ʵ�����ƶϡ�
	  auto���溯��ģ�巵������
		decltype,������auto���ʹ�������ɷ������ͺ����﷨�����ֺ����﷨��ʵҲ����ʹ��auto��decltype�������ɷ���ֵ���͵��Ƶ���
	��3.2�������ƶϵıȽ��Լ���ģ������б���ƶ�
		a)�Զ��ƶ�
		b)ָ������ģ�����,���ȼ����Զ��ƶϸ�
		c)ָ����ģ������б�<>�����þ��� �����mydouble����ģ������ǵ�����ͨ��mydouble������
*/
