@@ -3,6 +3,7 @@
 
 #include <cstring>
 #include "xgboost.h"
+#include "xgboost_data.h"
 #include "../utils/xgboost_omp.h"
 #include "../utils/xgboost_config.h"
 /*!
@@ -128,7 +129,7 @@ namespace xgboost{
                 utils::Assert( fi.Read( &param, sizeof(Param) ) != 0 );
                 boosters.resize( param.num_boosters );
                 for( size_t i = 0; i < boosters.size(); i ++ ){
-                    boosters[ i ] = booster::CreateBooster( param.booster_type );
+                    boosters[ i ] = booster::CreateBooster<FMatrixS>( param.booster_type );
                     boosters[ i ]->LoadModel( fi );
                 }
                 {// load info 
@@ -207,7 +208,7 @@ namespace xgboost{
                     for( size_t j = 0; j < boosters.size(); ++ j ){
                         if( j != 0 ) fprintf( fo, "\t" );
                         std::vector<int> path;
-                        boosters[j]->PredPath( path, data[i] );
+                        boosters[j]->PredPath( path, data, i );
                         fprintf( fo, "%d", path[0] );
                         for( size_t k = 1; k < path.size(); ++ k ){
                             fprintf( fo, ",%d", path[k] );
@@ -236,12 +237,13 @@ namespace xgboost{
             /*! 
              * \brief predict values for given sparse feature vector
              *   NOTE: in tree implementation, this is not threadsafe
-             * \param feat vector in sparse format
+             * \param feats feature matrix
+             * \param row_index  row index in the feature matrix
              * \param buffer_index the buffer index of the current feature line, default -1 means no buffer assigned
-             * \param rid root id of current instance, default = 0
+             * \param root_index root id of current instance, default = 0
              * \return prediction 
-             */        
-            virtual float Predict( const booster::FMatrixS::Line &feat, int buffer_index = -1, unsigned rid = 0 ){
+             */
+            inline float Predict( const FMatrixS &feats, bst_uint row_index, int buffer_index = -1, unsigned root_index = 0 ){
                 size_t istart = 0;
                 float  psum = 0.0f;
 
@@ -253,7 +255,7 @@ namespace xgboost{
                 }
             
                 for( size_t i = istart; i < this->boosters.size(); i ++ ){
-                    psum += this->boosters[ i ]->Predict( feat, rid );
+                    psum += this->boosters[ i ]->Predict( feats, row_index, root_index );
                 }
                 
                 // updated the buffered results
@@ -320,7 +322,7 @@ namespace xgboost{
             inline booster::IBooster *GetUpdateBooster( void ){
                 if( param.do_reboost == 0 || boosters.size() == 0 ){
                     param.num_boosters += 1;
-                    boosters.push_back( booster::CreateBooster( param.booster_type ) );
+                    boosters.push_back( booster::CreateBooster<FMatrixS>( param.booster_type ) );
                     booster_info.push_back( 0 );
                     this->ConfigBooster( boosters.back() );
                     boosters.back()->InitModel();                    