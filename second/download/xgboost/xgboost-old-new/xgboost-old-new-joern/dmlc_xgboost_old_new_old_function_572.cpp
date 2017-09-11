virtual float Eval(const std::vector<float> &preds,
                               const DMatrix::Info &info) const {
                const std::vector<unsigned> &gptr = info.group_ptr;
                utils::Assert(gptr.size() != 0, "must specify group when constructing rank file");
                utils::Assert( gptr.back() == preds.size(), "EvalRanklist: group structure must match number of prediction");
                const unsigned ngroup = static_cast<unsigned>(gptr.size() - 1);

                double sum_metric = 0.0f;
                #pragma omp parallel reduction(+:sum_metric) 
                {
                    // each thread takes a local rec
                    std::vector< std::pair<float, unsigned> > rec;
                    #pragma omp for schedule(static) 
                    for (unsigned k = 0; k < ngroup; ++k){
                        rec.clear();
                        for (unsigned j = gptr[k]; j < gptr[k + 1]; ++j){
                            rec.push_back(std::make_pair(preds[j], (int)info.labels[j]));
                        }
                        sum_metric += this->EvalMetric( rec );                        
                    }
                }
                return static_cast<float>(sum_metric) / ngroup;
            }