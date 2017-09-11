@@ -62,7 +62,7 @@ namespace xgboost {
                 * \param end, the end index of a specified group
                 * \return the generated pairs
                 */
-                virtual std::vector<std::pair<int, int>> GenPairs(const std::vector<float> &preds,
+                virtual std::vector< std::pair<int, int> > GenPairs(const std::vector<float> &preds,
                 const std::vector<float> &labels,
                 int start, int end) = 0;
 
@@ -78,10 +78,10 @@ namespace xgboost {
             *         we should guarantee the labels are 0 or 1
             */
             struct BinaryLinearSampler :public IPairSampler{
-                virtual std::vector<std::pair<int, int>> GenPairs(const std::vector<float> &preds,
+                virtual std::vector< std::pair<int, int> > GenPairs(const std::vector<float> &preds,
                 const std::vector<float> &labels,
                 int start, int end) {
-                    std::vector<std::pair<int, int>> ans;
+                    std::vector< std::pair<int, int> > ans;
                     return ans;
                 }
             };
@@ -100,7 +100,7 @@ namespace xgboost {
                 
                 ~PairSamplerWrapper(){ delete sampler_; }
 
-                std::vector<std::pair<int, int>> GenPairs(const std::vector<float> &preds,
+                std::vector< std::pair<int, int> > GenPairs(const std::vector<float> &preds,
                     const std::vector<float> &labels,
                     int start, int end){
                     utils::Assert(sampler_ != NULL, "Not config the sampler yet. Add rank:sampler in the config file\n");