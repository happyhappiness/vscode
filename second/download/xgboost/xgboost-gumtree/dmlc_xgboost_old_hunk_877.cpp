                                  const FMatrixS &feats,
                                  const std::vector<unsigned> &root_index ) = 0;
            /*! 
             * \brief predict values for given sparse feature vector
             *   NOTE: in tree implementation, this is not threadsafe, used dense version to ensure threadsafety
             * \param feat vector in sparse format
