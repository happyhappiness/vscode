inline void InteractRePredict( const FMatrixS &feats, bst_uint row_index, int buffer_index = -1, unsigned root_index = 0 ){
                if( tparam.reupdate_booster != -1 ){
                    const int bid = tparam.reupdate_booster;
                    utils::Assert( bid >= 0 && bid < (int)boosters.size(), "interact:booster_index exceed existing bound" );
                    if( mparam.do_reboost == 0 && buffer_index >= 0 ){
                        this->pred_buffer[ buffer_index ] += boosters[ bid ]->Predict( feats, row_index, root_index );
                    }
                }
            }