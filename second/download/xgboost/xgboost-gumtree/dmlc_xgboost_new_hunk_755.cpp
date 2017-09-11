                obj_->PredTransform( preds );
            }
            /*! \brief repredict trial */
            inline void InteractRePredict(const DMatrix &data){
                int buffer_offset = this->FindBufferOffset(data);
                utils::Assert( buffer_offset >=0, "interact mode must cache training data" );
                const unsigned ndata = static_cast<unsigned>(data.Size());
                #pragma omp parallel for schedule( static )
                for (unsigned j = 0; j < ndata; ++j){
                    base_gbm.InteractRePredict(data.data, j, buffer_offset + j);
                }
            }
        private:
            /*! \brief get un-transformed prediction*/
            inline void PredictRaw(std::vector<float> &preds, const DMatrix &data){
                this->PredictBuffer(preds, data, this->FindBufferOffset(data) );
            }
            /*! \brief get the un-transformed predictions, given data */
            inline void PredictBuffer(std::vector<float> &preds, const DMatrix &data, int buffer_offset){
                preds.resize(data.Size());
                const unsigned ndata = static_cast<unsigned>(data.Size());
                if( buffer_offset >= 0 ){  
                    #pragma omp parallel for schedule( static )
                    for (unsigned j = 0; j < ndata; ++j){
                        preds[j] = mparam.base_score + base_gbm.Predict(data.data, j, buffer_offset + j);
                    }
                }else
                    #pragma omp parallel for schedule( static )
                    for (unsigned j = 0; j < ndata; ++j){
                        preds[j] = mparam.base_score + base_gbm.Predict(data.data, j, -1);
                    }{
                }
            }
        private:
