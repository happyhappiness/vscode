inline void SetData(const DMatrix *train,
                                const std::vector<DMatrix *> &evals,
                                const std::vector<std::string> &evname){
                this->train_ = train;
                this->evals_ = evals;
                this->evname_ = evname;
                // estimate feature bound
                int num_feature = (int)(train->data.NumCol());
                // assign buffer index
                unsigned buffer_size = static_cast<unsigned>(train->Size());

                for (size_t i = 0; i < evals.size(); ++i){
                    buffer_size += static_cast<unsigned>(evals[i]->Size());
                    num_feature = std::max(num_feature, (int)(evals[i]->data.NumCol()));
                }

                char str_temp[25];
                if (num_feature > mparam.num_feature){
                    mparam.num_feature = num_feature;
                    sprintf(str_temp, "%d", num_feature);
                    base_gbm.SetParam("bst:num_feature", str_temp);
                }

                sprintf(str_temp, "%u", buffer_size);
                base_gbm.SetParam("num_pbuffer", str_temp);
                if (!silent){
                    printf("buffer_size=%u\n", buffer_size);
                }

                // set eval_preds tmp sapce
                this->eval_preds_.resize(evals.size(), std::vector<float>());
            }