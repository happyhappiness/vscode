@@ -75,6 +75,7 @@ namespace xgboost{
             inline void CheckInit(void){
                 if(!init_col_){
                     this->data.InitData();
+                    init_col_ = true;
                 }
                 utils::Assert( this->data.NumRow() == this->info.labels.size(), "DMatrix: number of labels must match number of rows in matrix");
             }