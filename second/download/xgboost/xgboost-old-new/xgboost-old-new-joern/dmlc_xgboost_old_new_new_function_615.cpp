Pairs GenPairs(const std::vector<float> &preds,
                    const std::vector<float> &labels,
                    int start, int end){
		    utils::Assert(sampler_ != NULL,"Not config the sampler yet. Add rank:sampler in the config file\n");
                    return sampler_->GenPairs(preds, labels, start, end);
                }