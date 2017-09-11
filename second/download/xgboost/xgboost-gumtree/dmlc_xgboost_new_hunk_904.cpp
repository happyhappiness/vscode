                */
                inline float Loss(const std::vector<float> &preds, const std::vector<float> &labels) const{
                    switch( loss_type ){
                    case kLinearSquare: return SquareLoss(preds,labels);
                    case kLogisticNeglik: return NegLoglikelihoodLoss(preds,labels);
                    default: utils::Error("unknown loss_type"); return 0.0f;
                    }
                }
