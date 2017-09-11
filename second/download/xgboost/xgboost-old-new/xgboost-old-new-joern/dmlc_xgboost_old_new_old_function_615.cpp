Pairs GenPairs(const std::vector<float> &preds,
			   const std::vector<float> &labels,
			   int start,int end){
	      return sampler_->GenPairs(preds,labels,start,end);
	    }