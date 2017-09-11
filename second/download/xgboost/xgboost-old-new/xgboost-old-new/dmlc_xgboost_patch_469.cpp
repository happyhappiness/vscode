@@ -11,6 +11,7 @@
 #include <algorithm>
 #include "../utils/xgboost_utils.h"
 #include "../utils/xgboost_omp.h"
+#include "../utils/xgboost_random.h"
 
 namespace xgboost{
     namespace regression{
@@ -30,10 +31,10 @@ namespace xgboost{
         /*! \brief RMSE */
         struct EvalRMSE : public IEvaluator{
             virtual float Eval(const std::vector<float> &preds,
-            const std::vector<float> &labels) const{
+                               const std::vector<float> &labels) const{
                 const unsigned ndata = static_cast<unsigned>(preds.size());
                 float sum = 0.0;
-#pragma omp parallel for reduction(+:sum) schedule( static )
+                #pragma omp parallel for reduction(+:sum) schedule( static )
                 for (unsigned i = 0; i < ndata; ++i){
                     float diff = preds[i] - labels[i];
                     sum += diff * diff;
@@ -48,10 +49,10 @@ namespace xgboost{
         /*! \brief Error */
         struct EvalError : public IEvaluator{
             virtual float Eval(const std::vector<float> &preds,
-            const std::vector<float> &labels) const{
+                               const std::vector<float> &labels) const{
                 const unsigned ndata = static_cast<unsigned>(preds.size());
                 unsigned nerr = 0;
-#pragma omp parallel for reduction(+:nerr) schedule( static )
+                #pragma omp parallel for reduction(+:nerr) schedule( static )
                 for (unsigned i = 0; i < ndata; ++i){
                     if (preds[i] > 0.5f){
                         if (labels[i] < 0.5f) nerr += 1;
@@ -67,14 +68,46 @@ namespace xgboost{
             }
         };
 
+        /*! \brief Area under curve */
+        struct EvalAuc : public IEvaluator{         
+            inline static bool CmpFirst( const std::pair<float,float> &a, const std::pair<float,float> &b ){
+                return a.first > b.first;
+            }
+            virtual float Eval( const std::vector<float> &preds, 
+                                const std::vector<float> &labels ) const{
+                const unsigned ndata = static_cast<unsigned>( preds.size() );
+                std::vector< std::pair<float, float> > rec;
+                for( unsigned i = 0; i < ndata; ++ i ){
+                    rec.push_back( std::make_pair( preds[i], labels[i]) );
+                }
+                random::Shuffle( rec );
+                std::sort( rec.begin(), rec.end(), CmpFirst );
+
+                long npos = 0, nhit = 0;
+                for( unsigned i = 0; i < ndata; ++ i ){
+                    if( rec[i].second > 0.5f ) {
+                        ++ npos; 
+                    }else{
+                        // this is the number of correct pairs
+                        nhit += npos;
+                    }
+                } 
+                long nneg = ndata - npos;
+                utils::Assert( nneg > 0, "the dataset only contains pos samples" );
+                return static_cast<float>(nhit) / nneg / npos;
+            }
+            virtual const char *Name( void ) const{
+                return "auc";
+            }
+        };
 
         /*! \brief Error */
         struct EvalLogLoss : public IEvaluator{
             virtual float Eval(const std::vector<float> &preds,
-            const std::vector<float> &labels) const{
+                               const std::vector<float> &labels) const{
                 const unsigned ndata = static_cast<unsigned>(preds.size());
                 unsigned nerr = 0;
-#pragma omp parallel for reduction(+:nerr) schedule( static )
+                #pragma omp parallel for reduction(+:nerr) schedule( static )
                 for (unsigned i = 0; i < ndata; ++i){
                     const float y = labels[i];
                     const float py = preds[i];
@@ -96,14 +129,15 @@ namespace xgboost{
                 if (!strcmp(name, "rmse")) evals_.push_back(&rmse_);
                 if (!strcmp(name, "error")) evals_.push_back(&error_);
                 if (!strcmp(name, "logloss")) evals_.push_back(&logloss_);
+                if (!strcmp( name, "auc"))   evals_.push_back( &auc_ );
             }
             inline void Init(void){
                 std::sort(evals_.begin(), evals_.end());
                 evals_.resize(std::unique(evals_.begin(), evals_.end()) - evals_.begin());
             }
             inline void Eval(FILE *fo, const char *evname,
-                const std::vector<float> &preds,
-                const std::vector<float> &labels) const{
+                             const std::vector<float> &preds,
+                             const std::vector<float> &labels) const{
                 for (size_t i = 0; i < evals_.size(); ++i){
                     float res = evals_[i]->Eval(preds, labels);
                     fprintf(fo, "\t%s-%s:%f", evname, evals_[i]->Name(), res);
@@ -112,6 +146,7 @@ namespace xgboost{
         private:
             EvalRMSE  rmse_;
             EvalError error_;
+            EvalAuc   auc_;
             EvalLogLoss logloss_;
             std::vector<const IEvaluator*> evals_;
         };