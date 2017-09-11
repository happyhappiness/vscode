@@ -48,7 +48,7 @@ class BoostLearnTask {
       std::string pname = rabit::GetProcessorName();
       fprintf(stderr, "start %s:%d\n", pname.c_str(), rabit::GetRank());
     }
-    if (rabit::IsDistributed()) {
+    if (rabit::IsDistributed() && data_split == "NONE") {
       this->SetParam("dsplit", "row");
     }
     if (rabit::GetRank() != 0) {
@@ -89,6 +89,7 @@ class BoostLearnTask {
     if (!strcmp("fmap", name)) name_fmap = val;
     if (!strcmp("name_dump", name)) name_dump = val;
     if (!strcmp("name_pred", name)) name_pred = val;
+    if (!strcmp("dsplit", name)) data_split = val;
     if (!strcmp("dump_stats", name)) dump_model_stats = atoi(val);
     if (!strncmp("eval[", name, 5)) {
       char evname[256];
@@ -116,6 +117,7 @@ class BoostLearnTask {
     name_pred = "pred.txt";
     name_dump = "dump.txt";
     model_dir_path = "./";
+    data_split = "NONE";
     load_part = 0;
     data = NULL;
   }
@@ -172,14 +174,24 @@ class BoostLearnTask {
   inline void TaskTrain(void) {
     int version = rabit::LoadCheckPoint(&learner);
     if (version == 0) this->InitLearner();
-
     const time_t start = time(NULL);
     unsigned long elapsed = 0;
     learner.CheckInit(data);
-    for (int i = version; i < num_round; ++i) {
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
       if (rabit::IsDistributed()){
         if (rabit::GetRank() == 0) {
@@ -193,9 +205,13 @@ class BoostLearnTask {
       if (save_period != 0 && (i + 1) % save_period == 0) {
         this->SaveModel(i);
       }
-      utils::Assert(rabit::VersionNumber() == i, "incorrect version number");
-      // checkpoint the model
-      rabit::CheckPoint(&learner);
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
@@ -272,6 +288,8 @@ class BoostLearnTask {
   std::string task;
   /*! \brief name of predict file */
   std::string name_pred;
+  /*! \brief data split mode */
+  std::string data_split;
   /*!\brief limit number of trees in prediction */
   int ntree_limit;
   /*!\brief whether to directly output margin value */