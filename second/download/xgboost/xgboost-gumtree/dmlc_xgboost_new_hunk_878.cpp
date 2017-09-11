                    boosters[i]->DumpModel( fo );
                }
            }
            /*! 
             * \brief Dump path of all trees
             * \param fo text file 
             * \param data input data
             */
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
        public:
            /*! 
             * \brief do gradient boost training for one step, using the information given
