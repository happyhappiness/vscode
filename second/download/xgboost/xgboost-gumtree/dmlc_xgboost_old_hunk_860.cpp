                utils::Assert( fi.Read( &param, sizeof(Param) ) != 0 );
                boosters.resize( param.num_boosters );
                for( size_t i = 0; i < boosters.size(); i ++ ){
                    boosters[ i ] = booster::CreateBooster( param.booster_type );
                    boosters[ i ]->LoadModel( fi );
                }
                {// load info 
