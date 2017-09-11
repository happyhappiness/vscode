@@ -110,6 +110,7 @@ namespace xgboost{
             virtual float Eval(const std::vector<float> &preds,
                                const DMatrix::Info &info) const {
                 const unsigned ndata = static_cast<unsigned>(preds.size());
+                utils::Assert( info.weights.size() == ndata, "we need weight to evaluate ams");
                 std::vector< std::pair<float, unsigned> > rec(ndata);
                 
                 #pragma omp parallel for schedule( static )                