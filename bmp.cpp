#include "stdafx.h"
#include "bmp.h"
#define PI 3.14159//圆周率宏定义 

//显示位图文件头信息  


	
void bmploader::rotate(int r) {
	int RotateAngle = r;//要旋转的角度数  
	

	strRot.biWidth = 2 * strInfo.biWidth;
	strRot.biHeight = 2 * strInfo.biHeight;

	imagedataRot = (IMAGEDATA*)malloc(strRot.biWidth * strRot.biHeight * sizeof(IMAGEDATA));
	//初始化旋转后图片的像素数组  
	for (int i = 0; i < strRot.biHeight; ++i)
	{
		for (int j = 0; j < strRot.biWidth; ++j)
		{
			(*(imagedataRot + i * strRot.biWidth + j)).blue = 0;
			(*(imagedataRot + i * strRot.biWidth + j)).green = 0;
			(*(imagedataRot + i * strRot.biWidth + j)).red = 0;
		}
	}


	//图片旋转处理  

	double angle;//要旋转的弧度数  
	int midX_pre, midY_pre, midX_aft, midY_aft;//旋转所围绕的中心点的坐标  
	midX_pre = strInfo.biWidth / 2;
	midY_pre = strInfo.biHeight / 2;
	midX_aft = strInfo.biWidth;
	midY_aft = strInfo.biHeight;
	int pre_i, pre_j, after_i, after_j;//旋转前后对应的像素点坐标  

	angle = 1.0 * RotateAngle * PI / 180;
	for (int i = 0; i < strRot.biHeight; ++i)
	{
		for (int j = 0; j < strRot.biWidth; ++j)
		{
			after_i = i - midY_aft;//坐标变换  
			after_j = j - midX_aft;
			pre_i = (int)(cos((double)angle) * after_i - sin((double)angle) * after_j) + midY_pre;
			pre_j = (int)(sin((double)angle) * after_i + cos((double)angle) * after_j) + midX_pre;
			if (pre_i >= 0 && pre_i < strInfo.biHeight && pre_j >= 0 && pre_j < strInfo.biWidth)//在原图范围内  
				*(imagedataRot + i * strRot.biWidth + j) = *(imagedata + pre_i * strInfo.biWidth + pre_j);
		}
	}

}

void bmploader::copy() {
	strRot = strInfo;
	imagedataRot = (IMAGEDATA*)malloc(strRot.biWidth * strRot.biHeight * sizeof(IMAGEDATA));
	//初始化原始图片的像素数组  
	for (int i = 0; i < strRot.biHeight; ++i)
	{
		for (int j = 0; j < strRot.biWidth; ++j)
		{
			(*(imagedataRot + i * strInfo.biWidth + j)) = (*(imagedata + i * strInfo.biWidth + j));
		}
	}

}

void bmploader::modifyoutputname(char * c) {
	strOutput = c;
}

void bmploader::showBmpHead(BITMAPFILEHEADER & pBmpHead) {
	pBmpHead = strHead;
}

void bmploader::showBmpInforHead(BITMAPINFOHEADER & pBmpInfoHead) {
	pBmpInfoHead = strInfo;
}

bool bmploader::save() {
	//保存bmp图片  
	if ((fpw = fopen(strOutput, "wb")) == NULL) {
		return 0;
	}
	else;

	WORD bfType_w = 0x4d42;
	fwrite(&bfType_w, 1, sizeof(WORD), fpw);
	
	fwrite(&strHeadRot, 1, sizeof(BITMAPFILEHEADER), fpw);

	fwrite(&strRot, 1, sizeof(BITMAPINFOHEADER), fpw);
	//保存调色板数据  
	for (unsigned int nCounti = 0; nCounti<strRot.biClrUsed; nCounti++)
	{
		fwrite(&strPlaRot[nCounti].rgbBlue, 1, sizeof(BYTE), fpw);
		fwrite(&strPlaRot[nCounti].rgbGreen, 1, sizeof(BYTE), fpw);
		fwrite(&strPlaRot[nCounti].rgbRed, 1, sizeof(BYTE), fpw);
	}
	//保存像素数据  
	for (int i = 0; i < strRot.biHeight; ++i)
	{
		for (int j = 0; j < strRot.biWidth; ++j)
		{
			fwrite(&(*(imagedataRot + i * strRot.biWidth + j)).red, 1, sizeof(BYTE), fpw);//注意三条语句的顺序：否则颜色会发生变化  
			fwrite(&(*(imagedataRot + i * strRot.biWidth + j)).green, 1, sizeof(BYTE), fpw);
			fwrite(&(*(imagedataRot + i * strRot.biWidth + j)).blue, 1, sizeof(BYTE), fpw);
		}
	}
	return 1;
}