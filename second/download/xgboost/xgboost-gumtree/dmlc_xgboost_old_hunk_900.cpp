                fo.Write( &mparam, sizeof(ModelParam) );
                base_model.SaveModel( fo );	
            } 

            /*! 
            * \brief update the model for one iteration
            * \param iteration the number of updating iteration 
            */           
            inline void UpdateOneIter( int iteration ){
                std::vector<float> grad,hess,preds;
                std::vector<unsigned> root_index;
                booster::FMatrixS::Image train_image((*train_).data);
                Predict(preds,*train_,0);
                Gradient(preds,(*train_).labels,grad,hess);
                base_model.DoBoost(grad,hess,train_image,root_index);
                int buffer_index_offset = (*train_).size();
                float loss = 0.0;
                for(int i = 0; i < evals_.size();i++){
                    Predict(preds, *evals_[i], buffer_index_offset);
                    loss = mparam.Loss(preds,(*evals_[i]).labels);
                    if(!silent){
                        printf("The loss of %s data set in %d the \
                               iteration is %f",evname_[i].c_str(),&iteration,&loss);
                    }
                    buffer_index_offset += (*evals_[i]).size();
                }

            }

            /*! \brief get the transformed predictions, given data */
            inline void Predict( std::vector<float> &preds, const DMatrix &data,int buffer_index_offset = 0 ){
                int data_size = data.size();
                preds.resize(data_size);
                for(int j = 0; j < data_size; j++){
                    preds[j] = mparam.PredTransform(mparam.base_score + 
                        base_model.Predict(data.data[j],buffer_index_offset + j));
                }
            }

        private:
            /*! \brief get the first order and second order gradient, given the transformed predictions and labels*/
            inline void Gradient(const std::vector<float> &preds, const std::vector<float> &labels, std::vector<float> &grad,
                std::vector<float> &hess){
                    grad.clear(); 
                    hess.clear();
                    for(int j = 0; j < preds.size(); j++){
                        grad.push_back(mparam.FirstOrderGradient(preds[j],labels[j]));
                        hess.push_back(mparam.SecondOrderGradient(preds[j],labels[j]));
                    }
            }

            enum LOSS_TYPE_LIST{
                LINEAR_SQUARE,
                LOGISTIC_NEGLOGLIKELIHOOD,
            };

            /*! \brief training parameter for regression */
