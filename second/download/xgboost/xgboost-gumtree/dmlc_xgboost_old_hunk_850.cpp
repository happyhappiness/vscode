                float  psum = 0.0f;

                // load buffered results if any
                if( param.do_reboost == 0 && buffer_index >= 0 ){
                    utils::Assert( buffer_index < param.num_pbuffer, "buffer index exceed num_pbuffer" );
                    istart = this->pred_counter[ buffer_index ];
                    psum   = this->pred_buffer [ buffer_index ];
                }
            
                for( size_t i = istart; i < this->boosters.size(); i ++ ){
                    psum += this->boosters[ i ]->Predict( feats, row_index, root_index );
                }
                
                // updated the buffered results
                if( param.do_reboost == 0 && buffer_index >= 0 ){
                    this->pred_counter[ buffer_index ] = static_cast<unsigned>( boosters.size() );
                    this->pred_buffer [ buffer_index ] = psum;
                }
                return psum;
            }
            /*! 
             * \brief predict values for given dense feature vector
             * \param feat feature vector in dense format
             * \param funknown indicator that the feature is missing
             * \param buffer_index the buffer index of the current feature line, default -1 means no buffer assigned
             * \param rid root id of current instance, default = 0
             * \return prediction 
             */                
            virtual float Predict( const std::vector<float> &feat, 
                                   const std::vector<bool>  &funknown,
                                   int buffer_index = -1,
                                   unsigned rid = 0 ){
                size_t istart = 0;
                float  psum = 0.0f;

                // load buffered results if any
                if( param.do_reboost == 0 && buffer_index >= 0 ){
                    utils::Assert( buffer_index < param.num_pbuffer, 
                                   "buffer index exceed num_pbuffer" );
                    istart = this->pred_counter[ buffer_index ];
                    psum   = this->pred_buffer [ buffer_index ];
                }
            
                for( size_t i = istart; i < this->boosters.size(); i ++ ){
                    psum += this->boosters[ i ]->Predict( feat, funknown, rid );
                }
                
                // updated the buffered results
                if( param.do_reboost == 0 && buffer_index >= 0 ){
                    this->pred_counter[ buffer_index ] = static_cast<unsigned>( boosters.size() );
                    this->pred_buffer [ buffer_index ] = psum;
                }
                return psum;
            }
            //-----------non public fields afterwards-------------
        protected:
            /*! \brief free space of the model */
            inline void FreeSpace( void ){
                for( size_t i = 0; i < boosters.size(); i ++ ){
                    delete boosters[i];
                }
                boosters.clear(); booster_info.clear(); param.num_boosters = 0; 
            }
            /*! \brief configure a booster */
            inline void ConfigBooster( booster::IBooster *bst ){
