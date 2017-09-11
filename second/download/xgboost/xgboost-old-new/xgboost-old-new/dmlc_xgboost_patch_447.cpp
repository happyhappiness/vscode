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
@@ -163,7 +164,9 @@ extern "C"{
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