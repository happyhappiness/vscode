inline void AssignSampler( int sampler_index ){                
            
	      switch(sampler_index){
		case BINARY_LINEAR_SAMPLER:sampler_ = &binary_linear_sampler;break;
	
		default:utils::Error("Cannot find the specified sampler");
	      }
	    }