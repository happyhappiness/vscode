	   * \return the generated pairs
	   */
	  virtual Pairs GenPairs(const std::vector<float> &preds,
				 const std::vector<float> &labels,
			         int start,int end) = 0;
		
      };
      
      enum{
	  BINARY_LINEAR_SAMPLER
      };
      
      /*! \brief A simple pair sampler when the rank relevence scale is binary
       *         for each positive instance, we will pick a negative
       *         instance and add in a pair. When using binary linear sampler, 
       *         we should guarantee the labels are 0 or 1
       */
      struct BinaryLinearSampler:public IPairSampler{
	virtual Pairs GenPairs(const std::vector<float> &preds,
			       const std::vector<float> &labels,
			       int start,int end) {
  	    Pairs pairs(start,end);
	    int pointer = 0, last_pointer = 0,index = start, interval = end - start;
	    for(int i = start; i < end; i++){
	      if(labels[i] == 1){
		while(true){
		  index = (++pointer) % interval + start;
		  if(labels[index] == 0) break;
		  if(pointer - last_pointer > interval) return pairs;
		} 
		pairs.push(i,index);
		pairs.push(index,i);
		last_pointer = pointer;
	      }
	    }
	    return pairs; 
	}	
      };
      
      
      /*! \brief Pair Sampler Wrapper*/
        struct PairSamplerWrapper{
        public:
            inline void AssignSampler( int sampler_index ){                
            
	      switch(sampler_index){
		case BINARY_LINEAR_SAMPLER:sampler_ = &binary_linear_sampler;break;
	
		default:utils::Error("Cannot find the specified sampler");
	      }
	    }
            
            Pairs GenPairs(const std::vector<float> &preds,
			   const std::vector<float> &labels,
			   int start,int end){
	      return sampler_.GenPairs(preds,labels,start,end);
	    }
        private:
	    BinaryLinearSampler binary_linear_sampler;
	    IPairSampler *sampler_; 
        };
    }
  }
