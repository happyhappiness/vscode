inline void DumpModel( FILE *fo ){
                for( size_t i = 0; i < boosters.size(); i ++ ){
                    fprintf( fo, "booster[%d]\n", (int)i );
                    boosters[i]->DumpModel( fo );
                }
            }