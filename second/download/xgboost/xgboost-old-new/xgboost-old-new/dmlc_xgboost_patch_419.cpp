@@ -200,11 +200,6 @@ namespace xgboost{
                 fprintf(fo, "[%d]", iter);
                 for (size_t i = 0; i < evals.size(); ++i){
                     this->PredictRaw(preds_, *evals[i]);
-                    for( size_t j = 0 ; j < preds_.size(); ++ j){
-                        if( fabsf(preds_[j]- 0.5f)>1e-6f){
-                            printf("p[%lu]=%f\n", j,preds_[j]);
-                        }
-                    }
                     obj_->PredTransform(preds_);
                     evaluator_.Eval(fo, evname[i].c_str(), preds_, evals[i]->info);
                 }
@@ -288,10 +283,7 @@ namespace xgboost{
                     #pragma omp parallel for schedule( static )
                     for (unsigned j = 0; j < ndata; ++j){
                         preds[j] = mparam.base_score + base_gbm.Predict(data.data, j, buffer_offset + j, data.info.GetRoot(j), bst_group );
-                        if( preds[j] != 0.5f ){
-                            printf("pred[%d:%u]=%f\n", bst_group, j, preds[j]);
-                        }
-                        utils::Assert( preds[j] == 0.5f, "BUG");
+
                     }
                 }else
                     #pragma omp parallel for schedule( static )