@@ -34,13 +34,17 @@ namespace xgboost{
                 }
                 this->InitData();
                 this->InitLearner();
-                if( !strcmp( task.c_str(), "dump") ){
+                if( task == "dump" ){
                     this->TaskDump();
                     return 0;
                 }
-                if( !strcmp( task.c_str(), "test") ){
+                if( task == "dumppath" ){
+                    this->TaskDumpPath();
+                    return 0;
+                }
+                if( task == "test" ){
                     this->TaskTest();
-                }else{
+                }else{                  
                     this->TaskTrain();
                 }
                 return 0;
@@ -73,6 +77,7 @@ namespace xgboost{
                 model_in = "NULL";
                 name_pred = "pred.txt";
                 name_dump = "dump.txt";
+                name_dumppath = "dump.path.txt";
                 model_dir_path = "./";
             }
             ~RegBoostTask( void ){
@@ -82,8 +87,8 @@ namespace xgboost{
             }
         private:
             inline void InitData( void ){
-                if( !strcmp( task.c_str(), "dump") ) return;
-                if( !strcmp( task.c_str(), "test") ){
+                if( task == "dump") return;
+                if( task == "test" || task == "dumppath" ){
                     data.CacheLoad( test_path.c_str() );
                 }else{
                     // training 
@@ -101,12 +106,12 @@ namespace xgboost{
                 while( cfg.Next() ){
                     learner.SetParam( cfg.name(), cfg.val() );
                 }
-                if( strcmp( model_in.c_str(), "NULL" ) != 0 ){
+                if( model_in != "NULL" ){
                     utils::FileStream fi( utils::FopenCheck( model_in.c_str(), "rb") );
                     learner.LoadModel( fi );
                     fi.Close();
                 }else{
-                    utils::Assert( !strcmp( task.c_str(), "train"), "model_in not specified" );
+                    utils::Assert( task == "train", "model_in not specified" );
                     learner.InitModel();
                 }
                 learner.InitTrainer();
@@ -138,6 +143,11 @@ namespace xgboost{
                 learner.DumpModel( fo );
                 fclose( fo );
             }
+            inline void TaskDumpPath( void ){
+                FILE *fo = utils::FopenCheck( name_dumppath.c_str(), "w" );
+                learner.DumpPath( fo, data );
+                fclose( fo );
+            }
             inline void SaveModel( int i ) const{
                 char fname[256];
                 sprintf( fname ,"%s/%04d.model", model_dir_path.c_str(), i+1 );
@@ -175,6 +185,8 @@ namespace xgboost{
             std::string name_pred;
             /* \brief name of dump file */
             std::string name_dump;
+            /* \brief name of dump path file */
+            std::string name_dumppath;
             /* \brief the paths of validation data sets */
             std::vector<std::string> eval_data_paths;            
             /* \brief the names of the evaluation data used in output log */