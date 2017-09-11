                utils::Assert( bid >= 0 && bid < mparam.num_boosters , "must specify booster index for deletion"); 
                delete boosters[ bid ];
                for( int i = bid + 1; i < mparam.num_boosters; ++ i ){
                    boosters[i-1] = boosters[ i ];
                    booster_info[i-1] = booster_info[ i ];
                } 
                boosters.resize( mparam.num_boosters -= 1 );
                booster_info.resize( boosters.size() );
            }
            /*! \brief update the prediction buffer, after booster have been updated */            
            inline void InteractRePredict( const FMatrixS &feats, bst_uint row_index, int buffer_index = -1, unsigned root_index = 0 ){
