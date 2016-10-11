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



//位图文件头定义;  
//其中不包含文件类型信息（由于结构体的内存结构决定，  
//要是加了的话将不能正确读取文件信息）  

class  BITMAPFILEHEADER {
public:
	//WORD bfType;//文件类型，必须是0x424D，即字符“BM”  
	DWORD bfSize;//文件大小  
	WORD bfReserved1;//保留字  
	WORD bfReserved2;//保留字  
	DWORD bfOffBits;//从文件头到实际位图数据的偏移字节数  
};

class BITMAPINFOHEADER {
public:
	DWORD biSize;//信息头大小  
	LONG biWidth;//图像宽度  
	LONG biHeight;//图像高度  
	WORD biPlanes;//位平面数，必须为1  
	WORD biBitCount;//每像素位数  
	DWORD  biCompression; //压缩类型  
	DWORD  biSizeImage; //压缩图像大小字节数  
	LONG  biXPelsPerMeter; //水平分辨率  
	LONG  biYPelsPerMeter; //垂直分辨率  
	DWORD  biClrUsed; //位图实际用到的色彩数  
	DWORD  biClrImportant; //本位图中重要的色彩数  
}; //位图信息头定义  

class RGBQUAD {
public:
	BYTE rgbBlue; //该颜色的蓝色分量  
	BYTE rgbGreen; //该颜色的绿色分量  
	BYTE rgbRed; //该颜色的红色分量  
	BYTE rgbReserved; //保留值  
};//调色板定义  

		 //像素信息  
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
			//先读取文件类型  
			WORD bfType;
			fread(&bfType, 1, sizeof(WORD), fpi);
			if (0x4d42 != bfType)
			{
				return;
			}
			else {
				iniSuccess = 1;
			}

			//读取bmp文件的文件头和信息头  
			fread(&strHead, 1, sizeof(BITMAPFILEHEADER), fpi);
			//showBmpHerad(strHead);//显示文件头  
			strHeadRot = strHead;
			fread(&strInfo, 1, sizeof(BITMAPINFOHEADER), fpi);
			//showBmpInforHead(strInfo);//显示文件信息头  
			strRot = strInfo;
			//读取调色板  
			for (unsigned int nCounti = 0; nCounti<strInfo.biClrUsed; nCounti++)
			{
				//存储的时候，一般去掉保留字rgbReserved  
				fread((char *)&strPla[nCounti].rgbBlue, 1, sizeof(BYTE), fpi);
				fread((char *)&strPla[nCounti].rgbGreen, 1, sizeof(BYTE), fpi);
				fread((char *)&strPla[nCounti].rgbRed, 1, sizeof(BYTE), fpi);
			}
			//读取调色板  
			for (unsigned int nCounti = 0; nCounti<strInfo.biClrUsed; nCounti++)
			{
				//存储的时候，一般去掉保留字rgbReserved  
				strPlaRot[nCounti] = strPla[nCounti];
			}
			imagedata = (IMAGEDATA*)malloc(strInfo.biWidth * strInfo.biHeight * sizeof(IMAGEDATA));
			//初始化原始图片的像素数组  
			for (int i = 0; i < strInfo.biHeight; ++i)
			{
				for (int j = 0; j < strInfo.biWidth; ++j)
				{
					(*(imagedata + i * strInfo.biWidth + j)).blue = 0;
					(*(imagedata + i * strInfo.biWidth + j)).green = 0;
					(*(imagedata + i *  strInfo.biWidth + j)).red = 0;
				}
			}

			//读出图片的像素数据  
			fread(imagedata, sizeof(class IMAGEDATA) * strInfo.biWidth, strInfo.biHeight, fpi);

			fclose(fpi);
			fclose(fpi);
		}
		else;
	}

	~bmploader() {
		//释放内存  
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
	IMAGEDATA *imagedata = NULL;//动态分配存储原图片的像素信息的二维数组  
	IMAGEDATA *imagedataRot = NULL;//动态分配存储旋转后的图片的像素信息的二维数组  
	FILE *fpi = nullptr;
	FILE *fpw = nullptr;
	char * strFile;//bmp文件名  
	char * strOutput;
	//int width, height;//图片的宽度和高度 
	BITMAPFILEHEADER strHead;
	RGBQUAD strPla[COLORS];//256色调色板  
	BITMAPINFOHEADER strInfo;
	BITMAPFILEHEADER strHeadRot;
	RGBQUAD strPlaRot[COLORS];//256色调色板
	BITMAPINFOHEADER strRot;
};
#endif // !BMPROT
