
        /*! \brief AMS: also records best threshold */
        struct EvalAMS : public IEvaluator{
            virtual float Eval(const std::vector<float> &preds,
                               const DMatrix::Info &info) const {
                const unsigned ndata = static_cast<unsigned>(preds.size());
