        public:
            EvalAMS(const char *name){
                name_ = name;
                utils::Assert( sscanf(name, "ams@%f", &ratio_ ) == 1, "invalid ams format" );
            }            
            virtual float Eval(const std::vector<float> &preds,
