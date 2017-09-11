             *             data matrices to continue training otherwise it will cause error
             * \param mats  array of pointers to matrix whose prediction result need to be cached
             */          
            inline void SetCacheData(const std::vector<const DMatrix *>& mats){
                // estimate feature bound
                int num_feature = 0;
                // assign buffer index
                unsigned buffer_size = 0;
                
                utils::Assert( cache_.size() == 0, "can only call cache data once" );
                for( size_t i = 0; i < mats.size(); ++i ){
                    bool dupilicate = false;
                    for( size_t j = 0; j < i; ++ j ){
                        if( mats[i] == mats[j] ) dupilicate = true;
                    }
                    if( dupilicate ) continue;
                    cache_.push_back( CacheEntry( mats[i], buffer_size ) );
                    buffer_size += static_cast<unsigned>(mats[i]->Size());
                    num_feature = std::max(num_feature, (int)(mats[i]->data.NumCol()));
