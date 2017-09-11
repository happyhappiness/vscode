                }
                return psum;
            }
            /*! \brief update the prediction buffer, after booster have been updated */            
            inline void InteractRePredict( const FMatrixS &feats, bst_uint row_index, int buffer_index = -1, unsigned root_index = 0 ){
                if( tparam.reupdate_booster != -1 ){
