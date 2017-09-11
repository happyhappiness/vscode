            }
        };

        /*! \brief Evaluate rank list */          
        struct EvalRankList : public IEvaluator{
        public:
            virtual float Eval(const std::vector<float> &preds,
                               const DMatrix::Info &info) const {
                const std::vector<unsigned> &gptr = info.group_ptr;
                utils::Assert(gptr.size() != 0 && gptr.back() == preds.size(), "EvalAuc: group structure must match number of prediction");
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
            virtual const char *Name(void) const{
                return name_.c_str();
            }
        protected:
            EvalRankList(const char *name){
                name_ = name;
                if( sscanf(name, "%*[^@]@%u", &topn_) != 1 ){
                    topn_ = UINT_MAX;
                }
            }
            /*! \return evaluation metric, given the pair_sort record, (pred,label) */
            virtual float EvalMetric( std::vector< std::pair<float, unsigned> > &pair_sort ) const = 0;
        protected:
            unsigned topn_;
            std::string name_;
        };
        
        /*! \brief Precison at N, for both classification and rank */
        struct EvalPrecision : public EvalRankList{
        public:
            EvalPrecision(const char *name):EvalRankList(name){}
        protected:
            virtual float EvalMetric( std::vector< std::pair<float, unsigned> > &rec ) const {
                // calculate Preicsion
                std::sort(rec.begin(), rec.end(), CmpFirst);
                unsigned nhit = 0;
                for (size_t j = 0; j < rec.size() && j < this->topn_; ++j){
                    nhit += (rec[j].second != 0 );
                }
                return static_cast<float>( nhit ) / topn_;
            }
        };


        /*! \brief NDCG */
        struct EvalNDCG : public EvalRankList{
        public:
            EvalNDCG(const char *name):EvalRankList(name){}
        protected:
            inline float CalcDCG( const std::vector< std::pair<float,unsigned> > &rec ) const {
                double sumdcg = 0.0;
                for( size_t i = 0; i < rec.size() && i < this->topn_; i ++ ){
                    const unsigned rel = rec[i].second;
                    if( rel != 0 ){ 
                        sumdcg += logf( 2.0f ) *((1<<rel)-1) / logf( i + 1 );
                    }
                }
                return static_cast<float>(sumdcg);
            }
            virtual float EvalMetric( std::vector< std::pair<float, unsigned> > &rec ) const {
                std::sort(rec.begin(), rec.end(), CmpFirst);
                float idcg = this->CalcDCG(rec);
                std::sort(rec.begin(), rec.end(), CmpSecond);
                float dcg = this->CalcDCG(rec);
                if( idcg == 0.0f ) return 0.0f;
                else return dcg/idcg;
            }
        };

        /*! \brief Precison at N, for both classification and rank */
        struct EvalMAP : public EvalRankList{
        public:
            EvalMAP(const char *name):EvalRankList(name){}
        protected:
            virtual float EvalMetric( std::vector< std::pair<float, unsigned> > &rec ) const {
                std::sort(rec.begin(), rec.end(), CmpFirst);
                unsigned nhits = 0;
                double sumap = 0.0;
                for( size_t i = 0; i < rec.size(); ++i){
                    if( rec[i].second != 0 ){
                        nhits += 1;
                        if( i < this->topn_ ){
                            sumap += static_cast<float>(nhits) / (i+1);
                        }
                    }
                }
                if (nhits != 0) sumap /= nhits;
                return static_cast<float>(sumap);                
            }
        };
    };
