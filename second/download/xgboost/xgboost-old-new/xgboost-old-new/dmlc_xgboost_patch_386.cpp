@@ -103,7 +103,7 @@ namespace xgboost{
             */
             inline void InitTrainer(void){
                 if( mparam.num_class != 0 ){
-                    if( name_obj_ != "multi:softmax" ){
+                    if( name_obj_ != "multi:softmax" && name_obj_ != "multi:softprob"){
                         name_obj_ = "multi:softmax";
                         printf("auto select objective=softmax to support multi-class classification\n" );
                     }
@@ -206,7 +206,7 @@ namespace xgboost{
                 fprintf(fo, "[%d]", iter);
                 for (size_t i = 0; i < evals.size(); ++i){
                     this->PredictRaw(preds_, *evals[i]);
-                    obj_->PredTransform(preds_);
+                    obj_->EvalTransform(preds_);
                     evaluator_.Eval(fo, evname[i].c_str(), preds_, evals[i]->info);
                 }
                 fprintf(fo, "\n");