            /*! \brief get prediction, without buffering */
            inline void Predict( std::vector<float> &preds, const DMatrix &data ){
                preds.resize( data.Size() );

                const unsigned ndata = static_cast<unsigned>( data.Size() );
                #pragma omp parallel for schedule( static )
                for( unsigned j = 0; j < ndata; ++ j ){
                    preds[j] = mparam.PredTransform
                        ( mparam.base_score + base_model.Predict( data.data[j], -1 ) );
                }
            }
        private:
            /*! \brief get the transformed predictions, given data */
            inline void PredictBuffer( std::vector<float> &preds, const DMatrix &data, unsigned buffer_offset ){
                preds.resize( data.Size() );

                const unsigned ndata = static_cast<unsigned>( data.Size() );
                #pragma omp parallel for schedule( static )
                for( unsigned j = 0; j < ndata; ++ j ){                
                    preds[j] = mparam.PredTransform
                        ( mparam.base_score + base_model.Predict( data.data[j], buffer_offset + j ) );
                }
