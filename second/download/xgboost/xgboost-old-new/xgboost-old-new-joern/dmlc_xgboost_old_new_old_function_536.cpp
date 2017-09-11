inline static void LoadBinary(utils::IStream &fi,
                std::vector<size_t> &ptr,
                std::vector<REntry> &data){
                size_t nrow;
                utils::Assert(fi.Read(&nrow, sizeof(size_t)) != 0, "Load FMatrixS");
                ptr.resize(nrow + 1);
                utils::Assert(fi.Read(&ptr[0], ptr.size() * sizeof(size_t)), "Load FMatrixS");

                data.resize(ptr.back());
                if (data.size() != 0){
                    utils::Assert(fi.Read(&data[0], data.size() * sizeof(REntry)), "Load FMatrixS");
                }
            }