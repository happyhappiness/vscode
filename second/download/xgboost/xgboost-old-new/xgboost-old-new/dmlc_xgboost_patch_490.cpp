@@ -19,7 +19,7 @@ namespace xgboost {
                  * \param start the begin index of the group
                  * \param end the end index of the group
                  */
-                Pairs(int start, int end) :start_(start), end_(end_){
+                Pairs(int start, int end) :start_(start), end_(end){
                     for (int i = start; i < end; i++){
                         std::vector<int> v;
                         pairs_.push_back(v);
@@ -30,7 +30,7 @@ namespace xgboost {
                  * \param index, the index of retrieved instance
                  * \return the index of instances paired
                  */
-                std::vector<int> GetPairs(int index) {
+                std::vector<int> GetPairs(int index) const{
                     utils::Assert(index >= start_ && index < end_, "The query index out of sampling bound");
                     return pairs_[index - start_];
                 }