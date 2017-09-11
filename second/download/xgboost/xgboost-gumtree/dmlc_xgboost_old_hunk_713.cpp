                obj_->PredTransform( preds );
            }
            /*! \brief repredict trial */
            inline void InteractRePredict(const DMatrix &data, unsigned buffer_offset){
                const unsigned ndata = static_cast<unsigned>(data.Size());
                #pragma omp parallel for schedule( static )
                for (unsigned j = 0; j < ndata; ++j){
                    base_gbm.InteractRePredict(data.data, j, buffer_offset + j);
                }
            }
        private:
            /*! \brief get the transformed predictions, given data */
            inline void PredictBuffer(std::vector<float> &preds, const DMatrix &data, unsigned buffer_offset){
                preds.resize(data.Size());
                const unsigned ndata = static_cast<unsigned>(data.Size());
                #pragma omp parallel for schedule( static )
                for (unsigned j = 0; j < ndata; ++j){
                    preds[j] = mparam.base_score + base_gbm.Predict(data.data, j, buffer_offset + j);
                }
            }
        private:
