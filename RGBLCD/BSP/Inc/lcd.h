/*
 * lcd.h
 *
 *  Created on: Jan 31, 2023
 *      Author: ASUS
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "main.h"
#include "ltdc.h"

extern LTDC_HandleTypeDef hltdc;

/* USER CODE BEGIN Private defines */
#define LCD_FRAME_BUF_ADDR	0XC0000000 //该定义未使用，仅提示LTDC LCD使用内存起始地址

//LCD LTDC重要参数
typedef struct
{
	uint32_t pwidth;		//LCD面板的宽度,固定参数,不随显示方向改变,如果为0,说明没有任何RGB屏接入
	uint32_t pheight;		//LCD面板的高度,固定参数,不随显示方向改变
	uint16_t hsw;			//水平同步宽度
	uint16_t vsw;			//垂直同步宽度
	uint16_t hbp;			//水平后廊
	uint16_t vbp;			//垂直后廊
	uint16_t hfp;			//水平前廊
	uint16_t vfp;			//垂直前廊
	uint8_t activelayer;	//当前层编号:0/1
	uint8_t dir;			//0,竖屏;1,横屏;
	uint16_t width;			//LCD宽度
	uint16_t height;		//LCD高度
	uint32_t pixsize;		//每个像素所占字节数
}_ltdc_dev;
extern _ltdc_dev lcdltdc;		            //管理LCD LTDC参数
extern LTDC_HandleTypeDef LTDC_Handler;	    //LTDC句柄
extern DMA2D_HandleTypeDef DMA2D_Handler;   //DMA2D句柄

////LCD重要参数集
//typedef struct
//{
//	uint16_t width;			//LCD 宽度
//	uint16_t height;		//LCD 高度
//	uint16_t id;			//LCD ID
//	uint8_t  dir;			//横屏还是竖屏控制：0，竖屏；1，横屏。
//	uint16_t wramcmd;		//开始写gram指令
//	uint16_t setxcmd;		//设置x坐标指令
//	uint16_t setycmd;		//设置y坐标指令
//}_lcd_dev;
//
////LCD参数保存位置在lcd.c
////extern _lcd_dev lcddev;	//管理LCD重要参数

extern uint32_t POINT_COLOR;		//画笔颜色
extern uint32_t BACK_COLOR;  		//背景色

#define LCD_PIXEL_FORMAT_ARGB8888       0X00
#define LCD_PIXEL_FORMAT_RGB888         0X01
#define LCD_PIXEL_FORMAT_RGB565         0X02
#define LCD_PIXEL_FORMAT_ARGB1555       0X03
#define LCD_PIXEL_FORMAT_ARGB4444       0X04
#define LCD_PIXEL_FORMAT_L8             0X05
#define LCD_PIXEL_FORMAT_AL44           0X06
#define LCD_PIXEL_FORMAT_AL88           0X07

//定义颜色像素格式,一般用RGB565
#define LCD_PIXFORMAT	LCD_PIXEL_FORMAT_RGB565

//画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000
#define BLUE         	 0x001F
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色
//GUI颜色
#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色

#define LIGHTGREEN     	 0X841F //浅绿色
//#define LIGHTGRAY        0XEF5B //浅灰色(PANNEL)
#define LGRAY 			 0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)
/* USER CODE END Private defines */

/* USER CODE BEGIN Prototypes */
void LTDC_ParameterInit();				//LTDC 参数初始化
void LTDC_Clear(uint32_t color);		//LTDC 清屏
void LTDC_Display_Dir(uint8_t dir);		//LTDC 设置显示方向
void LTDC_Select_Layer(uint8_t layerx);	//LTDC 选择显示层
void LTDC_Switch(uint8_t sw);			//LTDC 开关

uint32_t LTDC_Read_Point(uint16_t x,uint16_t y); 								//LTDC 读点函数
void LTDC_Draw_Point(uint16_t x,uint16_t y,uint32_t color);						//LTDC 画点函数
void LTDC_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint32_t color);	//LTDC 填充矩形，DMA2D 填充，颜色为值
void LTDC_Color_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t *color); //LTDC 填充矩形，DMA2D 填充，颜色数组

void LCD_Init(void);								//LCD 初始化函数
void LCD_DrawPoint(uint16_t x,uint16_t y);			//LCD 默认画点函数
uint32_t LCD_ReadPoint(uint16_t x,uint16_t y);		//LCD 默认读点函数
void LCD_Fast_DrawPoint(uint16_t x,uint16_t y,uint32_t color);	//LCD 以颜色画点函数
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);//LCD 默认画线函数
void LCD_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint32_t color);//LCD 以颜色填充的函数
void LCD_Color_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t *color);	//LCD 以颜色数组填充的函数
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);				//LCD 默认画矩形函数
void LCD_Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r);								//LCD 默认画圆函数
void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint8_t size,uint8_t mode);			//LCD 显示字符函数
void LCD_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size);			//LCD 显示数字函数
void LCD_ShowxNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size,uint8_t mode);		//LCD 显示若干数字函数
void LCD_ShowString(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t size,uint8_t *p);	//LCD 显示字符串函数

/* USER CODE END Prototypes */

#endif /* INC_LCD_H_ */
