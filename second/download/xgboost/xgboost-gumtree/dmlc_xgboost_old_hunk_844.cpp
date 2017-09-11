            inline void TaskInteractive( void ){
                const time_t start    = time( NULL );
                unsigned long elapsed = 0;
                learner.UpdateInteract();
                utils::Assert( model_out != "NULL", "interactive mode must specify model_out" );
                this->SaveModel( model_out.c_str() );
                elapsed = (unsigned long)(time(NULL) - start); 
