inline void InitLearner( void ) {
        cfg.BeforeFirst();
        while( cfg.Next() ) {
            learner.SetParam( cfg.name(), cfg.val() );
        }
        if( model_in != "NULL" ) {
            utils::FileStream fi( utils::FopenCheck( model_in.c_str(), "rb") );
            learner.LoadModel( fi );
            fi.Close();
        } else {
            utils::Assert( task == "train", "model_in not specified" );
            learner.InitModel();
        }
        learner.InitTrainer();
    }