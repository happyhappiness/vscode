@@ -39,6 +39,10 @@ namespace xgboost{
                     this->TaskDump();
                     return 0;
                 }
+                if( task == "interactive" ){
+                    this->TaskInteractive();
+                    return 0;
+                }
                 if( task == "dumppath" ){
                     this->TaskDumpPath();
                     return 0;
@@ -60,6 +64,7 @@ namespace xgboost{
                 if( !strcmp("data",  name ) )        train_path = val;
                 if( !strcmp("test:data",  name ) )   test_path  = val;
                 if( !strcmp("model_in",  name ) )    model_in   = val;
+                if( !strcmp("model_out",  name ) )   model_out   = val;
                 if( !strcmp("model_dir", name ) )    model_dir_path = val;
                 if( !strcmp("fmap",  name ) )        name_fmap = val;
                 if( !strcmp("name_dump",  name ) )   name_dump = val;
@@ -141,13 +146,30 @@ namespace xgboost{
                 }
                 // always save final round
                 if( save_period == 0 || num_round % save_period != 0 ){
-                    this->SaveModel( num_round );
+                    if( model_out == "NULL" ){
+                        this->SaveModel( num_round );
+                    }else{
+                        this->SaveModel( model_out.c_str() );
+                    }
                 }
                 if( !silent ){
                     printf("\nupdating end, %lu sec in all\n", elapsed );
                 }
             }
 
+            inline void TaskInteractive( void ){
+                const time_t start    = time( NULL );
+                unsigned long elapsed = 0;
+                learner.UpdateInteract();
+                utils::Assert( model_out != "NULL", "interactive mode must specify model_out" );
+                this->SaveModel( model_out.c_str() );
+                elapsed = (unsigned long)(time(NULL) - start); 
+
+                if( !silent ){
+                    printf("\ninteractive update, %lu sec in all\n", elapsed );
+                }
+            }
+
             inline void TaskDump( void ){
                 FILE *fo = utils::FopenCheck( name_dump.c_str(), "w" );
                 learner.DumpModel( fo, fmap, dump_model_stats != 0 );
@@ -158,13 +180,16 @@ namespace xgboost{
                 learner.DumpPath( fo, data );
                 fclose( fo );
             }
-            inline void SaveModel( int i ) const{
-                char fname[256];
-                sprintf( fname ,"%s/%04d.model", model_dir_path.c_str(), i+1 );
+            inline void SaveModel( const char *fname ) const{
                 utils::FileStream fo( utils::FopenCheck( fname, "wb" ) );
                 learner.SaveModel( fo );
                 fo.Close();
             }
+            inline void SaveModel( int i ) const{
+                char fname[256];
+                sprintf( fname ,"%s/%04d.model", model_dir_path.c_str(), i+1 );
+                this->SaveModel( fname );
+            }
             inline void TaskPred( void ){
                 std::vector<float> preds;
                 if( !silent ) printf("start prediction...\n");
@@ -189,6 +214,8 @@ namespace xgboost{
             std::string train_path, test_path;
             /* \brief the path of test model file, or file to restart training */
             std::string model_in;
+            /* \brief the path of final model file, to be saved */
+            std::string model_out;
             /* \brief the path of directory containing the saved models */
             std::string model_dir_path;
             /* \brief task to perform */