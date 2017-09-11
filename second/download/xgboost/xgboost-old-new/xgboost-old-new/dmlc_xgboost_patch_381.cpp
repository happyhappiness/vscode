@@ -48,7 +48,6 @@ class BoostLearnTask{
   inline void SetParam(const char *name, const char *val) {
     if (!strcmp("silent", name)) silent = atoi(val);
     if (!strcmp("use_buffer", name)) use_buffer = atoi(val);
-    if (!strcmp("seed", name)) random::Seed(atoi(val));
     if (!strcmp("num_round", name)) num_round = atoi(val);
     if (!strcmp("save_period", name)) save_period = atoi(val);
     if (!strcmp("eval_train", name)) eval_train = atoi(val);
@@ -103,9 +102,6 @@ class BoostLearnTask{
     } else {
       // training
       data = io::LoadDataMatrix(train_path.c_str(), silent != 0, use_buffer != 0);
-      {// intialize column access
-        data->fmat.InitColAccess();
-      }
       utils::Assert(eval_data_names.size() == eval_data_paths.size(), "BUG");
       for (size_t i = 0; i < eval_data_names.size(); ++i) {
         deval.push_back(io::LoadDataMatrix(eval_data_paths[i].c_str(), silent != 0, use_buffer != 0));
@@ -139,10 +135,11 @@ class BoostLearnTask{
   inline void TaskTrain(void) {
     const time_t start = time(NULL);
     unsigned long elapsed = 0;
+    learner.CheckInit(data);
     for (int i = 0; i < num_round; ++i) {
       elapsed = (unsigned long)(time(NULL) - start);
       if (!silent) printf("boosting round %d, %lu sec elapsed\n", i, elapsed);
-      learner.UpdateOneIter(i,data); 
+      learner.UpdateOneIter(i, *data); 
       std::string res = learner.EvalOneIter(i, devalall, eval_data_names);
       fprintf(stderr, "%s\n", res.c_str());
       if (save_period != 0 && (i + 1) % save_period == 0) {