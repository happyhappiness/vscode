@@ -62,7 +62,7 @@ namespace xgboost {
                 * \param end, the end index of a specified group
                 * \return the generated pairs
                 */
-                virtual Pairs GenPairs(const std::vector<float> &preds,
+                virtual std::vector<std::pair<int, int>> GenPairs(const std::vector<float> &preds,
                 const std::vector<float> &labels,
                 int start, int end) = 0;
 
@@ -78,24 +78,11 @@ namespace xgboost {
             *         we should guarantee the labels are 0 or 1
             */
             struct BinaryLinearSampler :public IPairSampler{
-                virtual Pairs GenPairs(const std::vector<float> &preds,
+                virtual std::vector<std::pair<int, int>> GenPairs(const std::vector<float> &preds,
                 const std::vector<float> &labels,
                 int start, int end) {
-                    Pairs pairs(start, end);
-                    int pointer = 0, last_pointer = 0, index = start, interval = end - start;
-                    for (int i = start; i < end; i++){
-                        if (labels[i] == 1){
-                            while (true){
-                                index = (++pointer) % interval + start;
-                                if (labels[index] == 0) break;
-                                if (pointer - last_pointer > interval) return pairs;
-                            }
-                            pairs.push(i, index);
-                            pairs.push(index, i);
-                            last_pointer = pointer;
-                        }
-                    }
-                    return pairs;
+                    std::vector<std::pair<int, int>> ans;
+                    return ans;
                 }
             };
 
@@ -113,7 +100,7 @@ namespace xgboost {
                 
                 ~PairSamplerWrapper(){ delete sampler_; }
 
-                Pairs GenPairs(const std::vector<float> &preds,
+                std::vector<std::pair<int, int>> GenPairs(const std::vector<float> &preds,
                     const std::vector<float> &labels,
                     int start, int end){
                     utils::Assert(sampler_ != NULL, "Not config the sampler yet. Add rank:sampler in the config file\n");
@@ -124,33 +111,7 @@ namespace xgboost {
                 IPairSampler *sampler_;
             };
 
-            template<typename T1, typename T2, typename T3>
-            class Triple{
-            public:
-                T1 f1_;
-                T2 f2_;
-                T3 f3_;
-                Triple(T1 f1, T2 f2, T3 f3) :f1_(f1), f2_(f2), f3_(f3){
-
-                }
-            };
-
-            template<typename T1, typename T2, typename T3, typename T4>
-            class Quadruple{
-            public:
-                T1 f1_;
-                T2 f2_;
-                T3 f3_;
-                T4 f4_;
-                Quadruple(T1 f1, T2 f2, T3 f3, T4 f4) :f1_(f1), f2_(f2), f3_(f3), f4_(f4){
-
-                }
-            };
-
-            bool Triplef1Comparer(const Triple<float, float, int> &a, const Triple<float, float, int> &b){
-                return a.f1_ > b.f1_;
-            }
-
+            
 
         }
     }