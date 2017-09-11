                */
                inline float NegLoglikelihoodLoss(const std::vector<float> &preds, const std::vector<float> &labels) const{
                    float ans = 0.0;
                    for(int i = 0; i < preds.size(); i++)
                        ans -= labels[i] * log(preds[i]) + ( 1 - labels[i] ) * log(1 - preds[i]);
                    return ans;
                }


                /*! 
                * \brief transform the linear sum to prediction 
                * \param x linear sum of boosting ensemble
                * \return transformed prediction
                */
                inline float PredTransform( float x ){
                    switch( loss_type ){                        
                    case LINEAR_SQUARE: return x;
                    case LOGISTIC_NEGLOGLIKELIHOOD: return 1.0f/(1.0f + expf(-x));
                    default: utils::Error("unknown loss_type"); return 0.0f;
                    }
                }


            };            
        private:            
            booster::GBMBaseModel base_model;
            ModelParam   mparam;
            const DMatrix *train_;
            std::vector<const DMatrix *> evals_;
            std::vector<std::string> evname_;
            bool silent;
        };
    }
};
