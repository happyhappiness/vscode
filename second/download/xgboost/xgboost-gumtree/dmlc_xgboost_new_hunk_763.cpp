        struct EvalSet{
        public:
            inline void AddEval(const char *name){
                for (size_t i = 0; i < evals_.size(); ++i){
                    if (!strcmp(name, evals_[i]->Name())) return;
                }
                if (!strcmp(name, "rmse"))    evals_.push_back(new EvalRMSE());
                if (!strcmp(name, "error"))   evals_.push_back(new EvalError());
                if (!strcmp(name, "logloss")) evals_.push_back(new EvalLogLoss());
                if (!strcmp(name, "auc"))    evals_.push_back(new EvalAuc());
                if (!strncmp(name, "pre@", 4)) evals_.push_back(new EvalPrecision(name));
            }
            ~EvalSet(){
                for (size_t i = 0; i < evals_.size(); ++i){
                    delete evals_[i];
                }
            }
            inline void Eval(FILE *fo, const char *evname,
                const std::vector<float> &preds,
                const DMatrix::Info &info) const{
                for (size_t i = 0; i < evals_.size(); ++i){
                    float res = evals_[i]->Eval(preds, info);
                    fprintf(fo, "\t%s-%s:%f", evname, evals_[i]->Name(), res);
