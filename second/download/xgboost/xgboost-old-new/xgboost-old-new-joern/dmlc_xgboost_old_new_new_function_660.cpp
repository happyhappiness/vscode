inline void DumpPath( FILE *fo, const FMatrixS &data ){
                for( size_t i = 0; i < data.NumRow(); ++ i ){
                    for( size_t j = 0; j < boosters.size(); ++ j ){
                        if( j != 0 ) fprintf( fo, "\t" );
                        std::vector<int> path;
                        boosters[j]->PredPath( path, data[i] );
                        fprintf( fo, "%d", path[0] );
                        for( size_t k = 1; k < path.size(); ++ k ){
                            fprintf( fo, ",%d", path[k] );
                        }
                    }
                    fprintf( fo, "\n" );
                }
            }