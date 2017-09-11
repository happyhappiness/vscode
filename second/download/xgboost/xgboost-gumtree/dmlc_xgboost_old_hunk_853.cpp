                }
                fprintf( fo,"\n" );
            }

            /*! \brief get prediction, without buffering */
            inline void Predict( std::vector<float> &preds, const DMatrix &data ){
                preds.resize( data.Size() );
