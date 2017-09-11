@@ -31,7 +31,7 @@ namespace xgboost{
              * \brief a regression booter associated with training and evaluating data
              * \param mats  array of pointers to matrix whose prediction result need to be cached
              */
-            RegRankBoostLearner(const std::vector<const DMatrix *>& mats){
+            RegRankBoostLearner(const std::vector<DMatrix *>& mats){
                 silent = 0;
                 obj_ = NULL;
                 name_obj_ = "reg:linear";
@@ -45,7 +45,7 @@ namespace xgboost{
              *             data matrices to continue training otherwise it will cause error
              * \param mats  array of pointers to matrix whose prediction result need to be cached
              */          
-            inline void SetCacheData(const std::vector<const DMatrix *>& mats){
+            inline void SetCacheData(const std::vector<DMatrix *>& mats){
                 // estimate feature bound
                 int num_feature = 0;
                 // assign buffer index
@@ -58,7 +58,9 @@ namespace xgboost{
                         if( mats[i] == mats[j] ) dupilicate = true;
                     }
                     if( dupilicate ) continue;
-                    cache_.push_back( CacheEntry( mats[i], buffer_size ) );
+                    // set mats[i]'s cache learner pointer to this
+                    mats[i]->cache_learner_ptr_ = this;
+                    cache_.push_back( CacheEntry( mats[i], buffer_size, mats[i]->Size() ) );
                     buffer_size += static_cast<unsigned>(mats[i]->Size());
                     num_feature = std::max(num_feature, (int)(mats[i]->data.NumCol()));
                 }
@@ -342,17 +344,25 @@ namespace xgboost{
         private:
             struct CacheEntry{
                 const DMatrix *mat_;
-                int buffer_offset_;
-                CacheEntry(const DMatrix *mat, int buffer_offset)
-                    :mat_(mat), buffer_offset_(buffer_offset){}
+                int   buffer_offset_;
+                size_t num_row_; 
+                CacheEntry(const DMatrix *mat, int buffer_offset, size_t num_row)
+                    :mat_(mat), buffer_offset_(buffer_offset), num_row_(num_row){}
             };           
             /*! \brief the entries indicates that we have internal prediction cache */
             std::vector<CacheEntry> cache_;
         private:
             // find internal bufer offset for certain matrix, if not exist, return -1
             inline int FindBufferOffset(const DMatrix &mat){
                 for(size_t i = 0; i < cache_.size(); ++i){
-                    if( cache_[i].mat_ == &mat ) return cache_[i].buffer_offset_; 
+                    if( cache_[i].mat_ == &mat && mat.cache_learner_ptr_ == this ) {
+                        if( cache_[i].num_row_ == mat.Size() ){                            
+                            return cache_[i].buffer_offset_; 
+                        }else{
+                            fprintf( stderr, "warning: number of rows in input matrix changed as remembered in cachelist, ignore cached results\n" );
+                            fflush( stderr );
+                        }
+                    }
                 }
                 return -1;
             } 