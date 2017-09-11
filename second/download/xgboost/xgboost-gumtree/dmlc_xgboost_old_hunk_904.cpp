                */
                inline float Loss(const std::vector<float> &preds, const std::vector<float> &labels) const{
                    switch( loss_type ){
                    case LINEAR_SQUARE: return SquareLoss(preds,labels);
                    case LOGISTIC_NEGLOGLIKELIHOOD: return NegLoglikelihoodLoss(preds,labels);
                    default: utils::Error("unknown loss_type"); return 0.0f;
                    }
                }
