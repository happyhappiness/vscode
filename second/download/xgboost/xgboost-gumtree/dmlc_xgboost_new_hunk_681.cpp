                }
                if (!strcmp(name, "rmse"))    evals_.push_back(new EvalRMSE());
                if (!strcmp(name, "error"))   evals_.push_back(new EvalError());
                if (!strcmp(name, "merror"))   evals_.push_back(new EvalMatchError("merror"));
                if (!strcmp(name, "mabserror"))   evals_.push_back(new EvalMatchError("mabserror"));
                if (!strcmp(name, "logloss")) evals_.push_back(new EvalLogLoss());
                if (!strcmp(name, "auc"))    evals_.push_back(new EvalAuc());
                if (!strncmp(name, "pre@", 4)) evals_.push_back(new EvalPrecision(name));
