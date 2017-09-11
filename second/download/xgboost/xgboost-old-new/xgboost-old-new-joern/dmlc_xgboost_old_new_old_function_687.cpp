inline void Predict( std::vector<float> &preds, const DMatrix &data,int buffer_index_offset = 0 ){
                int data_size = data.size();
                preds.resize(data_size);
                for(int j = 0; j < data_size; j++){
                    preds[j] = mparam.PredTransform(mparam.base_score + 
                        base_model.Predict(data.data[j],buffer_index_offset + j));
                }
            }