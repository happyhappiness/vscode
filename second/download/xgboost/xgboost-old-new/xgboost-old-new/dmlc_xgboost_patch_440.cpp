@@ -160,7 +160,8 @@ namespace xgboost{
             virtual float Eval(const std::vector<float> &preds,
                                const DMatrix::Info &info) const {
                 const std::vector<unsigned> &gptr = info.group_ptr;
-                utils::Assert(gptr.size() != 0 && gptr.back() == preds.size(), "EvalAuc: group structure must match number of prediction");
+                utils::Assert(gptr.size() != 0, "must specify group when constructing rank file");
+                utils::Assert( gptr.back() == preds.size(), "EvalRanklist: group structure must match number of prediction");
                 const unsigned ngroup = static_cast<unsigned>(gptr.size() - 1);
 
                 double sum_metric = 0.0f;