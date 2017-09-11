            }
            return fp;
        }

        /*! \brief replace fopen, */
        inline FILE *FopenTry(const char *fname, const char *flag){
            FILE *fp = fopen64(fname, flag);
            if (fp == NULL){
                fprintf(stderr, "can not open file \"%s\"\n", fname);
                exit(-1);
            }
            return fp;
        }
    };
};

