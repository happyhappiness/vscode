@@ -179,6 +179,25 @@ namespace xgboost{
                     boosters[i]->DumpModel( fo );
                 }
             }
+            /*! 
+             * \brief Dump path of all trees
+             * \param fo text file 
+             * \param data input data
+             */
+            inline void DumpPath( FILE *fo, const FMatrixS &data ){
+                for( size_t i = 0; i < data.NumRow(); ++ i ){
+                    for( size_t j = 0; j < boosters.size(); ++ j ){
+                        if( j != 0 ) fprintf( fo, "\t" );
+                        std::vector<int> path;
+                        boosters[j]->PredPath( path, data[i] );
+                        fprintf( fo, "%d", path[0] );
+                        for( size_t k = 1; k < path.size(); ++ k ){
+                            fprintf( fo, ",%d", path[k] );
+                        }
+                    }
+                    fprintf( fo, "\n" );
+                }
+            }
         public:
             /*! 
              * \brief do gradient boost training for one step, using the information given
@@ -195,7 +214,7 @@ namespace xgboost{
                                  const std::vector<unsigned> &root_index ) {
                 booster::IBooster *bst = this->GetUpdateBooster();
                 bst->DoBoost( grad, hess, feats, root_index );
-            }
+            }            
             /*! 
              * \brief predict values for given sparse feature vector
              *   NOTE: in tree implementation, this is not threadsafe
@@ -204,7 +223,7 @@ namespace xgboost{
              * \param rid root id of current instance, default = 0
              * \return prediction 
              */        
-            virtual float Predict( const booster::FMatrixS::Line &feat, int buffer_index = -1, unsigned rid = 0 ){               
+            virtual float Predict( const booster::FMatrixS::Line &feat, int buffer_index = -1, unsigned rid = 0 ){
                 size_t istart = 0;
                 float  psum = 0.0f;
 