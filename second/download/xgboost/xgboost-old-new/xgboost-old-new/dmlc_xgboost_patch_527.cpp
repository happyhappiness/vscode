@@ -40,69 +40,18 @@ namespace xgboost{
          *    (4) model.SaveModel to save learned results 
          *
          *  Bufferring: each instance comes with a buffer_index in Predict. 
-         *              when param.num_pbuffer != 0, a unique buffer index can be 
+         *              when mparam.num_pbuffer != 0, a unique buffer index can be 
          *              assigned to each instance to buffer previous results of boosters,
          *              this helps to speedup training, so consider assign buffer_index 
          *              for each training instances, if buffer_index = -1, the code
          *              recalculate things from scratch and will still works correctly
          */
-        class GBMBaseModel{
-        public:
-            /*! \brief model parameters */
-            struct Param{
-                /*! \brief number of boosters */
-                int num_boosters;
-                /*! \brief type of tree used */
-                int booster_type;
-                /*! \brief number of root: default 0, means single tree */
-                int num_roots;
-                /*! \brief number of features to be used by boosters */
-                int num_feature;
-                /*! \brief size of predicton buffer allocated for buffering boosting computation */
-                int num_pbuffer;
-                /*! 
-                 * \brief whether we repeatly update a single booster each round: default 0
-                 *        set to 1 for linear booster, so that regularization term can be considered
-                 */
-                int do_reboost;
-                /*! \brief reserved parameters */
-                int reserved[ 32 ];
-                /*! \brief constructor */
-                Param( void ){
-                    num_boosters = 0; 
-                    booster_type = 0;
-                    num_roots = num_feature = 0;                    
-                    do_reboost = 0;
-                    num_pbuffer = 0;
-                    memset( reserved, 0, sizeof( reserved ) );     
-                }
-                /*! 
-                 * \brief set parameters from outside 
-                 * \param name name of the parameter
-                 * \param val  value of the parameter
-                 */
-                inline void SetParam( const char *name, const char *val ){
-                    if( !strcmp("booster_type", name ) ){
-                        booster_type = atoi( val );
-                        // linear boost automatically set do reboost
-                        if( booster_type == 1 ) do_reboost = 1;
-                    }
-                    if( !strcmp("num_pbuffer", name ) )      num_pbuffer = atoi( val );
-                    if( !strcmp("do_reboost", name ) )       do_reboost  = atoi( val );
-                    if( !strcmp("bst:num_roots", name ) )    num_roots = atoi( val );
-                    if( !strcmp("bst:num_feature", name ) )  num_feature = atoi( val );
-                }
-            };
-        public:
-            /*! \brief model parameters */ 
-            Param param;
+        class GBMBase{
         public:
             /*! \brief number of thread used */
-            GBMBaseModel( void ){
-                this->nthread = 1;
-            }
+            GBMBase( void ){}
             /*! \brief destructor */
-            virtual ~GBMBaseModel( void ){
+            virtual ~GBMBase( void ){
                 this->FreeSpace();
             }
             /*! 
@@ -117,30 +66,30 @@ namespace xgboost{
                 if( !strcmp( name, "silent") ){
                     cfg.PushBack( name, val );
                 }
-                if( !strcmp( name, "nthread") ) nthread = atoi( val );
-                if( boosters.size() == 0 ) param.SetParam( name, val );
+                tparam.SetParam( name, val );
+                if( boosters.size() == 0 ) mparam.SetParam( name, val );
             }
             /*! 
              * \brief load model from stream
              * \param fi input stream
              */
             inline void LoadModel( utils::IStream &fi ){
                 if( boosters.size() != 0 ) this->FreeSpace();
-                utils::Assert( fi.Read( &param, sizeof(Param) ) != 0 );
-                boosters.resize( param.num_boosters );
+                utils::Assert( fi.Read( &mparam, sizeof(ModelParam) ) != 0 );
+                boosters.resize( mparam.num_boosters );
                 for( size_t i = 0; i < boosters.size(); i ++ ){
-                    boosters[ i ] = booster::CreateBooster<FMatrixS>( param.booster_type );
+                    boosters[ i ] = booster::CreateBooster<FMatrixS>( mparam.booster_type );
                     boosters[ i ]->LoadModel( fi );
                 }
                 {// load info 
-                    booster_info.resize( param.num_boosters );
-                    if( param.num_boosters != 0 ){
-                        utils::Assert( fi.Read( &booster_info[0], sizeof(int)*param.num_boosters ) != 0 );
+                    booster_info.resize( mparam.num_boosters );
+                    if( mparam.num_boosters != 0 ){
+                        utils::Assert( fi.Read( &booster_info[0], sizeof(int)*mparam.num_boosters ) != 0 );
                     }
                 }
-                if( param.num_pbuffer != 0 ){
-                    pred_buffer.resize ( param.num_pbuffer );
-                    pred_counter.resize( param.num_pbuffer );
+                if( mparam.num_pbuffer != 0 ){
+                    pred_buffer.resize ( mparam.num_pbuffer );
+                    pred_counter.resize( mparam.num_pbuffer );
                     utils::Assert( fi.Read( &pred_buffer[0] , pred_buffer.size()*sizeof(float) ) != 0 );
                     utils::Assert( fi.Read( &pred_counter[0], pred_counter.size()*sizeof(unsigned) ) != 0 );
                 }
@@ -150,15 +99,15 @@ namespace xgboost{
              * \param fo output stream
              */
             inline void SaveModel( utils::IStream &fo ) const {
-                utils::Assert( param.num_boosters == (int)boosters.size() );
-                fo.Write( &param, sizeof(Param) );
+                utils::Assert( mparam.num_boosters == (int)boosters.size() );
+                fo.Write( &mparam, sizeof(ModelParam) );
                 for( size_t i = 0; i < boosters.size(); i ++ ){
                     boosters[ i ]->SaveModel( fo ); 
                 }
                 if( booster_info.size() != 0 ){
                     fo.Write( &booster_info[0], sizeof(int) * booster_info.size() );
                 }
-                if( param.num_pbuffer != 0 ){
+                if( mparam.num_pbuffer != 0 ){
                     fo.Write( &pred_buffer[0] , pred_buffer.size()*sizeof(float) );
                     fo.Write( &pred_counter[0], pred_counter.size()*sizeof(unsigned) );
                 }
@@ -168,18 +117,18 @@ namespace xgboost{
              */
             inline void InitModel( void ){
                 pred_buffer.clear(); pred_counter.clear();
-                pred_buffer.resize ( param.num_pbuffer, 0.0 );
-                pred_counter.resize( param.num_pbuffer, 0 );
-                utils::Assert( param.num_boosters == 0 );
+                pred_buffer.resize ( mparam.num_pbuffer, 0.0 );
+                pred_counter.resize( mparam.num_pbuffer, 0 );
+                utils::Assert( mparam.num_boosters == 0 );
                 utils::Assert( boosters.size() == 0 );
             }
             /*!
              * \brief initialize solver before training, called before training
              * this function is reserved for solver to allocate necessary space and do other preparation 
              */            
             inline void InitTrainer( void ){
-                if( nthread != 0 ){
-                    omp_set_num_threads( nthread );
+                if( tparam.nthread != 0 ){
+                    omp_set_num_threads( tparam.nthread );
                 }
                 // make sure all the boosters get the latest parameters
                 for( size_t i = 0; i < this->boosters.size(); i ++ ){
@@ -233,10 +182,10 @@ namespace xgboost{
                                  const std::vector<unsigned> &root_index ) {
                 booster::IBooster *bst = this->GetUpdateBooster();
                 bst->DoBoost( grad, hess, feats, root_index );
-            }            
+            }
             /*! 
              * \brief predict values for given sparse feature vector
-             *   NOTE: in tree implementation, this is not threadsafe
+             *   NOTE: in tree implementation, this is only OpenMP threadsafe, but not threadsafe
              * \param feats feature matrix
              * \param row_index  row index in the feature matrix
              * \param buffer_index the buffer index of the current feature line, default -1 means no buffer assigned
@@ -248,65 +197,59 @@ namespace xgboost{
                 float  psum = 0.0f;
 
                 // load buffered results if any
-                if( param.do_reboost == 0 && buffer_index >= 0 ){
-                    utils::Assert( buffer_index < param.num_pbuffer, "buffer index exceed num_pbuffer" );
+                if( mparam.do_reboost == 0 && buffer_index >= 0 ){
+                    utils::Assert( buffer_index < mparam.num_pbuffer, "buffer index exceed num_pbuffer" );
                     istart = this->pred_counter[ buffer_index ];
                     psum   = this->pred_buffer [ buffer_index ];
                 }
             
                 for( size_t i = istart; i < this->boosters.size(); i ++ ){
                     psum += this->boosters[ i ]->Predict( feats, row_index, root_index );
-                }
-                
+                }                
                 // updated the buffered results
-                if( param.do_reboost == 0 && buffer_index >= 0 ){
+                if( mparam.do_reboost == 0 && buffer_index >= 0 ){
                     this->pred_counter[ buffer_index ] = static_cast<unsigned>( boosters.size() );
                     this->pred_buffer [ buffer_index ] = psum;
                 }
                 return psum;
             }
+        public:
+            //--------trial code for interactive update an existing booster------
+            //-------- usually not needed, ignore this region ---------
             /*! 
-             * \brief predict values for given dense feature vector
-             * \param feat feature vector in dense format
-             * \param funknown indicator that the feature is missing
-             * \param buffer_index the buffer index of the current feature line, default -1 means no buffer assigned
-             * \param rid root id of current instance, default = 0
-             * \return prediction 
-             */                
-            virtual float Predict( const std::vector<float> &feat, 
-                                   const std::vector<bool>  &funknown,
-                                   int buffer_index = -1,
-                                   unsigned rid = 0 ){
-                size_t istart = 0;
-                float  psum = 0.0f;
-
-                // load buffered results if any
-                if( param.do_reboost == 0 && buffer_index >= 0 ){
-                    utils::Assert( buffer_index < param.num_pbuffer, 
-                                   "buffer index exceed num_pbuffer" );
-                    istart = this->pred_counter[ buffer_index ];
-                    psum   = this->pred_buffer [ buffer_index ];
-                }
-            
-                for( size_t i = istart; i < this->boosters.size(); i ++ ){
-                    psum += this->boosters[ i ]->Predict( feat, funknown, rid );
-                }
-                
-                // updated the buffered results
-                if( param.do_reboost == 0 && buffer_index >= 0 ){
-                    this->pred_counter[ buffer_index ] = static_cast<unsigned>( boosters.size() );
-                    this->pred_buffer [ buffer_index ] = psum;
+             * \brief same as Predict, but removes the prediction of booster to be updated 
+             *        this function must be called once and only once for every data with pbuffer
+             */
+            inline float InteractPredict( const FMatrixS &feats, bst_uint row_index, int buffer_index = -1, unsigned root_index = 0 ){
+                float psum = this->Predict( feats, row_index, buffer_index, root_index );
+                if( tparam.reupdate_booster != -1 ){
+                    const int bid = tparam.reupdate_booster;
+                    utils::Assert( bid >= 0 && bid < (int)boosters.size(), "interact:booster_index exceed existing bound" );
+                    psum -= boosters[ bid ]->Predict( feats, row_index, root_index );
+                    if( mparam.do_reboost == 0 && buffer_index >= 0 ){
+                        this->pred_buffer[ buffer_index ] = psum;                        
+                    }
                 }
                 return psum;
             }
+            /*! \brief update the prediction buffer, after booster have been updated */            
+            inline void InteractRePredict( const FMatrixS &feats, bst_uint row_index, int buffer_index = -1, unsigned root_index = 0 ){
+                if( tparam.reupdate_booster != -1 ){
+                    const int bid = tparam.reupdate_booster;
+                    utils::Assert( bid >= 0 && bid < (int)boosters.size(), "interact:booster_index exceed existing bound" );
+                    if( mparam.do_reboost == 0 && buffer_index >= 0 ){
+                        this->pred_buffer[ buffer_index ] += boosters[ bid ]->Predict( feats, row_index, root_index );
+                    }
+                }
+            }
             //-----------non public fields afterwards-------------
         protected:
             /*! \brief free space of the model */
             inline void FreeSpace( void ){
                 for( size_t i = 0; i < boosters.size(); i ++ ){
                     delete boosters[i];
                 }
-                boosters.clear(); booster_info.clear(); param.num_boosters = 0; 
+                boosters.clear(); booster_info.clear(); mparam.num_boosters = 0; 
             }
             /*! \brief configure a booster */
             inline void ConfigBooster( booster::IBooster *bst ){
@@ -320,9 +263,16 @@ namespace xgboost{
              * \return the booster created
              */
             inline booster::IBooster *GetUpdateBooster( void ){
-                if( param.do_reboost == 0 || boosters.size() == 0 ){
-                    param.num_boosters += 1;
-                    boosters.push_back( booster::CreateBooster<FMatrixS>( param.booster_type ) );
+                if( tparam.reupdate_booster != -1 ){
+                    const int bid = tparam.reupdate_booster;
+                    utils::Assert( bid >= 0 && bid < (int)boosters.size(), "interact:booster_index exceed existing bound" );
+                    this->ConfigBooster( boosters[bid] );
+                    return boosters[ bid ];
+                }
+
+                if( mparam.do_reboost == 0 || boosters.size() == 0 ){
+                    mparam.num_boosters += 1;
+                    boosters.push_back( booster::CreateBooster<FMatrixS>( mparam.booster_type ) );
                     booster_info.push_back( 0 );
                     this->ConfigBooster( boosters.back() );
                     boosters.back()->InitModel();                    
@@ -332,8 +282,81 @@ namespace xgboost{
                 return boosters.back();
             }
         protected:
-            /*! \brief number of OpenMP threads */
-            int nthread;
+            /*! \brief model parameters */
+            struct ModelParam{
+                /*! \brief number of boosters */
+                int num_boosters;
+                /*! \brief type of tree used */
+                int booster_type;
+                /*! \brief number of root: default 0, means single tree */
+                int num_roots;
+                /*! \brief number of features to be used by boosters */
+                int num_feature;
+                /*! \brief size of predicton buffer allocated for buffering boosting computation */
+                int num_pbuffer;
+                /*! 
+                 * \brief whether we repeatly update a single booster each round: default 0
+                 *        set to 1 for linear booster, so that regularization term can be considered
+                 */
+                int do_reboost;
+                /*! \brief reserved parameters */
+                int reserved[ 32 ];
+                /*! \brief constructor */
+                ModelParam( void ){
+                    num_boosters = 0; 
+                    booster_type = 0;
+                    num_roots = num_feature = 0;                    
+                    do_reboost = 0;
+                    num_pbuffer = 0;
+                    memset( reserved, 0, sizeof( reserved ) );
+                }
+                /*! 
+                 * \brief set parameters from outside 
+                 * \param name name of the parameter
+                 * \param val  value of the parameter
+                 */
+                inline void SetParam( const char *name, const char *val ){
+                    if( !strcmp("booster_type", name ) ){
+                        booster_type = atoi( val );
+                        // linear boost automatically set do reboost
+                        if( booster_type == 1 ) do_reboost = 1;
+                    }
+                    if( !strcmp("num_pbuffer", name ) )      num_pbuffer = atoi( val );
+                    if( !strcmp("do_reboost", name ) )       do_reboost  = atoi( val );
+                    if( !strcmp("bst:num_roots", name ) )    num_roots = atoi( val );
+                    if( !strcmp("bst:num_feature", name ) )  num_feature = atoi( val );
+                }
+            };
+            /*! \brief training parameters */
+            struct TrainParam{
+                /*! \brief number of OpenMP threads */
+                int nthread;
+                /*! 
+                 * \brief index of specific booster to be re-updated, default = -1: update new booster 
+                 *  parameter this is part of trial interactive update mode
+                 */
+                int reupdate_booster;
+                /*! \brief constructor */
+                TrainParam( void ) {
+                    nthread = 1;
+                    reupdate_booster = -1;
+                }
+                /*! 
+                 * \brief set parameters from outside 
+                 * \param name name of the parameter
+                 * \param val  value of the parameter
+                 */                
+                inline void SetParam( const char *name, const char *val ){
+                    if( !strcmp("nthread", name ) )                 nthread = atoi( val );
+                    if( !strcmp("interact:booster_index", name ) )  reupdate_booster = atoi( val );
+                }
+            };
+        protected:
+            /*! \brief model parameters */ 
+            ModelParam mparam;
+            /*! \brief training parameters */ 
+            TrainParam tparam;
+        protected:
             /*! \brief component boosters */ 
             std::vector<booster::IBooster*> boosters;
             /*! \brief some information indicator of the booster, reserved */ 