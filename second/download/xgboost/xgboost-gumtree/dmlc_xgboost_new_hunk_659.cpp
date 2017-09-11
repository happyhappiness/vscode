                }
                if (!strcmp(name, "rmse"))    evals_.push_back(new EvalRMSE());
                if (!strcmp(name, "error"))   evals_.push_back(new EvalError());
                if (!strcmp(name, "merror"))   evals_.push_back(new EvalMatchError());
                if (!strcmp(name, "logloss")) evals_.push_back(new EvalLogLoss());
                if (!strcmp(name, "auc"))    evals_.push_back(new EvalAuc());
                if (!strncmp(name, "ams@",4))  evals_.push_back(new EvalAMS(name));
