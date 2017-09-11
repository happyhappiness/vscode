                xgboost::regrank::RegRankBoostLearner::LoadModel(fname);
                this->init_model = true;
            }
            const float *Pred( const DMatrix &dmat, size_t *len ){
                this->Predict( this->preds_, dmat );
                *len = this->preds_.size();
                return &this->preds_[0];
            }
        };
    };
};
