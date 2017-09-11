inline void DelteBooster( void ){
                const int bid = tparam.reupdate_booster;
                utils::Assert( bid >= 0 && bid < mparam.num_boosters , "must specify booster index for deletion"); 
                delete boosters[ bid ];
                for( int i = bid + 1; i < mparam.num_boosters; ++ i ){
                    boosters[ i - 1 ] = boosters[ i ];
                } 
                boosters.resize( mparam.num_boosters -= 1 );
            }