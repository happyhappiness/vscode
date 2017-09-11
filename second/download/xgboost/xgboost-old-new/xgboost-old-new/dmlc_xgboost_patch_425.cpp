@@ -32,6 +32,7 @@ namespace xgboost{
                 mat.row_data_.resize( mat.row_ptr_.back() + len );
                 memcpy( &mat.row_data_[mat.row_ptr_.back()], data, sizeof(XGEntry)*len );
                 mat.row_ptr_.push_back( mat.row_ptr_.back() + len );
+                init_col_ = false;
             }
             inline const XGEntry* GetRow(unsigned ridx, size_t* len) const{
                 const xgboost::booster::FMatrixS &mat = this->data;
@@ -72,7 +73,7 @@ namespace xgboost{
                 return &(this->info.labels[0]);
             }
             inline void CheckInit(void){
-                if(!this->data.HaveColAccess()){
+                if(!init_col_){
                     this->data.InitData();
                 }
                 utils::Assert( this->data.NumRow() == this->info.labels.size(), "DMatrix: number of labels must match number of rows in matrix");
@@ -101,11 +102,34 @@ namespace xgboost{
                 xgboost::regrank::RegRankBoostLearner::LoadModel(fname);
                 this->init_model = true;
             }
-            const float *Pred( const DMatrix &dmat, size_t *len ){
-                this->Predict( this->preds_, dmat );
+            const float *Pred( const DMatrix &dmat, size_t *len, int bst_group ){
+                this->CheckInit();
+
+                this->Predict( this->preds_, dmat, bst_group );
                 *len = this->preds_.size();
                 return &this->preds_[0];
             }
+            inline void BoostOneIter( const DMatrix &train, 
+                                      float *grad, float *hess, size_t len, int bst_group ){
+                this->grad_.resize( len ); this->hess_.resize( len );
+                memcpy( &this->grad_[0], grad, sizeof(float)*len );
+                memcpy( &this->hess_[0], hess, sizeof(float)*len );
+                
+                if( grad_.size() == train.Size() ){
+                    if( bst_group < 0 ) bst_group = 0;
+                    base_gbm.DoBoost(grad_, hess_, train.data, train.info.root_index, bst_group);
+                }else{
+                    utils::Assert( bst_group == -1, "must set bst_group to -1 to support all group boosting" );
+                    int ngroup = base_gbm.NumBoosterGroup();
+                    utils::Assert( grad_.size() == train.Size() * (size_t)ngroup, "BUG: UpdateOneIter: mclass" );
+                    std::vector<float> tgrad( train.Size() ), thess( train.Size() );
+                    for( int g = 0; g < ngroup; ++ g ){
+                        memcpy( &tgrad[0], &grad_[g*tgrad.size()], sizeof(float)*tgrad.size() );
+                        memcpy( &thess[0], &hess_[g*tgrad.size()], sizeof(float)*tgrad.size() );
+                        base_gbm.DoBoost(tgrad, thess, train.data, train.info.root_index, g );
+                    }
+                }                
+            }
         };
     };
 };
@@ -163,10 +187,15 @@ extern "C"{
     void *XGBoosterCreate( void *dmats[], size_t len ){
         std::vector<const xgboost::regrank::DMatrix*> mats;
         for( size_t i = 0; i < len; ++i ){
-            mats.push_back( static_cast<DMatrix*>(dmats[i]) );
+            DMatrix *dtr = static_cast<DMatrix*>(dmats[i]);
+            dtr->CheckInit();
+            mats.push_back( dtr );
         }
         return new Booster( mats );
     }
+    void XGBoosterFree( void *handle ){
+        delete  static_cast<Booster*>(handle);
+    }
     void XGBoosterSetParam( void *handle, const char *name, const char *value ){
         static_cast<Booster*>(handle)->SetParam( name, value );
     }
@@ -176,6 +205,13 @@ extern "C"{
         bst->CheckInit(); dtr->CheckInit(); 
         bst->UpdateOneIter( *dtr );
     }    
+    void XGBoosterBoostOneIter( void *handle, void *dtrain, 
+                                float *grad, float *hess, size_t len, int bst_group ){
+        Booster *bst = static_cast<Booster*>(handle);
+        DMatrix *dtr = static_cast<DMatrix*>(dtrain);
+        bst->CheckInit(); dtr->CheckInit(); 
+        bst->BoostOneIter( *dtr, grad, hess, len, bst_group );
+    }      
     void XGBoosterEvalOneIter( void *handle, int iter, void *dmats[], const char *evnames[], size_t len ){
         Booster *bst = static_cast<Booster*>(handle);
         bst->CheckInit();
@@ -188,8 +224,8 @@ extern "C"{
         }
         bst->EvalOneIter( iter, mats, names, stdout );
     }
-    const float *XGBoosterPredict( void *handle, void *dmat, size_t *len ){
-        return static_cast<Booster*>(handle)->Pred( *static_cast<DMatrix*>(dmat), len );
+    const float *XGBoosterPredict( void *handle, void *dmat, size_t *len, int bst_group ){
+        return static_cast<Booster*>(handle)->Pred( *static_cast<DMatrix*>(dmat), len, bst_group );
     }
     void XGBoosterLoadModel( void *handle, const char *fname ){        
         static_cast<Booster*>(handle)->LoadModel( fname );        
@@ -207,5 +243,13 @@ extern "C"{
         static_cast<Booster*>(handle)->DumpModel( fo, featmap, false );
         fclose( fo );
     }
+
+    void XGBoosterUpdateInteract( void *handle, void *dtrain, const char *action ){
+        Booster *bst = static_cast<Booster*>(handle);
+        DMatrix *dtr = static_cast<DMatrix*>(dtrain);        
+        bst->CheckInit(); dtr->CheckInit(); 
+        std::string act( action );
+        bst->UpdateInteract( act, *dtr );
+    }
 };
 