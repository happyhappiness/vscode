inline float PredTransform( float x ){
                    switch( loss_type ){                        
                    case LINEAR_SQUARE: return x;
                    case LOGISTIC_NEGLOGLIKELIHOOD: return 1.0f/(1.0f + expf(-x));
                    default: utils::Error("unknown loss_type"); return 0.0f;
                    }
                }