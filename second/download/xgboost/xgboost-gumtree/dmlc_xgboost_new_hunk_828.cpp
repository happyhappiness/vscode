        inline float SecondOrderGradient( float pred_diff_exp ) const {
            return pred_diff_exp/pow(1 + pred_diff_exp,2);
        }
    };
private:
    int silent;
    RankEvalSet evaluator_;
    sample::PairSamplerWrapper sampler;
    booster::GBMBase base_gbm;
    ModelParam   mparam;
    const RMatrix *train_;
