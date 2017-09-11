virtual float Eval(const std::vector<float> &preds,
                               const DMatrix::Info &info) const {
                const unsigned ndata = static_cast<unsigned>(preds.size());
                utils::Assert( info.weights.size() == ndata, "we need weight to evaluate ams");
                std::vector< std::pair<float, unsigned> > rec(ndata);
                
                #pragma omp parallel for schedule( static )                
                for (unsigned i = 0; i < ndata; ++i){
                    rec[i] = std::make_pair( preds[i], i );
                }
                std::sort( rec.begin(), rec.end(), CmpFirst );
                unsigned ntop = static_cast<unsigned>( ratio_ * ndata );
                if( ntop == 0 ) ntop = ndata;
                const double br = 10.0;
                unsigned thresindex = 0;
                double s_tp = 0.0, b_fp = 0.0, tams = 0.0;
                for (unsigned i = 0; i < ndata-1 && i < ntop; ++i){
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
                            thresindex = i;
                            tams = ams;
                        }
                    }
                }
                if( ntop == ndata ){
                    fprintf( stderr, "\tams-ratio=%g", float(thresindex)/ndata );
                    return tams;
                }else{
                    return sqrtf( 2*((s_tp+b_fp+br) * log( 1.0 + s_tp/(b_fp+br) ) - s_tp) );
                }
            }