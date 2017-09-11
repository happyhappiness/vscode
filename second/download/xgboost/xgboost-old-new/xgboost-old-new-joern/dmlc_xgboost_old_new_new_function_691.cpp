inline void SetParam( const char *name, const char *val ){
                if( !strcmp("silent", name ) )       silent = atoi( val );
                if( !strcmp("seed", name ) )         random::Seed( atoi(val) );
                if( !strcmp("num_round", name ) )    num_round = atoi( val );
                if( !strcmp("save_period", name ) )  save_period = atoi( val );
                if( !strcmp("task", name ) )         task = val;
                if( !strcmp("data",  name ) )        train_path = val;
                if( !strcmp("test:data",  name ) )   test_path  = val;
                if( !strcmp("model_in",  name ) )    model_in   = val;
                if( !strcmp("model_dir", name ) )    model_dir_path = val;
                if( !strncmp("eval[",  name, 5 ) ) {
                    char evname[ 256 ];
                    utils::Assert( sscanf( name, "eval[%[^]]", evname ) == 1, "must specify evaluation name for display");
                    eval_data_names.push_back( std::string( evname ) );
                    eval_data_paths.push_back( std::string( val ) );
                }
                cfg.PushBack( name, val );
            }