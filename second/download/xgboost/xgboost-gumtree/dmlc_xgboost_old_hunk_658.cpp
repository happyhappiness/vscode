            float ratio_;
        };

        /*! \brief Error */
        struct EvalMatchError : public IEvaluator{
        public:
            EvalMatchError(const char *name){
                name_ = name;
                abs_ = 0;
                if(!strcmp("mabserror", name)) abs_ =1;
            }            
            virtual float Eval(const std::vector<float> &preds,
                               const DMatrix::Info &info) const {
                const unsigned ndata = static_cast<unsigned>(preds.size());
