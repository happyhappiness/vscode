            * this function is reserved for solver to allocate necessary space and do other preparation
            */
            inline void InitTrainer(void){
                base_gbm.InitTrainer();
                obj_ = CreateObjFunction( name_obj_.c_str() );
                for( size_t i = 0; i < cfg_.size(); ++ i ){
                    obj_->SetParam( cfg_[i].first.c_str(), cfg_[i].second.c_str() );
                }
                evaluator_.AddEval( obj_->DefaultEvalMetric() );
            }
            /*!
            * \brief initialize the current data storage for model, if the model is used first time, call this function
            */
            inline void InitModel(void){
                base_gbm.InitModel();
                mparam.AdjustBase();
            }
            /*!
            * \brief load model from stream
            * \param fi input stream
            */
            inline void LoadModel(utils::IStream &fi){
                base_gbm.LoadModel(fi);
                utils::Assert(fi.Read(&mparam, sizeof(ModelParam)) != 0);
