inline void InitLearner( void ){
                cfg.BeforeFirst();
                while( cfg.Next() ){
                    learner.SetParam( cfg.name(), cfg.val() );
                }
                if( strcmp( model_in.c_str(), "NULL" ) != 0 ){
                    utils::FileStream fi( utils::FopenCheck( model_in.c_str(), "rb") );
                    learner.LoadModel( fi );
                    fi.Close();
                }else{
                    utils::Assert( !strcmp( task.c_str(), "train"), "model_in not specified" );
                    learner.InitModel();
                }
                learner.InitTrainer();
            }