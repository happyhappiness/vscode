@@ -87,6 +87,7 @@ class BoostLearnTask {
     if (!strcmp("name_pred", name)) name_pred = val;
     if (!strcmp("dsplit", name)) data_split = val;
     if (!strcmp("dump_stats", name)) dump_model_stats = atoi(val);
+    if (!strcmp("save_pbuffer", name)) save_with_pbuffer = atoi(val);
     if (!strncmp("eval[", name, 5)) {
       char evname[256];
       utils::Assert(sscanf(name, "eval[%[^]]", evname) == 1, "must specify evaluation name for display");
@@ -115,6 +116,7 @@ class BoostLearnTask {
     model_dir_path = "./";
     data_split = "NONE";
     load_part = 0;
+    save_with_pbuffer = 0;
     data = NULL;
   }
   ~BoostLearnTask(void){
@@ -241,7 +243,7 @@ class BoostLearnTask {
   }
   inline void SaveModel(const char *fname) const {
     if (rabit::GetRank() != 0) return;
-    learner.SaveModel(fname);
+    learner.SaveModel(fname, save_with_pbuffer != 0);
   }
   inline void SaveModel(int i) const {
     char fname[256];
@@ -297,6 +299,8 @@ class BoostLearnTask {
   int pred_margin;
   /*! \brief whether dump statistics along with model */
   int dump_model_stats;
+  /*! \brief whether save prediction buffer */
+  int save_with_pbuffer;
   /*! \brief name of feature map */
   std::string name_fmap;
   /*! \brief name of dump file */