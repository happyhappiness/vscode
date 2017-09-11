             * \param iteration iteration number
             */
            inline void UpdateOneIter( int iter ){
                this->PredictBuffer( preds_, *train_, 0 );
                this->GetGradient( preds_, train_->labels, grad_, hess_ );
                std::vector<unsigned> root_index;
                base_model.DoBoost( grad_, hess_, train_->data, root_index );                
            }
            /*! 
             * \brief evaluate the model for specific iteration
             * \param iter iteration number
             * \param fo file to output log
             */            
            inline void EvalOneIter( int iter, FILE *fo = stderr ){
                fprintf( fo, "[%d]", iter );
                int buffer_offset = static_cast<int>( train_->Size() );
                
                for( size_t i = 0; i < evals_.size(); ++i ){
                    std::vector<float> &preds = this->eval_preds_[ i ];                    
                    this->PredictBuffer( preds, *evals_[i], buffer_offset);
                    evaluator_.Eval( fo, evname_[i].c_str(), preds, (*evals_[i]).labels );
                    buffer_offset += static_cast<int>( evals_[i]->Size() );
                }
                fprintf( fo,"\n" );
