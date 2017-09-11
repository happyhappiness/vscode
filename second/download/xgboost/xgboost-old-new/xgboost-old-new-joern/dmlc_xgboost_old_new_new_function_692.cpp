inline void InitData( void ){
                if( !strcmp( task.c_str(), "test") ){
                    data.CacheLoad( test_path.c_str() );
                }else{
                    // training 
                    data.CacheLoad( train_path.c_str() );
                    utils::Assert( eval_data_names.size() == eval_data_paths.size() );
                    for( size_t i = 0; i < eval_data_names.size(); ++ i ){
                        deval.push_back( new DMatrix() );
                        deval.back()->CacheLoad( eval_data_paths[i].c_str() );
                    }
                }
                learner.SetData( &data, deval, eval_data_names );
            }