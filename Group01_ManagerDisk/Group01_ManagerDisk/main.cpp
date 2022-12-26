#include <iostream>
#include <string.h>
#include <iomanip>
#include <fstream>
#include<istream>
#include<conio.h>
#include<stdio.h>
#include<Windows.h>
#include "console.h" 
#include <conio.h>

using namespace std;
const int MAX = 100;

#define tuong_duoi 20
#define tuong_phai 100


typedef struct theLoai* NODETL;
typedef struct bangDia* NODEDia;

//banner nhom
void vetuong()
{
	TextColor(15);
	//ve tuong
	//tren 
	for (int i = 20; i < tuong_phai + 1; i++)
	{
		gotoXY(i, 0);
		putchar(220); //ma ascii
	}
	//trai
	for (int i = 1; i < tuong_duoi; i++)
	{
		gotoXY(20, i);
		putchar(219);
	}
	//duoi
	for (int i = 20; i < tuong_phai + 1; i++)
	{
		gotoXY(i, tuong_duoi);
		putchar(223);
	}
	//phai
	for (int i = 1; i < tuong_duoi; i++)
	{
		gotoXY(tuong_phai, i);
		putchar(219);
	}
}

void thanhVien()
{
	TextColor(12);
	gotoXY(30, tuong_duoi / 10);
	cout << "NHOM 01: The Store's Movie Disc Management Program";
	gotoXY(45, (tuong_duoi / 10) + 1);
	cout << "Luong Minh Nhat - 20110391 ";
	gotoXY(45, (tuong_duoi / 10) + 2);
	cout << "Nguyen Tan Phuoc - 2011392 ";
	gotoXY(45, (tuong_duoi / 10) + 3);
	cout << "Tang Tam Nhu - 20110431 ";
	gotoXY(45, (tuong_duoi / 10) + 4);
	cout << "Le Diep Tri - 20110421 ";


	TextColor(15);
	for (int i = 21; i < tuong_phai; i++)
	{
		gotoXY(i, 7);
		putchar(220); //ma ascii
	}


}

struct cuaHang
{
	char ten[30];
	char diachi[60];
	char sdt[30];
	NODETL dstheloai; //cua hang co nhieu the loai => nhieu dia (lien ket toi the loai cua sach)
};

struct theLoai
{
	int sodia;
	char ten[200]; //ten the loai
	NODETL nextTL; //con tro lien ket toi the loai dia
	NODEDia dsDia; //con tro lien ket toi ds dia (dia do thuoc the loai nao)
};

struct bangDia
{
	char Maso[10];
	char ten[200];
	char namphathanh[5];
	char daoDien[200];
	char dienVien[200];
	NODEDia nextDia; //con tro lien ke toi dia tiep theo trong ds
};

//tao danh sach the loai
NODETL create_dsDia(int i) {
	NODETL p = new theLoai;
	cin.ignore();
	cout << left << "- Nhap ten the loai " << i + 1 << ": " << setw(1) << "";
	cin.getline(p->ten, 200);
	cout << setw(24) << left << " + Nhap so luong dia: ";
	cin >> p->sodia;
	p->dsDia = NULL;
	p->nextTL = NULL;
	return p;
}

//tao danh sach dia
NODEDia create_Dia(int j) {
	NODEDia p = new bangDia;
	cin.ignore();
	cout << left << "  Lan " << j + 1 << ": " << endl;
	cin.ignore();
	cout << setw(25) << left << "\tNhap ma so dia: ";
	cin.getline(p->Maso, 10);
	cout << setw(25) << left << "\tNhap ten dia: ";
	cin.getline(p->ten, 200);
	cout << setw(25) << left << "\tNhap nam phat hanh: ";
	cin.getline(p->namphathanh, 5);
	cout << setw(25) << left << "\tNhap ten dao dien: ";
	cin.getline(p->daoDien, 200);
	cout << setw(25) << left << "\tNhap ten dien vien: ";
	cin.getline(p->dienVien, 200);
	cout << setw(25) << left << "        --------------" << endl;
	p->nextDia = NULL;

	return p;
}

void inIt(cuaHang& CH) {
	CH.dstheloai = NULL;
}

void nhapCuaHang(cuaHang& a)
{
	fstream f;
	f.open("thongtincuahang.txt");
	f.ignore();
	f.getline(a.ten, 30);
	f.getline(a.diachi, 60);
	f >> a.sdt;
	f.close();
}

void xuatCuaHang(cuaHang a)
{
	cout << "Ten cua hang: " << a.ten << endl;
	cout << "Dia chi: " << a.diachi << endl;
	cout << "Sdt: " << a.sdt << endl;
	cout << "---------------------------------" << endl;
}

void xuatDSdia(cuaHang CH)
{
	NODETL listTL = CH.dstheloai;	//khoi tao danh sach cac the loai cua CH
	NODEDia listDia;				//khoi tao danh sach cac dia trong CH

	cout << "\n------------------------------------------------------------------------------------------------------------\n";
	cout
		<< left	<< setw(17)	<< "The Loai" << "|   " << left	<< setw(12)	<< "Ma So Dia" << "|    " << left << setw(12) 
		<< "Ten Dia" << "|   " << left << setw(15) << "Nam Phat Hanh" << "|   "	<< left	<< setw(16)
		<< "Ten Dao Dien" << "|   "	<< left	<< setw(12)	<< "Ten Dien Vien" << "|   "
		<< "\n------------------------------------------------------------------------------------------------------------\n";
	while (listTL != NULL)		//check ds cac the loai khac rong
	{
		listDia = listTL->dsDia;	//gan du lieu danh sach dia theo tung the loai
		if (listTL->sodia == 0)		//neu the loai ko co dia -> xuat ra rong
		cout << "Empty!!!" << endl;

		while (listDia != NULL) {
			cout
				<< left	<< setw(17)	<< listTL->ten << "|     " << left << setw(10) << listDia->Maso << "|    "
				<< left	<< setw(12)	<< listDia->ten << "|      " << left << setw(12) << listDia->namphathanh << "|       "
				<< left	<< setw(12)	<< listDia->daoDien << "|   " << left << setw(13) << listDia->dienVien <<"|"
				<< "\n------------------------------------------------------------------------------------------------------------\n";
			listDia = listDia->nextDia;		//tro toi danh sach dia tiep theo trong cung the loai
		}
		
		listTL = listTL->nextTL;		//tro toi the loai tiep theo trong danh sach the loai dia
	}
}

//ham them the loai dia hoac them dia theo the loai
void Add(cuaHang& CH)
{

	NODETL listTL = CH.dstheloai; //khoi tao danh sach cac the loai cua CH
	NODEDia listDia; //khoi tao danh sach cac dia trong CH
	int a;
	do {
		cout << "----- Nhap 1 de them the loai, nhap 2 de them dia -----" << "\nChon: ";
		cin >> a;
	} while (a != 1 && a != 2);
	switch (a)
	{
	case 2: {
		int j = 0;
		bool flap = true; //check the loai da ton tai hay chua(true: chua co, false:co roi)
		char tenth[200]; //ten the loai
		cout << " +  the loai cua dia can them: ";
		cin.ignore(); // xoa bo nho de tang toc vung nho
		cin.getline(tenth, 200); //nhap ten tl
		while (listTL != NULL)
		{
			if (strcmp(tenth, listTL->ten) == 0) //so sanh ten the loai vua nhap voi danh sach the loai ton tai trong CH (neu nhap dia thuoc the loai hoat hinh ma khong co trong CH thi tu choi thuc hien nhap)
			{
				listDia = listTL->dsDia; //lay danh sach dia thuoc the loai trong CH
				cout << "Nhap dia can them: "; //neu ten the loai nhap co ton tai trc do trong danh sach cua CH se xuat hien dong nay
				listTL->sodia++; //tang so luong dia vao the loai vua nhap
				if (listDia == NULL) { //neu ds dia rong
					listTL->dsDia = create_Dia(j); //tao 1 danh sach dia moi 
				}
				else {
					while (listDia->nextDia != NULL)
						listDia = listDia->nextDia;
					listDia->nextDia = create_Dia(j); //them 1 dia vao cuoi danh sach
				}
				flap = false;
				break; //thoat vong lap danh sach dia
			}
			listTL = listTL->nextTL; //tro toi the loai tiep theo trong danh sach
		}
		if (flap)
			cout << "\nKhong co the loai nay!" << endl;
		break;
	}
	case 1: {
		int i = 1;
		listTL = CH.dstheloai;
		if (listTL == NULL) //check rong cac the loai trong CH
			CH.dstheloai = create_dsDia(i); //tao 1 danh sach the loai moi trong CH
		else {
			while (listTL->nextTL != NULL) //duyet toi cuoi danh sach the loai
			{
				listTL = listTL->nextTL; //van duyet toi cuoi
				i++; //so luong the loai
			}
			listTL->nextTL = create_dsDia(i); //tao moi dia theo the loai tiep theo
			for (int j = 0; j < listTL->nextTL->sodia; j++) //lap so luong dia trong the loai tiep theo cua danh sach
			{
				listDia = listTL->nextTL->dsDia; //tro toi danh sach dia trong the loai tiep theo
				if (listDia == NULL) { //node hien tai co phai la node cuoi cung trong danh sach ko (neu == null: node cuoi)
					listTL->nextTL->dsDia = create_Dia(j); //them moi dia vao danh sach dia cua the loai tiep theo 
				}
				else {
					while (listDia->nextDia != NULL) //duyet tu dau den cuoi danh sach dia
						listDia = listDia->nextDia;
					listDia->nextDia = create_Dia(j); //tao dia tai node cuoi cung 
				}
			}
		}
	}
	default:
		break;
	}
}

void xoaDia(cuaHang& CH) {
	NODETL listTL = CH.dstheloai; ////khoi tao danh sach cac the loai cua CH
	NODEDia listDia; //khoi tao danh sach cac dia trong CH
	bool flap = true; //check the loai da ton tai hay chua(true: chua co, false:co roi)
	char tenxoa[200]; //ten the loai can xoa
	cout << "-  the loai cua dia can xoa: ";
	cin.ignore();
	cin.getline(tenxoa, 200);
	while (listTL != NULL) //check ds the loai rong
	{
		if (strcmp(tenxoa, listTL->ten) == 0) //so sanh ten the loai vua nhap voi danh sach the loai ton tai trong CH (neu nhap dia thuoc the loai hoat hinh ma khong co trong CH thi tu choi thuc hien nhap)
		{
			listDia = listTL->dsDia; //lay danh sach dia thuoc the loai trong CH
			char xoa[200]; //lay danh sach dia thuoc the loai trong CH
			cout << " + Ten cua dia can xoa: "; //neu ten the loai nhap co ton tai trc do trong danh sach cua CH se xuat hien dong nay
			cin.getline(xoa, 200);
			listTL->sodia--; //giam so luong dia vao the loai vua nhap
			if (strcmp(listDia->ten, xoa) == 0) { //kiem tra ten can xoa co ton tai trong danh sach dia hay ko
				NODEDia p = listDia;
				listTL->dsDia = listDia->nextDia; //xoa danh sach dia co trong the loai
				flap = false;
			}
			else
				while (listDia != NULL) //danh sach dia co ton tai
				{
					if (strcmp(listDia->nextDia->ten, xoa) == 0) { //kiem tra ten can xoa co ton tai trong danh sach dia hay ko
						NODEDia p = listDia->nextDia; //gan p la node can xoa
						listDia->nextDia = listDia->nextDia->nextDia;//xoa dia trong danh sach dia
						delete p; //giai phong vung nho cua node vua xoa
						flap = false;
					}
					listDia = listDia->nextDia;
				}
		}
		listTL = listTL->nextTL;
	}
	if (flap)
		cout << "\nKhong xoa thanh cong!!!" << endl;
	else
		cout << "\nXoa thanh cong!!!" << endl;
}

void search(cuaHang CH) {
	NODETL listTL = CH.dstheloai; //khoi tao danh sach cac the loai cua CH
	NODEDia listDia; //khoi tao danh sach cac dia trong CH
	bool flap = false; //check the loai da ton tai hay chua(true: chua co, false:co roi)

	int a;
	do {
		cout << "----- Nhap 1 de tim theo ten, nhap 2 de tim theo maso, nhap 3 de tim theo dien vien ------" << endl << "\nChon: ";
		cin >> a;
	} while (a != 1 && a != 2 && a != 3);
	switch (a)
	{
	case 1: {
		char ed[200]; //ten dia can tim
		cout << "- Nhap ten dia can tim: ";
		cin.ignore();
		cin.getline(ed, 200); //get ten dia can tim
		while (listTL != NULL) //check ds the loai
		{
			listDia = listTL->dsDia; //tro danh sach dia theo the loai
			while (listDia != NULL) //check danh sach dia 
			{
				if (strcmp(ed, listDia->ten) == 0) //check ten dia da co ton tai trong danh sach dia hay chua 
				{
					cout << setw(25) << left << "\t  Ma so dia: " << listDia->Maso << endl;
					cout << setw(25) << left << "\t  Ten dia: " << listDia->ten << endl;
					cout << setw(25) << left << "\t  Nam phat hanh: " << listDia->namphathanh << endl;
					cout << setw(25) << left << "\t  Ten dao dien: " << listDia->daoDien << endl;
					cout << setw(25) << left << "\t  Ten dien vien: " << listDia->dienVien << endl;
					flap = true;
				}
				listDia = listDia->nextDia; //tro toi dia tiep theo
			}
			listTL = listTL->nextTL; //tro toi the loai tiep theo
		}
		break;
	}
	case 2: {
		char ed[5]; //ma so dia can tim
		cout << "- Nhap ma so dia can tim: ";
		cin.ignore();
		cin.getline(ed, 200); //get ma so dia
		while (listTL != NULL) //check danh sach the loai
		{
			listDia = listTL->dsDia; //tro danh sach dia theo the loai
			while (listDia != NULL) //check danh sach dia 
			{
				if (strcmp(ed, listDia->Maso) == 0) //check ma so dia da co ton tai trong danh sach dia hay chua 
				{
					cout << setw(25) << left << "\t  Ma so dia: " << listDia->Maso << endl;
					cout << setw(25) << left << "\t  Ten dia: " << listDia->ten << endl;
					cout << setw(25) << left << "\t  Nam phat hanh: " << listDia->namphathanh << endl;
					cout << setw(25) << left << "\t  Ten dao dien: " << listDia->daoDien << endl;
					cout << setw(25) << left << "\t  Ten dien vien: " << listDia->dienVien << endl;
					flap = true;
				}
				listDia = listDia->nextDia; //tro toi dia tiep theo
			}
			listTL = listTL->nextTL; //tro toi the loai tiep theo
		}
		break;
	}

	case 3: //tuong tu 2 case tren
	{
		char ed[200];
		cout << "- Nhap ten dien vien can tim: ";
		cin.ignore();
		cin.getline(ed, 200);
		while (listTL != NULL)
		{
			listDia = listTL->dsDia;
			while (listDia != NULL)
			{
				if (strcmp(ed, listDia->dienVien) == 0)
				{
					cout << setw(25) << left << "\t  Ma so dia: " << listDia->Maso << endl;
					cout << setw(25) << left << "\t  Ten dia: " << listDia->ten << endl;
					cout << setw(25) << left << "\t  Nam phat hanh: " << listDia->namphathanh << endl;
					cout << setw(25) << left << "\t  Ten dao dien: " << listDia->daoDien << endl;
					cout << setw(25) << left << "\t  Ten dien vien: " << listDia->dienVien << endl;
					flap = true;
				}
				listDia = listDia->nextDia;
			}
			listTL = listTL->nextTL;
		}
		break;
	}
	default:
		break;
	}
	if (!flap)
		cout << "\nKhong tim thay!!!" << endl;
}

void Edit(cuaHang& CH) {
	NODETL listTL = CH.dstheloai;	//khoi tao danh sach cac the loai cua CH
	NODEDia listDia;				//khoi tao danh sach cac dia trong CH
	char ed[5], tL[200];
	cout << "- Nhap ten the loai dia can sua: ";
	cin.ignore();
	cin.getline(tL, 200);
	cout << "    + Nhap ma so dia can sua: ";
	cin.getline(ed, 5);
	while (listTL != NULL)
	{
		listDia = listTL->dsDia;
		if (strcmp(tL, listTL->ten) == 0)	//so sanh ten the loai neu =0 thi trung nhau
			while (listDia != NULL)
			{
				if (strcmp(ed, listDia->Maso) == 0)		//so sanh ma so dia
				{
					cout << "\tMa so dia moi: ";
					cin.getline(listDia->Maso, 5);
					cout << "\tTen dia moi: ";
					cin.getline(listDia->ten, 200);
					cout << "\tNhap nam phat hanh moi: ";
					cin.getline(listDia->namphathanh, 5);
					cout << "\tNhap ten dao dien moi: ";
					cin.getline(listDia->daoDien, 200);
					cout << "\tNhap ten dien vien moi: ";
					cin.getline(listDia->dienVien, 200);
				}
				listDia = listDia->nextDia;		//tro toi danh sach dia tiep theo trong cung the loai
			}
		listTL = listTL->nextTL;			//tro toi the loai tiep theo trong danh sach the loai dia
	}
}

void sort(cuaHang& CH) {
	NODETL i = CH.dstheloai;		//khoi tao danh sach cac the loai cua CH
	NODEDia j;
	for (i; i != NULL; i = i->nextTL) {
		for (j = i->dsDia; j != NULL; j = j->nextDia) {
			if (j->nextDia != NULL && strcmp(j->ten, j->nextDia->ten) == 1)			//so sanh dia t1 voi dia tiep theo
			{		
				NODEDia c = new bangDia;
				c = j->nextDia;
				j->nextDia = j->nextDia->nextDia;
				c->nextDia = j;
				i->dsDia = c;
			}
			if (j->nextDia != NULL && j->nextDia->nextDia != NULL && strcmp(j->nextDia->ten, j->nextDia->nextDia->ten) == 1)	//so sanh dia t2 voi dia tiep theo
			{
				NODEDia c = new bangDia;
				c = j->nextDia->nextDia;
				j->nextDia->nextDia = j->nextDia->nextDia->nextDia;
				if (c->nextDia != NULL)
					c->nextDia->nextDia = j;
				j->nextDia = c;
			}
		}
	}

	cout << "\nSap Xep Thanh Cong!!!" << endl;
}

