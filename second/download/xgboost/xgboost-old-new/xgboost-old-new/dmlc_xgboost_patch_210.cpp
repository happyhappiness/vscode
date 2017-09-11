@@ -31,6 +31,11 @@ class BoostLearnTask {
         this->SetParam(name, val);
       }
     }
+    // do not save anything when save to stdout
+    if (model_out == "stdout") {
+      this->SetParam("silent", "1");
+      save_period = 0;
+    }
     // whether need data rank
     bool need_data_rank = strchr(train_path.c_str(), '%') != NULL;
     // if need data rank in loading, initialize rabit engine before load data
@@ -41,7 +46,7 @@ class BoostLearnTask {
     if (!need_data_rank) rabit::Init(argc, argv);
     if (rabit::IsDistributed()) {
       std::string pname = rabit::GetProcessorName();
-      printf("start %s:%d\n", pname.c_str(), rabit::GetRank());
+      fprintf(stderr, "start %s:%d\n", pname.c_str(), rabit::GetRank());
     }
     if (rabit::IsDistributed()) {
       this->SetParam("data_split", "col");
@@ -158,9 +163,7 @@ class BoostLearnTask {
   }
   inline void InitLearner(void) {
     if (model_in != "NULL") {
-      utils::FileStream fi(utils::FopenCheck(model_in.c_str(), "rb"));
-      learner.LoadModel(fi);
-      fi.Close();
+      learner.LoadModel(model_in.c_str());
     } else {
       utils::Assert(task == "train", "model_in not specified");
       learner.InitModel();
@@ -215,9 +218,7 @@ class BoostLearnTask {
   }
   inline void SaveModel(const char *fname) const {
     if (rabit::GetRank() != 0) return;
-    utils::FileStream fo(utils::FopenCheck(fname, "wb"));
-    learner.SaveModel(fo);
-    fo.Close();
+    learner.SaveModel(fname);
   }
   inline void SaveModel(int i) const {
     char fname[256];