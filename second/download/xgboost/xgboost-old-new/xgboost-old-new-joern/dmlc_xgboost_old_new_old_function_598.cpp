inline void SaveBinary(const char* fname, bool silent = false){
                // initialize column support as well
                data.InitData();
                
                utils::FileStream fs(utils::FopenCheck(fname, "wb"));
                data.SaveBinary(fs);
                fs.Write(&info.labels[0], sizeof(float)* data.NumRow());
                fs.Close();
                if (!silent){
                    printf("%ux%u matrix with %lu entries is saved to %s\n",
                       (unsigned)data.NumRow(), (unsigned)data.NumCol(), (unsigned long)data.NumEntry(), fname);
                }
            }