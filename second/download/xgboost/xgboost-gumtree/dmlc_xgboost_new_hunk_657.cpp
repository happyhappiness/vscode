        public:
            EvalAMS(const char *name){
                name_ = name;
                // note: ams@0 will automatically select which ratio to go
                utils::Assert( sscanf(name, "ams@%f", &ratio_ ) == 1, "invalid ams format" );
            }            
            virtual float Eval(const std::vector<float> &preds,
