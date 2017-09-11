inline booster::IBooster *GetUpdateBooster( void ){
                if( param.do_reboost == 0 || boosters.size() == 0 ){
                    param.num_boosters += 1;
                    boosters.push_back( booster::CreateBooster<FMatrixS>( param.booster_type ) );
                    booster_info.push_back( 0 );
                    this->ConfigBooster( boosters.back() );
                    boosters.back()->InitModel();                    
                }else{
                    this->ConfigBooster( boosters.back() );
                }
                return boosters.back();
            }