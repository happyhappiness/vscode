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
            /*! \brief get un-transformed prediction*/
            inline void PredictRaw(std::vector<float> &preds, const DMatrix &data, int bst_group = -1 ){
                int buffer_offset =  this->FindBufferOffset(data);
                if( bst_group < 0 ){
                    int ngroup = base_gbm.NumBoosterGroup();
                    preds.resize( data.Size() * ngroup );
                    for( int g = 0; g < ngroup; ++ g ){ 
                        this->PredictBuffer(&preds[ data.Size() * g ], data, buffer_offset, g );
                    }
                }else{
                    preds.resize( data.Size() );
                    this->PredictBuffer(&preds[0], data, buffer_offset, bst_group );
                }
            }
            /*! \brief get the un-transformed predictions, given data */
            inline void PredictBuffer(float *preds, const DMatrix &data, int buffer_offset, int bst_group ){
                const unsigned ndata = static_cast<unsigned>(data.Size());
                if( buffer_offset >= 0 ){  
                    #pragma omp parallel for schedule( static )
                    for (unsigned j = 0; j < ndata; ++j){
                        preds[j] = mparam.base_score + base_gbm.Predict(data.data, j, buffer_offset + j, data.info.GetRoot(j), bst_group );
                    }
                }else
                    #pragma omp parallel for schedule( static )
                    for (unsigned j = 0; j < ndata; ++j){
                        preds[j] = mparam.base_score + base_gbm.Predict(data.data, j, -1, data.info.GetRoot(j), bst_group );
                    }{
                }
            }
        private:
