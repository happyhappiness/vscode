@@ -51,6 +51,7 @@ namespace xgboost{
             }
             inline void SetParam( const char *name, const char *val ){
                 if( !strcmp("silent", name ) )       silent = atoi( val );
+                if( !strcmp("use_buffer", name ) )   use_buffer = atoi( val );
                 if( !strcmp("seed", name ) )         random::Seed( atoi(val) );
                 if( !strcmp("num_round", name ) )    num_round = atoi( val );
                 if( !strcmp("save_period", name ) )  save_period = atoi( val );
@@ -71,6 +72,7 @@ namespace xgboost{
             RegBoostTask( void ){
                 // default parameters
                 silent = 0;
+                use_buffer = 1;
                 num_round = 10;
                 save_period = 0;
                 task = "train";                
@@ -89,14 +91,14 @@ namespace xgboost{
             inline void InitData( void ){
                 if( task == "dump") return;
                 if( task == "test" || task == "dumppath" ){
-                    data.CacheLoad( test_path.c_str() );
+                    data.CacheLoad( test_path.c_str(), silent!=0, use_buffer!=0 );
                 }else{
                     // training 
-                    data.CacheLoad( train_path.c_str() );
+                    data.CacheLoad( train_path.c_str(), silent!=0, use_buffer!=0 );
                     utils::Assert( eval_data_names.size() == eval_data_paths.size() );
                     for( size_t i = 0; i < eval_data_names.size(); ++ i ){
                         deval.push_back( new DMatrix() );
-                        deval.back()->CacheLoad( eval_data_paths[i].c_str() );
+                        deval.back()->CacheLoad( eval_data_paths[i].c_str(), silent!=0, use_buffer!=0 );
                     }
                 }
                 learner.SetData( &data, deval, eval_data_names );
@@ -169,6 +171,8 @@ namespace xgboost{
         private:
             /* \brief whether silent */
             int silent;
+            /* \brief whether use auto binary buffer */
+            int use_buffer;
             /* \brief number of boosting iterations */
             int num_round;            
             /* \brief the period to save the model, 0 means only save the final round model */