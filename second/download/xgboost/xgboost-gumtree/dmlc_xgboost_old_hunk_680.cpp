
        /*! \brief Error */
        struct EvalMatchError : public IEvaluator{
            virtual float Eval(const std::vector<float> &preds,
                               const DMatrix::Info &info) const {
                const unsigned ndata = static_cast<unsigned>(preds.size());
                float sum = 0.0f, wsum = 0.0f;
                #pragma omp parallel for reduction(+:sum,wsum) schedule( static )
                for (unsigned i = 0; i < ndata; ++i){
                    const float wt = info.GetWeight(i);                    
                    if (static_cast<int>(preds[i]) != static_cast<int>(info.labels[i]) ){
                        sum += wt;
                    }
                    wsum += wt;
                }
                return sum / wsum;
            }
            virtual const char *Name(void) const{
                return "merror";
            }
        };

        /*! \brief Area under curve, for both classification and rank */
        struct EvalAuc : public IEvaluator{
            virtual float Eval(const std::vector<float> &preds,
