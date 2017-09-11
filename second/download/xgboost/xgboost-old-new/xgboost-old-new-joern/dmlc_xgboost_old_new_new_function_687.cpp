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