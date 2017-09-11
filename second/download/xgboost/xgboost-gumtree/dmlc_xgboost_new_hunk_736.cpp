                fprintf(fo, "\n");
                fflush(fo);
            }
            /*! 
             * \brief get prediction
             * \param storage to store prediction
             * \param data input data
             * \param bst_group booster group we are in
             */
            inline void Predict(std::vector<float> &preds, const DMatrix &data, int bst_group = -1){
                this->PredictRaw( preds, data, bst_group );
                obj_->PredTransform( preds );
            }            
        public:
