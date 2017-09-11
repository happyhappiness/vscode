            inline void CacheLoad(const char *fname, bool silent = false, bool savebuffer = true){
                int len = strlen(fname);
                if (len > 8 && !strcmp(fname + len - 7, ".buffer")){
                    if( !this->LoadBinary(fname, silent) ){
                        fprintf(stderr,"can not open file \"%s\"", fname);
                        utils::Error("DMatrix::CacheLoad failed");
                    }
                    return;
                }
                char bname[1024];
                sprintf(bname, "%s.buffer", fname);
