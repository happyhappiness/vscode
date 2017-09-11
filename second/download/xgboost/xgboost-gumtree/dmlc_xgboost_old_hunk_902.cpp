                */
                inline float FirstOrderGradient( float predt, float label ) const{
                    switch( loss_type ){                        
                    case LINEAR_SQUARE: return predt - label;
                    case 1: return predt - label;
                    default: utils::Error("unknown loss_type"); return 0.0f;
                    }
