                }
                // always save final round
                if( save_period == 0 || num_round % save_period != 0 ){
                    this->SaveModel( num_round );
                }
                if( !silent ){
                    printf("\nupdating end, %lu sec in all\n", elapsed );
                }
            }

            inline void TaskDump( void ){
                FILE *fo = utils::FopenCheck( name_dump.c_str(), "w" );
                learner.DumpModel( fo, fmap, dump_model_stats != 0 );
