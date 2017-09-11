                mparam.AdjustBase();
            }
            /*!
             * \brief load model from file 
             * \param fname file name
             */
            inline void LoadModel(const char *fname){
                utils::FileStream fi(utils::FopenCheck(fname, "rb"));
                this->LoadModel(fi);
                fi.Close();                
            }
            /*!
             * \brief load model from stream
             * \param fi input stream
             */
            inline void LoadModel(utils::IStream &fi){
                base_gbm.LoadModel(fi);
                utils::Assert(fi.Read(&mparam, sizeof(ModelParam)) != 0);
