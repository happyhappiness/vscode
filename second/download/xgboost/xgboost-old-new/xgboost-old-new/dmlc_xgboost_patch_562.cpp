@@ -1,13 +1,13 @@
 #ifndef _XGBOOST_REG_TRAIN_H_
 #define _XGBOOST_REG_TRAIN_H_
 
-#include<iostream>
-#include<string>
-#include<fstream>
-#include"../utils/xgboost_config.h"
-#include"xgboost_reg.h"
-#include"xgboost_regdata.h"
-#include"../utils/xgboost_string.h"
+#include <iostream>
+#include <string>
+#include <fstream>
+#include "../utils/xgboost_config.h"
+#include "xgboost_reg.h"
+#include "xgboost_regdata.h"
+#include "../utils/xgboost_string.h"
 
 using namespace xgboost::utils;
 
@@ -28,7 +28,8 @@ namespace xgboost{
             * \param silent whether to print feedback messages
             */
             void train(char* config_path,bool silent = false){
-                reg_boost_learner = new xgboost::regression::RegBoostLearner(silent);
+                reg_boost_learner = new xgboost::regression::RegBoostLearner();
+                
                 ConfigIterator config_itr(config_path);
                 //Get the training data and validation data paths, config the Learner
                 while (config_itr.Next()){
@@ -38,14 +39,14 @@ namespace xgboost{
                 }
 
                 Assert(train_param.validation_data_paths.size() == train_param.validation_data_names.size(),
-                    "The number of validation paths is not the same as the number of validation data set names");
+                       "The number of validation paths is not the same as the number of validation data set names");
 
                 //Load Data
                 xgboost::regression::DMatrix train;
                 printf("%s",train_param.train_path);
                 train.LoadText(train_param.train_path);
                 std::vector<const xgboost::regression::DMatrix*> evals;
-                for(int i = 0; i < train_param.validation_data_paths.size(); i++){
+                for(size_t i = 0; i < train_param.validation_data_paths.size(); i++){
                     xgboost::regression::DMatrix eval;
                     eval.LoadText(train_param.validation_data_paths[i].c_str());
                     evals.push_back(&eval);
@@ -58,7 +59,7 @@ namespace xgboost{
                 for(int i = 1; i <= train_param.boost_iterations; i++){
                     reg_boost_learner->UpdateOneIter(i);
                     if(train_param.save_period != 0 && i % train_param.save_period == 0){
-                        sscanf(suffix,"%d.model",i);
+                        sprintf(suffix,"%d.model",i);
                         SaveModel(suffix);
                     }
                 }