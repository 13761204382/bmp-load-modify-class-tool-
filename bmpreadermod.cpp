// bmpreader.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>  
#include "bmp.h"  
#include "stdlib.h"  
#include "math.h"  
#include <iostream>  
#pragma warning(disable:4996) 
 
#define LENGTH_NAME_BMP 128//bmp图片文件名的最大长度  







int main() {
	char strFile[LENGTH_NAME_BMP];
	unsigned short flag;
	BITMAPFILEHEADER pBmpHead;
	BITMAPINFOHEADER pBmpInfoHead;
	bmploader b("Nicole.bmp","b.bmp");
	b.showBmpHead(pBmpHead);
	b.showBmpInforHead(pBmpInfoHead);
	std::cout << "位图文件头:" << std::endl;
	std::cout << "文件大小:" << pBmpHead.bfSize << std::endl;
	std::cout << "保留字_1:" << pBmpHead.bfReserved1 << std::endl;
	std::cout << "保留字_2:" << pBmpHead.bfReserved2 << std::endl;
	std::cout << "实际位图数据的偏移字节数:" << pBmpHead.bfOffBits << std::endl << std::endl;
	std::cout << "位图信息头:" << std::endl;
	std::cout << "结构体的长度:" << pBmpInfoHead.biSize << std::endl;
	std::cout << "位图宽:" << pBmpInfoHead.biWidth << std::endl;
	std::cout << "位图高:" << pBmpInfoHead.biHeight << std::endl;
	std::cout << "biPlanes平面数:" << pBmpInfoHead.biPlanes << std::endl;
	std::cout << "biBitCount采用颜色位数:" << pBmpInfoHead.biBitCount << std::endl;
	std::cout << "压缩方式:" << pBmpInfoHead.biCompression << std::endl;
	std::cout << "biSizeImage实际位图数据占用的字节数:" << pBmpInfoHead.biSizeImage << std::endl;
	std::cout << "X方向分辨率:" << pBmpInfoHead.biXPelsPerMeter << std::endl;
	std::cout << "Y方向分辨率:" << pBmpInfoHead.biYPelsPerMeter << std::endl;
	std::cout << "使用的颜色数:" << pBmpInfoHead.biClrUsed << std::endl;
	std::cout << "重要颜色数:" << pBmpInfoHead.biClrImportant << std::endl;
	b.rotate(30);
	b.save();
	b.modifyoutputname("c.bmp");
	b.copy();
	b.save();
	getchar();
	getchar();
}


