                    switch( loss_type ){
                    case kLinearSquare: return SquareLoss(preds,labels);
                    case kLogisticNeglik: return NegLoglikelihoodLoss(preds,labels);
                    case kLogisticClassify: return ClassificationError(preds, labels);
                    default: utils::Error("unknown loss_type"); return 0.0f;
                    }
                }
