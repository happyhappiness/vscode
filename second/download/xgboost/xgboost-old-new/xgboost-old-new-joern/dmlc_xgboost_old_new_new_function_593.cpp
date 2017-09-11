inline void SetCacheData(const std::vector<const DMatrix *> mats){
                // estimate feature bound
                int num_feature = 0;
                // assign buffer index
                unsigned buffer_size = 0;

                utils::Assert( cache_.size() == 0, "can only call cache data once" );
                for( size_t i = 0; i < mats.size(); ++i ){
                    cache_.push_back( CacheEntry( mats[i], buffer_size ) );
                    buffer_size += static_cast<unsigned>(mats[i]->Size());
                    num_feature = std::max(num_feature, (int)(mats[i]->data.NumCol()));
                }
                
                char str_temp[25];
                if (num_feature > mparam.num_feature){
                    mparam.num_feature = num_feature;
                    sprintf(str_temp, "%d", num_feature);
                    base_gbm.SetParam("bst:num_feature", str_temp);
                }

                sprintf(str_temp, "%u", buffer_size);
                base_gbm.SetParam("num_pbuffer", str_temp);
                if (!silent){
                    printf("buffer_size=%u\n", buffer_size);
                }
            }