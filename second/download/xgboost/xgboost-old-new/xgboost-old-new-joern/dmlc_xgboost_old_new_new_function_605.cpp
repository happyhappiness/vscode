virtual float Eval( const std::vector<float> &preds, 
                                const DMatrix::Info &info ) const {
                std::vector<unsigned> tgptr(2,0); tgptr[1] = preds.size();
                const std::vector<unsigned> &gptr = info.group_ptr.size() == 0 ? tgptr : info.group_ptr;
                utils::Assert( gptr.back() == preds.size(), "EvalAuc: group structure must match number of prediction" );
                const unsigned ngroup = static_cast<unsigned>( gptr.size() );
            
                double sum_auc = 0.0f;
                #pragma omp parallel reduction(+:sum_auc) 
                {                   
                    // each thread takes a local rec
                    std::vector< std::pair<float,unsigned> > rec;
                    #pragma omp for schedule(static) 
                    for( unsigned k = 0; k < ngroup; ++ k ){
                        rec.clear();
                        for( unsigned j = gptr[k]; j < gptr[k+1]; ++ j ){                        
                            rec.push_back( std::make_pair( preds[j], j ) );
                        }
                        std::sort( rec.begin(), rec.end(), CmpFirst );                    
                        // calculate AUC
                        double sum_pospair = 0.0;
                        double sum_npos = 0.0, sum_nneg = 0.0, buf_pos = 0.0, buf_neg = 0.0;
                        for( size_t j = 0; j < rec.size(); ++ j ){
                            const float wt  = info.GetWeight( rec[j].second );
                            const float ctr = info.labels[ rec[j].second ];
                            // keep bucketing predictions in same bucket
                            if( j != 0 && rec[j].first != rec[j-1].first ){
                                sum_pospair += buf_neg * (sum_npos + buf_pos *0.5);
                                sum_npos += buf_pos; sum_nneg += buf_neg;
                                buf_neg = buf_pos = 0.0f;
                            }
                            buf_pos += ctr * wt; buf_neg += (1.0f-ctr) * wt;
                        }
                        sum_pospair += buf_neg * (sum_npos + buf_pos *0.5);                    
                        sum_npos += buf_pos; sum_nneg += buf_neg;
                        // 
                        utils::Assert( sum_npos > 0.0 && sum_nneg > 0.0, "the dataset only contains pos or neg samples" );
                        // this is the AUC
                        sum_auc += sum_pospair / (sum_npos*sum_nneg);
                    }
                }
                // return average AUC over list
                return static_cast<float>(sum_auc) / ngroup;
            }