@@ -14,7 +14,7 @@ namespace xgboost {
 /*!
  * \brief wrapping the training process 
  */
-class BoostLearnTask{
+class BoostLearnTask {
  public:
   inline int Run(int argc, char *argv[]) {
     if (argc < 2) {
@@ -31,6 +31,9 @@ class BoostLearnTask{
         this->SetParam(name, val);
       }
     }
+    if (sync::IsDistributed()) {
+      this->SetParam("updater", "distcol");
+    }
     if (sync::GetRank() != 0) {
       this->SetParam("silent", "2");
     }
@@ -93,6 +96,7 @@ class BoostLearnTask{
     name_pred = "pred.txt";
     name_dump = "dump.txt";
     model_dir_path = "./";
+    load_part = 0;
     data = NULL;
   }
   ~BoostLearnTask(void){
@@ -103,13 +107,20 @@ class BoostLearnTask{
   }
  private:
   inline void InitData(void) {
+    if (strchr(train_path.c_str(), '%') != NULL) {
+      char s_tmp[256];
+      utils::SPrintf(s_tmp, sizeof(s_tmp), train_path.c_str(), sync::GetRank());
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
@@ -182,6 +193,7 @@ class BoostLearnTask{
     fclose(fo);
   }
   inline void SaveModel(const char *fname) const {
+    if (sync::GetRank() != 0) return;
     utils::FileStream fo(utils::FopenCheck(fname, "wb"));
     learner.SaveModel(fo);
     fo.Close();
@@ -205,6 +217,8 @@ class BoostLearnTask{
  private:
   /*! \brief whether silent */
   int silent;
+  /*! \brief special load */
+  int load_part;
   /*! \brief whether use auto binary buffer */
   int use_buffer;
   /*! \brief whether evaluate training statistics */            