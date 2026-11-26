#ifndef TFT_h
#define TFT_h

void tft1_print();
void tft2_print();
void tft_init();

namespace tft1
{
    void init_index();
    void shadow(int16_t x,int16_t y,int16_t w,int16_t h,uint16_t color);
    void Name(const String &name);
    void SD_stat(bool sd_stat);
    void BT_stat(bool bt_stat);
    void Mode(int mode);
    void Proc(const String &proc);
    void Fname(const String &fname);
    void Size(size_t file_size);
    void refresh(const String &name,bool sd_stat,bool bt_stat,int mode,const String &proc,const String &fname,size_t file_size);

}

namespace tft2
{

}

#endif