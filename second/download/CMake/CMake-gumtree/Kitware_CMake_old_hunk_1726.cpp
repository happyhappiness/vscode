#define TEST_NEED_SUCK

void *suck(int *);



int main(int argc, char **argv, char **envp) {

        char *base64;

        int base64Len;

        unsigned char *data;

        int dataLen;

        

        base64 = (char *)suck(&base64Len);

        data = (unsigned char *)malloc(base64Len * 3/4 + 8);

        dataLen = Curl_base64_decode(base64, data);



        fprintf(stderr, "%d\n", dataLen);

        fwrite(data,1,dataLen,stdout);

        



        free(base64); free(data);

        return 0;

}

#endif



#ifdef TEST_NEED_SUCK

/* this function 'sucks' in as much as possible from stdin */

void *suck(int *lenptr) {

        int cursize = 8192;

        unsigned char *buf = NULL;

        int lastread;

        int len = 0;

        

        do {

                cursize *= 2;

                buf = (unsigned char *)realloc(buf, cursize);

                memset(buf + len, 0, cursize - len);

                lastread = fread(buf + len, 1, cursize - len, stdin);

                len += lastread;

        } while(!feof(stdin));

        

        lenptr[0] = len;

        return (void *)buf;

}

#endif





/*

 * local variables:

 * eval: (load-file "../curl-mode.el")
