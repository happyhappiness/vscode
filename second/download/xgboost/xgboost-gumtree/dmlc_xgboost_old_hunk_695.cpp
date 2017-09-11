                fprintf(fo, "\n");
                fflush(fo);
            }
            /*! \brief get prediction, without buffering */
            inline void Predict(std::vector<float> &preds, const DMatrix &data){
                this->PredictRaw(preds,data);
                obj_->PredTransform( preds );
            }            
        public:
