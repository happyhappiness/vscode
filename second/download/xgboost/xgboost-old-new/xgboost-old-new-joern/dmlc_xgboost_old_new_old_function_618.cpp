inline void InitData( void ) {
        if( name_fmap != "NULL" ) fmap.LoadText( name_fmap.c_str() );
        if( task == "dump" ) return;
        if( task == "pred" || task == "dumppath" ) {
            data.CacheLoad( test_path.c_str(), silent!=0, use_buffer!=0 );
        } else {
            // training
            data.CacheLoad( train_path.c_str(), silent!=0, use_buffer!=0 );
            utils::Assert( eval_data_names.size() == eval_data_paths.size() );
            for( size_t i = 0; i < eval_data_names.size(); ++ i ) {
                deval.push_back( new RMatrix() );
                deval.back()->CacheLoad( eval_data_paths[i].c_str(), silent!=0, use_buffer!=0 );
            }
        }
        learner.SetData( &data, deval, eval_data_names );
    }