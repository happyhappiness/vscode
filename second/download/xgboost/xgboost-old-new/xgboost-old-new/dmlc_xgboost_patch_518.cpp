@@ -73,6 +73,9 @@ namespace xgboost{
                 if( !strcmp("name_pred",  name ) )   name_pred = val;
                 if( !strcmp("dump_stats", name ) )   dump_model_stats = atoi( val );
                 if( !strcmp("interact:action",  name ) )  interact_action = val;
+                if( !strncmp("batch:",  name, 6 ) ){
+                    cfg_batch.PushBack( name + 6, val );
+                }
                 if( !strncmp("eval[",  name, 5 ) ) {
                     char evname[ 256 ];
                     utils::Assert( sscanf( name, "eval[%[^]]", evname ) == 1, "must specify evaluation name for display");
@@ -167,13 +170,27 @@ namespace xgboost{
             inline void TaskInteractive( void ){
                 const time_t start    = time( NULL );
                 unsigned long elapsed = 0;
-                learner.UpdateInteract( interact_action );
+                int batch_action = 0;
+                
+                cfg_batch.BeforeFirst();
+                while( cfg_batch.Next() ){
+                    if( !strcmp( cfg_batch.name(), "run" ) ){
+                        learner.UpdateInteract( interact_action );
+                        batch_action += 1;
+                    } else{
+                        learner.SetParam( cfg_batch.name(), cfg_batch.val() );
+                    }
+                }
+
+                if( batch_action == 0 ){
+                    learner.UpdateInteract( interact_action );
+                }
                 utils::Assert( model_out != "NULL", "interactive mode must specify model_out" );
                 this->SaveModel( model_out.c_str() );
                 elapsed = (unsigned long)(time(NULL) - start); 
 
                 if( !silent ){
-                    printf("\ninteractive update, %lu sec in all\n", elapsed );
+                    printf("\ninteractive update, %d batch actions, %lu sec in all\n", batch_action, elapsed );
                 }
             }
 
@@ -245,6 +262,8 @@ namespace xgboost{
             std::vector<std::string> eval_data_names;            
             /*! \brief saves configurations */
             utils::ConfigSaver cfg;
+            /*! \brief batch configurations */
+            utils::ConfigSaver cfg_batch;
         private:
             DMatrix data;
             std::vector<DMatrix*> deval;