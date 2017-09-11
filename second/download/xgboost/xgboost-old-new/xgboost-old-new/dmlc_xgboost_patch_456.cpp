@@ -62,6 +62,7 @@ namespace xgboost{
                 if (!strcmp("seed", name))         random::Seed(atoi(val));
                 if (!strcmp("num_round", name))    num_round = atoi(val);
                 if (!strcmp("save_period", name))  save_period = atoi(val);
+                if (!strcmp("eval_train", name))   eval_train = atoi(val);
                 if (!strcmp("task", name))         task = val;
                 if (!strcmp("data", name))        train_path = val;
                 if (!strcmp("test:data", name))   test_path = val;
@@ -92,6 +93,7 @@ namespace xgboost{
                 use_buffer = 1;
                 num_round = 10;
                 save_period = 0;
+                eval_train = 0;
                 dump_model_stats = 0;
                 task = "train";
                 model_in = "NULL";
@@ -122,9 +124,22 @@ namespace xgboost{
                     for (size_t i = 0; i < eval_data_names.size(); ++i){
                         deval.push_back(new DMatrix());
                         deval.back()->CacheLoad(eval_data_paths[i].c_str(), silent != 0, use_buffer != 0);
+                        devalall.push_back(deval.back());
                     }
+                    std::vector<const DMatrix *> dcache(1, &data);
+                    for( size_t i = 0; i < deval.size(); ++ i){
+                        dcache.push_back( deval[i] );
+                    }
+                    // set cache data to be all training and evaluation data
+                    learner.SetCacheData(dcache);
+
+                    // add training set to evaluation set if needed
+                    if( eval_train != 0 ){
+                        devalall.push_back( &data );
+                        eval_data_names.push_back( std::string("train") );
+                    }
+
                 }
-                learner.SetData(&data, deval, eval_data_names);
             }
             inline void InitLearner(void){
                 cfg.BeforeFirst();
@@ -148,8 +163,8 @@ namespace xgboost{
                 for (int i = 0; i < num_round; ++i){
                     elapsed = (unsigned long)(time(NULL) - start);
                     if (!silent) printf("boosting round %d, %lu sec elapsed\n", i, elapsed);
-                    learner.UpdateOneIter(i);
-                    learner.EvalOneIter(i);
+                    learner.UpdateOneIter(i, data);                    
+                    learner.EvalOneIter(i, devalall, eval_data_names);
                     if (save_period != 0 && (i + 1) % save_period == 0){
                         this->SaveModel(i);
                     }
@@ -169,7 +184,7 @@ namespace xgboost{
                 }
             }
             inline void TaskEval(void){
-                learner.EvalOneIter(0);
+                learner.EvalOneIter(0, devalall, eval_data_names);
             }
             inline void TaskInteractive(void){
                 const time_t start = time(NULL);
@@ -179,7 +194,7 @@ namespace xgboost{
                 cfg_batch.BeforeFirst();
                 while (cfg_batch.Next()){
                     if (!strcmp(cfg_batch.name(), "run")){
-                        learner.UpdateInteract(interact_action);
+                        learner.UpdateInteract(interact_action, data);
                         batch_action += 1;
                     }
                     else{
@@ -188,7 +203,7 @@ namespace xgboost{
                 }
 
                 if (batch_action == 0){
-                    learner.UpdateInteract(interact_action);
+                    learner.UpdateInteract(interact_action, data);
                 }
                 utils::Assert(model_out != "NULL", "interactive mode must specify model_out");
                 this->SaveModel(model_out.c_str());
@@ -235,6 +250,8 @@ namespace xgboost{
             int silent;
             /* \brief whether use auto binary buffer */
             int use_buffer;
+            /* \brief whether evaluate training statistics */            
+            int eval_train;
             /* \brief number of boosting iterations */
             int num_round;
             /* \brief the period to save the model, 0 means only save the final round model */
@@ -272,6 +289,7 @@ namespace xgboost{
         private:
             DMatrix data;
             std::vector<DMatrix*> deval;
+            std::vector<const DMatrix*> devalall;
             utils::FeatMap fmap;
             RegRankBoostLearner learner;
         };