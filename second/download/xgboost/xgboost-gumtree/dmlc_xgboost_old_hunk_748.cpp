            inline void CacheLoad(const char *fname, bool silent = false, bool savebuffer = true){
                int len = strlen(fname);
                if (len > 8 && !strcmp(fname + len - 7, ".buffer")){
                    this->LoadBinary(fname, silent); return;
                }
                char bname[1024];
                sprintf(bname, "%s.buffer", fname);
