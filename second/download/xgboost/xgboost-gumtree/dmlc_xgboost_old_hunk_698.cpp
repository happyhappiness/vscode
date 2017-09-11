            virtual ~IEvaluator(void){}
        };

        inline static bool CmpFirst(const std::pair<float, unsigned> &a, const std::pair<float, unsigned> &b){
            return a.first > b.first;
        }
        inline static bool CmpSecond(const std::pair<float, unsigned> &a, const std::pair<float, unsigned> &b){
            return a.second > b.second;
        }

        /*! \brief RMSE */
        struct EvalRMSE : public IEvaluator{
            virtual float Eval(const std::vector<float> &preds,
                               const DMatrix::Info &info) const {
                const unsigned ndata = static_cast<unsigned>(preds.size());
                float sum = 0.0, wsum = 0.0;
                #pragma omp parallel for reduction(+:sum,wsum) schedule( static )
