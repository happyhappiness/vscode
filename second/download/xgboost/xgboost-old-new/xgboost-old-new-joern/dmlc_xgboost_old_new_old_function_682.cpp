inline void LoadModel( utils::IStream &fi ){
                utils::Assert( fi.Read( &mparam, sizeof(ModelParam) ) != 0 );
                base_model.LoadModel( fi );
            }