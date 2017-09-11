@@ -31,14 +31,32 @@ class BoostLearnTask {
         this->SetParam(name, val);
       }
     }
+    // whether need data rank
+    bool need_data_rank = strchr(train_path.c_str(), '%') != NULL;
+    // if need data rank in loading, initialize rabit engine before load data
+    // otherwise, initialize rabit engine after loading data
+    // lazy initialization of rabit engine can be helpful in speculative execution
+    if (need_data_rank) rabit::Init(argc, argv);
+    this->InitData();
+    if (!need_data_rank) rabit::Init(argc, argv);
+    if (rabit::IsDistributed()) {
+      std::string pname = rabit::GetProcessorName();
+      printf("start %s:%d\n", pname.c_str(), rabit::GetRank());
+    }
     if (rabit::IsDistributed()) {
       this->SetParam("data_split", "col");
     }
     if (rabit::GetRank() != 0) {
       this->SetParam("silent", "2");
     }
-    this->InitData();
-    this->InitLearner();
+    
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
@@ -47,8 +65,6 @@ class BoostLearnTask {
     }
     if (task == "pred") {
       this->TaskPred();
-    } else {
-      this->TaskTrain();
     }
     return 0;
   }
@@ -152,10 +168,13 @@ class BoostLearnTask {
     }
   }
   inline void TaskTrain(void) {
+    int version = rabit::LoadCheckPoint(&learner);
+    if (version == 0) this->InitLearner();
+
     const time_t start = time(NULL);
     unsigned long elapsed = 0;
     learner.CheckInit(data);
-    for (int i = 0; i < num_round; ++i) {
+    for (int i = version; i < num_round; ++i) {
       elapsed = (unsigned long)(time(NULL) - start);
       if (!silent) printf("boosting round %d, %lu sec elapsed\n", i, elapsed);
       learner.UpdateOneIter(i, *data); 
@@ -166,6 +185,9 @@ class BoostLearnTask {
       if (save_period != 0 && (i + 1) % save_period == 0) {
         this->SaveModel(i);
       }
+      utils::Assert(rabit::VersionNumber() == i, "incorrect version number");
+      // checkpoint the model
+      rabit::CheckPoint(&learner);
       elapsed = (unsigned long)(time(NULL) - start);
     }
     // always save final round
@@ -263,11 +285,6 @@ class BoostLearnTask {
 }
 
 int main(int argc, char *argv[]){
-  rabit::Init(argc, argv);
-  if (rabit::IsDistributed()) {
-    std::string pname = rabit::GetProcessorName();
-    printf("start %s:%d\n", pname.c_str(), rabit::GetRank());
-  }
   xgboost::random::Seed(0);
   xgboost::BoostLearnTask tsk;
   int ret = tsk.Run(argc, argv);