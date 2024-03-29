/**
 * 雷霄骅 Lei Xiaohua
 * leixiaohua1020@126.com
 * 中国传媒大学/数字电视技术
 * Communication University of China / Digital TV Technology
 * http://blog.csdn.net/leixiaohua1020
 * https://github.com/leixiaohua1020/simplest_ffmpeg_mobile/blob/master/simplest_ffmpeg_android_helloworld/jni/simplest_ffmpeg_helloworld.c
 *
 *
 * 它可以打印出FFmpeg类库的下列信息：
 * Protocol:  FFmpeg类库支持的协议
 * AVFormat:  FFmpeg类库支持的封装格式
 * AVCodec:   FFmpeg类库支持的编解码器
 * AVFilter:  FFmpeg类库支持的滤镜
 * Configure: FFmpeg类库的配置信息
 */

#include <stdio.h>

#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavfilter/avfilter.h"

char info[40000]={0};

//FIX
struct URLProtocol;
/**
 * FFmpeg类库支持的协议
 * Protocol Support Information
 */
char *urlprotocolinfo() {
    memset(info, 0x00, sizeof(info));

    av_register_all();

    struct URLProtocol *pup = NULL;
    //Input
    struct URLProtocol **p_temp = &pup;
    avio_enum_protocols((void **)p_temp, 0);
    while ((*p_temp) != NULL){
        sprintf(info, "%s[In ][%10s]\n", info, avio_enum_protocols((void **)p_temp, 0));
    }
    pup = NULL;

    //Output
    avio_enum_protocols((void **)p_temp, 1);
    while ((*p_temp) != NULL){
        sprintf(info, "%s[Out][%10s]\n", info, avio_enum_protocols((void **)p_temp, 1));
    }

    return info;
}

/**
 * FFmpeg类库支持的封装格式
 * AVFormat Support Information
 */
char *avformatinfo(){
    memset(info, 0x00, sizeof(info));

    av_register_all();

    AVInputFormat *if_temp = av_iformat_next(NULL);
    AVOutputFormat *of_temp = av_oformat_next(NULL);
    //Input
    while(if_temp!=NULL){
        sprintf(info, "%s[In ][%10s]\n", info, if_temp->name);
        if_temp=if_temp->next;
    }

    //Output
    while (of_temp != NULL){
        sprintf(info, "%s[Out][%10s]\n", info, of_temp->name);
        of_temp = of_temp->next;
    }

    return info;
}

/**
 * FFmpeg类库支持的编解码器
 * AVCodec Support Information
 */
char *avcodecinfo()
{
    memset(info, 0x00, sizeof(info));

    av_register_all();

    AVCodec *c_temp = av_codec_next(NULL);

    while(c_temp!=NULL){
        if (c_temp->decode!=NULL){
            sprintf(info, "%s[Dec]", info);
        } else {
            sprintf(info, "%s[Enc]", info);
        }

        switch (c_temp->type){
            case AVMEDIA_TYPE_VIDEO:
                sprintf(info, "%s[Video]", info);
                break;
            case AVMEDIA_TYPE_AUDIO:
                sprintf(info, "%s[Audio]", info);
                break;
            default:
                sprintf(info, "%s[Other]", info);
                break;
        }
        sprintf(info, "%s[%10s]\n", info, c_temp->name);


        c_temp=c_temp->next;
    }

    return info;
}

/**
 * FFmpeg类库支持的滤镜
 * AVFilter Support Information
 */
char *avfilterinfo()
{
    memset(info, 0x00, sizeof(info));
    avfilter_register_all();
    AVFilter *f_temp = (AVFilter *)avfilter_next(NULL);
    while (f_temp != NULL){
        sprintf(info, "%s[%10s]\n", info, f_temp->name);
        f_temp = (AVFilter *)avfilter_next(f_temp);  // 此处修改了雷神的一些小错误
    }

    return info;
}

/**
 * FFmpeg类库的配置信息
 */
char *configurationinfo()
{
    memset(info, 0x00, sizeof(info));
    av_register_all();

    sprintf(info, "%s\n", avcodec_configuration());

    return info;
}


int main(int argc, char* argv[])
{
    printf("-----------------------------------------------FFmpeg类库支持的协议\n");
	printf("%s\n", urlprotocolinfo());

    printf("-----------------------------------------------FFmpeg类库支持的封装格式\n");
    printf("%s\n", avformatinfo());

    printf("-----------------------------------------------FFmpeg类库支持的编解码器\n");
    printf("%s\n", avcodecinfo());

    printf("-----------------------------------------------FFmpeg类库支持的滤镜\n");
    printf("%s\n", avfilterinfo());

    printf("-----------------------------------------------FFmpeg类库的配置信息\n");
    printf("%s\n", configurationinfo());
	return 0;
}

