//
// Created by lqd on 19-4-19.
//

#ifndef LINUXLEARN_CHARPTER5_H
#define LINUXLEARN_CHARPTER5_H



#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <fcntl.h>
#include <iostream>

bool is_unbuffered(FILE *pFile);

bool is_linebuffered(FILE *pFile);

int buffer_size(FILE *pFile);

void pr_stdio(const char* name,FILE* fp);

//region // 5.2 流和FILE对象
/* int fwide(FILE *fp,int mode) 设置流的定向
 * 返回值：若流是定向的，返回正值，若流是字节定向的返回负值，若流是为定向的，返回0
 * 参数：mode 为负，fwide 将试图使指定的流是字节定向的、
 *      mode 为正，fwide 将试图使指定的流是宽定向的、
 *      mode 为0，fwide 返回f的流定向值、
 * */
void test_fwide(){
    FILE *f;
    int ret = fwide(f,1);
}
//endregion

//region //5.4 缓冲
/*  全缓冲：磁盘文件为全缓冲
 *  行缓冲：终端的标准输入输出为行缓冲
 *  无缓冲：标准错误流stderr无缓冲
 *
 *  void setbuf (FILE *__restrict __stream, char *__restrict __buf)
 *  参数：buf非空：长度为BUFSIZ的用户缓冲区buf
 *       buf为空：无缓冲
 *
 *  nt setvbuf (FILE *__restrict __stream, char *__restrict __buf,int __modes, size_t __n)
 *  参数：mode：_IOFBF _IOLBF _IONBF
 * */
void test_buffer(){
    FILE *f;
    setbuf(f, nullptr);

    char *buf;
    setvbuf(f,buf,_IOFBF, sizeof(buf));
}
//endregion

//region //5.5 打开流
/* 打开指定路径的文件
 * FILE *fopen (const char *__restrict __filename,const char *__restrict __modes)
 *
 * 在指定的流上打开文件，如果流已经打开，则先关闭再打开。如果流已经定向，则使用freopen清除定向
 *  FILE *freopen (const char *__restrict __filename,const char *__restrict __modes,FILE *__restrict __stream)
 *
 *  使用已有的文件描述符打开
 *  FILE *fdopen (int __fd, const char *__modes)
 *
 *  关闭流
 *  int fclose(FILE *fp)
 *
 * */
void test_open(){
    const char * pathname = "test.txt";
    FILE *f = fopen(pathname,"wb");

    const char* pathname1 = "test1.txt";
    FILE *f1 = freopen(pathname1,O_RDONLY,f);

    FILE *f2 = fdopen(1,"r");
}
//endregion


//region //5.6读和写流
/*
 *  每次一个字符：getc(FILE *fp);fgetc(FILE *fp);getchar(FILE *fp);
 *  每次一行：fgets(); gets(); fputs(); puts();
 *  直接I/O: fread fwrite
 *
 *  错误处理：
 *      ferror()
 *      feof()
 *      clearerr()
 *
 *   将读取到的数据重新亚辉流
 *   ungetc(int c,FILE *fp);
 *
 * */
void test_get(){

}
//endregion


//region //5.10定位流
/*
 *  获取文件位置
 *  ftell(); ftello(); fgetpos()
 *
 *  设置文件位置
 *  fseek(); fseeko(); fsetpos()
 *
 *  rewind(FILE *fp)
 * */

void test_seek(){

}
//endregion

//5.11格式化I/O
/*
 *  格式化输出：
 *  printf()：格式化数据写到标准输出
 *  fprintf():写到指定的流
 *  dprintf()：写到指定的文件描述符
 *  sprintf()：格式化字符写入buf，自动追加结束符'\0'
 *  snprintf()：与sprintf()相同但是可以指定缓冲区长度，超过的会被丢弃
 *
 *  转换说明：
 *  %[flags] [fldwidth] [precision] [lenmodifier] convtype
 *
 *  flags:
 *      '   : 将整数按千位分组字符
 *      -   : 在字段内左对齐输出
 *      +   : 总是显示带符号转换的正负号
 *      空格 : 如果第一个字符不是正负号，则在其前面加一个空格
 *      #   : 指定另一种转化格式（如十六进制 加 0x 前缀）
 *      0   : 添加前导0 进行填充
 *
 *  fldwidth: 说明最小字段宽度，如果转换后长度不够多余的用空格填充
 *  precision : 说明整型转换后最少输出数字位数，浮点数转换后小数点后的最少位数 .后面跟随一个非负数
 *  lenmodifier:
 *      hh  : 将相应的参数按signed或unsigned char类型输出
 *      h   ：将对应的参数按signed或unsigned short类型输出
 *      l   ：将对应的参数按signed或unsigned long类型输出
 *      ll  ：将对应的参数按signed或unsigned long long类型输出
 *      j   : intmax_t或 uintmax_t
 *      z   :size_t
 *      t   :ptrdiff_t
 *      L   :long double
 *
 *  convtype:
 *      d、i : 有符号十进制
 *      o   ：无符号八进制
 *      u   ：无符号十进制
 *      x、X ：无符号十六进制
 *      f、F ：双精度浮点数
 *      e、E ：指数格式双精度浮点数
 *      g、G ：根据转换后的值解释为f、F、e、G
 *      a、A ： 十六进制指数格式双精度浮点数
 *      c   ：字符
 *      s   ：字符串
 *      p   ：指向void的指针
 *      n   ：
 *      %   ：%字符
 *      C   ：宽字符
 *      S   ：宽字符串
 *
 *
 *
 *  格式化输入：
 *  scanf()
 *  fscanf()
 *  sscanf()
 *
 *  转换说明：
 *  %[*] [fldwidth] [m] [lenmodifier] convtype
 *
 *  convtype 与输出转换相同，增加：
 *      [   :匹配列出的字符序列，以]结束
 *      [^  :匹配除列出字符以外的所有字符，以]终止
 *
 * */

//5.12实现细节
/*
 * int fileno(FILE *fp) 获取文件描述符
 * */
void test_io(){
    FILE *fp;
    fputs("enter any character\n",stdout);
    if(getchar() == EOF){
        std::cout<<"getchar error";
    }
    fputs("one line to standard error\n",stderr);
    pr_stdio("stdin",stdin);

    pr_stdio("stdout",stdout);

    pr_stdio("stderror",stderr);

    if((fp = fopen("/etc/passwd","r")) == nullptr){
        printf("fopen error\n");
    }
    if(getc(fp) == EOF){
        printf("getc error\n");
    }
    pr_stdio("/etc/passwd",fp);

}



void pr_stdio(const char* name,FILE* fp){
    if(is_unbuffered(fp)){
        printf("unbuffered\n");
    }
    else if(is_linebuffered(fp)){
        printf("line buffered\n");
    }
    else{
        printf("fully buffered\n");
    }
    printf("%s , buffer size = %d\n",name,buffer_size(fp));
}

#if defined(_IO_UNBUFFERED)
int  buffer_size(FILE *pFile) {
    return  int(pFile->_IO_buf_end-pFile->_IO_buf_base);
}

bool is_linebuffered(FILE *pFile) {
    return pFile->_flags & _IO_LINE_BUF;
}

bool is_unbuffered(FILE *pFile) {
    return pFile->_flags & _IO_UNBUFFERED;
}

#elif defined(__SNBF)
int  buffer_size(FILE *pFile) {
    return  pFile->_bf._size;
}

bool is_linebuffered(FILE *pFile) {
    return pFile->_flags & __SNBF;
}

bool is_unbuffered(FILE *pFile) {
    return pFile->_flags & __SLBF;
}

#elif defined(_IONBF)

#ifdef _LP64
#define _flag __pad[4]
#define _ptr __pad[1]
#define _base __pad[2]
#endif

int  buffer_size(FILE *pFile) {
#ifdef _LP64
    return  pFile->_base -fp->_ptr;
#else
    return BUFSIZ;
#endif
}

bool is_linebuffered(FILE *pFile) {
    return pFile->_flags & _IOLBF;
}

bool is_unbuffered(FILE *pFile) {
    return pFile->_flags & _IONBF;
}

#else

#error unknown stdio
#endif

//5.13临时文件
/*
 * char *tmpnam(char *ptr): 产生一个与现有文件名不同的一个有效路径名 字符串 ptr位NULL 产生的路径名存放在静态区
 * FILE *tmpfile(void):创建一个临时二进制文件(wb+)，程序结束或文件关闭自动删除
 *
 *
 * */

