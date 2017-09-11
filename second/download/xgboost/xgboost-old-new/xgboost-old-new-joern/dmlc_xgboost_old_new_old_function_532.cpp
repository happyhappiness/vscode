virtual float Eval(const std::vector<float> &preds,
                               const DMatrix::Info &info) const {
                const unsigned ndata = static_cast<unsigned>(preds.size());
                double s_tp = 0.0, b_fp = 0.0;
                #pragma omp parallel for reduction(+:s_tp,b_fp) schedule( static )
                for (unsigned i = 0; i < ndata; ++i){
                    const float wt = info.GetWeight(i);                    
                    if (preds[i] > 0.5f){
                        if( info.labels[i] > 0.5f ) s_tp += wt;
                        else b_fp += wt;
                    }
                }       
                const double br = 10.0;
                return sqrtf( 2*((s_tp+b_fp+br) * log( 1.0 + s_tp/(b_fp+br) ) - s_tp) );
            }