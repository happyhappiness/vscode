                fo.Write( &mparam, sizeof(ModelParam) );
                base_model.SaveModel( fo );	
            } 
            /*! 
             * \brief update the model for one iteration
             * \param iteration iteration number
             */
            inline void UpdateOneIter( int iter ){
                std::vector<float> grad, hess, preds;
                this->Predict( preds, *train_, 0 );
                this->GetGradient( preds, train_->labels, grad, hess );

                std::vector<unsigned> root_index;
                booster::FMatrixS::Image train_image( train_->data );                
                base_model.DoBoost(grad,hess,train_image,root_index);                
            }
            /*! 
             * \brief evaluate the model for specific iteration
             * \param iter iteration number
             * \param fo file to output log
             */            
            inline void EvalOneIter( int iter, FILE *fo = stderr ){
                std::vector<float> preds;
                fprintf( fo, "[%d]", iter );
                int buffer_offset = static_cast<int>( train_->Size() );

                for(size_t i = 0; i < evals_.size();i++){
                    this->Predict(preds, *evals_[i], buffer_offset);
                    this->Eval( fo, evname_[i].c_str(), preds, (*evals_[i]).labels );
                    buffer_offset += static_cast<int>( evals_[i]->Size() );
                }
                fprintf( fo,"\n" );
            }

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
            }

            /*! \brief get the first order and second order gradient, given the transformed predictions and labels */
            inline void GetGradient( const std::vector<float> &preds, 
                                     const std::vector<float> &labels, 
                                     std::vector<float> &grad,
                                     std::vector<float> &hess ){
                grad.clear(); hess.clear();
                for( size_t j = 0; j < preds.size(); j++ ){
                    grad.push_back( mparam.FirstOrderGradient (preds[j],labels[j]) );
                    hess.push_back( mparam.SecondOrderGradient(preds[j],labels[j]) );
                }
            }

        private:
            enum LossType{
                kLinearSquare = 0,
                kLogisticNeglik = 1,
            };

            /*! \brief training parameter for regression */
