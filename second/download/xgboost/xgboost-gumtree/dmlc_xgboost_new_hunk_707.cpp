                    booster_info[i - 1] = booster_info[i];
                }
                boosters.resize(mparam.num_boosters -= 1);
                booster_info.resize(boosters.size());                
                // update pred counter
                for( size_t i = 0; i < pred_counter.size(); ++ i ){
                    if( pred_counter[i] > (unsigned)bid ) pred_counter[i] -= 1;                    
                }
            }
            /*! \brief update the prediction buffer, after booster have been updated */
            inline void InteractRePredict(const FMatrixS &feats, bst_uint row_index, 
                                          int buffer_index = -1, unsigned root_index = 0, int bst_group = 0 ){
                if (tparam.reupdate_booster != -1){
                    const int bid = tparam.reupdate_booster;
                    if( booster_info[bid]  != bst_group ) return;
                    utils::Assert(bid >= 0 && bid < (int)boosters.size(), "interact:booster_index exceed existing bound");
                    if (mparam.do_reboost == 0 && buffer_index >= 0){
                        this->pred_buffer[mparam.BufferOffset(buffer_index,bst_group)] += boosters[bid]->Predict(feats, row_index, root_index);
                    }
                }
            }
