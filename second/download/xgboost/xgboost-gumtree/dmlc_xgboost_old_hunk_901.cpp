                        base_score = - logf( 1.0f / base_score - 1.0f );
                    }
                }
                /*! 
                * \brief calculate first order gradient of loss, given transformed prediction
                * \param predt transformed prediction
