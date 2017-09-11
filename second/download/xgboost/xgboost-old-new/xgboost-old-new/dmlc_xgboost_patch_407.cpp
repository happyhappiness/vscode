@@ -101,6 +101,11 @@ namespace xgboost{
 
         /*! \brief AMS: also records best threshold */
         struct EvalAMS : public IEvaluator{
+        public:
+            EvalAMS(const char *name){
+                name_ = name;
+                utils::Assert( sscanf(name, "ams@%f", &ratio_ ) == 1, "invalid ams format" );
+            }            
             virtual float Eval(const std::vector<float> &preds,
                                const DMatrix::Info &info) const {
                 const unsigned ndata = static_cast<unsigned>(preds.size());
@@ -111,10 +116,12 @@ namespace xgboost{
                     rec[i] = std::make_pair( preds[i], i );
                 }
                 std::sort( rec.begin(), rec.end(), CmpFirst );
-
+                unsigned ntop = static_cast<unsigned>( ratio_ * ndata );
+                if( ntop == 0 ) ntop = ndata;
                 const double br = 10.0;
-                double s_tp = 0.0, b_fp = 0.0, tams = 0.0, threshold = 0.0;
-                for (unsigned i = 0; i < ndata-1; ++i){
+                unsigned thresindex = 0;
+                double s_tp = 0.0, b_fp = 0.0, tams = 0.0;
+                for (unsigned i = 0; i < ndata-1 && i < ntop; ++i){
                     const unsigned ridx = rec[i].second;
                     const float wt = info.weights[ridx];
                     if( info.labels[ridx] > 0.5f ){
@@ -125,18 +132,24 @@ namespace xgboost{
                     if( rec[i].first != rec[i+1].first ){
                         double ams = sqrtf( 2*((s_tp+b_fp+br) * log( 1.0 + s_tp/(b_fp+br) ) - s_tp) );
                         if( tams < ams ){
-                            threshold = (rec[i].first + rec[i+1].first) / 2.0;
+                            thresindex = i;
                             tams = ams;
                         }
                     }
                 }
-                fprintf( stderr, "\tams-thres=%g", threshold );
-                return tams;
+                if( ntop == ndata ){
+                    fprintf( stderr, "\tams-ratio=%g", float(thresindex)/ndata );
+                    return tams;
+                }else{
+                    return sqrtf( 2*((s_tp+b_fp+br) * log( 1.0 + s_tp/(b_fp+br) ) - s_tp) );
+                }
             }
             virtual const char *Name(void) const{
-                return "ams";
+                return name_.c_str();
             }
-            double wtarget;
+        private:
+            std::string name_;
+            float ratio_;
         };
 
         /*! \brief Error */
@@ -355,9 +368,9 @@ namespace xgboost{
                 if (!strcmp(name, "error"))   evals_.push_back(new EvalError());
                 if (!strcmp(name, "merror"))   evals_.push_back(new EvalMatchError("merror"));
                 if (!strcmp(name, "mabserror"))   evals_.push_back(new EvalMatchError("mabserror"));
-                if (!strcmp(name, "ams"))         evals_.push_back(new EvalAMS());
                 if (!strcmp(name, "logloss")) evals_.push_back(new EvalLogLoss());
                 if (!strcmp(name, "auc"))    evals_.push_back(new EvalAuc());
+                if (!strncmp(name, "ams@",4))  evals_.push_back(new EvalAMS(name));
                 if (!strncmp(name, "pre@", 4)) evals_.push_back(new EvalPrecision(name));
                 if (!strncmp(name, "map", 3))   evals_.push_back(new EvalMAP(name));
                 if (!strncmp(name, "ndcg", 3))  evals_.push_back(new EvalNDCG(name));