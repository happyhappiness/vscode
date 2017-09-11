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
        public:
            //--------trial code for interactive update an existing booster------
            //-------- usually not needed, ignore this region ---------
            /*! 
             * \brief same as Predict, but removes the prediction of booster to be updated 
             *        this function must be called once and only once for every data with pbuffer
             */
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
            /*! \brief update the prediction buffer, after booster have been updated */            
            inline void InteractRePredict( const FMatrixS &feats, bst_uint row_index, int buffer_index = -1, unsigned root_index = 0 ){
                if( tparam.reupdate_booster != -1 ){
                    const int bid = tparam.reupdate_booster;
                    utils::Assert( bid >= 0 && bid < (int)boosters.size(), "interact:booster_index exceed existing bound" );
                    if( mparam.do_reboost == 0 && buffer_index >= 0 ){
                        this->pred_buffer[ buffer_index ] += boosters[ bid ]->Predict( feats, row_index, root_index );
                    }
                }
            }
            //-----------non public fields afterwards-------------
        protected:
            /*! \brief free space of the model */
            inline void FreeSpace( void ){
                for( size_t i = 0; i < boosters.size(); i ++ ){
                    delete boosters[i];
                }
                boosters.clear(); booster_info.clear(); mparam.num_boosters = 0; 
            }
            /*! \brief configure a booster */
            inline void ConfigBooster( booster::IBooster *bst ){
