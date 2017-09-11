                if (!strcmp(name, "rmse")) evals_.push_back(&rmse_);
                if (!strcmp(name, "error")) evals_.push_back(&error_);
                if (!strcmp(name, "logloss")) evals_.push_back(&logloss_);
            }
            inline void Init(void){
                std::sort(evals_.begin(), evals_.end());
                evals_.resize(std::unique(evals_.begin(), evals_.end()) - evals_.begin());
            }
            inline void Eval(FILE *fo, const char *evname,
                const std::vector<float> &preds,
                const std::vector<float> &labels) const{
                for (size_t i = 0; i < evals_.size(); ++i){
                    float res = evals_[i]->Eval(preds, labels);
                    fprintf(fo, "\t%s-%s:%f", evname, evals_[i]->Name(), res);
