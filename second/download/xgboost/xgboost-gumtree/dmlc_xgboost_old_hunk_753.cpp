                name_obj_ = "reg";
            }
            /*!
            * \brief a regression booter associated with training and evaluating data
            * \param train pointer to the training data
            * \param evals array of evaluating data
            * \param evname name of evaluation data, used print statistics
            */
            RegRankBoostLearner(const DMatrix *train,
                                const std::vector<DMatrix *> &evals,
                                const std::vector<std::string> &evname){
                silent = 0;
                this->SetData(train, evals, evname);
            }

            /*!
            * \brief associate regression booster with training and evaluating data
            * \param train pointer to the training data
            * \param evals array of evaluating data
            * \param evname name of evaluation data, used print statistics
            */
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
