            inline void TaskInteractive( void ){
                const time_t start    = time( NULL );
                unsigned long elapsed = 0;
                int batch_action = 0;
                
                cfg_batch.BeforeFirst();
                while( cfg_batch.Next() ){
                    if( !strcmp( cfg_batch.name(), "run" ) ){
                        learner.UpdateInteract( interact_action );
                        batch_action += 1;
                    } else{
                        learner.SetParam( cfg_batch.name(), cfg_batch.val() );
                    }
                }

                if( batch_action == 0 ){
                    learner.UpdateInteract( interact_action );
                }
                utils::Assert( model_out != "NULL", "interactive mode must specify model_out" );
                this->SaveModel( model_out.c_str() );
                elapsed = (unsigned long)(time(NULL) - start); 

                if( !silent ){
                    printf("\ninteractive update, %d batch actions, %lu sec in all\n", batch_action, elapsed );
                }
            }

