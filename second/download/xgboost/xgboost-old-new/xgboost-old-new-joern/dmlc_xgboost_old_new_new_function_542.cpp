inline void AddEval(const char *name){
                for (size_t i = 0; i < evals_.size(); ++i){
                    if (!strcmp(name, evals_[i]->Name())) return;
                }
                if (!strcmp(name, "rmse"))    evals_.push_back(new EvalRMSE());
                if (!strcmp(name, "error"))   evals_.push_back(new EvalError());
                if (!strcmp(name, "merror"))   evals_.push_back(new EvalMatchError());
                if (!strcmp(name, "logloss")) evals_.push_back(new EvalLogLoss());
                if (!strcmp(name, "auc"))    evals_.push_back(new EvalAuc());
                if (!strncmp(name, "pre@", 4)) evals_.push_back(new EvalPrecision(name));
                if (!strncmp(name, "map", 3))   evals_.push_back(new EvalMAP(name));
                if (!strncmp(name, "ndcg", 3))  evals_.push_back(new EvalNDCG(name));
            }