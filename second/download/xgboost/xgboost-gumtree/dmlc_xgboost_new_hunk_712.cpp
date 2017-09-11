                fo.Write(&mparam, sizeof(ModelParam));
            }
            /*!
             * \brief save model into file
             * \param fname file name
             */
            inline void SaveModel(const char *fname) const{
                utils::FileStream fo(utils::FopenCheck(fname, "wb"));
                this->SaveModel(fo);
                fo.Close();                
            }
            /*!
             * \brief update the model for one iteration
             */
            inline void UpdateOneIter(const DMatrix &train){
                this->PredictRaw(preds_, train);
                obj_->GetGradient(preds_, train.info, base_gbm.NumBoosters(), grad_, hess_);
                if( grad_.size() == train.Size() ){
                    base_gbm.DoBoost(grad_, hess_, train.data, train.info.root_index);
                }else{
                    int ngroup = base_gbm.NumBoosterGroup();
                    utils::Assert( grad_.size() == train.Size() * (size_t)ngroup, "BUG: UpdateOneIter: mclass" );
                    std::vector<float> tgrad( train.Size() ), thess( train.Size() );
                    for( int g = 0; g < ngroup; ++ g ){
                        memcpy( &tgrad[0], &grad_[g*tgrad.size()], sizeof(float)*tgrad.size() );
                        memcpy( &thess[0], &hess_[g*tgrad.size()], sizeof(float)*tgrad.size() );
                        base_gbm.DoBoost(tgrad, thess, train.data, train.info.root_index, g );
                    }
                }
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
            /*! 
             * \brief get prediction
             * \param storage to store prediction
             * \param data input data
             * \param bst_group booster group we are in
             */
            inline void Predict(std::vector<float> &preds, const DMatrix &data, int bst_group = -1){
                this->PredictRaw( preds, data, bst_group );
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
