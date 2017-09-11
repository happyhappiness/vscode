inline void InitModel( void ){
                pred_buffer.clear(); pred_counter.clear();
                pred_buffer.resize ( param.num_pbuffer, 0.0 );
                pred_counter.resize( param.num_pbuffer, 0 );
                utils::Assert( param.num_boosters == 0 );
                utils::Assert( boosters.size() == 0 );
            }