virtual float Eval(const std::vector<float> &preds,
                               const DMatrix::Info &info) const {
                const unsigned ndata = static_cast<unsigned>(preds.size());
                std::vector< std::pair<float, unsigned> > rec(ndata);
                
                #pragma omp parallel for schedule( static )                
                for (unsigned i = 0; i < ndata; ++i){
                    rec[i] = std::make_pair( preds[i], i );
                }
                std::sort( rec.begin(), rec.end(), CmpFirst );

                const double br = 10.0;
                double s_tp = 0.0, b_fp = 0.0, tams = 0.0, threshold = 0.0;
                for (unsigned i = 0; i < ndata-1; ++i){
                    const unsigned ridx = rec[i].second;
                    const float wt = info.weights[ridx];
                    if( info.labels[ridx] > 0.5f ){
                        s_tp += wt;
                    }else{
                        b_fp += wt;
                    }
                    if( rec[i].first != rec[i+1].first ){
                        double ams = sqrtf( 2*((s_tp+b_fp+br) * log( 1.0 + s_tp/(b_fp+br) ) - s_tp) );
                        if( tams < ams ){
                            threshold = (rec[i].first + rec[i+1].first) / 2.0;
                            tams = ams;
                        }
                    }
                }
                fprintf( stderr, "\tams-thres=%g", threshold );
                return tams;
            }