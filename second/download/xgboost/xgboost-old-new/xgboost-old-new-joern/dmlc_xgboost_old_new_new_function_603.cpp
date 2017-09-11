virtual float Eval( const std::vector<float> &preds, 
                                const DMatrix::Info &info ) const {
                const std::vector<unsigned> &gptr = info.group_ptr;
                utils::Assert( gptr.size()!=0 && gptr.back() == preds.size(), "EvalAuc: group structure must match number of prediction" );
                const unsigned ngroup = static_cast<unsigned>( gptr.size() - 1 );

                double sum_pre = 0.0f;
                #pragma omp parallel reduction(+:sum_pre) 
                {                   
                    // each thread takes a local rec
                    std::vector< std::pair<float,unsigned> > rec;
                    #pragma omp for schedule(static) 
                    for( unsigned k = 0; k < ngroup; ++ k ){
                        rec.clear();
                        for( unsigned j = gptr[k]; j < gptr[k+1]; ++ j ){                        
                            rec.push_back( std::make_pair( preds[j], (int)info.labels[j] ) );
                        }
                        std::sort( rec.begin(), rec.end(), CmpFirst );                    
                        // calculate Preicsion
                        unsigned nhit = 0;
                        for( size_t j = 0; j < rec.size() && j < topn_; ++ j ){
                            nhit += rec[j].second;
                        }
                        sum_pre += ((float)nhit) / topn_;
                    }
                }
                return static_cast<float>(sum_pre) / ngroup;
            }