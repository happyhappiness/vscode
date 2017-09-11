inline int FindBufferOffset(const DMatrix &mat){
                for(size_t i = 0; i < cache_.size(); ++i){
                    if( cache_[i].mat_ == &mat ) return cache_[i].buffer_offset_; 
                }
                return -1;
            }