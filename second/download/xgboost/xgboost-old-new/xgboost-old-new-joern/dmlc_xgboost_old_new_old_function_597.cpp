inline bool LoadBinary(const char* fname, bool silent = false){
                FILE *fp = fopen64(fname, "rb");
                if (fp == NULL) return false;
                utils::FileStream fs(fp);
                data.LoadBinary(fs);
                info.labels.resize(data.NumRow());
                utils::Assert(fs.Read(&info.labels[0], sizeof(float)* data.NumRow()) != 0, "DMatrix LoadBinary");
                fs.Close();
                // initialize column support as well
                data.InitData();
                
                if (!silent){
                    printf("%ux%u matrix with %lu entries is loaded from %s\n",
                           (unsigned)data.NumRow(), (unsigned)data.NumCol(), (unsigned long)data.NumEntry(), fname);
                }
                this->TryLoadGroup(fname, silent);
                this->TryLoadWeight(fname, silent);
                return true;
            }