// bmpreader.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>  
#include "bmp.h"  
#include "stdlib.h"  
#include "math.h"  
#include <iostream>  
#pragma warning(disable:4996) 
 
#define LENGTH_NAME_BMP 128//bmpͼƬ�ļ�������󳤶�  







int main() {
	char strFile[LENGTH_NAME_BMP];
	unsigned short flag;
	BITMAPFILEHEADER pBmpHead;
	BITMAPINFOHEADER pBmpInfoHead;
	bmploader b("Nicole.bmp","b.bmp");
	b.showBmpHead(pBmpHead);
	b.showBmpInforHead(pBmpInfoHead);
	std::cout << "λͼ�ļ�ͷ:" << std::endl;
	std::cout << "�ļ���С:" << pBmpHead.bfSize << std::endl;
	std::cout << "������_1:" << pBmpHead.bfReserved1 << std::endl;
	std::cout << "������_2:" << pBmpHead.bfReserved2 << std::endl;
	std::cout << "ʵ��λͼ���ݵ�ƫ���ֽ���:" << pBmpHead.bfOffBits << std::endl << std::endl;
	std::cout << "λͼ��Ϣͷ:" << std::endl;
	std::cout << "�ṹ��ĳ���:" << pBmpInfoHead.biSize << std::endl;
	std::cout << "λͼ��:" << pBmpInfoHead.biWidth << std::endl;
	std::cout << "λͼ��:" << pBmpInfoHead.biHeight << std::endl;
	std::cout << "biPlanesƽ����:" << pBmpInfoHead.biPlanes << std::endl;
	std::cout << "biBitCount������ɫλ��:" << pBmpInfoHead.biBitCount << std::endl;
	std::cout << "ѹ����ʽ:" << pBmpInfoHead.biCompression << std::endl;
	std::cout << "biSizeImageʵ��λͼ����ռ�õ��ֽ���:" << pBmpInfoHead.biSizeImage << std::endl;
	std::cout << "X����ֱ���:" << pBmpInfoHead.biXPelsPerMeter << std::endl;
	std::cout << "Y����ֱ���:" << pBmpInfoHead.biYPelsPerMeter << std::endl;
	std::cout << "ʹ�õ���ɫ��:" << pBmpInfoHead.biClrUsed << std::endl;
	std::cout << "��Ҫ��ɫ��:" << pBmpInfoHead.biClrImportant << std::endl;
	b.rotate(30);
	b.save();
	b.modifyoutputname("c.bmp");
	b.copy();
	b.save();
	getchar();
	getchar();
}


