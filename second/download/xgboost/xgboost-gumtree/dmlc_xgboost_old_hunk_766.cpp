                if (!strcmp(name, "error"))   evals_.push_back( new EvalError() );
                if (!strcmp(name, "logloss")) evals_.push_back( new EvalLogLoss() );
                if (!strcmp( name, "auc"))    evals_.push_back( new EvalAuc() );
            }
            ~EvalSet(){
                for( size_t i = 0; i < evals_.size(); ++ i ){
