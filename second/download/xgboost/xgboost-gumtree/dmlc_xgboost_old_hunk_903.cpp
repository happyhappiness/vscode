                */
                inline float SecondOrderGradient( float predt, float label ) const{
                    switch( loss_type ){                        
                    case LINEAR_SQUARE: return 1.0f;
                    case LOGISTIC_NEGLOGLIKELIHOOD: return predt * ( 1 - predt );
                    default: utils::Error("unknown loss_type"); return 0.0f;
                    }
                }
