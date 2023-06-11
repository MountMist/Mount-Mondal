/*
--------READ ME FIRST-------
���ܣ�
������ʹ�����������������ջʵ���Թ��Զ�Ѱ·
�������û����Թ���Ϸ���ǳ����Զ�Ѱ·��
�Թ��ɳ����еĶ�ά������������Խ����޸ģ�Ѱ·������Ȼ��Ч
ʹ��easyX�����˼򵥵�ͼ�ν��棬������ʾ��������·����Ҳ�������ַ��������������ʾ
��������ͼ���زľ��������ֻ� hhhh��
Ϊ�������û��Ļ�������У���������Ϊ�ɹ�Ѱ·���û�����һ����һ��ֱ���ߵ��յ�
���������ͼ����ʼ���޽⣬�����ʾ��δ�ҵ�·����

���㣺
������ֻ��Ѱ��һ�����е�·��������֤�ڶ���·������������Ѱ�ҵ�����·��
����������Ĺ����п��ܴ���һЩ��ֵĵط�����Ϊ���������ж������������޸�
��������ĳЩ�ط������˽϶����߸�Ϊ��Ϥ��C���Է��C++�ķ�װ���д����
----------------------
*/
#include<stdio.h>
#include<iostream>
#include<graphics.h>
#include"mystack.h"
using namespace std;
//�����ͼ��С������������
#define ROWS 10
#define COLS 10
//����ÿһ�����ӵĴ�С
#define SPACE 70
//����ͼƬ
IMAGE road, path, wall,start,finish;
//ö��Ѱ·������ڱ�0123��������
enum direct{tup,tdown,tleft,tright};
//��Ǳ������ڼ�¼�Ƿ�ɹ�Ѱ·
bool successfind = false;
bool flag = false;
struct pathnode {
	int dir;	//Ѱ·����
	bool vis;	//�Ƿ��Ѿ����ʹ�
};
struct cpoint {
	int row;
	int col;
};
void printmap(int map[ROWS][COLS]){
	//�ַ�������ʾ��ͼ
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < ROWS; j++) {
			if (map[i][j] == 0)
				cout << "  ";
			else if (map[i][j] == 1)
				cout << "ǽ";
		}
		cout << endl;
	}
};
void showmap(int map[ROWS][COLS]) {
	//ͼ�ν�����ʾ��ͼ
	for (int i = 0; i < ROWS; i++) {		//y������
		for (int j = 0; j < ROWS; j++) {	//x������
			if (map[i][j] == 0)
				putimage(j * SPACE, i * SPACE, &road);
			else if (map[i][j] == 1)
				putimage(j * SPACE, i * SPACE, &wall);
			else if (map[i][j] == 2)
				putimage(j * SPACE, i * SPACE, &path);
			else if (map[i][j] == 3)
				putimage(j * SPACE, i * SPACE, &finish);
			else if (map[i][j] == 4)
				putimage(j * SPACE, i * SPACE, &start);
		}
		cout << endl;
	}
};
int main()
{
	//����ͼ�δ���
	initgraph(COLS*SPACE,ROWS*SPACE,1);
	loadimage(&road,"road.png", SPACE, SPACE, true);
	loadimage(&wall, "wall.png", SPACE, SPACE, true);
	loadimage(&path, "path.png", SPACE/2, SPACE/2, true);
	loadimage(&start, "start.png", SPACE, SPACE, true);
	loadimage(&finish, "finish.png", SPACE, SPACE, true);
	//�����ͼ��1��ʾǽ��0��ʾ·
	int map[ROWS][COLS] = {
		{1,1,1,1,1,1,1,1,1,1},
		{1,0,1,0,1,1,0,0,0,1},
		{1,0,1,0,1,1,0,1,0,1},
		{1,0,1,0,0,0,0,1,0,1},
		{1,0,1,0,1,1,0,1,0,1},
		{1,0,1,1,1,1,0,1,0,1},
		{1,0,1,0,1,0,0,1,0,1},
		{1,0,1,0,1,0,1,1,0,1},
		{1,0,1,0,0,0,1,1,0,1},
		{1,1,1,1,1,1,1,1,1,1}
	};
	pathnode vismap[ROWS][COLS];
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			vismap[i][j].dir = 0;
			vismap[i][j].vis = false;
		}
	}
	//�ȳ�ʼ����ͼ��ÿ���㣬����Ϊδ���ʣ��ҳ�ʼѰ·����Ϊ��
	cpoint beginpoint = { 1,1 };

	cpoint endpoint = { 8,8 };
	
	//���������Ϊ�ѷ���
	vismap[beginpoint.row][beginpoint.col].vis = true;
	cpoint current = beginpoint;
	cpoint next;
	//����һ��point���͵�ջ��׼����������ʹ��
	mystack<cpoint>stack;
	stack.push(beginpoint);//�����ջ
	printmap(map);
	showmap(map);
	
	while (1) {
		//ȷ����ǰѰ·��ʼ��
		next = current;
		//������һ��Ѱ·����
		
		switch (vismap[current.row][current.col].dir)
		{
		case tup:	
			next.row--;//�ƶ�������
			vismap[current.row][current.col].dir++;//��ǰ������Ѱ�ң�׼����һ������
			if (map[next.row][next.col] == 0 && vismap[next.row][next.col].vis == false)
			{
				//�����һ���ǿ�����·����0����δ�����ʹ���vis==false��
				current = next;//���ߵ���һ��
				vismap[current.row][current.col].vis = true;//��ǵ�ǰ��Ϊ�ѷ���
				stack.push(current);//��ջ���浱ǰ�ֳ�
				
			}
			break;
		case tdown:
			next.row++;
			vismap[current.row][current.col].dir++;//��ǰ������Ѱ�ң�׼����һ������
			if (map[next.row][next.col] == 0 && vismap[next.row][next.col].vis == false)
			{
				//�����һ���ǿ�����·����0����δ�����ʹ���vis==false��
				current = next;//���ߵ���һ��
				vismap[current.row][current.col].vis = true;//��ǵ�ǰ��Ϊ�ѷ���
				stack.push(current);//��ջ���浱ǰ�ֳ�
				
			}
			break;
		case tleft:	
			next.col--;
			vismap[current.row][current.col].dir++;//��ǰ������Ѱ�ң�׼����һ������
			if (map[next.row][next.col] == 0 && vismap[next.row][next.col].vis == false)
			{
				//�����һ���ǿ�����·����0����δ�����ʹ���vis==false��
				current = next;//���ߵ���һ��
				vismap[current.row][current.col].vis = true;//��ǵ�ǰ��Ϊ�ѷ���
				stack.push(current);//��ջ���浱ǰ�ֳ�
				
			}
			break;
			
			//ǰ���������߼�Ϊ���������ߵ���һ�����������򻻵���һ��Ѱ·����
			//���һ��������߼�Ϊ���������ߵ���һ������������˵���˴�Ϊ��·�����ٻ�����һ������

		case tright:
			next.col++;
			
			if (map[next.row][next.col] == 0 && vismap[next.row][next.col].vis == false)
			{
				//�����һ���ǿ�����·����0����δ�����ʹ���vis==false��
				current = next;//���ߵ���һ��
				vismap[current.row][current.col].vis = true;//��ǵ�ǰ��Ϊ�ѷ���
				stack.push(current);//��ջ���浱ǰ�ֳ�
			
			}
			else {//��·����Ҫ���ݶ���
				stack.pop();
				current = stack.gettop();
			}
			break;
		
		default:
			break;
		}
		if (current.row == endpoint.row && current.col == endpoint.col) {
			successfind = true;
			flag = true;
			//�����ǰ������յ㣬��Ѱ·�ɹ�������Ѱ��
		}
		if (stack.empty())flag = true;//�������Ϊ�գ���δ�ҵ�·����Ҳ����Ѱ��

		if(flag==true)break;
		
	}
	if (successfind == true) {
		
		cout << "�ɹ��ҵ�·��:" << endl;
		//·���㶼�����ջ�У����ջ��Ԫ�ؼ�Ϊ·���ϸ����������
		cout << "���";
		while (!stack.empty()) {
			map[stack.gettop().row][stack.gettop().col] = 2;
			map[1][1] = 3;
			map[8][8] = 4;
			//Ϊ����ʾ��ʼ���롰�ա������������������޸ģ�����ǰ�����û��������
			showmap(map);
			cout << "(" << stack.gettop().row << "," << stack.gettop().col << ")->";
			stack.pop();
			system("pause");
		}
		cout << "�յ�" << endl;
	}
	else {
		map[1][1] = 3;
		map[8][8] = 4;
		//Ϊ����ʾ��ʼ���롰�ա������������������޸ģ�����ǰ�����û��������
		showmap(map);
		cout << "δ�ҵ�·����" << endl;
	} 
	system("pause");
	return 0;
}