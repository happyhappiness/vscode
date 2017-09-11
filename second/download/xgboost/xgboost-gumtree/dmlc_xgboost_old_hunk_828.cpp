        inline float SecondOrderGradient( float pred_diff_exp ) const {
            return pred_diff_exp/pow(1 + pred_diff_exp,2);
        }

        /*!
         * \brief calculating the loss, given the predictions, labels and the loss type
         * \param preds the given predictions
         * \param labels the given labels
         * \return the specified loss
         */
        inline float Loss(const std::vector<float> &preds, const std::vector<float> &labels) const {
            switch( loss_type ) {
            case kLinearSquare:
                return SquareLoss(preds,labels);
            case kLogisticNeglik:
            case kLogisticClassify:
                return NegLoglikelihoodLoss(preds,labels);
            default:
                utils::Error("unknown loss_type");
                return 0.0f;
            }
        }

        /*!
         * \brief calculating the square loss, given the predictions and labels
         * \param preds the given predictions
         * \param labels the given labels
         * \return the summation of square loss
         */
        inline float SquareLoss(const std::vector<float> &preds, const std::vector<float> &labels) const {
            float ans = 0.0;
            for(size_t i = 0; i < preds.size(); i++) {
                float dif = preds[i] - labels[i];
                ans += dif * dif;
            }
            return ans;
        }

        /*!
         * \brief calculating the square loss, given the predictions and labels
         * \param preds the given predictions
         * \param labels the given labels
         * \return the summation of square loss
         */
        inline float NegLoglikelihoodLoss(const std::vector<float> &preds, const std::vector<float> &labels) const {
            float ans = 0.0;
            for(size_t i = 0; i < preds.size(); i++)
                ans -= labels[i] * logf(preds[i]) + ( 1 - labels[i] ) * logf(1 - preds[i]);
            return ans;
        }
    };
private:
    int silent;
    RankEvalSet evaluator_;
    booster::GBMBase base_gbm;
    ModelParam   mparam;
    const RMatrix *train_;
