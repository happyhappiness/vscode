             * \param iteration iteration number
             */
            inline void UpdateOneIter( int iter ){
                std::vector<float> grad, hess, preds;
                this->Predict( preds, *train_, 0 );
                this->GetGradient( preds, train_->labels, grad, hess );

                std::vector<unsigned> root_index;
                base_model.DoBoost(grad,hess,train_->data,root_index);                
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
