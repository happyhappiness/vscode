             * \return the row id added line
             */
            inline size_t AddRow(const std::vector<bst_uint> &findex,
                const std::vector<bst_float> &fvalue,
                unsigned fstart = 0, unsigned fend = UINT_MAX){
                utils::Assert(findex.size() == fvalue.size());
                unsigned cnt = 0;
                for (size_t i = 0; i < findex.size(); i++){
