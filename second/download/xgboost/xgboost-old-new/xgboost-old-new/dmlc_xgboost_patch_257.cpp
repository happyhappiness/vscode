@@ -5,6 +5,7 @@
 #include <string>
 #include <cstring>
 #include "io/io.h"
+#include "sync/sync.h"
 #include "utils/utils.h"
 #include "utils/config.h"
 #include "learner/learner-inl.hpp"
@@ -19,7 +20,7 @@ class BoostLearnTask{
     if (argc < 2) {
       printf("Usage: <config>\n");
       return 0;
-    }
+    }    
     utils::ConfigIterator itr(argv[1]);
     while (itr.Next()) {
       this->SetParam(itr.name(), itr.val());
@@ -30,6 +31,9 @@ class BoostLearnTask{
         this->SetParam(name, val);
       }
     }
+    if (sync::GetRank() != 0) {
+      this->SetParam("silent", "2");
+    }
     this->InitData();
     this->InitLearner();
     if (task == "dump") {
@@ -145,7 +149,9 @@ class BoostLearnTask{
       if (!silent) printf("boosting round %d, %lu sec elapsed\n", i, elapsed);
       learner.UpdateOneIter(i, *data); 
       std::string res = learner.EvalOneIter(i, devalall, eval_data_names);
-      fprintf(stderr, "%s\n", res.c_str());
+      if (silent < 1) {
+        fprintf(stderr, "%s\n", res.c_str());
+      }
       if (save_period != 0 && (i + 1) % save_period == 0) {
         this->SaveModel(i);
       }
@@ -243,7 +249,10 @@ class BoostLearnTask{
 }
 
 int main(int argc, char *argv[]){
+  xgboost::sync::Init(argc, argv);
   xgboost::random::Seed(0);
   xgboost::BoostLearnTask tsk;
-  return tsk.Run(argc, argv);
+  int ret = tsk.Run(argc, argv);
+  xgboost::sync::Finalize();
+  return ret;
 }