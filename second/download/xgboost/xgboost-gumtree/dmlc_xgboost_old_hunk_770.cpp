                    buffer_offset += static_cast<int>(evals_[i]->Size());
                }
                fprintf(fo, "\n");
            }
            /*! \brief get prediction, without buffering */
            inline void Predict(std::vector<float> &preds, const DMatrix &data){
