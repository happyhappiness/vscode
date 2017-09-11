                }

                Assert(train_param.validation_data_paths.size() == train_param.validation_data_names.size(),
                    "The number of validation paths is not the same as the number of validation data set names");

                //Load Data
                xgboost::regression::DMatrix train;
                printf("%s",train_param.train_path);
                train.LoadText(train_param.train_path);
                std::vector<const xgboost::regression::DMatrix*> evals;
                for(int i = 0; i < train_param.validation_data_paths.size(); i++){
                    xgboost::regression::DMatrix eval;
                    eval.LoadText(train_param.validation_data_paths[i].c_str());
                    evals.push_back(&eval);