void test_temp(){
    char name[L_tmpnam];
    char line[1024];
    FILE *fp;
    printf("ptr null tmpnam: %s\n",tmpnam(nullptr));

    tmpnam(name);
    printf("name by tmpnam:%s\n",name);

    if((fp = tmpfile()) == nullptr){
        printf("create tmpfile failed\n");
    }
    fputs("one line of output\n",fp);
    rewind(fp);
    if(fgets(line, sizeof(line),fp) == nullptr){
        printf("fgets error\n");
    }
    fputs(line,stdout);
}


/*
 * char *mkdtemp(char *template):创建一个目录，该目录有一个唯一的名字
 * int mkstemp(char *template):创建一个文件，改文件有个一唯一的名字，名字通过template选择，后六位位xxxxxx
 *              mkstemp产生的文件不会自动删除，如果想自动删除必须unlink
 *
 *
 * */

#include <errno.h>
#include <err.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <cstring>

void make_temp(char *_template);

void test_temp1(){
    printf(" 10test_temp1");

    char good_template[] = "/tmp/dirXXXXXX";
    const char *bad_template = "tmp/dirXXXXXX";
    printf("trying to create temp file\n");
    make_temp(good_template);
    //make_temp(bad_template);
}

void make_temp(char *_template){
    int fd;
    struct stat sbuf;
    if((fd = mkstemp(_template))<0){
        printf("create temp file failed\n");
    }
    printf("template name = %s\n",_template);
    unlink(_template);
    close(fd);
    if (stat(_template,&sbuf) <0){
        if (errno == ENOENT){
            printf("file does not exist\n");
        }
        else{
            printf("stat failed\n");
        }
    }
    else{
        printf("file exist\n");
    }

}


//5.14内存流
/*
 * FILE *fmemopen (void *__s, size_t __len, const char *__modes)：
 *      __s指向缓冲区的开始位置，__len指定缓冲区的大小，如果__s为空 自动分配__len字节的缓冲区，这时关闭流缓冲区自动释放
 *
 * note：
 *      一、任何时候以追加的方式打开内存流，当前文件位置设为缓冲区中第一个null字节、如果缓冲区不存在null，则当前位置设为缓冲区结尾的后一个字节
 *      如果不是以追加的方式打开，当前位置设为缓冲区的开始位置。内存流不合适存储二进制数据
 *      二、__s为空，内存流无任何意义
 *      三、任何时候调用fclose、fflush、fseek、fseeko、fsetpos都会在当前位置写入一个null字节
 *
 *  open_memstream(): 创建的流只能写打开、不能指定自己的缓冲区，但可以通过buf和size访问缓冲区地址和大小，关闭流后需要自行释放缓冲区，对流添加字节会增加缓冲区大小
 *  open_wmemstream();
 *
 * */


#define BSZ 48

void test_mem_io(){
    printf("*************test_mem_io****************");
    FILE *fp;
    char buf[BSZ];

    memset(buf,'a',BSZ-2);
    buf[BSZ-2] = '\0';
    buf[BSZ-1] = 'X';
    if((fp = fmemopen(buf,BSZ,"w+"))== nullptr){
        printf("fmemopen failed\n");
    }
    printf("initial buffer contents: %s\n",buf);
    fprintf(fp,"hello world");
    printf("before flush: %s\n",buf);
    fflush(fp);
    printf("after fflush: %s\n",buf);
    printf("len of buf: %d\n",strlen(buf));

    memset(buf,'b',BSZ-2);
    buf[BSZ-2] = '\0';
    buf[BSZ-1] = 'X';
    fprintf(fp,"hello,world");
    fseek(fp,0,SEEK_SET);
    printf("after seek:%s\n",buf);
    printf("len of buf:%d\n",strlen(buf));

    memset(buf,'c',BSZ-2);
    buf[BSZ-2] = '\0';
    buf[BSZ-1] = 'X';
    fprintf(fp,"hello ,world");
    fclose(fp);
    printf("after fclose: %s\n",buf);

}







#endif //LINUXLEARN_CHARPTER5_H
