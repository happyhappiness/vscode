@@ -1,7 +1,7 @@
 #ifndef _XGBOOST_SAMPLE_H_
 #define _XGBOOST_SAMPLE_H_
 
-#include<vector>
+#include <vector>
 #include"../utils/xgboost_utils.h"
 
 namespace xgboost {
@@ -21,7 +21,7 @@ namespace xgboost {
        */
       Pairs(int start,int end):start_(start),end_(end_){
 	for(int i = start; i < end; i++){
-	  vector<int> v;
+	  std::vector<int> v;
 	  pairs_.push_back(v);
 	}
       }
@@ -31,7 +31,7 @@ namespace xgboost {
        * \return the index of instances paired
        */
       std::vector<int> GetPairs(int index) {
-        utils::assert(index >= start_ && index < end_,"The query index out of sampling bound");
+	utils::Assert(index >= start_ && index < end_,"The query index out of sampling bound");
         return pairs_[index-start_];
       }
 
@@ -44,7 +44,7 @@ namespace xgboost {
 	pairs_[index - start_].push_back(paired_index);
       }
       
-      std::vector<std::vector<int>> pairs_;
+      std::vector< std::vector<int> > pairs_;
       int start_;
       int end_;
     };
@@ -115,7 +115,7 @@ namespace xgboost {
             Pairs GenPairs(const std::vector<float> &preds,
 			   const std::vector<float> &labels,
 			   int start,int end){
-	      return sampler_.GenPairs(preds,labels,start,end);
+	      return sampler_->GenPairs(preds,labels,start,end);
 	    }
         private:
 	    BinaryLinearSampler binary_linear_sampler;
@@ -124,4 +124,4 @@ namespace xgboost {
     }
   }
 }
-
+#endif
\ No newline at end of file