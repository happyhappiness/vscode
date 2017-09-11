                    utils::Assert( bid >= 0 && bid < (int)boosters.size(), "interact:booster_index exceed existing bound" );
                    psum -= boosters[ bid ]->Predict( feats, row_index, root_index );
                    if( mparam.do_reboost == 0 && buffer_index >= 0 ){
                        this->pred_buffer[ buffer_index ] = psum;
                    }
                }
                return psum;
