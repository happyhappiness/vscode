@@ -5,6 +5,7 @@
 #include <string>
 #include <cstring>
 #include "xgboost_reg.h"
+#include "../utils/xgboost_fmap.h"
 #include "../utils/xgboost_random.h"
 #include "../utils/xgboost_config.h"
 
@@ -60,6 +61,10 @@ namespace xgboost{
                 if( !strcmp("test:data",  name ) )   test_path  = val;
                 if( !strcmp("model_in",  name ) )    model_in   = val;
                 if( !strcmp("model_dir", name ) )    model_dir_path = val;
+                if( !strcmp("fmap",  name ) )        name_fmap = val;
+                if( !strcmp("name_dump",  name ) )   name_dump = val;
+                if( !strcmp("name_pred",  name ) )   name_pred = val;
+                if( !strcmp("dump_stats", name ) )   dump_model_stats = atoi( val );
                 if( !strncmp("eval[",  name, 5 ) ) {
                     char evname[ 256 ];
                     utils::Assert( sscanf( name, "eval[%[^]]", evname ) == 1, "must specify evaluation name for display");
@@ -75,8 +80,10 @@ namespace xgboost{
                 use_buffer = 1;
                 num_round = 10;
                 save_period = 0;
+                dump_model_stats = 0;
                 task = "train";                
                 model_in = "NULL";
+                name_fmap = "NULL";
                 name_pred = "pred.txt";
                 name_dump = "dump.txt";
                 name_dumppath = "dump.path.txt";
@@ -89,7 +96,8 @@ namespace xgboost{
             }
         private:
             inline void InitData( void ){
-                if( task == "dump") return;
+                if( name_fmap != "NULL" ) fmap.LoadText( name_fmap.c_str() );
+                if( task == "dump" ) return;
                 if( task == "test" || task == "dumppath" ){
                     data.CacheLoad( test_path.c_str(), silent!=0, use_buffer!=0 );
                 }else{
@@ -142,7 +150,7 @@ namespace xgboost{
 
             inline void TaskDump( void ){
                 FILE *fo = utils::FopenCheck( name_dump.c_str(), "w" );
-                learner.DumpModel( fo );
+                learner.DumpModel( fo, fmap, dump_model_stats != 0 );
                 fclose( fo );
             }
             inline void TaskDumpPath( void ){
@@ -187,19 +195,24 @@ namespace xgboost{
             std::string task;
             /* \brief name of predict file */
             std::string name_pred;
+            /* \brief whether dump statistics along with model */
+            int dump_model_stats;
+            /* \brief name of feature map */
+            std::string name_fmap;
             /* \brief name of dump file */
             std::string name_dump;
             /* \brief name of dump path file */
             std::string name_dumppath;
             /* \brief the paths of validation data sets */
             std::vector<std::string> eval_data_paths;            
             /* \brief the names of the evaluation data used in output log */
-            std::vector<std::string> eval_data_names;
+            std::vector<std::string> eval_data_names;            
             /*! \brief saves configurations */
             utils::ConfigSaver cfg;
         private:
             DMatrix data;
             std::vector<DMatrix*> deval;
+            utils::FeatMap fmap;
             RegBoostLearner learner;
         };
     };