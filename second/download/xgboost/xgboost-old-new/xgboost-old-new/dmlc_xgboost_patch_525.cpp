@@ -71,6 +71,7 @@ namespace xgboost{
                 if( !strcmp("name_dumppath",  name ) )   name_dumppath = val;
                 if( !strcmp("name_pred",  name ) )   name_pred = val;
                 if( !strcmp("dump_stats", name ) )   dump_model_stats = atoi( val );
+                if( !strcmp("interact:action",  name ) )  interact_action = val;
                 if( !strncmp("eval[",  name, 5 ) ) {
                     char evname[ 256 ];
                     utils::Assert( sscanf( name, "eval[%[^]]", evname ) == 1, "must specify evaluation name for display");
@@ -95,6 +96,7 @@ namespace xgboost{
                 name_dump = "dump.txt";
                 name_dumppath = "dump.path.txt";
                 model_dir_path = "./";
+                interact_action = "update";
             }
             ~RegBoostTask( void ){
                 for( size_t i = 0; i < deval.size(); i ++ ){
@@ -162,7 +164,7 @@ namespace xgboost{
             inline void TaskInteractive( void ){
                 const time_t start    = time( NULL );
                 unsigned long elapsed = 0;
-                learner.UpdateInteract();
+                learner.UpdateInteract( interact_action );
                 utils::Assert( model_out != "NULL", "interactive mode must specify model_out" );
                 this->SaveModel( model_out.c_str() );
                 elapsed = (unsigned long)(time(NULL) - start); 
@@ -211,7 +213,9 @@ namespace xgboost{
             /* \brief number of boosting iterations */
             int num_round;            
             /* \brief the period to save the model, 0 means only save the final round model */
-            int save_period;            
+            int save_period;
+            /*! \brief interfact action */
+            std::string interact_action;
             /* \brief the path of training/test data set */
             std::string train_path, test_path;
             /* \brief the path of test model file, or file to restart training */