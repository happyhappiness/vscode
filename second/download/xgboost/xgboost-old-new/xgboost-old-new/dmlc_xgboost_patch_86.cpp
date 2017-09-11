@@ -1,26 +1,28 @@
+// Copyright 2014 by Contributors
 #define _CRT_SECURE_NO_WARNINGS
 #define _CRT_SECURE_NO_DEPRECATE
 #define NOMINMAX
 #include <ctime>
 #include <string>
 #include <cstring>
+#include <vector>
 #include "./sync/sync.h"
-#include "io/io.h"
-#include "utils/utils.h"
-#include "utils/config.h"
-#include "learner/learner-inl.hpp"
+#include "./io/io.h"
+#include "./utils/utils.h"
+#include "./utils/config.h"
+#include "./learner/learner-inl.hpp"
 
 namespace xgboost {
 /*!
- * \brief wrapping the training process 
+ * \brief wrapping the training process
  */
 class BoostLearnTask {
  public:
   inline int Run(int argc, char *argv[]) {
     if (argc < 2) {
       printf("Usage: <config>\n");
       return 0;
-    }    
+    }
     utils::ConfigIterator itr(argv[1]);
     while (itr.Next()) {
       this->SetParam(itr.name(), itr.val());
@@ -44,10 +46,10 @@ class BoostLearnTask {
     }
     if (rabit::IsDistributed() && data_split == "NONE") {
       this->SetParam("dsplit", "row");
-    }    
+    }
     if (rabit::GetRank() != 0) {
       this->SetParam("silent", "2");
-    }    
+    }
     this->InitData();
 
     if (task == "train") {
@@ -90,12 +92,14 @@ class BoostLearnTask {
     if (!strcmp("save_pbuffer", name)) save_with_pbuffer = atoi(val);
     if (!strncmp("eval[", name, 5)) {
       char evname[256];
-      utils::Assert(sscanf(name, "eval[%[^]]", evname) == 1, "must specify evaluation name for display");
+      utils::Assert(sscanf(name, "eval[%[^]]", evname) == 1,
+                    "must specify evaluation name for display");
       eval_data_names.push_back(std::string(evname));
       eval_data_paths.push_back(std::string(val));
     }
     learner.SetParam(name, val);
   }
+
  public:
   BoostLearnTask(void) {
     // default parameters
@@ -119,12 +123,13 @@ class BoostLearnTask {
     save_with_pbuffer = 0;
     data = NULL;
   }
-  ~BoostLearnTask(void){
-    for (size_t i = 0; i < deval.size(); i++){
+  ~BoostLearnTask(void) {
+    for (size_t i = 0; i < deval.size(); i++) {
       delete deval[i];
     }
     if (data != NULL) delete data;
   }
+
  private:
   inline void InitData(void) {
     if (strchr(train_path.c_str(), '%') != NULL) {
@@ -151,14 +156,14 @@ class BoostLearnTask {
                                            loadsplit));
         devalall.push_back(deval.back());
       }
-            
+
       std::vector<io::DataMatrix *> dcache(1, data);
-      for (size_t i = 0; i < deval.size(); ++ i) {
+      for (size_t i = 0; i < deval.size(); ++i) {
         dcache.push_back(deval[i]);
       }
       // set cache data to be all training and evaluation data
       learner.SetCacheData(dcache);
-      
+
       // add training set to evaluation set if needed
       if (eval_train != 0) {
         devalall.push_back(data);
@@ -178,13 +183,13 @@ class BoostLearnTask {
     int version = rabit::LoadCheckPoint(&learner);
     if (version == 0) this->InitLearner();
     const time_t start = time(NULL);
-    unsigned long elapsed = 0;
+    unsigned long elapsed = 0;  // NOLINT(*)
     learner.CheckInit(data);
 
     bool allow_lazy = learner.AllowLazyCheckPoint();
     for (int i = version / 2; i < num_round; ++i) {
-      elapsed = (unsigned long)(time(NULL) - start);
-      if (version % 2 == 0) { 
+      elapsed = (unsigned long)(time(NULL) - start);  // NOLINT(*)
+      if (version % 2 == 0) {
         if (!silent) printf("boosting round %d, %lu sec elapsed\n", i, elapsed);
         learner.UpdateOneIter(i, *data);
         if (allow_lazy) {
@@ -196,7 +201,7 @@ class BoostLearnTask {
       }
       utils::Assert(version == rabit::VersionNumber(), "consistent check");
       std::string res = learner.EvalOneIter(i, devalall, eval_data_names);
-      if (rabit::IsDistributed()){
+      if (rabit::IsDistributed()) {
         if (rabit::GetRank() == 0) {
           rabit::TrackerPrintf("%s\n", res.c_str());
         }
@@ -215,29 +220,29 @@ class BoostLearnTask {
       }
       version += 1;
       utils::Assert(version == rabit::VersionNumber(), "consistent check");
-      elapsed = (unsigned long)(time(NULL) - start);
+      elapsed = (unsigned long)(time(NULL) - start);  // NOLINT(*)
     }
     // always save final round
     if ((save_period == 0 || num_round % save_period != 0) && model_out != "NONE") {
-      if (model_out == "NULL"){
+      if (model_out == "NULL") {
         this->SaveModel(num_round - 1);
       } else {
         this->SaveModel(model_out.c_str());
       }
     }
-    if (!silent){
+    if (!silent) {
       printf("\nupdating end, %lu sec in all\n", elapsed);
     }
   }
   inline void TaskEval(void) {
     learner.EvalOneIter(0, devalall, eval_data_names);
   }
-  inline void TaskDump(void){
+  inline void TaskDump(void) {
     FILE *fo = utils::FopenCheck(name_dump.c_str(), "w");
     std::vector<std::string> dump = learner.DumpModel(fmap, dump_model_stats != 0);
-    for (size_t i = 0; i < dump.size(); ++ i) {
-      fprintf(fo,"booster[%lu]:\n", i);
-      fprintf(fo,"%s", dump[i].c_str()); 
+    for (size_t i = 0; i < dump.size(); ++i) {
+      fprintf(fo, "booster[%lu]:\n", i);
+      fprintf(fo, "%s", dump[i].c_str());
     }
     fclose(fo);
   }
@@ -247,14 +252,15 @@ class BoostLearnTask {
   }
   inline void SaveModel(int i) const {
     char fname[256];
-    sprintf(fname, "%s/%04d.model", model_dir_path.c_str(), i + 1);
+    utils::SPrintf(fname, sizeof(fname),
+                   "%s/%04d.model", model_dir_path.c_str(), i + 1);
     this->SaveModel(fname);
   }
   inline void TaskPred(void) {
     std::vector<float> preds;
     if (!silent) printf("start prediction...\n");
     learner.Predict(*data, pred_margin != 0, &preds, ntree_limit);
-    if (!silent) printf("writing prediction to %s\n", name_pred.c_str());    
+    if (!silent) printf("writing prediction to %s\n", name_pred.c_str());
     FILE *fo;
     if (name_pred != "stdout") {
       fo = utils::FopenCheck(name_pred.c_str(), "w");
@@ -266,14 +272,15 @@ class BoostLearnTask {
     }
     if (fo != stdout) fclose(fo);
   }
+
  private:
   /*! \brief whether silent */
   int silent;
   /*! \brief special load */
   int load_part;
   /*! \brief whether use auto binary buffer */
   int use_buffer;
-  /*! \brief whether evaluate training statistics */            
+  /*! \brief whether evaluate training statistics */
   int eval_train;
   /*! \brief number of boosting iterations */
   int num_round;
@@ -309,16 +316,17 @@ class BoostLearnTask {
   std::vector<std::string> eval_data_paths;
   /*! \brief the names of the evaluation data used in output log */
   std::vector<std::string> eval_data_names;
+
  private:
   io::DataMatrix* data;
   std::vector<io::DataMatrix*> deval;
   std::vector<const io::DataMatrix*> devalall;
   utils::FeatMap fmap;
   learner::BoostLearner learner;
 };
-}
+}  // namespace xgboost
 
-int main(int argc, char *argv[]){
+int main(int argc, char *argv[]) {
   xgboost::BoostLearnTask tsk;
   tsk.SetParam("seed", "0");
   int ret = tsk.Run(argc, argv);