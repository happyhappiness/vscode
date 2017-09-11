            * \brief initialize the current data storage for model, if the model is used first time, call this function
            */
            inline void InitModel( void ){
                base_gbm.InitModel();
                mparam.AdjustBase();
            }
            /*! 
            * \brief load model from stream
            * \param fi input stream
            */          
            inline void LoadModel( utils::IStream &fi ){
                base_gbm.LoadModel( fi );
                utils::Assert( fi.Read( &mparam, sizeof(ModelParam) ) != 0 );
            }
            /*! 
