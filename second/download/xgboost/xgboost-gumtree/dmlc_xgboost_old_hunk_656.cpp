            virtual float Eval(const std::vector<float> &preds,
                               const DMatrix::Info &info) const {
                const unsigned ndata = static_cast<unsigned>(preds.size());
                std::vector< std::pair<float, unsigned> > rec(ndata);
                
                #pragma omp parallel for schedule( static )                
