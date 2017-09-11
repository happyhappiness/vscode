            * \param fi input stream
            */          
            inline void LoadModel( utils::IStream &fi ){
                utils::Assert( fi.Read( &mparam, sizeof(ModelParam) ) != 0 );
                base_model.LoadModel( fi );
            }
            /*! 
            * \brief save model to stream
            * \param fo output stream
            */
            inline void SaveModel( utils::IStream &fo ) const{
                fo.Write( &mparam, sizeof(ModelParam) );
                base_model.SaveModel( fo );	
            } 
            /*! 
             * \brief update the model for one iteration
