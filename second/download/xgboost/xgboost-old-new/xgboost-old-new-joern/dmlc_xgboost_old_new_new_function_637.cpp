inline float Predict( const FMatrixS &feats, bst_uint row_index, int buffer_index = -1, unsigned root_index = 0 ){
                size_t istart = 0;
                float  psum = 0.0f;

                // load buffered results if any
                if( mparam.do_reboost == 0 && buffer_index >= 0 ){
                    utils::Assert( buffer_index < mparam.num_pbuffer, "buffer index exceed num_pbuffer" );
                    istart = this->pred_counter[ buffer_index ];
                    psum   = this->pred_buffer [ buffer_index ];
                }
            
                for( size_t i = istart; i < this->boosters.size(); i ++ ){
                    psum += this->boosters[ i ]->Predict( feats, row_index, root_index );
                }                
                // updated the buffered results
                if( mparam.do_reboost == 0 && buffer_index >= 0 ){
                    this->pred_counter[ buffer_index ] = static_cast<unsigned>( boosters.size() );
                    this->pred_buffer [ buffer_index ] = psum;
                }
                return psum;
            }