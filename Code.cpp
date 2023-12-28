#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<time.h>
#include<stack>
#include <queue>
#include<Windows.h>
using namespace std;
queue<int> Q;//������� ��� �������� ���������� ������ 
queue<int> Q2;
int SizeG, check, back = 0;
void DelLast() {//������� �������� ������� � ������
	int x = Q.size() - 1;
	for (int i = 0; i < x; i++) {
		Q2.push(Q.front());
		Q.pop();}
	Q.pop();
	while (!Q2.empty()) {
		Q.push(Q2.front());
		Q2.pop();}}
int FordFulkersonAlg(int v, int** g, int* NUM) {
	NUM[v] = 1;
	Q.push(v);
	if (v != SizeG - 1) {//�������� �� ���������� �������� �������
		int count = 0;
		for (int i = 0; i < SizeG; i++) {
			if (g[v][SizeG - 1] > 0 && NUM[SizeG - 1] == -1 && check != 1) {//���� ���� ���� � �������� �������, �� ��������� ������� �������� � ����
				back = 0;
				FordFulkersonAlg(SizeG - 1, g, NUM);
			}//�������� �������������� ���� � �������� �����
			else if (g[v][i] > 0 && NUM[i] == -1 && check != 1) {
				back = 0;//��������� �������� ����� ������������ ��� �������� �� �������� �������
				FordFulkersonAlg(i, g, NUM);
			}//��������  ���� � �������� �����
			else {
				count++;
				if (count == SizeG || back == 1 && i == SizeG - 1) {//���� ����� �� ����� ������� ��� ��������, �� ������� �������� ������� �� ������ � ������������ �����
					DelLast();
					back = 1;//��������� �������� �����
				}}}
		if (count == SizeG) {
			return 0;}}
	else { //���� ���������� �������� �����, �� ��������� �����������, ��������� �������, ��� ����������� ����� ������
		check = 1;
		return 1;}}
void review(int** G) {//����� �������
	cout << "������� ���������\n";
	for (int i = 0; i < SizeG; i++) {
		for (int j = 0; j < SizeG; j++) {
			cout << G[i][j] << " ";}
		cout << "\n";}}
int main() {
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));
	int** G, * DIST, vershina, vibor, max = 0, vivod, GO = 1, maxPotok = 0, c = 0, count;
	cout << "����� ���� �� ������:\n1) ��������������� ��������\n2) �������� � ���������\n3) �������� � ���������\n";
	cin >> check;
	switch (check) {
	case(1)://��������� ��������� �������
		cout << "������� ������ �����: ";
		cin >> SizeG;
		break;
	case(2)://�������� ��������� � ������� �������
		SizeG = 5;
		break;
	case(3)://�������� ��������� � ��������� �� ���������� ������� � �������� �������
		SizeG = 5;
		break;
	default:
		cout << "\n!������!";}
	DIST = new int[SizeG];//������ ���������� ������
	G = new int* [SizeG]; // ������ ��������� ������ 
	for (int i = 0; i < SizeG; i++) {
		G[i] = new int[SizeG];
		for (int j = 0; j < SizeG; j++) {
			G[i][j] = 0;}}
	if (check == 3) { G[0][1] = 60, G[1][2] = 30, G[0][3] = 60, G[3][4] = 60; }
	if (check == 2) { G[0][3] = 20, G[2][3] = 20, G[0][1] = 30, G[2][4] = 30, G[3][4] = 30, G[0][2] = 40, G[1][4] = 40, G[1][2] = 50; }
	if (check == 1) {
		for (int i = 0; i < SizeG - 1; i++) {
			for (int j = 1; j < SizeG; j++) {
				if ((rand() % 10) > 3 && i != j) {//���������� ��������� �������
					G[i][j] = (rand() % 10) * 10;}}}
		for (int i = 0; i < SizeG; i++) {
			count = 0;
			for (int j = 0; j < SizeG; j++) {
				if (G[i][j] == 0) {
					count++;}}
			if (count == SizeG) {
				G[i][SizeG - 1] == (rand() % 10) * 10;}}
		for (int i = 0; i < SizeG; i++) {
			count = 0;
			for (int j = 0; j < SizeG; j++) {
				if (G[j][i] == 0) {
					count++;}}
			if (count == SizeG) {
				G[1][i] == (rand() % 10) * 10;}}}
	check = 0;
	review(G);
	while (GO) {
		c++;
		while (!Q.empty()) {
			Q.pop();}
		for (int i = 0; i < SizeG; i++) {
			DIST[i] = -1;}
		GO = FordFulkersonAlg(0, G, DIST);
		check = 0;
		if (GO != 0 && !Q.empty()) {
			int Minimum = 0, operand1 = Q.front(), operand2;
			Q2.push(operand1);
			Q.pop();
			while (!Q.empty()) {
				operand2 = Q.front();
				Q.pop();
				if (G[operand1][operand2] < Minimum) {
					Minimum = G[operand1][operand2];}
				else if (Minimum == 0) {
					Minimum = G[operand1][operand2];}
				operand1 = operand2;
				Q2.push(operand1);}
			cout << "����� = " << Minimum << "\n";
			while (!Q2.empty()) {
				Q.push(Q2.front());
				Q2.pop();}
			maxPotok += Minimum;
			operand1 = Q.front();
			cout << "����� ������: " << Q.front() + 1;
			Q.pop();
			while (!Q.empty()) {
				operand2 = Q.front();
				cout << " " << Q.front() + 1;
				Q.pop();
				G[operand1][operand2] -= Minimum;
				G[operand2][operand1] += Minimum;
				operand1 = operand2;}
			cout << "\n_____________________________________________\n";
			review(G);}
		if (c > SizeG+1) {
			GO = 0;}}
	cout << "������������ ����� ����� " << maxPotok << "\n";
	system("pause");
	return 0;}
