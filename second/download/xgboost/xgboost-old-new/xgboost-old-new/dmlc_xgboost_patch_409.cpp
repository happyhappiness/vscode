@@ -99,26 +99,44 @@ namespace xgboost{
             }
         };
 
-        /*! \brief AMS */
+        /*! \brief AMS: also records best threshold */
         struct EvalAMS : public IEvaluator{
             virtual float Eval(const std::vector<float> &preds,
                                const DMatrix::Info &info) const {
                 const unsigned ndata = static_cast<unsigned>(preds.size());
-                double s_tp = 0.0, b_fp = 0.0;
-                #pragma omp parallel for reduction(+:s_tp,b_fp) schedule( static )
+                std::vector< std::pair<float, unsigned> > rec(ndata);
+                
+                #pragma omp parallel for schedule( static )                
                 for (unsigned i = 0; i < ndata; ++i){
-                    const float wt = info.GetWeight(i);                    
-                    if (preds[i] > 0.5f){
-                        if( info.labels[i] > 0.5f ) s_tp += wt;
-                        else b_fp += wt;
-                    }
-                }       
+                    rec[i] = std::make_pair( preds[i], i );
+                }
+                std::sort( rec.begin(), rec.end(), CmpFirst );
+
                 const double br = 10.0;
-                return sqrtf( 2*((s_tp+b_fp+br) * log( 1.0 + s_tp/(b_fp+br) ) - s_tp) );
+                double s_tp = 0.0, b_fp = 0.0, tams = 0.0, threshold = 0.0;
+                for (unsigned i = 0; i < ndata-1; ++i){
+                    const unsigned ridx = rec[i].second;
+                    const float wt = info.weights[ridx];
+                    if( info.labels[ridx] > 0.5f ){
+                        s_tp += wt;
+                    }else{
+                        b_fp += wt;
+                    }
+                    if( rec[i].first != rec[i+1].first ){
+                        double ams = sqrtf( 2*((s_tp+b_fp+br) * log( 1.0 + s_tp/(b_fp+br) ) - s_tp) );
+                        if( tams < ams ){
+                            threshold = (rec[i].first + rec[i+1].first) / 2.0;
+                            tams = ams;
+                        }
+                    }
+                }
+                fprintf( stderr, "\tams-thres=%g", threshold );
+                return tams;
             }
             virtual const char *Name(void) const{
                 return "ams";
             }
+            double wtarget;
         };
 
         /*! \brief Error */