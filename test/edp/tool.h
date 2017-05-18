#ifndef _H_EDP_UNITTEST_TOOL_H_
#define _H_EDP_UNITTEST_TOOL_H_

#include <stdio.h>
#ifdef __cplusplus
extern "C"{
#endif

    class Tool{
    public:
        static void Dump(const char* name, const char* data, int len){
            printf("%s len = %d\n", name , len);
            unsigned char * p = (unsigned char*)data;
            for (int i = 0; i < len; i++)
            {
                printf("%02X ", (unsigned)p[i]);
                if ((i+1) % 10 == 0)
                    putchar('\n');
            }
            putchar('\n');
        }
    };

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif
