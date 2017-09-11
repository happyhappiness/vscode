inline void GetGroupGradient(const std::vector<float> &preds,
                const std::vector<float> &labels,
                const std::vector<int> &group_index,
                std::vector<float> &grad,
                std::vector<float> &hess,
		const std::vector< Triple<float,float,int> > sorted_triple,
		const std::vector<int> index_remap,
		const sample::Pairs& pairs,
	        int group){
	        bool j_better;
                float IDCG, pred_diff, pred_diff_exp, delta;
		float first_order_gradient, second_order_gradient;
                std::vector< Quadruple<float,float,float,float> > map_acc;
		
		if(mparam.loss_type == NDCG){
		  IDCG = GetIDCG(sorted_triple);
		}else if(mparam.loss_type == MAP){
		  map_acc = GetMAPAcc(sorted_triple);
		}
		
		for (int j = group_index[group]; j < group_index[group + 1]; j++){
		    std::vector<int> pair_instance = pairs.GetPairs(j);
                    for (int k = 0; k < pair_instance.size(); k++){
			j_better = labels[j] > labels[pair_instance[k]];
                        if (j_better){
			    switch(mparam.loss_type){
			      case PAIRWISE: delta = 1.0;break;
			      case MAP: delta = GetLambdaMAP(sorted_triple,index_remap[j - group_index[group]],index_remap[pair_instance[k]-group_index[group]],map_acc);break;
			      case NDCG: delta = GetLambdaNDCG(sorted_triple,index_remap[j - group_index[group]],index_remap[pair_instance[k]-group_index[group]],IDCG);break;
			      default: utils::Error("Cannot find the specified loss type");
			    }
		        
			    pred_diff = preds[preds[j] - pair_instance[k]];
			    pred_diff_exp = j_better ? expf(-pred_diff) : expf(pred_diff);
			    first_order_gradient = delta * FirstOrderGradient(pred_diff_exp);
			    second_order_gradient = 2 * delta * SecondOrderGradient(pred_diff_exp);
			    hess[j] += second_order_gradient;
			    grad[j] += first_order_gradient;
			    hess[pair_instance[k]] += second_order_gradient;
			    grad[pair_instance[k]] += -first_order_gradient;
			}
		    }
                }
	    }