void outPutFile(cuaHang& CH) {
	NODETL listTL = CH.dstheloai, tamlistTL = CH.dstheloai;		//tao ra danh sach tam thoi de xuat ra man hinh
	NODEDia listDia;

	fstream f;
	f.open("dSDia.txt");

	int x;//so luong the loai.
	f >> x;

	for (int i = 0; i < x; i++)			//duyet so luong the loai
	{
		listTL = CH.dstheloai;
		if (listTL == NULL) {
			NODETL p = new theLoai;		//goi ra struct the loai 
			f.ignore();
			f.getline(p->ten, 200);		//add ten + so dia vao cac node the loai
			f >> p->sodia;
			p->dsDia = NULL;
			p->nextTL = NULL;
			CH.dstheloai = p;
			tamlistTL = CH.dstheloai;	//tamlistTL de luu lai danh sach the loai goi ra tu file
		}
		else {
			while (listTL->nextTL != NULL)
				listTL = listTL->nextTL;	//giong i++, duyet the loai tang dan
			NODETL p = new theLoai;
			f.getline(p->ten, 200);
			f >> p->sodia;
			p->dsDia = NULL;
			p->nextTL = NULL;
			listTL->nextTL = p;
			tamlistTL = listTL->nextTL;
		}

		for (int j = 0; j < tamlistTL->sodia; j++)	//duyet so dia co trong the loai
		{
			listDia = tamlistTL->dsDia;				//gan danh sach dia trong tamlistTL cho listDia
			if (tamlistTL->dsDia == NULL) {			
				NODEDia p = new bangDia;
				f.ignore();
				f.getline(p->Maso, 5);
				f.getline(p->ten, 200);
				f.getline(p->namphathanh, 5);
				f.getline(p->daoDien, 200);
				f.getline(p->dienVien, 200);
				p->nextDia = NULL;
				tamlistTL->dsDia = p;
			}
			else {									//them dia trong list danh sach dia
				while (listDia->nextDia != NULL)
					listDia = listDia->nextDia;		//giong i++, duyet dia tang dan
				NODEDia p = new bangDia;

				f.getline(p->Maso, 5);
				f.getline(p->ten, 200);
				f.getline(p->namphathanh, 5);
				f.getline(p->daoDien, 200);
				f.getline(p->dienVien, 200);
				p->nextDia = NULL;
				listDia->nextDia = p;
			}
		}

	}
	cout << "\nNHAP DS DIA THANH CONG!!!" << endl;
}

void menu()
{
	thanhVien();
	cout << "\n\t\t\t ============================== MENU =================================" << endl;
	cout << "\t\t\t\t\t 1: Xuat Thong Tin Cua hang." << endl;
	cout << "\t\t\t\t\t 2: Xuat Danh Sach Dia" << endl;
	cout << "\t\t\t\t\t 3: Them." << endl;
	cout << "\t\t\t\t\t 4: Xoa Dia" << endl;
	cout << "\t\t\t\t\t 5: Tim." << endl;
	cout << "\t\t\t\t\t 6: Sua Thong Tin Dia" << endl;
	cout << "\t\t\t\t\t 7: Sap Xep               " << endl;
	cout << "\t\t\t\t\t 8: Xoa Man Hinh" << endl;
	cout << "\t\t\t =======================================================================" << endl;
	vetuong();
}

void MENU() {
	cuaHang CH;
	inIt(CH);
	int a; bool flat = false;
	menu();
	cout << "\n\n\n";
	outPutFile(CH);

	do
	{
		if (flat) {
			cout << "========================================== MENU =======================================" << endl;
			cout << "2: Xuat DS Dia";
			cout << "\t\t\t3: Them";
			cout << "\t\t\t4: Xoa Dia";
			cout << "\t\t5: Tim";
			cout << "\n6: Sua Thong Tin Dia";
			cout << "\t\t7: Sap Xep";
			cout << "\t\t8: Xoa Man Hinh" << endl;
			cout << "=======================================================================================" << endl;
		}
		flat = true;
		cout << "\n\nChon Chuc Nang (Nhap -99 De Thoat): "; 
		cin >> a;
		switch (a)
		{
		case 1: {
			nhapCuaHang(CH);
			xuatCuaHang(CH);
			break;
		}
		case 2: {
			xuatDSdia(CH);
			break;
		}
		case 3: {
			Add(CH);
			break;
		}
		case 4: {
			xoaDia(CH);
			break;
		}
		case 5: {
			search(CH);
			break;
		}
		case 6: {
			Edit(CH);
			break;
		}
		case 7: {
			sort(CH);
			break;
		}
		case 8: {
			clrscr();
			menu();

			flat = false;
			break;
		}
		default: {
			if (a != -99)
				cout << "\t\tBan Nhap Sai!!! Vui Long Nhap Lai." << endl;
			break;
		}

		}
	} while (a != -99);

}

void main()
{
	MENU();
}