            }
        };

        /*! \brief Precison at N, for both classification and rank */
        struct EvalPrecision : public IEvaluator{
            unsigned topn_;
            std::string name_;
            EvalPrecision(const char *name){
                name_ = name;
                utils::Assert(sscanf(name, "pre@%u", &topn_));
            }
            virtual float Eval(const std::vector<float> &preds,
                const DMatrix::Info &info) const {
                const std::vector<unsigned> &gptr = info.group_ptr;
                utils::Assert(gptr.size() != 0 && gptr.back() == preds.size(), "EvalAuc: group structure must match number of prediction");
                const unsigned ngroup = static_cast<unsigned>(gptr.size() - 1);

                double sum_pre = 0.0f;
#pragma omp parallel reduction(+:sum_pre) 
                {
                    // each thread takes a local rec
                    std::vector< std::pair<float, unsigned> > rec;
#pragma omp for schedule(static) 
                    for (unsigned k = 0; k < ngroup; ++k){
                        rec.clear();
                        for (unsigned j = gptr[k]; j < gptr[k + 1]; ++j){
                            rec.push_back(std::make_pair(preds[j], (int)info.labels[j]));
                        }
                        std::sort(rec.begin(), rec.end(), CmpFirst);
                        // calculate Preicsion
                        unsigned nhit = 0;
                        for (size_t j = 0; j < rec.size() && j < topn_; ++j){
                            nhit += rec[j].second;
                        }
                        sum_pre += ((float)nhit) / topn_;
                    }
                }
                return static_cast<float>(sum_pre) / ngroup;
            }
            virtual const char *Name(void) const{
                return name_.c_str();
            }
        };

        /*! \brief Normalized DCG */
        class EvalNDCG : public IEvaluator {
        public:
            virtual float Eval(const std::vector<float> &preds,
                const DMatrix::Info &info) const{
                if (info.group_ptr.size() <= 1) return 0;
                float acc = 0;
                std::vector< std::pair<float, float> > pairs_sort;
                for (int i = 0; i < info.group_ptr.size() - 1; i++){
                    for (int j = info.group_ptr[i]; j < info.group_ptr[i + 1]; j++){
                        pairs_sort.push_back(std::make_pair(preds[j], info.labels[j]));
                    }
                    acc += NDCG(pairs_sort);
                }
                return acc / (info.group_ptr.size() - 1);
            }

            static float DCG(const std::vector<float> &labels){
                float ans = 0.0;
                for (int i = 0; i < labels.size(); i++){
                    ans += (pow(2, labels[i]) - 1) / log(i + 2);
                }
                return ans;
            }

            virtual const char *Name(void) const {
                return "NDCG";
            }

        private:
            /*\brief Obtain NDCG given the list of labels and predictions
            * \param pairs_sort the first field is prediction and the second is label
            */
            float NDCG(std::vector< std::pair<float, float> > pairs_sort) const{
                std::sort(pairs_sort.begin(), pairs_sort.end(), [](std::pair<float, float> a, std::pair<float, float> b){
                    return std::get<0>(a) > std::get<0>(b);
                });
                float dcg = DCG(pairs_sort);
                std::sort(pairs_sort.begin(), pairs_sort.end(), [](std::pair<float, float> a, std::pair<float, float> b){
                    return std::get<1>(a) > std::get<1>(b);
                });
                float IDCG = DCG(pairs_sort);
                if (IDCG == 0) return 0;
                return dcg / IDCG;
            }

            float DCG(std::vector< std::pair<float, float> > pairs_sort) const{
                std::vector<float> labels;
                for (int i = 1; i < pairs_sort.size(); i++){
                    labels.push_back(std::get<1>(pairs_sort[i]));
                }
                return DCG(labels);
            }
        };


        /*! \brief Mean Average Precision */
        class EvalMAP : public IEvaluator {
        public:
            virtual float Eval(const std::vector<float> &preds,
                const DMatrix::Info &info) const{
                if (info.group_ptr.size() <= 1) return 0;
                float acc = 0;
                std::vector<std::pair<float,float>> pairs_sort;
                for (int i = 0; i < info.group_ptr.size() - 1; i++){
                    for (int j = info.group_ptr[i]; j < info.group_ptr[i + 1]; j++){
                        pairs_sort.push_back(std::make_pair(preds[j], info.labels[j]));
                    }
                    acc += average_precision(pairs_sort);
                }
                return acc / (info.group_ptr.size() - 1);
            }

            virtual const char *Name(void) const {
                return "MAP";
            }

        private:
            /*\brief Obtain average precision given the list of labels and predictions
            * \param pairs_sort the first field is prediction and the second is label
            */
            float average_precision(std::vector< std::pair<float,float> > pairs_sort) const{
                std::sort(pairs_sort.begin(), pairs_sort.end(), [](std::pair<float, float> a, std::pair<float, float> b){
                    return std::get<0>(a) > std::get<0>(b);
                });
                float hits = 0;
                float average_precision = 0;
                for (int j = 0; j < pairs_sort.size(); j++){
                    if (std::get<1>(pairs_sort[j]) == 1){
                        hits++;
                        average_precision += hits / (j + 1);
                    }
                }
                if (hits != 0) average_precision /= hits;
                return average_precision;
            }
        };
    };
