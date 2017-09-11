
        /*! \brief AMS: also records best threshold */
        struct EvalAMS : public IEvaluator{
        public:
            EvalAMS(const char *name){
                name_ = name;
                utils::Assert( sscanf(name, "ams@%f", &ratio_ ) == 1, "invalid ams format" );
            }            
            virtual float Eval(const std::vector<float> &preds,
                               const DMatrix::Info &info) const {
                const unsigned ndata = static_cast<unsigned>(preds.size());
