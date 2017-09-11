inline void EvalOneIter(int iter, FILE *fo = stderr){
                fprintf(fo, "[%d]", iter);
                int buffer_offset = static_cast<int>(train_->Size());

                for (size_t i = 0; i < evals_.size(); ++i){
                    std::vector<float> &preds = this->eval_preds_[i];
                    this->PredictBuffer(preds, *evals_[i], buffer_offset);
                    obj_->PredTransform(preds);
                    evaluator_.Eval(fo, evname_[i].c_str(), preds, evals_[i]->info);
                    buffer_offset += static_cast<int>(evals_[i]->Size());
                }
                fprintf(fo, "\n");
                fflush(fo);
            }