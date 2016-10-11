#include "stdafx.h"
#include "bmp.h"
#define PI 3.14159//Բ���ʺ궨�� 

//��ʾλͼ�ļ�ͷ��Ϣ  


	
void bmploader::rotate(int r) {
	int RotateAngle = r;//Ҫ��ת�ĽǶ���  
	

	strRot.biWidth = 2 * strInfo.biWidth;
	strRot.biHeight = 2 * strInfo.biHeight;

	imagedataRot = (IMAGEDATA*)malloc(strRot.biWidth * strRot.biHeight * sizeof(IMAGEDATA));
	//��ʼ����ת��ͼƬ����������  
	for (int i = 0; i < strRot.biHeight; ++i)
	{
		for (int j = 0; j < strRot.biWidth; ++j)
		{
			(*(imagedataRot + i * strRot.biWidth + j)).blue = 0;
			(*(imagedataRot + i * strRot.biWidth + j)).green = 0;
			(*(imagedataRot + i * strRot.biWidth + j)).red = 0;
		}
	}


	//ͼƬ��ת����  

	double angle;//Ҫ��ת�Ļ�����  
	int midX_pre, midY_pre, midX_aft, midY_aft;//��ת��Χ�Ƶ����ĵ������  
	midX_pre = strInfo.biWidth / 2;
	midY_pre = strInfo.biHeight / 2;
	midX_aft = strInfo.biWidth;
	midY_aft = strInfo.biHeight;
	int pre_i, pre_j, after_i, after_j;//��תǰ���Ӧ�����ص�����  

	angle = 1.0 * RotateAngle * PI / 180;
	for (int i = 0; i < strRot.biHeight; ++i)
	{
		for (int j = 0; j < strRot.biWidth; ++j)
		{
			after_i = i - midY_aft;//����任  
			after_j = j - midX_aft;
			pre_i = (int)(cos((double)angle) * after_i - sin((double)angle) * after_j) + midY_pre;
			pre_j = (int)(sin((double)angle) * after_i + cos((double)angle) * after_j) + midX_pre;
			if (pre_i >= 0 && pre_i < strInfo.biHeight && pre_j >= 0 && pre_j < strInfo.biWidth)//��ԭͼ��Χ��  
				*(imagedataRot + i * strRot.biWidth + j) = *(imagedata + pre_i * strInfo.biWidth + pre_j);
		}
	}

}

void bmploader::copy() {
	strRot = strInfo;
	imagedataRot = (IMAGEDATA*)malloc(strRot.biWidth * strRot.biHeight * sizeof(IMAGEDATA));
	//��ʼ��ԭʼͼƬ����������  
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
	//����bmpͼƬ  
	if ((fpw = fopen(strOutput, "wb")) == NULL) {
		return 0;
	}
	else;

	WORD bfType_w = 0x4d42;
	fwrite(&bfType_w, 1, sizeof(WORD), fpw);
	
	fwrite(&strHeadRot, 1, sizeof(BITMAPFILEHEADER), fpw);

	fwrite(&strRot, 1, sizeof(BITMAPINFOHEADER), fpw);
	//�����ɫ������  
	for (unsigned int nCounti = 0; nCounti<strRot.biClrUsed; nCounti++)
	{
		fwrite(&strPlaRot[nCounti].rgbBlue, 1, sizeof(BYTE), fpw);
		fwrite(&strPlaRot[nCounti].rgbGreen, 1, sizeof(BYTE), fpw);
		fwrite(&strPlaRot[nCounti].rgbRed, 1, sizeof(BYTE), fpw);
	}
	//������������  
	for (int i = 0; i < strRot.biHeight; ++i)
	{
		for (int j = 0; j < strRot.biWidth; ++j)
		{
			fwrite(&(*(imagedataRot + i * strRot.biWidth + j)).red, 1, sizeof(BYTE), fpw);//ע����������˳�򣺷�����ɫ�ᷢ���仯  
			fwrite(&(*(imagedataRot + i * strRot.biWidth + j)).green, 1, sizeof(BYTE), fpw);
			fwrite(&(*(imagedataRot + i * strRot.biWidth + j)).blue, 1, sizeof(BYTE), fpw);
		}
	}
	return 1;
}