                }
                // always save final round
                if( save_period == 0 || num_round % save_period != 0 ){
                    if( model_out == "NULL" ){
                        this->SaveModel( num_round );
                    }else{
                        this->SaveModel( model_out.c_str() );
                    }
                }
                if( !silent ){
                    printf("\nupdating end, %lu sec in all\n", elapsed );
                }
            }

            inline void TaskInteractive( void ){
                const time_t start    = time( NULL );
                unsigned long elapsed = 0;
                learner.UpdateInteract();
                utils::Assert( model_out != "NULL", "interactive mode must specify model_out" );
                this->SaveModel( model_out.c_str() );
                elapsed = (unsigned long)(time(NULL) - start); 

                if( !silent ){
                    printf("\ninteractive update, %lu sec in all\n", elapsed );
                }
            }

            inline void TaskDump( void ){
                FILE *fo = utils::FopenCheck( name_dump.c_str(), "w" );
                learner.DumpModel( fo, fmap, dump_model_stats != 0 );
