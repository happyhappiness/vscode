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
