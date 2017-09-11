inline float InteractPredict( const FMatrixS &feats, bst_uint row_index, int buffer_index = -1, unsigned root_index = 0 ){
                float psum = this->Predict( feats, row_index, buffer_index, root_index );
                if( tparam.reupdate_booster != -1 ){
                    const int bid = tparam.reupdate_booster;
                    utils::Assert( bid >= 0 && bid < (int)boosters.size(), "interact:booster_index exceed existing bound" );
                    psum -= boosters[ bid ]->Predict( feats, row_index, root_index );
                    if( mparam.do_reboost == 0 && buffer_index >= 0 ){
                        this->pred_buffer[ buffer_index ] = psum;                        
                    }
                }
                return psum;
            }