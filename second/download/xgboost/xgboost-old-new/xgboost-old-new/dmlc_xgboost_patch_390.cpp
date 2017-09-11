@@ -34,7 +34,7 @@ namespace xgboost{
             RegRankBoostLearner(const std::vector<const DMatrix *>& mats){
                 silent = 0;
                 obj_ = NULL;
-                name_obj_ = "reg";
+                name_obj_ = "reg:linear";
                 this->SetCacheData(mats);
             }            
             /*!
@@ -114,7 +114,7 @@ namespace xgboost{
              */
             inline void InitModel(void){
                 base_gbm.InitModel();
-                mparam.AdjustBase();
+                mparam.AdjustBase(name_obj_.c_str());
             }
             /*!
              * \brief load model from file 
@@ -308,7 +308,7 @@ namespace xgboost{
                 /*! \brief constructor */
                 ModelParam(void){
                     base_score = 0.5f;
-                    loss_type = 0;
+                    loss_type = -1;
                     num_feature = 0;
                     num_class = 0;
                     memset(reserved, 0, sizeof(reserved));
@@ -320,14 +320,19 @@ namespace xgboost{
                  */
                 inline void SetParam(const char *name, const char *val){
                     if (!strcmp("base_score", name))  base_score = (float)atof(val);
-                    if (!strcmp("loss_type", name))   loss_type = atoi(val);
                     if (!strcmp("num_class", name))   num_class = atoi(val);
+                    if (!strcmp("loss_type", name))   loss_type = atoi(val);
                     if (!strcmp("bst:num_feature", name)) num_feature = atoi(val);
                 }
                 /*!
-                * \brief adjust base_score
+                * \brief adjust base_score based on loss type and objective function
                 */
-                inline void AdjustBase(void){
+                inline void AdjustBase(const char *obj){
+                    // some tweaks for loss type
+                    if( loss_type == -1 ){
+                        loss_type = 1;
+                        if( !strcmp("reg:linear", obj ) ) loss_type = 0;
+                    }
                     if (loss_type == 1 || loss_type == 2|| loss_type == 3){
                         utils::Assert(base_score > 0.0f && base_score < 1.0f, "sigmoid range constrain");
                         base_score = -logf(1.0f / base_score - 1.0f);