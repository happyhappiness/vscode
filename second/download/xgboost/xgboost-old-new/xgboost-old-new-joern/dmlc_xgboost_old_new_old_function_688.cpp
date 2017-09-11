inline void Gradient(const std::vector<float> &preds, const std::vector<float> &labels, std::vector<float> &grad,
                std::vector<float> &hess){
                    grad.clear(); 
                    hess.clear();
                    for(int j = 0; j < preds.size(); j++){
                        grad.push_back(mparam.FirstOrderGradient(preds[j],labels[j]));
                        hess.push_back(mparam.SecondOrderGradient(preds[j],labels[j]));
                    }
            }