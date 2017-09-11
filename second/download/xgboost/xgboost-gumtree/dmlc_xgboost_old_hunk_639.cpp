        private:
            struct CacheEntry{
                const DMatrix *mat_;
                int buffer_offset_;
                CacheEntry(const DMatrix *mat, int buffer_offset)
                    :mat_(mat), buffer_offset_(buffer_offset){}
            };           
            /*! \brief the entries indicates that we have internal prediction cache */
            std::vector<CacheEntry> cache_;
        private:
            // find internal bufer offset for certain matrix, if not exist, return -1
            inline int FindBufferOffset(const DMatrix &mat){
                for(size_t i = 0; i < cache_.size(); ++i){
                    if( cache_[i].mat_ == &mat ) return cache_[i].buffer_offset_; 
                }
                return -1;
            } 
