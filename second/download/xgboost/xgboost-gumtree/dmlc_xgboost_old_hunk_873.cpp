                }

                /*!
                * \brief calculating the square loss, given the predictions and labels
                * \param preds the given predictions
                * \param labels the given labels
                * \return the summation of square loss
                */
                inline float NegLoglikelihoodLoss(const std::vector<float> &preds, const std::vector<float> &labels) const{
                    float ans = 0.0;
                    for(size_t i = 0; i < preds.size(); i++)
                        ans -= labels[i] * logf(preds[i]) + ( 1 - labels[i] ) * logf(1 - preds[i]);
                    return ans;
                }

                /*!
                * \brief calculating the ClassificationError  loss, given the predictions and labels
                * \param preds the given predictions
                * \param labels the given labels
                * \return the summation of square loss
                */
                inline float ClassificationError(const std::vector<float> &preds, const std::vector<float> &labels) const{
                    int nerr = 0;
                    for(size_t i = 0; i < preds.size(); i++){
                        if( preds[i] > 0.5f ){
                            if( labels[i] < 0.5f ) nerr ++;
                        }else{
                            if( labels[i] > 0.5f ) nerr ++;
                        }
                    }
                    return (float)nerr/preds.size();
                }                
            };
        private:
            int silent;
            booster::GBMBaseModel base_model;
            ModelParam   mparam;
            const DMatrix *train_;
            std::vector<DMatrix *> evals_;
            std::vector<std::string> evname_;
            std::vector<unsigned> buffer_index_;
        };
    }
};
