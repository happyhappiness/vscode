                if( !strcmp( name, "silent") ){
                    cfg.PushBack( name, val );
                }
                if( !strcmp( name, "nthread") ) nthread = atoi( val );
                if( boosters.size() == 0 ) param.SetParam( name, val );
            }
            /*! 
             * \brief load model from stream
             * \param fi input stream
             */
            inline void LoadModel( utils::IStream &fi ){
                if( boosters.size() != 0 ) this->FreeSpace();
                utils::Assert( fi.Read( &param, sizeof(Param) ) != 0 );
                boosters.resize( param.num_boosters );
                for( size_t i = 0; i < boosters.size(); i ++ ){
                    boosters[ i ] = booster::CreateBooster<FMatrixS>( param.booster_type );
                    boosters[ i ]->LoadModel( fi );
                }
                {// load info 
                    booster_info.resize( param.num_boosters );
                    if( param.num_boosters != 0 ){
                        utils::Assert( fi.Read( &booster_info[0], sizeof(int)*param.num_boosters ) != 0 );
                    }
                }
                if( param.num_pbuffer != 0 ){
                    pred_buffer.resize ( param.num_pbuffer );
                    pred_counter.resize( param.num_pbuffer );
                    utils::Assert( fi.Read( &pred_buffer[0] , pred_buffer.size()*sizeof(float) ) != 0 );
                    utils::Assert( fi.Read( &pred_counter[0], pred_counter.size()*sizeof(unsigned) ) != 0 );
                }
