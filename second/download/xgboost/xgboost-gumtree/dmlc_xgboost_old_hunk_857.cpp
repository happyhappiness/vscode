            /*! 
             * \brief predict the path ids along a trees, for given sparse feature vector. When booster is a tree
             * \param path the result of path
             * \param rid root id of current instance, default = 0
             */
            virtual void PredPath( std::vector<int> &path, const FMatrixS::Line &feat, unsigned rid = 0 ){
                utils::Error( "not implemented" );
            }
            /*! 
             * \brief predict values for given sparse feature vector
             * 
             *   NOTE: in tree implementation, Sparse Predict is OpenMP threadsafe, but not threadsafe in general,
             *         dense version of Predict to ensures threadsafety
             * \param feat vector in sparse format
             * \param rid root id of current instance, default = 0
             * \return prediction 
             */        
            virtual float Predict( const FMatrixS::Line &feat, unsigned rid = 0 ){
                utils::Error( "not implemented" );
                return 0.0f;
            }
