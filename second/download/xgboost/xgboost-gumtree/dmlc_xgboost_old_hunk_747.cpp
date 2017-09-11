                mparam.AdjustBase();
            }
            /*!
            * \brief load model from stream
            * \param fi input stream
            */
            inline void LoadModel(utils::IStream &fi){
                base_gbm.LoadModel(fi);
                utils::Assert(fi.Read(&mparam, sizeof(ModelParam)) != 0);
