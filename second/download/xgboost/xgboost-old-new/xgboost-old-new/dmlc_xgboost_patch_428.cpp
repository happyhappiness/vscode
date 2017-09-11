@@ -13,6 +13,7 @@
 #include "../utils/xgboost_omp.h"
 #include "../utils/xgboost_random.h"
 #include "xgboost_regrank_data.h"
+#include "xgboost_regrank_utils.h"
 
 namespace xgboost{
     namespace regrank{
@@ -31,17 +32,11 @@ namespace xgboost{
             virtual ~IEvaluator(void){}
         };
 
-        inline static bool CmpFirst(const std::pair<float, unsigned> &a, const std::pair<float, unsigned> &b){
-            return a.first > b.first;
-        }
-        inline static bool CmpSecond(const std::pair<float, unsigned> &a, const std::pair<float, unsigned> &b){
-            return a.second > b.second;
-        }
-
         /*! \brief RMSE */
         struct EvalRMSE : public IEvaluator{
             virtual float Eval(const std::vector<float> &preds,
                                const DMatrix::Info &info) const {
+                utils::Assert( preds.size() == info.labels.size(), "label size predict size not match" );
                 const unsigned ndata = static_cast<unsigned>(preds.size());
                 float sum = 0.0, wsum = 0.0;
                 #pragma omp parallel for reduction(+:sum,wsum) schedule( static )
@@ -62,6 +57,7 @@ namespace xgboost{
         struct EvalLogLoss : public IEvaluator{
             virtual float Eval(const std::vector<float> &preds,
                                const DMatrix::Info &info) const {
+                utils::Assert( preds.size() == info.labels.size(), "label size predict size not match" );
                 const unsigned ndata = static_cast<unsigned>(preds.size());
                 float sum = 0.0f, wsum = 0.0f;
                 #pragma omp parallel for reduction(+:sum,wsum) schedule( static )
@@ -106,7 +102,8 @@ namespace xgboost{
         /*! \brief Area under curve, for both classification and rank */
         struct EvalAuc : public IEvaluator{
             virtual float Eval(const std::vector<float> &preds,
-            const DMatrix::Info &info) const {
+                               const DMatrix::Info &info) const {
+                utils::Assert( preds.size() == info.labels.size(), "label size predict size not match" );
                 std::vector<unsigned> tgptr(2, 0); tgptr[1] = preds.size();
                 const std::vector<unsigned> &gptr = info.group_ptr.size() == 0 ? tgptr : info.group_ptr;
                 utils::Assert(gptr.back() == preds.size(), "EvalAuc: group structure must match number of prediction");
@@ -159,8 +156,10 @@ namespace xgboost{
         public:
             virtual float Eval(const std::vector<float> &preds,
                                const DMatrix::Info &info) const {
+                utils::Assert( preds.size() == info.labels.size(), "label size predict size not match" );
                 const std::vector<unsigned> &gptr = info.group_ptr;
-                utils::Assert(gptr.size() != 0 && gptr.back() == preds.size(), "EvalAuc: group structure must match number of prediction");
+                utils::Assert(gptr.size() != 0, "must specify group when constructing rank file");
+                utils::Assert( gptr.back() == preds.size(), "EvalRanklist: group structure must match number of prediction");
                 const unsigned ngroup = static_cast<unsigned>(gptr.size() - 1);
 
                 double sum_metric = 0.0f;