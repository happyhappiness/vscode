inline bool LoadBinary(const char* fname, bool silent = false){
                FILE *fp = fopen64(fname, "rb");
                if (fp == NULL) return false;
                utils::FileStream fs(fp);
                data.LoadBinary(fs);
                info.labels.resize(data.NumRow());
                utils::Assert(fs.Read(&info.labels[0], sizeof(float)* data.NumRow()) != 0, "DMatrix LoadBinary");
                {// load in group ptr
                    unsigned ngptr;
                    if( fs.Read(&ngptr, sizeof(unsigned) ) != 0 ){
                        info.group_ptr.resize( ngptr );
                        utils::Assert( fs.Read(&info.group_ptr[0], sizeof(unsigned) * ngptr) != 0, "Load group file");
                        if( ngptr != 0 ){
                            utils::Assert( fs.Read(&info.group_ptr[0], sizeof(unsigned) * ngptr) != 0, "Load group file");
                            utils::Assert( info.group_ptr.back() == data.NumRow(), "number of group must match number of record" );
                        }
                    }
                }
                fs.Close();
                
                if (!silent){
                    printf("%ux%u matrix with %lu entries is loaded from %s\n",
                           (unsigned)data.NumRow(), (unsigned)data.NumCol(), (unsigned long)data.NumEntry(), fname);
                    if( info.group_ptr.size() != 0 ){
                        printf("data contains %u groups\n", (unsigned)info.group_ptr.size()-1 );
                    }
                }
                this->TryLoadWeight(fname, silent);
                return true;
            }