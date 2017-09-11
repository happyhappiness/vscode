             * \brief update the model for one iteration
             * \param iteration iteration number
             */
            inline void UpdateOneIter(int iter, const DMatrix &train){
                this->PredictRaw(preds_, train);
                obj_->GetGradient(preds_, train.info, base_gbm.NumBoosters(), grad_, hess_);
                // do boost
                std::vector<unsigned> root_index;
                base_gbm.DoBoost(grad_, hess_, train.data, root_index);
            }
            /*!
             * \brief evaluate the model for specific iteration
             * \param iter iteration number
             * \param evals datas i want to evaluate
             * \param evname name of each dataset
             * \param fo file to output log
             */
            inline void EvalOneIter(int iter,
                                    const std::vector<const DMatrix*> &evals,
                                    const std::vector<std::string> &evname,
                                    FILE *fo=stderr ){
                fprintf(fo, "[%d]", iter);
                for (size_t i = 0; i < evals.size(); ++i){
                    this->PredictRaw(preds_, *evals[i]);
                    obj_->PredTransform(preds_);
                    evaluator_.Eval(fo, evname[i].c_str(), preds_, evals[i]->info);
                }
                fprintf(fo, "\n");
                fflush(fo);
            }
            /*! \brief get prediction, without buffering */
            inline void Predict(std::vector<float> &preds, const DMatrix &data){
                this->PredictRaw(preds,data);
                obj_->PredTransform( preds );
            }            
        public:
            /*!
             * \brief interactive update 
             * \param action action type 
             * \parma train training data
             */
            inline void UpdateInteract(std::string action, const DMatrix& train){
                for(size_t i = 0; i < cache_.size(); ++i){
                    this->InteractPredict(preds_, *cache_[i].mat_);
                }

                if (action == "remove"){
                    base_gbm.DelteBooster(); return;
                }

                obj_->GetGradient(preds_, train.info, base_gbm.NumBoosters(), grad_, hess_);
                std::vector<unsigned> root_index;
                base_gbm.DoBoost(grad_, hess_, train.data, root_index);

                for(size_t i = 0; i < cache_.size(); ++i){
                    this->InteractRePredict(*cache_[i].mat_);
                }
            }
        private:
            /*! \brief get the transformed predictions, given data */
            inline void InteractPredict(std::vector<float> &preds, const DMatrix &data){
                int buffer_offset = this->FindBufferOffset(data);
                utils::Assert( buffer_offset >=0, "interact mode must cache training data" );
                preds.resize(data.Size());
                const unsigned ndata = static_cast<unsigned>(data.Size());
                #pragma omp parallel for schedule( static )
