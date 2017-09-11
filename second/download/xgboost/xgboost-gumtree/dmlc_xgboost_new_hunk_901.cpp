                        base_score = - logf( 1.0f / base_score - 1.0f );
                    }
                }

                /*! 
                * \brief transform the linear sum to prediction 
                * \param x linear sum of boosting ensemble
                * \return transformed prediction
                */
                inline float PredTransform( float x ){
                    switch( loss_type ){                        
                    case kLinearSquare: return x;
                    case kLogisticNeglik: return 1.0f/(1.0f + expf(-x));
                    default: utils::Error("unknown loss_type"); return 0.0f;
                    }
                }

                /*! 
                * \brief calculate first order gradient of loss, given transformed prediction
                * \param predt transformed prediction
