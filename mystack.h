#pragma once
#include<iostream>
template<class t>
class mystack {
private:
	t* pfir;
	size_t len;
	size_t maxlen;
	//size_t ���ͱ�ʾC���κζ������ܴﵽ����󳤶�
	//size_t �������±���ڴ������֮��ĵط��㷺ʹ��
public:
	mystack() { pfir = NULL; len = 0; maxlen = 0; }
	~mystack() { if (pfir)delete[] pfir; pfir = NULL; len = 0; maxlen = 0; }
	void push(const t& data);
	void pop() { len--; }
	t gettop() { return pfir[len - 1]; }
	bool empty() {
		if (len == 0)return true;
		else return false;
	}
};

template<class t>
//��ջ����ʵ��
void mystack<t>::push(const t& data) {
	if (len <= maxlen) {
		maxlen = maxlen + ((maxlen >> 1) > 1 ? (maxlen >> 1) : 1);
		/*
		��Ŀ�����:   <���ʽ1> ? <���ʽ2> : <���ʽ3>;
		����ֵ��������ʽ 1 ��ֵ�����Ϊ�棬��ִ�б��ʽ 2��
		�����ر��ʽ 2 �Ľ����
		������ʽ 1 ��ֵΪ�٣���ִ�б��ʽ 3��
		�����ر��ʽ 3 �Ľ����

		λ���㣺>>1 ��ʾ����������1λ���൱�ڳ���2
		����ڴ�����ֱ��ʹ��(+��-��*��/)�������
		���������λ�������������ߴ����ڻ����ϵ�ִ��Ч�ʡ�
		*/
		t* ptemp = new t[maxlen];
		if (pfir) {
			memcpy(ptemp, pfir, sizeof(t) * len);
			delete[] pfir;
		}
		pfir = ptemp;
	};
	pfir[len++] = data;
}
