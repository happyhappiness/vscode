@@ -56,20 +56,63 @@ namespace xgboost{
                 this->info.labels.resize( len );
                 memcpy( &(this->info).labels[0], label, sizeof(float)*len );
             }
+            inline void SetGroup( const unsigned *group, size_t len ){
+                this->info.group_ptr.resize( len + 1 );
+                this->info.group_ptr[0] = 0;
+                for( size_t i = 0; i < len; ++ i ){
+                    this->info.group_ptr[i+1] = this->info.group_ptr[i]+group[i];
+                }
+            }
+            inline void SetWeight( const float *weight, size_t len ){
+                this->info.weights.resize( len );
+                memcpy( &(this->info).weights[0], weight, sizeof(float)*len );
+            }
             inline const float* GetLabel( size_t* len ) const{
                 *len = this->info.labels.size();
                 return &(this->info.labels[0]);
             }
-            inline void InitTrain(void){
-                if(!this->data.HaveColAccess()) this->data.InitData();
+            inline void CheckInit(void){
+                if(!this->data.HaveColAccess()){
+                    this->data.InitData();
+                }
                 utils::Assert( this->data.NumRow() == this->info.labels.size(), "DMatrix: number of labels must match number of rows in matrix");
             }
         };
+    
+        class Booster: public xgboost::regrank::RegRankBoostLearner{
+        private:
+            bool init_trainer, init_model;
+        public:
+            Booster(const std::vector<const regrank::DMatrix *> mats){
+                silent = 1;
+                init_trainer = false;
+                init_model = false;
+                this->SetCacheData(mats);
+            }
+            inline void CheckInit(void){
+                if( !init_trainer ){
+                    this->InitTrainer(); init_trainer = true;
+                }
+                if( !init_model ){
+                    this->InitModel(); init_model = true;
+                }
+            }
+            inline void LoadModel( const char *fname ){
+                xgboost::regrank::RegRankBoostLearner::LoadModel(fname);
+                this->init_model = true;
+            }
+            const float *Pred( const DMatrix &dmat, size_t *len ){
+                this->Predict( this->preds_, dmat );
+                *len = this->preds_.size();
+                return &this->preds_[0];
+            }
+        };
     };
 };
 
 using namespace xgboost::python;
 
+
 extern "C"{
     void* XGDMatrixCreate( void ){
         return new DMatrix();
@@ -94,6 +137,12 @@ extern "C"{
     void XGDMatrixSetLabel( void *handle, const float *label, size_t len ){
         static_cast<DMatrix*>(handle)->SetLabel(label,len);        
     }
+    void XGDMatrixSetWeight( void *handle, const float *weight, size_t len ){
+        static_cast<DMatrix*>(handle)->SetWeight(weight,len);        
+    }
+    void XGDMatrixSetGroup( void *handle, const unsigned *group, size_t len ){
+        static_cast<DMatrix*>(handle)->SetGroup(group,len);        
+    }
     const float* XGDMatrixGetLabel( const void *handle, size_t* len ){
         return static_cast<const DMatrix*>(handle)->GetLabel(len);
     }
@@ -109,5 +158,54 @@ extern "C"{
     const XGEntry* XGDMatrixGetRow(void *handle, unsigned ridx, size_t* len){
         return static_cast<DMatrix*>(handle)->GetRow(ridx, len);
     }
+
+    // xgboost implementation
+    void *XGBoosterCreate( void *dmats[], size_t len ){
+        std::vector<const xgboost::regrank::DMatrix*> mats;
+        for( size_t i = 0; i < len; ++i ){
+            mats.push_back( static_cast<DMatrix*>(dmats[i]) );
+        }
+        return new Booster( mats );
+    }
+    void XGBoosterSetParam( void *handle, const char *name, const char *value ){
+        static_cast<Booster*>(handle)->SetParam( name, value );
+    }
+    void XGBoosterUpdateOneIter( void *handle, void *dtrain ){
+        Booster *bst = static_cast<Booster*>(handle);
+        DMatrix *dtr = static_cast<DMatrix*>(dtrain);
+        bst->CheckInit(); dtr->CheckInit(); 
+        bst->UpdateOneIter( *dtr );
+    }    
+    void XGBoosterEvalOneIter( void *handle, int iter, void *dmats[], const char *evnames[], size_t len ){
+        Booster *bst = static_cast<Booster*>(handle);
+        bst->CheckInit();
+
+        std::vector<std::string> names;
+        std::vector<const xgboost::regrank::DMatrix*> mats;
+        for( size_t i = 0; i < len; ++i ){
+            mats.push_back( static_cast<DMatrix*>(dmats[i]) );
+            names.push_back( std::string( evnames[i]) );
+        }
+        bst->EvalOneIter( iter, mats, names, stdout );
+    }
+    const float *XGBoosterPredict( void *handle, void *dmat, size_t *len ){
+        return static_cast<Booster*>(handle)->Pred( *static_cast<DMatrix*>(dmat), len );
+    }
+    void XGBoosterLoadModel( void *handle, const char *fname ){        
+        static_cast<Booster*>(handle)->LoadModel( fname );        
+    } 
+    void XGBoosterSaveModel( const void *handle, const char *fname ){
+        static_cast<const Booster*>(handle)->SaveModel( fname );
+    }
+    void XGBoosterDumpModel( void *handle, const char *fname, const char *fmap ){
+        using namespace xgboost::utils;
+        FILE *fo = FopenCheck( fname, "w" );
+        FeatMap featmap; 
+        if( strlen(fmap) != 0 ){ 
+            featmap.LoadText( fmap );
+        }
+        static_cast<Booster*>(handle)->DumpModel( fo, featmap, false );
+        fclose( fo );
+    }
 };
 