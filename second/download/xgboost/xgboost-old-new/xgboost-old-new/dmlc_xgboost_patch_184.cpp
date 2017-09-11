@@ -1,9 +1,10 @@
 #define _CRT_SECURE_NO_WARNINGS
 #define _CRT_SECURE_NO_DEPRECATE
-
+#define NOMINMAX
 #include <ctime>
 #include <string>
 #include <cstring>
+#include "./sync/sync.h"
 #include "io/io.h"
 #include "utils/utils.h"
 #include "utils/config.h"
@@ -13,13 +14,13 @@ namespace xgboost {
 /*!
  * \brief wrapping the training process 
  */
-class BoostLearnTask{
+class BoostLearnTask {
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
@@ -30,8 +31,36 @@ class BoostLearnTask{
         this->SetParam(name, val);
       }
     }
+    // do not save anything when save to stdout
+    if (model_out == "stdout" || name_pred == "stdout") {
+      this->SetParam("silent", "1");
+      save_period = 0;
+    }
+    // whether need data rank
+    bool need_data_rank = strchr(train_path.c_str(), '%') != NULL;
+    // if need data rank in loading, initialize rabit engine before load data
+    // otherwise, initialize rabit engine after loading data
+    // lazy initialization of rabit engine can be helpful in speculative execution
+    if (need_data_rank) rabit::Init(argc, argv);
     this->InitData();
-    this->InitLearner();
+    if (!need_data_rank) rabit::Init(argc, argv);
+    if (rabit::IsDistributed()) {
+      std::string pname = rabit::GetProcessorName();
+      fprintf(stderr, "start %s:%d\n", pname.c_str(), rabit::GetRank());
+    }
+    if (rabit::IsDistributed() && data_split == "NONE") {
+      this->SetParam("dsplit", "row");
+    }
+    if (rabit::GetRank() != 0) {
+      this->SetParam("silent", "2");
+    }    
+    if (task == "train") {
+      // if task is training, will try recover from checkpoint
+      this->TaskTrain();
+      return 0;
+    } else {
+      this->InitLearner();
+    }
     if (task == "dump") {
       this->TaskDump(); return 0;
     }
@@ -40,8 +69,6 @@ class BoostLearnTask{
     }
     if (task == "pred") {
       this->TaskPred();
-    } else {
-      this->TaskTrain();
     }
     return 0;
   }
@@ -62,6 +89,7 @@ class BoostLearnTask{
     if (!strcmp("fmap", name)) name_fmap = val;
     if (!strcmp("name_dump", name)) name_dump = val;
     if (!strcmp("name_pred", name)) name_pred = val;
+    if (!strcmp("dsplit", name)) data_split = val;
     if (!strcmp("dump_stats", name)) dump_model_stats = atoi(val);
     if (!strncmp("eval[", name, 5)) {
       char evname[256];
@@ -89,6 +117,8 @@ class BoostLearnTask{
     name_pred = "pred.txt";
     name_dump = "dump.txt";
     model_dir_path = "./";
+    data_split = "NONE";
+    load_part = 0;
     data = NULL;
   }
   ~BoostLearnTask(void){
@@ -99,13 +129,20 @@ class BoostLearnTask{
   }
  private:
   inline void InitData(void) {
+    if (strchr(train_path.c_str(), '%') != NULL) {
+      char s_tmp[256];
+      utils::SPrintf(s_tmp, sizeof(s_tmp), train_path.c_str(), rabit::GetRank());
+      train_path = s_tmp;
+      load_part = 1;
+    }
+
     if (name_fmap != "NULL") fmap.LoadText(name_fmap.c_str());
     if (task == "dump") return;
     if (task == "pred") {
       data = io::LoadDataMatrix(test_path.c_str(), silent != 0, use_buffer != 0);
     } else {
       // training
-      data = io::LoadDataMatrix(train_path.c_str(), silent != 0, use_buffer != 0);
+      data = io::LoadDataMatrix(train_path.c_str(), silent != 0 && load_part == 0, use_buffer != 0);
       utils::Assert(eval_data_names.size() == eval_data_paths.size(), "BUG");
       for (size_t i = 0; i < eval_data_names.size(); ++i) {
         deval.push_back(io::LoadDataMatrix(eval_data_paths[i].c_str(), silent != 0, use_buffer != 0));
@@ -120,35 +157,61 @@ class BoostLearnTask{
       learner.SetCacheData(dcache);
       
       // add training set to evaluation set if needed
-      if( eval_train != 0 ) {
+      if (eval_train != 0) {
         devalall.push_back(data);
         eval_data_names.push_back(std::string("train"));
       }
     }
   }
   inline void InitLearner(void) {
-    if (model_in != "NULL"){
-      utils::FileStream fi(utils::FopenCheck(model_in.c_str(), "rb"));
-      learner.LoadModel(fi);
-      fi.Close();
+    if (model_in != "NULL") {
+      learner.LoadModel(model_in.c_str());
     } else {
       utils::Assert(task == "train", "model_in not specified");
       learner.InitModel();
     }
   }
   inline void TaskTrain(void) {
+    int version = rabit::LoadCheckPoint(&learner);
+    if (version == 0) this->InitLearner();
     const time_t start = time(NULL);
     unsigned long elapsed = 0;
     learner.CheckInit(data);
-    for (int i = 0; i < num_round; ++i) {
+
+    bool allow_lazy = learner.AllowLazyCheckPoint();
+    for (int i = version / 2; i < num_round; ++i) {
       elapsed = (unsigned long)(time(NULL) - start);
-      if (!silent) printf("boosting round %d, %lu sec elapsed\n", i, elapsed);
-      learner.UpdateOneIter(i, *data); 
+      if (version % 2 == 0) { 
+        if (!silent) printf("boosting round %d, %lu sec elapsed\n", i, elapsed);
+        learner.UpdateOneIter(i, *data);
+        if (allow_lazy) {
+          rabit::LazyCheckPoint(&learner);
+        } else {
+          rabit::CheckPoint(&learner);
+        }
+        version += 1;
+      }
+      utils::Assert(version == rabit::VersionNumber(), "consistent check");
       std::string res = learner.EvalOneIter(i, devalall, eval_data_names);
-      fprintf(stderr, "%s\n", res.c_str());
+      if (rabit::IsDistributed()){
+        if (rabit::GetRank() == 0) {
+          rabit::TrackerPrintf("%s\n", res.c_str());
+        }
+      } else {
+        if (silent < 2) {
+          fprintf(stderr, "%s\n", res.c_str());
+        }
+      }
       if (save_period != 0 && (i + 1) % save_period == 0) {
         this->SaveModel(i);
       }
+      if (allow_lazy) {
+        rabit::LazyCheckPoint(&learner);
+      } else {
+        rabit::CheckPoint(&learner);
+      }
+      version += 1;
+      utils::Assert(version == rabit::VersionNumber(), "consistent check");
       elapsed = (unsigned long)(time(NULL) - start);
     }
     // always save final round
@@ -176,9 +239,8 @@ class BoostLearnTask{
     fclose(fo);
   }
   inline void SaveModel(const char *fname) const {
-    utils::FileStream fo(utils::FopenCheck(fname, "wb"));
-    learner.SaveModel(fo);
-    fo.Close();
+    if (rabit::GetRank() != 0) return;
+    learner.SaveModel(fname);
   }
   inline void SaveModel(int i) const {
     char fname[256];
@@ -189,16 +251,23 @@ class BoostLearnTask{
     std::vector<float> preds;
     if (!silent) printf("start prediction...\n");
     learner.Predict(*data, pred_margin != 0, &preds, ntree_limit);
-    if (!silent) printf("writing prediction to %s\n", name_pred.c_str());
-    FILE *fo = utils::FopenCheck(name_pred.c_str(), "w");
-    for (size_t i = 0; i < preds.size(); i++) {
-      fprintf(fo, "%f\n", preds[i]);
+    if (!silent) printf("writing prediction to %s\n", name_pred.c_str());    
+    FILE *fo;
+    if (name_pred != "stdout") {
+      fo = utils::FopenCheck(name_pred.c_str(), "w");
+    } else {
+      fo = stdout;
     }
-    fclose(fo);
+    for (size_t i = 0; i < preds.size(); ++i) {
+      fprintf(fo, "%g\n", preds[i]);
+    }
+    if (fo != stdout) fclose(fo);
   }
  private:
   /*! \brief whether silent */
   int silent;
+  /*! \brief special load */
+  int load_part;
   /*! \brief whether use auto binary buffer */
   int use_buffer;
   /*! \brief whether evaluate training statistics */            
@@ -219,6 +288,8 @@ class BoostLearnTask{
   std::string task;
   /*! \brief name of predict file */
   std::string name_pred;
+  /*! \brief data split mode */
+  std::string data_split;
   /*!\brief limit number of trees in prediction */
   int ntree_limit;
   /*!\brief whether to directly output margin value */
@@ -243,7 +314,9 @@ class BoostLearnTask{
 }
 
 int main(int argc, char *argv[]){
-  xgboost::random::Seed(0);
   xgboost::BoostLearnTask tsk;
-  return tsk.Run(argc, argv);
+  tsk.SetParam("seed", "0");
+  int ret = tsk.Run(argc, argv);
+  rabit::Finalize();
+  return ret;
 }