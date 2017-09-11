@@ -83,7 +83,7 @@ namespace xgboost{
                 float sum = 0.0f, wsum = 0.0f;
                 #pragma omp parallel for reduction(+:sum,wsum) schedule( static )
                 for (unsigned i = 0; i < ndata; ++i){
-                    const float wt = info.GetWeight(i);
+                    const float wt = info.GetWeight(i);                    
                     if (preds[i] > 0.5f){
                         if (info.labels[i] < 0.5f) sum += wt;
                     }
@@ -99,6 +99,39 @@ namespace xgboost{
             }
         };
 
+
+        /*! \brief Error */
+        struct EvalMatchError : public IEvaluator{
+        public:
+            EvalMatchError(const char *name){
+                name_ = name;
+                abs_ = 0;
+                if(!strcmp("mabserror", name)) abs_ =1;
+            }            
+            virtual float Eval(const std::vector<float> &preds,
+                               const DMatrix::Info &info) const {
+                const unsigned ndata = static_cast<unsigned>(preds.size());
+                float sum = 0.0f, wsum = 0.0f;
+                #pragma omp parallel for reduction(+:sum,wsum) schedule( static )
+                for (unsigned i = 0; i < ndata; ++i){
+                    const float wt = info.GetWeight(i);
+                    int label = static_cast<int>(info.labels[i]);
+                    if( label < 0 && abs_ != 0 ) label = -label-1;
+                    if (static_cast<int>(preds[i]) != label ){
+                        sum += wt;
+                    }
+                    wsum += wt;
+                }
+                return sum / wsum;
+            }
+            virtual const char *Name(void) const{
+                return name_.c_str();
+            }
+            int abs_;
+            std::string name_;
+        };
+
+
         /*! \brief Area under curve, for both classification and rank */
         struct EvalAuc : public IEvaluator{
             virtual float Eval(const std::vector<float> &preds,
@@ -281,6 +314,8 @@ namespace xgboost{
                 }
                 if (!strcmp(name, "rmse"))    evals_.push_back(new EvalRMSE());
                 if (!strcmp(name, "error"))   evals_.push_back(new EvalError());
+                if (!strcmp(name, "merror"))   evals_.push_back(new EvalMatchError("merror"));
+                if (!strcmp(name, "mabserror"))   evals_.push_back(new EvalMatchError("mabserror"));
                 if (!strcmp(name, "logloss")) evals_.push_back(new EvalLogLoss());
                 if (!strcmp(name, "auc"))    evals_.push_back(new EvalAuc());
                 if (!strncmp(name, "pre@", 4)) evals_.push_back(new EvalPrecision(name));