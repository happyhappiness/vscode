inline void LoadModel(utils::IStream &fi){
                base_gbm.LoadModel(fi);
                utils::Assert(fi.Read(&mparam, sizeof(ModelParam)) != 0);
                // save name obj
                size_t len;                
                if( fi.Read(&len, sizeof(len)) != 0 ){
                    name_obj_.resize( len );
                    if( len != 0 ){
                        utils::Assert( fi.Read(&name_obj_[0], len*sizeof(char)) != 0 );
                    }
                }
            }