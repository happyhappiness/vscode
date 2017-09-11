inline float ClassificationError(const std::vector<float> &preds, const std::vector<float> &labels) const{
                    int nerr = 0;
                    for(size_t i = 0; i < preds.size(); i++){
                        if( preds[i] > 0.5f ){
                            if( labels[i] < 0.5f ) nerr ++;
                        }else{
                            if( labels[i] > 0.5f ) nerr ++;
                        }
                    }
                    return (float)nerr/preds.size();
                }