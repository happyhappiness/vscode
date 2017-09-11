@@ -31,7 +31,7 @@ namespace xgboost{
              * \brief a regression booter associated with training and evaluating data
              * \param mats  array of pointers to matrix whose prediction result need to be cached
              */
-            RegRankBoostLearner(const std::vector<const DMatrix *> mats){
+            RegRankBoostLearner(const std::vector<const DMatrix *>& mats){
                 silent = 0;
                 obj_ = NULL;
                 name_obj_ = "reg";
@@ -45,14 +45,19 @@ namespace xgboost{
              *             data matrices to continue training otherwise it will cause error
              * \param mats  array of pointers to matrix whose prediction result need to be cached
              */          
-            inline void SetCacheData(const std::vector<const DMatrix *> mats){
+            inline void SetCacheData(const std::vector<const DMatrix *>& mats){
                 // estimate feature bound
                 int num_feature = 0;
                 // assign buffer index
                 unsigned buffer_size = 0;
-
+                
                 utils::Assert( cache_.size() == 0, "can only call cache data once" );
                 for( size_t i = 0; i < mats.size(); ++i ){
+                    bool dupilicate = false;
+                    for( size_t j = 0; j < i; ++ j ){
+                        if( mats[i] == mats[j] ) dupilicate = true;
+                    }
+                    if( dupilicate ) continue;
                     cache_.push_back( CacheEntry( mats[i], buffer_size ) );
                     buffer_size += static_cast<unsigned>(mats[i]->Size());
                     num_feature = std::max(num_feature, (int)(mats[i]->data.NumCol()));
@@ -105,9 +110,18 @@ namespace xgboost{
                 mparam.AdjustBase();
             }
             /*!
-            * \brief load model from stream
-            * \param fi input stream
-            */
+             * \brief load model from file 
+             * \param fname file name
+             */
+            inline void LoadModel(const char *fname){
+                utils::FileStream fi(utils::FopenCheck(fname, "rb"));
+                this->LoadModel(fi);
+                fi.Close();                
+            }
+            /*!
+             * \brief load model from stream
+             * \param fi input stream
+             */
             inline void LoadModel(utils::IStream &fi){
                 base_gbm.LoadModel(fi);
                 utils::Assert(fi.Read(&mparam, sizeof(ModelParam)) != 0);
@@ -138,10 +152,18 @@ namespace xgboost{
                 fo.Write(&mparam, sizeof(ModelParam));
             }
             /*!
+             * \brief save model into file
+             * \param fname file name
+             */
+            inline void SaveModel(const char *fname) const{
+                utils::FileStream fo(utils::FopenCheck(fname, "wb"));
+                this->SaveModel(fo);
+                fo.Close();                
+            }
+            /*!
              * \brief update the model for one iteration
-             * \param iteration iteration number
              */
-            inline void UpdateOneIter(int iter, const DMatrix &train){
+            inline void UpdateOneIter(const DMatrix &train){
                 this->PredictRaw(preds_, train);
                 obj_->GetGradient(preds_, train.info, base_gbm.NumBoosters(), grad_, hess_);
                 // do boost
@@ -295,7 +317,7 @@ namespace xgboost{
                 }
                 return -1;
             } 
-        private:
+        protected:
             int silent;
             EvalSet evaluator_;
             booster::GBMBase base_gbm;
@@ -305,7 +327,7 @@ namespace xgboost{
             // name of objective function
             std::string name_obj_;
             std::vector< std::pair<std::string, std::string> > cfg_;
-        private:
+        protected:
             std::vector<float> grad_, hess_, preds_;
         };
     }