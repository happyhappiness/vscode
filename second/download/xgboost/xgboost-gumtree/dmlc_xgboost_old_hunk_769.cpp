            }
        };

        /*! \brief Area under curve */
        struct EvalAuc : public IEvaluator{         
            inline static bool CmpFirst( const std::pair<float,float> &a, const std::pair<float,float> &b ){
                return a.first > b.first;
            }
            virtual float Eval( const std::vector<float> &preds, 
                                const DMatrix::Info &info ) const {
                const std::vector<float> &labels  = info.labels;
                const unsigned ndata = static_cast<unsigned>( preds.size() );
                std::vector< std::pair<float, float> > rec;
                for( unsigned i = 0; i < ndata; ++ i ){
                    rec.push_back( std::make_pair( preds[i], labels[i]) );
                }
                random::Shuffle( rec );
                std::sort( rec.begin(), rec.end(), CmpFirst );

                long npos = 0, nhit = 0;
                for( unsigned i = 0; i < ndata; ++ i ){
                    if( rec[i].second > 0.5f ) {
                        ++ npos; 
                    }else{
                        // this is the number of correct pairs
                        nhit += npos;
                    }
                } 
                long nneg = ndata - npos;
                utils::Assert( nneg > 0, "the dataset only contains pos samples" );
                return static_cast<float>(nhit) / nneg / npos;
            }
            virtual const char *Name( void ) const{
                return "auc";
