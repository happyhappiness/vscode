inline void SaveModel( utils::IStream &fo ) const {
                utils::Assert( param.num_boosters == (int)boosters.size() );
                fo.Write( &param, sizeof(Param) );
                for( size_t i = 0; i < boosters.size(); i ++ ){
                    boosters[ i ]->SaveModel( fo ); 
                }
                if( booster_info.size() != 0 ){
                    fo.Write( &booster_info[0], sizeof(int) * booster_info.size() );
                }
                if( param.num_pbuffer != 0 ){
                    fo.Write( &pred_buffer[0] , pred_buffer.size()*sizeof(float) );
                    fo.Write( &pred_counter[0], pred_counter.size()*sizeof(unsigned) );
                }
            }