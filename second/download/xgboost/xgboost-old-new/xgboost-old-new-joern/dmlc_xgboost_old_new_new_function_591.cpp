inline FILE *FopenCheck(const char *fname, const char *flag){
            FILE *fp = fopen64(fname, flag);
            if (fp == NULL){
                fprintf(stderr, "can not open file \"%s\" \n", fname);
                fflush(stderr);
                exit(-1);
            }
            return fp;
        }