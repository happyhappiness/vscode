            /*! \brief get prediction, without buffering */
            inline void Predict( std::vector<float> &preds, const DMatrix &data ){
                preds.resize( data.Size() );
                for( size_t j = 0; j < data.Size(); j++ ){
                    preds[j] = mparam.PredTransform
                        ( mparam.base_score + base_model.Predict( data.data[j], -1 ) );
                }
            }
        private:
            /*! \brief print evaluation results */
            inline void Eval( FILE *fo, const char *evname,
                              const std::vector<float> &preds, 
                              const std::vector<float> &labels ){
                const float loss = mparam.Loss( preds, labels );
                fprintf( fo, "\t%s:%f", evname, loss );
            }
            /*! \brief get the transformed predictions, given data */
            inline void Predict( std::vector<float> &preds, const DMatrix &data, unsigned buffer_offset ){
                preds.resize( data.Size() );
                for( size_t j = 0; j < data.Size(); j++ ){
                    preds[j] = mparam.PredTransform
                        ( mparam.base_score + base_model.Predict( data.data[j], buffer_offset + j ) );
                }
