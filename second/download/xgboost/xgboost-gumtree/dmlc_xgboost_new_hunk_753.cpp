                name_obj_ = "reg";
            }
            /*!
             * \brief a regression booter associated with training and evaluating data
             * \param mats  array of pointers to matrix whose prediction result need to be cached
             */
            RegRankBoostLearner(const std::vector<const DMatrix *> mats){
                silent = 0;
                obj_ = NULL;
                name_obj_ = "reg";
                this->SetCacheData(mats);
            }            
            /*!
             * \brief add internal cache space for mat, this can speedup prediction for matrix,
             *        please cache prediction for training and eval data
             *    warning: if the model is loaded from file from some previous training history
             *             set cache data must be called with exactly SAME 
             *             data matrices to continue training otherwise it will cause error
             * \param mats  array of pointers to matrix whose prediction result need to be cached
             */          
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
