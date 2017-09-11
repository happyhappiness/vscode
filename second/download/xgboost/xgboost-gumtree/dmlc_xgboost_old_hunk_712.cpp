                fo.Write(&mparam, sizeof(ModelParam));
            }
            /*!
             * \brief update the model for one iteration
             * \param iteration iteration number
             */
            inline void UpdateOneIter(int iter){
                this->PredictBuffer(preds_, *train_, 0);
                obj_->GetGradient(preds_, train_->info, base_gbm.NumBoosters(), grad_, hess_);
                std::vector<unsigned> root_index;
                base_gbm.DoBoost(grad_, hess_, train_->data, root_index);
            }
            /*!
             * \brief evaluate the model for specific iteration
             * \param iter iteration number
             * \param fo file to output log
             */
            inline void EvalOneIter(int iter, FILE *fo = stderr){
                fprintf(fo, "[%d]", iter);
                int buffer_offset = static_cast<int>(train_->Size());

                for (size_t i = 0; i < evals_.size(); ++i){
                    std::vector<float> &preds = this->eval_preds_[i];
                    this->PredictBuffer(preds, *evals_[i], buffer_offset);
                    obj_->PredTransform(preds);
                    evaluator_.Eval(fo, evname_[i].c_str(), preds, evals_[i]->info);
                    buffer_offset += static_cast<int>(evals_[i]->Size());
                }
                fprintf(fo, "\n");
                fflush(fo);
            }
            /*! \brief get prediction, without buffering */
            inline void Predict(std::vector<float> &preds, const DMatrix &data){
                preds.resize(data.Size());
                const unsigned ndata = static_cast<unsigned>(data.Size());
                #pragma omp parallel for schedule( static )
                for (unsigned j = 0; j < ndata; ++j){
                    preds[j] = mparam.base_score + base_gbm.Predict(data.data, j, -1);
                }
                obj_->PredTransform( preds );
            }            
        public:
            /*!
             * \brief interactive update 
             * \param action action type 
             */
            inline void UpdateInteract(std::string action){
                this->InteractPredict(preds_, *train_, 0);

                int buffer_offset = static_cast<int>(train_->Size());
                for (size_t i = 0; i < evals_.size(); ++i){
                    std::vector<float> &preds = this->eval_preds_[i];
                    this->InteractPredict(preds, *evals_[i], buffer_offset);
                    buffer_offset += static_cast<int>(evals_[i]->Size());
                }

                if (action == "remove"){
                    base_gbm.DelteBooster(); return;
                }

                obj_->GetGradient(preds_, train_->info, base_gbm.NumBoosters(), grad_, hess_);
                std::vector<unsigned> root_index;
                base_gbm.DoBoost(grad_, hess_, train_->data, root_index);

                this->InteractRePredict(*train_, 0);
                buffer_offset = static_cast<int>(train_->Size());
                for (size_t i = 0; i < evals_.size(); ++i){
                    this->InteractRePredict(*evals_[i], buffer_offset);
                    buffer_offset += static_cast<int>(evals_[i]->Size());
                }
            }
        private:
            /*! \brief get the transformed predictions, given data */
            inline void InteractPredict(std::vector<float> &preds, const DMatrix &data, unsigned buffer_offset){
                preds.resize(data.Size());
                const unsigned ndata = static_cast<unsigned>(data.Size());
                #pragma omp parallel for schedule( static )
