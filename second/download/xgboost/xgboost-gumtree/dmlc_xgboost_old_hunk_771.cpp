            inline void LoadText(FILE *fi){
                int fid;
                char fname[256], ftype[256];
                while (fscanf(fi, "%d%s%s", &fid, fname, ftype) == 3){
                    utils::Assert(fid == (int)names_.size(), "invalid fmap format");
                    names_.push_back(std::string(fname));
                    types_.push_back(GetType(ftype));
