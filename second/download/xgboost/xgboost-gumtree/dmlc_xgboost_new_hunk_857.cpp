            /*! 
             * \brief predict the path ids along a trees, for given sparse feature vector. When booster is a tree
             * \param path the result of path
             * \param feats feature matrix
             * \param row_index  row index in the feature matrix
             * \param root_index root id of current instance, default = 0
             */
            virtual void PredPath( std::vector<int> &path, const FMatrix &feats, 
                                   bst_uint row_index, unsigned root_index = 0 ){
                utils::Error( "not implemented" );
            }
            /*! 
             * \brief predict values for given sparse feature vector
             * 
             *   NOTE: in tree implementation, Sparse Predict is OpenMP threadsafe, but not threadsafe in general,
             *         dense version of Predict to ensures threadsafety
             * \param feats feature matrix
             * \param row_index  row index in the feature matrix
             * \param root_index root id of current instance, default = 0
             * \return prediction 
             */        
            virtual float Predict( const FMatrix &feats, bst_uint row_index, unsigned root_index = 0 ){                
                utils::Error( "not implemented" );
                return 0.0f;
            }
