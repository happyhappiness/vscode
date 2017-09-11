@@ -104,6 +104,7 @@ namespace xgboost{
         public:
             EvalAMS(const char *name){
                 name_ = name;
+                // note: ams@0 will automatically select which ratio to go
                 utils::Assert( sscanf(name, "ams@%f", &ratio_ ) == 1, "invalid ams format" );
             }            
             virtual float Eval(const std::vector<float> &preds,
@@ -152,14 +153,9 @@ namespace xgboost{
             float ratio_;
         };
 
-        /*! \brief Error */
+        /*! \brief Error for multi-class classification, need exact match */
         struct EvalMatchError : public IEvaluator{
         public:
-            EvalMatchError(const char *name){
-                name_ = name;
-                abs_ = 0;
-                if(!strcmp("mabserror", name)) abs_ =1;
-            }            
             virtual float Eval(const std::vector<float> &preds,
                                const DMatrix::Info &info) const {
                 const unsigned ndata = static_cast<unsigned>(preds.size());
@@ -168,19 +164,14 @@ namespace xgboost{
                 for (unsigned i = 0; i < ndata; ++i){
                     const float wt = info.GetWeight(i);
                     int label = static_cast<int>(info.labels[i]);
-                    if( label < 0 && abs_ != 0 ) label = -label-1;
-                    if (static_cast<int>(preds[i]) != label ){
-                        sum += wt;
-                    }
+                    if (static_cast<int>(preds[i]) != label ) sum += wt;
                     wsum += wt;
                 }
                 return sum / wsum;
             }
             virtual const char *Name(void) const{
-                return name_.c_str();
+                return "merror";
             }
-            int abs_;
-            std::string name_;
         };
 
 
@@ -328,7 +319,7 @@ namespace xgboost{
                 float idcg = this->CalcDCG(rec);
                 std::sort(rec.begin(), rec.end(), CmpSecond);
                 float dcg = this->CalcDCG(rec);
-		if( idcg == 0.0f ) return 0.0f;
+                if( idcg == 0.0f ) return 0.0f;
                 else return dcg/idcg;
             }
         };
@@ -366,8 +357,7 @@ namespace xgboost{
                 }
                 if (!strcmp(name, "rmse"))    evals_.push_back(new EvalRMSE());
                 if (!strcmp(name, "error"))   evals_.push_back(new EvalError());
-                if (!strcmp(name, "merror"))   evals_.push_back(new EvalMatchError("merror"));
-                if (!strcmp(name, "mabserror"))   evals_.push_back(new EvalMatchError("mabserror"));
+                if (!strcmp(name, "merror"))   evals_.push_back(new EvalMatchError());
                 if (!strcmp(name, "logloss")) evals_.push_back(new EvalLogLoss());
                 if (!strcmp(name, "auc"))    evals_.push_back(new EvalAuc());
                 if (!strncmp(name, "ams@",4))  evals_.push_back(new EvalAMS(name));