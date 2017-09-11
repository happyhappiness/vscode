                xgboost::regrank::RegRankBoostLearner::LoadModel(fname);
                this->init_model = true;
            }
            const float *Pred( const DMatrix &dmat, size_t *len, int bst_group ){
                this->CheckInit();

                this->Predict( this->preds_, dmat, bst_group );
                *len = this->preds_.size();
                return &this->preds_[0];
            }
            inline void BoostOneIter( const DMatrix &train, 
                                      float *grad, float *hess, size_t len, int bst_group ){
                this->grad_.resize( len ); this->hess_.resize( len );
                memcpy( &this->grad_[0], grad, sizeof(float)*len );
                memcpy( &this->hess_[0], hess, sizeof(float)*len );
                
                if( grad_.size() == train.Size() ){
                    if( bst_group < 0 ) bst_group = 0;
                    base_gbm.DoBoost(grad_, hess_, train.data, train.info.root_index, bst_group);
                }else{
                    utils::Assert( bst_group == -1, "must set bst_group to -1 to support all group boosting" );
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
        };
    };
};
