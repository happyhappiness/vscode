@@ -60,13 +60,14 @@ namespace xgboost{
                 }
 
                 char str_temp[25];
-                if( num_feature > base_model.param.num_feature ){
+                if( num_feature > mparam.num_feature ){
+                    mparam.num_feature = num_feature;
                     sprintf( str_temp, "%d", num_feature );
-                    base_model.SetParam( "bst:num_feature", str_temp );
+                    base_gbm.SetParam( "bst:num_feature", str_temp );
                 }
                 
                 sprintf( str_temp, "%u", buffer_size );
-                base_model.SetParam( "num_pbuffer", str_temp );
+                base_gbm.SetParam( "num_pbuffer", str_temp );
                 if( !silent ){
                     printf( "buffer_size=%u\n", buffer_size );
                 }
@@ -81,16 +82,16 @@ namespace xgboost{
             */
             inline void SetParam( const char *name, const char *val ){
                 if( !strcmp( name, "silent") )  silent = atoi( val );
-                if( !strcmp( name, "eval_metric") )  evaluator_.AddEval( val );
+                if( !strcmp( name, "eval_metric") )  evaluator_.AddEval( val );                
                 mparam.SetParam( name, val );
-                base_model.SetParam( name, val );
+                base_gbm.SetParam( name, val );
             }
             /*!
             * \brief initialize solver before training, called before training
             * this function is reserved for solver to allocate necessary space and do other preparation 
             */
             inline void InitTrainer( void ){
-                base_model.InitTrainer();
+                base_gbm.InitTrainer();
                 if( mparam.loss_type == kLogisticClassify ){
                     evaluator_.AddEval( "error" );
                 }else{
@@ -102,15 +103,15 @@ namespace xgboost{
             * \brief initialize the current data storage for model, if the model is used first time, call this function
             */
             inline void InitModel( void ){
-                base_model.InitModel();
+                base_gbm.InitModel();
                 mparam.AdjustBase();
             }
             /*! 
             * \brief load model from stream
             * \param fi input stream
             */          
             inline void LoadModel( utils::IStream &fi ){
-                base_model.LoadModel( fi );
+                base_gbm.LoadModel( fi );
                 utils::Assert( fi.Read( &mparam, sizeof(ModelParam) ) != 0 );
             }
             /*! 
@@ -120,22 +121,22 @@ namespace xgboost{
               * \param with_stats whether print statistics as well
              */            
             inline void DumpModel( FILE *fo, const utils::FeatMap& fmap, bool with_stats ){
-                base_model.DumpModel( fo, fmap, with_stats );
+                base_gbm.DumpModel( fo, fmap, with_stats );
             }
             /*! 
              * \brief Dump path of all trees
              * \param fo text file 
              * \param data input data
              */
             inline void DumpPath( FILE *fo, const DMatrix &data ){
-                base_model.DumpPath( fo, data.data );
+                base_gbm.DumpPath( fo, data.data );
             }
             /*! 
             * \brief save model to stream
             * \param fo output stream
             */
             inline void SaveModel( utils::IStream &fo ) const{
-                base_model.SaveModel( fo );	
+                base_gbm.SaveModel( fo );	
                 fo.Write( &mparam, sizeof(ModelParam) );
             } 
             /*! 
@@ -146,7 +147,7 @@ namespace xgboost{
                 this->PredictBuffer( preds_, *train_, 0 );
                 this->GetGradient( preds_, train_->labels, grad_, hess_ );
                 std::vector<unsigned> root_index;
-                base_model.DoBoost( grad_, hess_, train_->data, root_index );                
+                base_gbm.DoBoost( grad_, hess_, train_->data, root_index );                
             }
             /*! 
              * \brief evaluate the model for specific iteration
@@ -165,7 +166,6 @@ namespace xgboost{
                 }
                 fprintf( fo,"\n" );
             }
-
             /*! \brief get prediction, without buffering */
             inline void Predict( std::vector<float> &preds, const DMatrix &data ){
                 preds.resize( data.Size() );
@@ -174,7 +174,51 @@ namespace xgboost{
                 #pragma omp parallel for schedule( static )
                 for( unsigned j = 0; j < ndata; ++ j ){
                     preds[j] = mparam.PredTransform
-                        ( mparam.base_score + base_model.Predict( data.data, j, -1 ) );
+                        ( mparam.base_score + base_gbm.Predict( data.data, j, -1 ) );
+                }
+            }
+        public:
+            /*! 
+             * \brief update the model for one iteration
+             * \param iteration iteration number
+             */
+            inline void UpdateInteract( void ){
+                this->InteractPredict( preds_, *train_, 0 );
+                int buffer_offset = static_cast<int>( train_->Size() );
+                for( size_t i = 0; i < evals_.size(); ++i ){
+                    std::vector<float> &preds = this->eval_preds_[ i ];                
+                    this->InteractPredict( preds, *evals_[i], buffer_offset );
+                    buffer_offset += static_cast<int>( evals_[i]->Size() );
+                }
+                
+                this->GetGradient( preds_, train_->labels, grad_, hess_ );
+                std::vector<unsigned> root_index;
+                base_gbm.DoBoost( grad_, hess_, train_->data, root_index );
+
+                this->InteractRePredict( *train_, 0 );
+                buffer_offset = static_cast<int>( train_->Size() );
+                for( size_t i = 0; i < evals_.size(); ++i ){
+                    this->InteractRePredict( *evals_[i], buffer_offset );
+                    buffer_offset += static_cast<int>( evals_[i]->Size() );
+                }
+            }
+        private:
+            /*! \brief get the transformed predictions, given data */
+            inline void InteractPredict( std::vector<float> &preds, const DMatrix &data, unsigned buffer_offset ){
+                preds.resize( data.Size() );
+                const unsigned ndata = static_cast<unsigned>( data.Size() );
+                #pragma omp parallel for schedule( static )
+                for( unsigned j = 0; j < ndata; ++ j ){                
+                    preds[j] = mparam.PredTransform
+                        ( mparam.base_score + base_gbm.InteractPredict( data.data, j, buffer_offset + j ) );
+                }
+            }
+            /*! \brief repredict trial */
+            inline void InteractRePredict( const DMatrix &data, unsigned buffer_offset ){
+                const unsigned ndata = static_cast<unsigned>( data.Size() );
+                #pragma omp parallel for schedule( static )
+                for( unsigned j = 0; j < ndata; ++ j ){
+                    base_gbm.InteractRePredict( data.data, j, buffer_offset + j );
                 }
             }
         private:
@@ -186,7 +230,7 @@ namespace xgboost{
                 #pragma omp parallel for schedule( static )
                 for( unsigned j = 0; j < ndata; ++ j ){                
                     preds[j] = mparam.PredTransform
-                        ( mparam.base_score + base_model.Predict( data.data, j, buffer_offset + j ) );
+                        ( mparam.base_score + base_gbm.Predict( data.data, j, buffer_offset + j ) );
                 }
             }
 
@@ -218,9 +262,16 @@ namespace xgboost{
                 float base_score;
                 /* \brief type of loss function */
                 int loss_type;
+                /* \brief number of features  */
+                int num_feature;
+                /*! \brief reserved field */
+                int reserved[ 16 ];
+                /*! \brief constructor */
                 ModelParam( void ){
                     base_score = 0.5f;
                     loss_type  = 0;
+                    num_feature = 0;
+                    memset( reserved, 0, sizeof( reserved ) );
                 }
                 /*! 
                 * \brief set parameters from outside 
@@ -230,6 +281,7 @@ namespace xgboost{
                 inline void SetParam( const char *name, const char *val ){
                     if( !strcmp("base_score", name ) )  base_score = (float)atof( val );
                     if( !strcmp("loss_type", name ) )   loss_type = atoi( val );
+                    if( !strcmp("bst:num_feature", name ) ) num_feature = atoi( val );
                 }
                 /*! 
                 * \brief adjust base_score
@@ -330,7 +382,7 @@ namespace xgboost{
         private:
             int silent;
             EvalSet evaluator_;
-            booster::GBMBaseModel base_model;
+            booster::GBMBase base_gbm;
             ModelParam   mparam;
             const DMatrix *train_;
             std::vector<DMatrix *> evals_;