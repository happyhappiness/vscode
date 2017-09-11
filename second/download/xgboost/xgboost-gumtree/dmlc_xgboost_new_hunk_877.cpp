                                  const FMatrixS &feats,
                                  const std::vector<unsigned> &root_index ) = 0;
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
             *   NOTE: in tree implementation, this is not threadsafe, used dense version to ensure threadsafety
             * \param feat vector in sparse format
