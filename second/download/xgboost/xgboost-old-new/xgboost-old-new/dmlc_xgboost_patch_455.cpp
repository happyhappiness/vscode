@@ -28,40 +28,36 @@ namespace xgboost{
                 name_obj_ = "reg";
             }
             /*!
-            * \brief a regression booter associated with training and evaluating data
-            * \param train pointer to the training data
-            * \param evals array of evaluating data
-            * \param evname name of evaluation data, used print statistics
-            */
-            RegRankBoostLearner(const DMatrix *train,
-                                const std::vector<DMatrix *> &evals,
-                                const std::vector<std::string> &evname){
+             * \brief a regression booter associated with training and evaluating data
+             * \param mats  array of pointers to matrix whose prediction result need to be cached
+             */
+            RegRankBoostLearner(const std::vector<const DMatrix *> mats){
                 silent = 0;
-                this->SetData(train, evals, evname);
-            }
-
+                obj_ = NULL;
+                name_obj_ = "reg";
+                this->SetCacheData(mats);
+            }            
             /*!
-            * \brief associate regression booster with training and evaluating data
-            * \param train pointer to the training data
-            * \param evals array of evaluating data
-            * \param evname name of evaluation data, used print statistics
-            */
-            inline void SetData(const DMatrix *train,
-                                const std::vector<DMatrix *> &evals,
-                                const std::vector<std::string> &evname){
-                this->train_ = train;
-                this->evals_ = evals;
-                this->evname_ = evname;
+             * \brief add internal cache space for mat, this can speedup prediction for matrix,
+             *        please cache prediction for training and eval data
+             *    warning: if the model is loaded from file from some previous training history
+             *             set cache data must be called with exactly SAME 
+             *             data matrices to continue training otherwise it will cause error
+             * \param mats  array of pointers to matrix whose prediction result need to be cached
+             */          
+            inline void SetCacheData(const std::vector<const DMatrix *> mats){
                 // estimate feature bound
-                int num_feature = (int)(train->data.NumCol());
+                int num_feature = 0;
                 // assign buffer index
-                unsigned buffer_size = static_cast<unsigned>(train->Size());
+                unsigned buffer_size = 0;
 
-                for (size_t i = 0; i < evals.size(); ++i){
-                    buffer_size += static_cast<unsigned>(evals[i]->Size());
-                    num_feature = std::max(num_feature, (int)(evals[i]->data.NumCol()));
+                utils::Assert( cache_.size() == 0, "can only call cache data once" );
+                for( size_t i = 0; i < mats.size(); ++i ){
+                    cache_.push_back( CacheEntry( mats[i], buffer_size ) );
+                    buffer_size += static_cast<unsigned>(mats[i]->Size());
+                    num_feature = std::max(num_feature, (int)(mats[i]->data.NumCol()));
                 }
-
+                
                 char str_temp[25];
                 if (num_feature > mparam.num_feature){
                     mparam.num_feature = num_feature;
@@ -74,15 +70,13 @@ namespace xgboost{
                 if (!silent){
                     printf("buffer_size=%u\n", buffer_size);
                 }
-
-                // set eval_preds tmp sapce
-                this->eval_preds_.resize(evals.size(), std::vector<float>());
             }
+
             /*!
-            * \brief set parameters from outside
-            * \param name name of the parameter
-            * \param val  value of the parameter
-            */
+             * \brief set parameters from outside
+             * \param name name of the parameter
+             * \param val  value of the parameter
+             */
             inline void SetParam(const char *name, const char *val){
                 if (!strcmp(name, "silent"))  silent = atoi(val);
                 if (!strcmp(name, "eval_metric"))  evaluator_.AddEval(val);
@@ -104,8 +98,8 @@ namespace xgboost{
                 evaluator_.AddEval( obj_->DefaultEvalMetric() );
             }
             /*!
-            * \brief initialize the current data storage for model, if the model is used first time, call this function
-            */
+             * \brief initialize the current data storage for model, if the model is used first time, call this function
+             */
             inline void InitModel(void){
                 base_gbm.InitModel();
                 mparam.AdjustBase();
@@ -147,74 +141,66 @@ namespace xgboost{
              * \brief update the model for one iteration
              * \param iteration iteration number
              */
-            inline void UpdateOneIter(int iter){
-                this->PredictBuffer(preds_, *train_, 0);
-                obj_->GetGradient(preds_, train_->info, base_gbm.NumBoosters(), grad_, hess_);
+            inline void UpdateOneIter(int iter, const DMatrix &train){
+                this->PredictRaw(preds_, train);
+                obj_->GetGradient(preds_, train.info, base_gbm.NumBoosters(), grad_, hess_);
+                // do boost
                 std::vector<unsigned> root_index;
-                base_gbm.DoBoost(grad_, hess_, train_->data, root_index);
+                base_gbm.DoBoost(grad_, hess_, train.data, root_index);
             }
             /*!
              * \brief evaluate the model for specific iteration
              * \param iter iteration number
+             * \param evals datas i want to evaluate
+             * \param evname name of each dataset
              * \param fo file to output log
              */
-            inline void EvalOneIter(int iter, FILE *fo = stderr){
+            inline void EvalOneIter(int iter,
+                                    const std::vector<const DMatrix*> &evals,
+                                    const std::vector<std::string> &evname,
+                                    FILE *fo=stderr ){
                 fprintf(fo, "[%d]", iter);
-                int buffer_offset = static_cast<int>(train_->Size());
-
-                for (size_t i = 0; i < evals_.size(); ++i){
-                    std::vector<float> &preds = this->eval_preds_[i];
-                    this->PredictBuffer(preds, *evals_[i], buffer_offset);
-                    obj_->PredTransform(preds);
-                    evaluator_.Eval(fo, evname_[i].c_str(), preds, evals_[i]->info);
-                    buffer_offset += static_cast<int>(evals_[i]->Size());
+                for (size_t i = 0; i < evals.size(); ++i){
+                    this->PredictRaw(preds_, *evals[i]);
+                    obj_->PredTransform(preds_);
+                    evaluator_.Eval(fo, evname[i].c_str(), preds_, evals[i]->info);
                 }
                 fprintf(fo, "\n");
                 fflush(fo);
             }
             /*! \brief get prediction, without buffering */
             inline void Predict(std::vector<float> &preds, const DMatrix &data){
-                preds.resize(data.Size());
-                const unsigned ndata = static_cast<unsigned>(data.Size());
-                #pragma omp parallel for schedule( static )
-                for (unsigned j = 0; j < ndata; ++j){
-                    preds[j] = mparam.base_score + base_gbm.Predict(data.data, j, -1);
-                }
+                this->PredictRaw(preds,data);
                 obj_->PredTransform( preds );
             }            
         public:
             /*!
              * \brief interactive update 
              * \param action action type 
+             * \parma train training data
              */
-            inline void UpdateInteract(std::string action){
-                this->InteractPredict(preds_, *train_, 0);
-
-                int buffer_offset = static_cast<int>(train_->Size());
-                for (size_t i = 0; i < evals_.size(); ++i){
-                    std::vector<float> &preds = this->eval_preds_[i];
-                    this->InteractPredict(preds, *evals_[i], buffer_offset);
-                    buffer_offset += static_cast<int>(evals_[i]->Size());
+            inline void UpdateInteract(std::string action, const DMatrix& train){
+                for(size_t i = 0; i < cache_.size(); ++i){
+                    this->InteractPredict(preds_, *cache_[i].mat_);
                 }
 
                 if (action == "remove"){
                     base_gbm.DelteBooster(); return;
                 }
 
-                obj_->GetGradient(preds_, train_->info, base_gbm.NumBoosters(), grad_, hess_);
+                obj_->GetGradient(preds_, train.info, base_gbm.NumBoosters(), grad_, hess_);
                 std::vector<unsigned> root_index;
-                base_gbm.DoBoost(grad_, hess_, train_->data, root_index);
+                base_gbm.DoBoost(grad_, hess_, train.data, root_index);
 
-                this->InteractRePredict(*train_, 0);
-                buffer_offset = static_cast<int>(train_->Size());
-                for (size_t i = 0; i < evals_.size(); ++i){
-                    this->InteractRePredict(*evals_[i], buffer_offset);
-                    buffer_offset += static_cast<int>(evals_[i]->Size());
+                for(size_t i = 0; i < cache_.size(); ++i){
+                    this->InteractRePredict(*cache_[i].mat_);
                 }
             }
         private:
             /*! \brief get the transformed predictions, given data */
-            inline void InteractPredict(std::vector<float> &preds, const DMatrix &data, unsigned buffer_offset){
+            inline void InteractPredict(std::vector<float> &preds, const DMatrix &data){
+                int buffer_offset = this->FindBufferOffset(data);
+                utils::Assert( buffer_offset >=0, "interact mode must cache training data" );
                 preds.resize(data.Size());
                 const unsigned ndata = static_cast<unsigned>(data.Size());
                 #pragma omp parallel for schedule( static )
@@ -224,21 +210,34 @@ namespace xgboost{
                 obj_->PredTransform( preds );
             }
             /*! \brief repredict trial */
-            inline void InteractRePredict(const DMatrix &data, unsigned buffer_offset){
+            inline void InteractRePredict(const DMatrix &data){
+                int buffer_offset = this->FindBufferOffset(data);
+                utils::Assert( buffer_offset >=0, "interact mode must cache training data" );
                 const unsigned ndata = static_cast<unsigned>(data.Size());
                 #pragma omp parallel for schedule( static )
                 for (unsigned j = 0; j < ndata; ++j){
                     base_gbm.InteractRePredict(data.data, j, buffer_offset + j);
                 }
             }
         private:
-            /*! \brief get the transformed predictions, given data */
-            inline void PredictBuffer(std::vector<float> &preds, const DMatrix &data, unsigned buffer_offset){
+            /*! \brief get un-transformed prediction*/
+            inline void PredictRaw(std::vector<float> &preds, const DMatrix &data){
+                this->PredictBuffer(preds, data, this->FindBufferOffset(data) );
+            }
+            /*! \brief get the un-transformed predictions, given data */
+            inline void PredictBuffer(std::vector<float> &preds, const DMatrix &data, int buffer_offset){
                 preds.resize(data.Size());
                 const unsigned ndata = static_cast<unsigned>(data.Size());
-                #pragma omp parallel for schedule( static )
-                for (unsigned j = 0; j < ndata; ++j){
-                    preds[j] = mparam.base_score + base_gbm.Predict(data.data, j, buffer_offset + j);
+                if( buffer_offset >= 0 ){  
+                    #pragma omp parallel for schedule( static )
+                    for (unsigned j = 0; j < ndata; ++j){
+                        preds[j] = mparam.base_score + base_gbm.Predict(data.data, j, buffer_offset + j);
+                    }
+                }else
+                    #pragma omp parallel for schedule( static )
+                    for (unsigned j = 0; j < ndata; ++j){
+                        preds[j] = mparam.base_score + base_gbm.Predict(data.data, j, -1);
+                    }{
                 }
             }
         private:
@@ -260,10 +259,10 @@ namespace xgboost{
                     memset(reserved, 0, sizeof(reserved));
                 }
                 /*!
-                * \brief set parameters from outside
-                * \param name name of the parameter
-                * \param val  value of the parameter
-                */
+                 * \brief set parameters from outside
+                 * \param name name of the parameter
+                 * \param val  value of the parameter
+                 */
                 inline void SetParam(const char *name, const char *val){
                     if (!strcmp("base_score", name))  base_score = (float)atof(val);
                     if (!strcmp("loss_type", name))   loss_type = atoi(val);
@@ -280,22 +279,34 @@ namespace xgboost{
                 }
             };
         private:
+            struct CacheEntry{
+                const DMatrix *mat_;
+                int buffer_offset_;
+                CacheEntry(const DMatrix *mat, int buffer_offset)
+                    :mat_(mat), buffer_offset_(buffer_offset){}
+            };           
+            /*! \brief the entries indicates that we have internal prediction cache */
+            std::vector<CacheEntry> cache_;
+        private:
+            // find internal bufer offset for certain matrix, if not exist, return -1
+            inline int FindBufferOffset(const DMatrix &mat){
+                for(size_t i = 0; i < cache_.size(); ++i){
+                    if( cache_[i].mat_ == &mat ) return cache_[i].buffer_offset_; 
+                }
+                return -1;
+            } 
+        private:
             int silent;
             EvalSet evaluator_;
             booster::GBMBase base_gbm;
-            ModelParam   mparam;
-            const DMatrix *train_;
-            std::vector<DMatrix *> evals_;
-            std::vector<std::string> evname_;
-            std::vector<unsigned> buffer_index_;
+            ModelParam   mparam;           
             // objective fnction
             IObjFunction *obj_;
             // name of objective function
             std::string name_obj_;
             std::vector< std::pair<std::string, std::string> > cfg_;
         private:
             std::vector<float> grad_, hess_, preds_;
-            std::vector< std::vector<float> > eval_preds_;
         };
     }
 };