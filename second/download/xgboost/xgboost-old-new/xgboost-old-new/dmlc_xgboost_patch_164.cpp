@@ -36,24 +36,20 @@ class BoostLearnTask {
       this->SetParam("silent", "1");
       save_period = 0;
     }
-    // whether need data rank
-    bool need_data_rank = strchr(train_path.c_str(), '%') != NULL;
-    // if need data rank in loading, initialize rabit engine before load data
-    // otherwise, initialize rabit engine after loading data
-    // lazy initialization of rabit engine can be helpful in speculative execution
-    if (need_data_rank) rabit::Init(argc, argv);
-    this->InitData();
-    if (!need_data_rank) rabit::Init(argc, argv);
+    // initialized the result
+    rabit::Init(argc, argv);
     if (rabit::IsDistributed()) {
       std::string pname = rabit::GetProcessorName();
       fprintf(stderr, "start %s:%d\n", pname.c_str(), rabit::GetRank());
     }
     if (rabit::IsDistributed() && data_split == "NONE") {
       this->SetParam("dsplit", "row");
-    }
+    }    
     if (rabit::GetRank() != 0) {
       this->SetParam("silent", "2");
     }    
+    this->InitData();
+
     if (task == "train") {
       // if task is training, will try recover from checkpoint
       this->TaskTrain();
@@ -135,17 +131,22 @@ class BoostLearnTask {
       train_path = s_tmp;
       load_part = 1;
     }
-
+    bool loadsplit = data_split == "row";
     if (name_fmap != "NULL") fmap.LoadText(name_fmap.c_str());
     if (task == "dump") return;
     if (task == "pred") {
-      data = io::LoadDataMatrix(test_path.c_str(), silent != 0, use_buffer != 0);
+      data = io::LoadDataMatrix(test_path.c_str(), silent != 0, use_buffer != 0, loadsplit);
     } else {
       // training
-      data = io::LoadDataMatrix(train_path.c_str(), silent != 0 && load_part == 0, use_buffer != 0);
+      data = io::LoadDataMatrix(train_path.c_str(),
+                                silent != 0 && load_part == 0,
+                                use_buffer != 0, loadsplit);
       utils::Assert(eval_data_names.size() == eval_data_paths.size(), "BUG");
       for (size_t i = 0; i < eval_data_names.size(); ++i) {
-        deval.push_back(io::LoadDataMatrix(eval_data_paths[i].c_str(), silent != 0, use_buffer != 0));
+        deval.push_back(io::LoadDataMatrix(eval_data_paths[i].c_str(),
+                                           silent != 0,
+                                           use_buffer != 0,
+                                           loadsplit));
         devalall.push_back(deval.back());
       }
             