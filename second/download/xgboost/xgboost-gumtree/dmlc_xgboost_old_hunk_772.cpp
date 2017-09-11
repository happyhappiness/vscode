            }
        };


        /*! \brief Error */
        struct EvalLogLoss : public IEvaluator{
            virtual float Eval(const std::vector<float> &preds,
            const std::vector<float> &labels) const{
                const unsigned ndata = static_cast<unsigned>(preds.size());
                unsigned nerr = 0;
#pragma omp parallel for reduction(+:nerr) schedule( static )
                for (unsigned i = 0; i < ndata; ++i){
                    const float y = labels[i];
                    const float py = preds[i];
