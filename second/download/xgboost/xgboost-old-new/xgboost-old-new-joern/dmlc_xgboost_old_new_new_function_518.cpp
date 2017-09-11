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