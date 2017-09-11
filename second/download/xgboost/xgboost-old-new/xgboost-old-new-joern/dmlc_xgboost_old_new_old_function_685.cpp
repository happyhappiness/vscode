inline void InitLearner( void ){
                cfg.BeforeFirst();
                while( cfg.Next() ){
                    learner.SetParam( cfg.name(), cfg.val() );
                }
                if( strcmp( model_in.c_str(), "NULL" ) != 0 ){
                    utils::Assert( !strcmp( task.c_str(), "train"), "model_in not specified" );
                    utils::FileStream fi( utils::FopenCheck( model_in.c_str(), "rb") );
                    learner.LoadModel( fi );
                    fi.Close();
                }else{
                    learner.InitModel();
                }
                learner.InitTrainer();
            }