        private:
            struct CacheEntry{
                const DMatrix *mat_;
                int   buffer_offset_;
                size_t num_row_; 
                CacheEntry(const DMatrix *mat, int buffer_offset, size_t num_row)
                    :mat_(mat), buffer_offset_(buffer_offset), num_row_(num_row){}
            };           
            /*! \brief the entries indicates that we have internal prediction cache */
            std::vector<CacheEntry> cache_;
        private:
            // find internal bufer offset for certain matrix, if not exist, return -1
            inline int FindBufferOffset(const DMatrix &mat){
                for(size_t i = 0; i < cache_.size(); ++i){
                    if( cache_[i].mat_ == &mat && mat.cache_learner_ptr_ == this ) {
                        if( cache_[i].num_row_ == mat.Size() ){                            
                            return cache_[i].buffer_offset_; 
                        }else{
                            fprintf( stderr, "warning: number of rows in input matrix changed as remembered in cachelist, ignore cached results\n" );
                            fflush( stderr );
                        }
                    }
                }
                return -1;
            } 
