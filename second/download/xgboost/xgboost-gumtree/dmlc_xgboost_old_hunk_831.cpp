	   * \return the generated pairs
	   */
	  virtual Pairs GenPairs(const std::vector<float> &preds,
				const std::vector<float> &labels,
			      int start,int end) = 0;
      };
      
      /*! \brief a set of evaluators */
        struct PairSamplerSet{
        public:
            inline void AssignSampler( const char *name ){                
                if( !strcmp( name, "rmse") ) evals_.push_back( &rmse_ );
                if( !strcmp( name, "error") ) evals_.push_back( &error_ );
                if( !strcmp( name, "logloss") ) evals_.push_back( &logloss_ );
            }
            
            
            Pairs GenPairs(const std::vector<float> &preds,
			   const std::vector<float> &labels,
			   int start,int end){
			
	      
	    }
        private:
            EvalRMSE  rmse_;
            EvalError error_;
            EvalLogLoss logloss_;
            std::vector<const IEvaluator*> evals_;  
        };
    }
  }
