                fprintf(fo, "\n");
            }

            inline void SetParam(const char *name, const char *val){
                if (!strcmp(name, "eval_metric"))  evaluator_.AddEval(val);
                if (!strcmp(name, "rank:sampler"))  sampler.AssignSampler(atoi(val));
            }
            /*! \brief get the first order and second order gradient, given the transformed predictions and labels */
            inline void GetGradient(const std::vector<float> &preds,
                const std::vector<float> &labels,
                const std::vector<int> &group_index,
                std::vector<float> &grad,
                std::vector<float> &hess) {
                grad.resize(preds.size());
                hess.resize(preds.size());
                bool j_better;
                float pred_diff, pred_diff_exp, first_order_gradient, second_order_gradient;
                for (int i = 0; i < group_index.size() - 1; i++){
		    sample::Pairs pairs = sampler.GenPairs(preds, labels, group_index[i], group_index[i + 1]);
                    for (int j = group_index[i]; j < group_index[i + 1]; j++){
		        std::vector<int> pair_instance = pairs.GetPairs(j);
                        for (int k = 0; k < pair_instance.size(); k++){
			    j_better = labels[j] > labels[pair_instance[k]];
                            if (j_better){
                                pred_diff = preds[preds[j] - pair_instance[k]];
                                pred_diff_exp = j_better ? expf(-pred_diff) : expf(pred_diff);
                                first_order_gradient = FirstOrderGradient(pred_diff_exp);
                                second_order_gradient = 2 * SecondOrderGradient(pred_diff_exp);
                                hess[j] += second_order_gradient;
                                grad[j] += first_order_gradient;
                                hess[pair_instance[k]] += second_order_gradient;
                                grad[pair_instance[k]] += -first_order_gradient;
                            }
                        }
                    }
                }
            }

            inline void UpdateInteract(std::string action) {

            }
        private:
            enum LossType {
                PAIRWISE = 0,
