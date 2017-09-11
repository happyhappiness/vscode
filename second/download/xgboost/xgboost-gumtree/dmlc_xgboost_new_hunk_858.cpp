             * \param feat feature vector in dense format
             * \param funknown indicator that the feature is missing
             * \param rid root id of current instance, default = 0
             * \return prediction
             */
            virtual float Predict( const std::vector<float> &feat, 
                                   const std::vector<bool>  &funknown,
                                   unsigned rid = 0 ){
                utils::Error( "not implemented" );
                return 0.0f;
            }
            /*! 
