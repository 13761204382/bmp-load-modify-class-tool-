#ifndef BMPROT
#define BMPROT
#include <fstream> 
#include <exception>
#pragma warning(disable:4996) 
#define COLORS 256
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef long LONG;



//λͼ�ļ�ͷ����;  
//���в������ļ�������Ϣ�����ڽṹ����ڴ�ṹ������  
//Ҫ�Ǽ��˵Ļ���������ȷ��ȡ�ļ���Ϣ��  

class  BITMAPFILEHEADER {
public:
	//WORD bfType;//�ļ����ͣ�������0x424D�����ַ���BM��  
	DWORD bfSize;//�ļ���С  
	WORD bfReserved1;//������  
	WORD bfReserved2;//������  
	DWORD bfOffBits;//���ļ�ͷ��ʵ��λͼ���ݵ�ƫ���ֽ���  
};

class BITMAPINFOHEADER {
public:
	DWORD biSize;//��Ϣͷ��С  
	LONG biWidth;//ͼ����  
	LONG biHeight;//ͼ��߶�  
	WORD biPlanes;//λƽ����������Ϊ1  
	WORD biBitCount;//ÿ����λ��  
	DWORD  biCompression; //ѹ������  
	DWORD  biSizeImage; //ѹ��ͼ���С�ֽ���  
	LONG  biXPelsPerMeter; //ˮƽ�ֱ���  
	LONG  biYPelsPerMeter; //��ֱ�ֱ���  
	DWORD  biClrUsed; //λͼʵ���õ���ɫ����  
	DWORD  biClrImportant; //��λͼ����Ҫ��ɫ����  
}; //λͼ��Ϣͷ����  

class RGBQUAD {
public:
	BYTE rgbBlue; //����ɫ����ɫ����  
	BYTE rgbGreen; //����ɫ����ɫ����  
	BYTE rgbRed; //����ɫ�ĺ�ɫ����  
	BYTE rgbReserved; //����ֵ  
};//��ɫ�嶨��  

		 //������Ϣ  
class IMAGEDATA {
public:
	BYTE red;
	BYTE green;
	BYTE blue;
};



class bmploader {
public:
	bmploader(char * s1, char * s2) {
		strFile = s1;
		strOutput = s2;
		fpi = fopen(strFile, "rb");
		if (fpi != NULL) {
			//�ȶ�ȡ�ļ�����  
			WORD bfType;
			fread(&bfType, 1, sizeof(WORD), fpi);
			if (0x4d42 != bfType)
			{
				return;
			}
			else {
				iniSuccess = 1;
			}

			//��ȡbmp�ļ����ļ�ͷ����Ϣͷ  
			fread(&strHead, 1, sizeof(BITMAPFILEHEADER), fpi);
			//showBmpHerad(strHead);//��ʾ�ļ�ͷ  
			strHeadRot = strHead;
			fread(&strInfo, 1, sizeof(BITMAPINFOHEADER), fpi);
			//showBmpInforHead(strInfo);//��ʾ�ļ���Ϣͷ  
			strRot = strInfo;
			//��ȡ��ɫ��  
			for (unsigned int nCounti = 0; nCounti<strInfo.biClrUsed; nCounti++)
			{
				//�洢��ʱ��һ��ȥ��������rgbReserved  
				fread((char *)&strPla[nCounti].rgbBlue, 1, sizeof(BYTE), fpi);
				fread((char *)&strPla[nCounti].rgbGreen, 1, sizeof(BYTE), fpi);
				fread((char *)&strPla[nCounti].rgbRed, 1, sizeof(BYTE), fpi);
			}
			//��ȡ��ɫ��  
			for (unsigned int nCounti = 0; nCounti<strInfo.biClrUsed; nCounti++)
			{
				//�洢��ʱ��һ��ȥ��������rgbReserved  
				strPlaRot[nCounti] = strPla[nCounti];
			}
			imagedata = (IMAGEDATA*)malloc(strInfo.biWidth * strInfo.biHeight * sizeof(IMAGEDATA));
			//��ʼ��ԭʼͼƬ����������  
			for (int i = 0; i < strInfo.biHeight; ++i)
			{
				for (int j = 0; j < strInfo.biWidth; ++j)
				{
					(*(imagedata + i * strInfo.biWidth + j)).blue = 0;
					(*(imagedata + i * strInfo.biWidth + j)).green = 0;
					(*(imagedata + i *  strInfo.biWidth + j)).red = 0;
				}
			}

			//����ͼƬ����������  
			fread(imagedata, sizeof(class IMAGEDATA) * strInfo.biWidth, strInfo.biHeight, fpi);

			fclose(fpi);
			fclose(fpi);
		}
		else;
	}

	~bmploader() {
		//�ͷ��ڴ�  
		delete[] imagedata;
		delete[] imagedataRot;
	}

	void modifyoutputname(char *);
	void showBmpHead(BITMAPFILEHEADER &);
	void showBmpInforHead(BITMAPINFOHEADER &);
	void rotate(int);
	void copy();
	bool save();
private:
	bmploader() {}
	bool iniSuccess = 0;
	IMAGEDATA *imagedata = NULL;//��̬����洢ԭͼƬ��������Ϣ�Ķ�ά����  
	IMAGEDATA *imagedataRot = NULL;//��̬����洢��ת���ͼƬ��������Ϣ�Ķ�ά����  
	FILE *fpi = nullptr;
	FILE *fpw = nullptr;
	char * strFile;//bmp�ļ���  
	char * strOutput;
	//int width, height;//ͼƬ�Ŀ�Ⱥ͸߶� 
	BITMAPFILEHEADER strHead;
	RGBQUAD strPla[COLORS];//256ɫ��ɫ��  
	BITMAPINFOHEADER strInfo;
	BITMAPFILEHEADER strHeadRot;
	RGBQUAD strPlaRot[COLORS];//256ɫ��ɫ��
	BITMAPINFOHEADER strRot;
};
#endif // !BMPROT
