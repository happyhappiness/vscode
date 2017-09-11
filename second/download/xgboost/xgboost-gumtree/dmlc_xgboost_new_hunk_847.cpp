                if( !strcmp( name, "silent") ){
                    cfg.PushBack( name, val );
                }
                tparam.SetParam( name, val );
                if( boosters.size() == 0 ) mparam.SetParam( name, val );
            }
            /*! 
             * \brief load model from stream
             * \param fi input stream
             */
            inline void LoadModel( utils::IStream &fi ){
                if( boosters.size() != 0 ) this->FreeSpace();
                utils::Assert( fi.Read( &mparam, sizeof(ModelParam) ) != 0 );
                boosters.resize( mparam.num_boosters );
                for( size_t i = 0; i < boosters.size(); i ++ ){
                    boosters[ i ] = booster::CreateBooster<FMatrixS>( mparam.booster_type );
                    boosters[ i ]->LoadModel( fi );
                }
                {// load info 
                    booster_info.resize( mparam.num_boosters );
                    if( mparam.num_boosters != 0 ){
                        utils::Assert( fi.Read( &booster_info[0], sizeof(int)*mparam.num_boosters ) != 0 );
                    }
                }
                if( mparam.num_pbuffer != 0 ){
                    pred_buffer.resize ( mparam.num_pbuffer );
                    pred_counter.resize( mparam.num_pbuffer );
                    utils::Assert( fi.Read( &pred_buffer[0] , pred_buffer.size()*sizeof(float) ) != 0 );
                    utils::Assert( fi.Read( &pred_counter[0], pred_counter.size()*sizeof(unsigned) ) != 0 );
                }
