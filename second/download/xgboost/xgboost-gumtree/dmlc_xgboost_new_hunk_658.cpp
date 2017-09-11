            float ratio_;
        };

        /*! \brief Error for multi-class classification, need exact match */
        struct EvalMatchError : public IEvaluator{
        public:
            virtual float Eval(const std::vector<float> &preds,
                               const DMatrix::Info &info) const {
                const unsigned ndata = static_cast<unsigned>(preds.size());
