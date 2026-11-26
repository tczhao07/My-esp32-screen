#include "C++\TFT\TFT.h"
#include "C++\Pin\Pin.h"
#include "C++\Color\Color.h"

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

//创建对象
Adafruit_ST7735 tft1(TFT_CS1,TFT_DC1,TFT_RES1);
Adafruit_ST7735 tft2(TFT_CS2,TFT_DC2,TFT_RES2);

//字体打印函数
void tft1_print(int x,int y,int size,uint16_t color,const String &content)
{
    tft1.setCursor(x,y);
    tft1.setTextSize(size);
    tft1.setTextColor(color);
    tft1.print(content);
    return;
}

void tft2_print(int x,int y,int size,uint16_t color,const String &content)
{
    tft2.setCursor(x,y);
    tft2.setTextSize(size);
    tft2.setTextColor(color);
    tft2.print(content);
    return;
}

//屏幕初始化函数
void tft_init()
{
    //SPI初始化
    SPI.begin(SPI_SCLK,-1,SPI_MOSI,-1);

    tft1.initR(INITR_GREENTAB);
    tft2.initR(INITR_GREENTAB);

    tft1.setRotation(0);
    tft2.setRotation(0);

    //背景
    tft1.fillScreen(BLACK);
    tft2.fillScreen(BLACK);

    //字幕
    tft1_print(16,72,2,SKY_BLUE,"Welcome!");
    tft2_print(4,72,2,SKY_BLUE,"Initing...");

    delay(1000);

    return;
}

//状态屏幕专属函数
namespace tft1
{
    //索引初始化
    void init_index()
    {
        tft1_fillScreen(BLACK);

        tft1_print(25,8,1,SKY_BLUE,"SYSTEM STATUS");     //标题      
        tft1_print(0,25,1,WHITE,"Name:");               //设备名称  30
        tft1_print(0,41,1,WHITE,"SD_stat:");            //SD卡状态  40
        tft1_print(0,57,1,WHITE,"BT_stat:");            //蓝牙状态  40
        tft1_print(0,73,1,WHITE,"Mode:");               //模式      30
        tft1_print(0,89,1,WHITE,"Proc:");               //进程      30
        tft1_print(0,105,1,WHITE,"Fname:");             //文件名称  36
        tft1_print(0,121,1,WHITE,"Fsize:");             //文件大小  36
    }

    //蒙版函数
    void shadow(int16_t x,int16_t y,int16_t w,int16_t h,uint16_t color)
    {
        tft1.fillRect(x,y,w,h,color);
        return;
    }

    //设备名称
    void Name(const String &name)
    {
        shadow(30,25,98,16,BLACK);
        tft1_print(name.c_str());
        return;
    }

    //SD卡状态
    void SD_stat(bool sd_stat)
    {
        shadow(40,41,88,16,BLACK);

        if(sd_stat)
        {
            tft1_print(40,41,1,GREEN,"True");
        }
        else
        {
            tft1_print(40,41,1,RED,"False");
        }

        return;
    }

    //蓝牙状态
    void BT_stat(bool bt_stat)
    {
        shadow(40,57,88,16,BLACK);

        if(bt_stat)
        {
            tft1_print(40,57,1,GREEN,"True");
        }
        else
        {
            tft1_print(40,57,1,RED,"False");
        }

        return;
    }

    //模式
    void Mode(int mode)
    {
        shadow(30,73,98,16,BLACK);
        
        switch(mode)
        {
            case 1:
                tft1_print(30,73,1,WHITE,"BlueTooth");
                break;
            case 2:
                tft1_print(30,73,1,WHITE,"Image");
                break;
            case 3:
                tft1_print(30,73,1,WHITE,"Gif");
                break;
            case 4:
                tft1_print(30,73,1,WHITE,"Vedio");
                break;
            default:
                tft1_print(30,73,1,Yellow,"None");
        }

        return;
    }

    //进程
    void Proc(const String &proc)
    {
        shadow(30,89,98,16,BLACK);
        
        tft1_print(30,89,1,WHITE,proc.c_str());

        return;
    }

    //文件名称
    void Fname(const String &fname)
    {
        shadow(36,105,92,16,BLACK);
        
        tft1_print(36,105,1,WHITE,fname.c_str());

        return;
    }

    //文件大小
    void Size(size_t file_size)
    {
        shadow(36,121,92,16,BLACK);

        char size_text[12];
        snprintf(size_text, sizeof(size_text), "%lu",(unsigned long)file_size);
        tft1_print(36,121,1,WHITE,size_text);

        return;
    }

    //状态屏幕整体更新
    void refresh(const String &name,bool sd_stat,bool bt_stat,int mode,const String &proc,const String &fname,size_t file_size)
    {
        init_index();
        Name(const String &name);
        SD_stat(bool sd_stat);
        BT_stat(bool bt_stat);
        Mode(int mode)
        Proc(const String &proc);
        Fname(const String &fname);
        Size(size_t file_size);
        return;
    }
}

//目录屏幕专属函数
namespace tft2
{

}