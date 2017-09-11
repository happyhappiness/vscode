        /*! \brief Area under curve, for both classification and rank */
        struct EvalAuc : public IEvaluator{
            virtual float Eval(const std::vector<float> &preds,
                               const DMatrix::Info &info) const {
                utils::Assert( preds.size() == info.labels.size(), "label size predict size not match" );
                std::vector<unsigned> tgptr(2, 0); tgptr[1] = preds.size();
                const std::vector<unsigned> &gptr = info.group_ptr.size() == 0 ? tgptr : info.group_ptr;
                utils::Assert(gptr.back() == preds.size(), "EvalAuc: group structure must match number of prediction");
