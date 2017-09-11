inline void SetParam( const char *name, const char *val ) {
        if( !strcmp("silent", name ) )       silent = atoi( val );
        if( !strcmp("use_buffer", name ) )   use_buffer = atoi( val );
        if( !strcmp("seed", name ) )         random::Seed( atoi(val) );
        if( !strcmp("num_round", name ) )    num_round = atoi( val );
        if( !strcmp("save_period", name ) )  save_period = atoi( val );
        if( !strcmp("task", name ) )         task = val;
        if( !strcmp("data",  name ) )        train_path = val;
        if( !strcmp("test:data",  name ) )   test_path  = val;
        if( !strcmp("model_in",  name ) )    model_in   = val;
        if( !strcmp("model_out",  name ) )   model_out   = val;
        if( !strcmp("model_dir", name ) )    model_dir_path = val;
        if( !strcmp("fmap",  name ) )        name_fmap = val;
        if( !strcmp("name_dump",  name ) )   name_dump = val;
        if( !strcmp("name_dumppath",  name ) )   name_dumppath = val;
        if( !strcmp("name_pred",  name ) )   name_pred = val;
        if( !strcmp("dump_stats", name ) )   dump_model_stats = atoi( val );
        if( !strcmp("interact:action",  name ) )  interact_action = val;
        if( !strncmp("batch:",  name, 6 ) ) {
            cfg_batch.PushBack( name + 6, val );
        }
        if( !strncmp("eval[",  name, 5 ) ) {
            char evname[ 256 ];
            utils::Assert( sscanf( name, "eval[%[^]]", evname ) == 1, "must specify evaluation name for display");
            eval_data_names.push_back( std::string( evname ) );
            eval_data_paths.push_back( std::string( val ) );
        }
        cfg.PushBack( name, val );
    }