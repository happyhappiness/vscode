inline void InteractPredict(std::vector<float> &preds, const DMatrix &data){
                int buffer_offset = this->FindBufferOffset(data);
                utils::Assert( buffer_offset >=0, "interact mode must cache training data" );
                preds.resize(data.Size());
                const unsigned ndata = static_cast<unsigned>(data.Size());
                #pragma omp parallel for schedule( static )
                for (unsigned j = 0; j < ndata; ++j){
                    preds[j] = mparam.base_score + base_gbm.InteractPredict(data.data, j, buffer_offset + j);                    
                }
                obj_->PredTransform( preds );
            }