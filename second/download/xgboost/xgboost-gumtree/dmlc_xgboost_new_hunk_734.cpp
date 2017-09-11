                        // linear boost automatically set do reboost
                        if (booster_type == 1) do_reboost = 1;
                    }
                    if (!strcmp("num_pbuffer", name))       num_pbuffer = atoi(val);
                    if (!strcmp("do_reboost", name))        do_reboost = atoi(val);
                    if (!strcmp("num_booster_group", name)) num_booster_group = atoi(val);
                    if (!strcmp("bst:num_roots", name))     num_roots = atoi(val);
                    if (!strcmp("bst:num_feature", name))   num_feature = atoi(val);
                }
                inline int PredBufferSize(void) const{
                    if (num_booster_group == 0) return num_pbuffer;
                    else return num_booster_group * num_pbuffer;
                }
                inline int BufferOffset( int buffer_index, int bst_group ) const{
                    if( buffer_index < 0 ) return -1;
                    utils::Assert( buffer_index < num_pbuffer, "buffer_indexexceed num_pbuffer" ); 
                    return buffer_index + num_pbuffer * bst_group;
                    
                }
            };
            /*! \brief training parameters */
