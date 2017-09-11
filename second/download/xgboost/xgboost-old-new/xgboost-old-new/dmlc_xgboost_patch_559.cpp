@@ -96,11 +96,11 @@ namespace xgboost{
                     learner.SetParam( cfg.name(), cfg.val() );
                 }
                 if( strcmp( model_in.c_str(), "NULL" ) != 0 ){
-                    utils::Assert( !strcmp( task.c_str(), "train"), "model_in not specified" );
                     utils::FileStream fi( utils::FopenCheck( model_in.c_str(), "rb") );
                     learner.LoadModel( fi );
                     fi.Close();
                 }else{
+                    utils::Assert( !strcmp( task.c_str(), "train"), "model_in not specified" );
                     learner.InitModel();
                 }
                 learner.InitTrainer();
@@ -114,19 +114,19 @@ namespace xgboost{
                     learner.UpdateOneIter( i );
                     learner.EvalOneIter( i );
                     if( save_period != 0 && (i+1) % save_period == 0 ){
-                        SaveModel( i );
+                        this->SaveModel( i );
                     }
                     elapsed = (unsigned long)(time(NULL) - start); 
                 }
                 // always save final round
-                if( num_round % save_period != 0 ){
-                    SaveModel( num_round );
+                if( save_period == 0 || num_round % save_period != 0 ){
+                    this->SaveModel( num_round );
                 }
                 if( !silent ){
                     printf("\nupdating end, %lu sec in all\n", elapsed );
                 }
             }
-            inline void SaveModel( int i ){
+            inline void SaveModel( int i ) const{
                 char fname[256];
                 sprintf( fname ,"%s/%04d.model", model_dir_path.c_str(), i+1 );
                 utils::FileStream fo( utils::FopenCheck( fname, "wb" ) );
@@ -135,7 +135,9 @@ namespace xgboost{
             }
             inline void TaskTest( void ){
                 std::vector<float> preds;
+                if( !silent ) printf("start prediction...\n");
                 learner.Predict( preds, data );
+                if( !silent ) printf("writing prediction to %s\n", name_pred.c_str() );
                 FILE *fo = utils::FopenCheck( name_pred.c_str(), "w" );
                 for( size_t i = 0; i < preds.size(); i ++ ){
                     fprintf( fo, "%f\n", preds[i] );