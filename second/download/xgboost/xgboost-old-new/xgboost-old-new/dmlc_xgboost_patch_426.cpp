@@ -86,6 +86,7 @@ namespace xgboost{
                 if (!strcmp(name, "silent"))  silent = atoi(val);
                 if (!strcmp(name, "eval_metric"))  evaluator_.AddEval(val);
                 if (!strcmp(name, "objective") )   name_obj_ = val;
+                if (!strcmp(name, "num_class") )   base_gbm.SetParam("num_booster_group", val );
                 mparam.SetParam(name, val);
                 base_gbm.SetParam(name, val);
                 cfg_.push_back( std::make_pair( std::string(name), std::string(val) ) );
@@ -95,7 +96,13 @@ namespace xgboost{
             * this function is reserved for solver to allocate necessary space and do other preparation
             */
             inline void InitTrainer(void){
-                base_gbm.InitTrainer();
+                if( mparam.num_class != 0 ){
+                    if( name_obj_ != "softmax" ){
+                        name_obj_ = "softmax";
+                        printf("auto select objective=softmax to support multi-class classification\n" );
+                    }
+                }
+                base_gbm.InitTrainer();                
                 obj_ = CreateObjFunction( name_obj_.c_str() );
                 for( size_t i = 0; i < cfg_.size(); ++ i ){
                     obj_->SetParam( cfg_[i].first.c_str(), cfg_[i].second.c_str() );
@@ -166,9 +173,18 @@ namespace xgboost{
             inline void UpdateOneIter(const DMatrix &train){
                 this->PredictRaw(preds_, train);
                 obj_->GetGradient(preds_, train.info, base_gbm.NumBoosters(), grad_, hess_);
-                // do boost
-                std::vector<unsigned> root_index;
-                base_gbm.DoBoost(grad_, hess_, train.data, root_index);
+                if( grad_.size() == train.Size() ){
+                    base_gbm.DoBoost(grad_, hess_, train.data, train.info.root_index);
+                }else{
+                    int ngroup = base_gbm.NumBoosterGroup();
+                    utils::Assert( grad_.size() == train.Size() * (size_t)ngroup, "BUG: UpdateOneIter: mclass" );
+                    std::vector<float> tgrad( train.Size() ), thess( train.Size() );
+                    for( int g = 0; g < ngroup; ++ g ){
+                        memcpy( &tgrad[0], &grad_[g*tgrad.size()], sizeof(float)*tgrad.size() );
+                        memcpy( &thess[0], &hess_[g*tgrad.size()], sizeof(float)*tgrad.size() );
+                        base_gbm.DoBoost(tgrad, thess, train.data, train.info.root_index, g );
+                    }
+                }
             }
             /*!
              * \brief evaluate the model for specific iteration
@@ -190,9 +206,14 @@ namespace xgboost{
                 fprintf(fo, "\n");
                 fflush(fo);
             }
-            /*! \brief get prediction, without buffering */
-            inline void Predict(std::vector<float> &preds, const DMatrix &data){
-                this->PredictRaw(preds,data);
+            /*! 
+             * \brief get prediction
+             * \param storage to store prediction
+             * \param data input data
+             * \param bst_group booster group we are in
+             */
+            inline void Predict(std::vector<float> &preds, const DMatrix &data, int bst_group = -1){
+                this->PredictRaw( preds, data, bst_group );
                 obj_->PredTransform( preds );
             }            
         public:
@@ -241,24 +262,32 @@ namespace xgboost{
                     base_gbm.InteractRePredict(data.data, j, buffer_offset + j);
                 }
             }
-        private:
             /*! \brief get un-transformed prediction*/
-            inline void PredictRaw(std::vector<float> &preds, const DMatrix &data){
-                this->PredictBuffer(preds, data, this->FindBufferOffset(data) );
+            inline void PredictRaw(std::vector<float> &preds, const DMatrix &data, int bst_group = -1 ){
+                int buffer_offset =  this->FindBufferOffset(data);
+                if( bst_group < 0 ){
+                    int ngroup = base_gbm.NumBoosterGroup();
+                    preds.resize( data.Size() * ngroup );
+                    for( int g = 0; g < ngroup; ++ g ){ 
+                        this->PredictBuffer(&preds[ data.Size() * g ], data, buffer_offset, g );
+                    }
+                }else{
+                    preds.resize( data.Size() );
+                    this->PredictBuffer(&preds[0], data, buffer_offset, bst_group );
+                }
             }
             /*! \brief get the un-transformed predictions, given data */
-            inline void PredictBuffer(std::vector<float> &preds, const DMatrix &data, int buffer_offset){
-                preds.resize(data.Size());
+            inline void PredictBuffer(float *preds, const DMatrix &data, int buffer_offset, int bst_group ){
                 const unsigned ndata = static_cast<unsigned>(data.Size());
                 if( buffer_offset >= 0 ){  
                     #pragma omp parallel for schedule( static )
                     for (unsigned j = 0; j < ndata; ++j){
-                        preds[j] = mparam.base_score + base_gbm.Predict(data.data, j, buffer_offset + j);
+                        preds[j] = mparam.base_score + base_gbm.Predict(data.data, j, buffer_offset + j, data.info.GetRoot(j), bst_group );
                     }
                 }else
                     #pragma omp parallel for schedule( static )
                     for (unsigned j = 0; j < ndata; ++j){
-                        preds[j] = mparam.base_score + base_gbm.Predict(data.data, j, -1);
+                        preds[j] = mparam.base_score + base_gbm.Predict(data.data, j, -1, data.info.GetRoot(j), bst_group );
                     }{
                 }
             }
@@ -270,14 +299,17 @@ namespace xgboost{
                 /* \brief type of loss function */
                 int loss_type;
                 /* \brief number of features  */
-                int num_feature;                
+                int num_feature;  
+                /* \brief number of class, if it is multi-class classification  */
+                int num_class; 
                 /*! \brief reserved field */
-                int reserved[16];
+                int reserved[15];
                 /*! \brief constructor */
                 ModelParam(void){
                     base_score = 0.5f;
                     loss_type = 0;
                     num_feature = 0;
+                    num_class = 0;
                     memset(reserved, 0, sizeof(reserved));
                 }
                 /*!
@@ -288,6 +320,7 @@ namespace xgboost{
                 inline void SetParam(const char *name, const char *val){
                     if (!strcmp("base_score", name))  base_score = (float)atof(val);
                     if (!strcmp("loss_type", name))   loss_type = atoi(val);
+                    if (!strcmp("num_class", name))   num_class = atoi(val);
                     if (!strcmp("bst:num_feature", name)) num_feature = atoi(val);
                 }
                 /*!