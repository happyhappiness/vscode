@@ -94,20 +94,20 @@ class RankBoostLearner {
     inline void InitTrainer( void ) {
         base_gbm.InitTrainer();
         if( mparam.loss_type == PAIRWISE) {
-            evaluator_.AddEval( "pairwise" );
+            evaluator_.AddEval( "PAIR" );
         } else if( mparam.loss_type == MAP) {
             evaluator_.AddEval( "MAP" );
         } else {
             evaluator_.AddEval( "NDCG" );
         }
         evaluator_.Init();
+	sampler.AssignSampler(mparam.sampler_type);
     }
     /*!
     * \brief initialize the current data storage for model, if the model is used first time, call this function
     */
     inline void InitModel( void ) {
         base_gbm.InitModel();
-        mparam.AdjustBase();
     }
     /*!
     * \brief load model from stream
@@ -134,6 +134,7 @@ class RankBoostLearner {
     inline void DumpPath( FILE *fo, const RMatrix &data ) {
         base_gbm.DumpPath( fo, data.data );
     }
+    
     /*!
     * \brief save model to stream
     * \param fo output stream
@@ -142,6 +143,7 @@ class RankBoostLearner {
         base_gbm.SaveModel( fo );
         fo.Write( &mparam, sizeof(ModelParam) );
     }
+    
     /*!
      * \brief update the model for one iteration
      * \param iteration iteration number
@@ -177,7 +179,7 @@ class RankBoostLearner {
         const unsigned ndata = static_cast<unsigned>( data.Size() );
         #pragma omp parallel for schedule( static )
         for( unsigned j = 0; j < ndata; ++ j ) {
-            preds[j] = mparam.base_score + base_gbm.Predict( data.data, j, -1 );
+            preds[j] = base_gbm.Predict( data.data, j, -1 );
         }
     }
     
@@ -219,7 +221,7 @@ class RankBoostLearner {
         const unsigned ndata = static_cast<unsigned>( data.Size() );
         #pragma omp parallel for schedule( static )
         for( unsigned j = 0; j < ndata; ++ j ) {
-            preds[j] = mparam.base_score + base_gbm.InteractPredict( data.data, j, buffer_offset + j );
+            preds[j] = base_gbm.InteractPredict( data.data, j, buffer_offset + j );
         }
     }
     /*! \brief repredict trial */
@@ -238,7 +240,7 @@ class RankBoostLearner {
         const unsigned ndata = static_cast<unsigned>( data.Size() );
         #pragma omp parallel for schedule( static )
         for( unsigned j = 0; j < ndata; ++ j ) {
-            preds[j] = mparam.base_score + base_gbm.Predict( data.data, j, buffer_offset + j );
+            preds[j] = base_gbm.Predict( data.data, j, buffer_offset + j );
       
 	}
     }
@@ -254,23 +256,23 @@ class RankBoostLearner {
 	bool j_better;
 	float pred_diff,pred_diff_exp,first_order_gradient,second_order_gradient;
 	for(int i = 0; i < group_index.size() - 1; i++){
-	  xgboost::rank::sample::PairSamplerSet sampler;
-	  xgboost::rank::sample::Pairs pairs = sampler.GenPairs(preds,labels,group_index[i],group_index[i+1]);
-	  for(int j = group_index[i]; j < group_index[i+1]; j++){
-	    std::vector<int> pair_instance = pairs.GetPairs(j);
-	    j_better =  labels[j] > labels[pair_instance[k]];
-	    if(j_better){
+	  
+	  sample::Pairs pairs = sampler.GenPairs(preds,labels,group_index[i],group_index[i+1]);
+	  for(int j = group_index[i]; j < group_index[i + 1]; j++){
+	      std::vector<int> pair_instance = pairs.GetPairs(j);
 	      for(int k = 0; k < pair_instance.size(); k++){
-	         pred_diff = preds[preds[j] - pair_instance[k]];
-	         pred_diff_exp =  j_better? expf(-pred_diff):expf(pred_diff);
-                 first_order_gradient = mparam.FirstOrderGradient(pred_diff_exp);	    
-	         second_order_gradient = 2 * mparam.SecondOrderGradient(pred_diff_exp);	    
-	         hess[j] += second_order_gradient;
-	         grad[j] += first_order_gradient;
-	         hess[pair_instance[k]] += second_order_gradient;
-		 grad[pair_instance[k]] += -first_order_gradient;
+		 j_better =  labels[j] > labels[pair_instance[k]];
+	         if(j_better){
+	   	     pred_diff = preds[preds[j] - pair_instance[k]];
+		     pred_diff_exp =  j_better? expf(-pred_diff):expf(pred_diff);
+                     first_order_gradient = mparam.FirstOrderGradient(pred_diff_exp);	    
+	             second_order_gradient = 2 * mparam.SecondOrderGradient(pred_diff_exp);	    
+	             hess[j] += second_order_gradient;
+	             grad[j] += first_order_gradient;
+	             hess[pair_instance[k]] += second_order_gradient;
+		     grad[pair_instance[k]] += -first_order_gradient;
+	         }
 	      }
-	    }
 	  }
 	}
       
@@ -282,20 +284,19 @@ class RankBoostLearner {
         MAP = 1,
         NDCG = 2
     };
-
+    
     /*! \brief training parameter for regression */
     struct ModelParam {
-        /* \brief global bias */
-        float base_score;
         /* \brief type of loss function */
         int loss_type;
         /* \brief number of features  */
         int num_feature;
         /*! \brief reserved field */
         int reserved[ 16 ];
+	/*! \brief sampler type */
+	int sampler_type;
         /*! \brief constructor */
         ModelParam( void ) {
-            base_score = 0.5f;
             loss_type  = 0;
             num_feature = 0;
             memset( reserved, 0, sizeof( reserved ) );
@@ -306,36 +307,11 @@ class RankBoostLearner {
         * \param val  value of the parameter
         */
         inline void SetParam( const char *name, const char *val ) {
-            if( !strcmp("base_score", name ) )  base_score = (float)atof( val );
             if( !strcmp("loss_type", name ) )   loss_type = atoi( val );
             if( !strcmp("bst:num_feature", name ) ) num_feature = atoi( val );
-        }
-        /*!
-        * \brief adjust base_score
-        */
-        inline void AdjustBase( void ) {
-            if( loss_type == 1 || loss_type == 2 ) {
-                utils::Assert( base_score > 0.0f && base_score < 1.0f, "sigmoid range constrain" );
-                base_score = - logf( 1.0f / base_score - 1.0f );
-            }
+	    if( !strcmp("rank:sampler",name)) sampler = atoi( val );
         }
 
-        /*!
-        * \brief transform the linear sum to prediction
-        * \param x linear sum of boosting ensemble
-        * \return transformed prediction
-        */
-        inline float PredTransform( float x ) {
-            switch( loss_type ) {
-            case PAIRWISE:
-            case MAP:
-            case NDCG:
-                return 1.0f/(1.0f + expf(-x));
-            default:
-                utils::Error("unknown loss_type");
-                return 0.0f;
-            }
-        }
 
         /*!
         * \brief calculate first order gradient of pairwise loss function(f(x) = ln(1+exp(-x)), 
@@ -358,57 +334,11 @@ class RankBoostLearner {
         inline float SecondOrderGradient( float pred_diff_exp ) const {
             return pred_diff_exp/pow(1 + pred_diff_exp,2);
         }
-
-        /*!
-         * \brief calculating the loss, given the predictions, labels and the loss type
-         * \param preds the given predictions
-         * \param labels the given labels
-         * \return the specified loss
-         */
-        inline float Loss(const std::vector<float> &preds, const std::vector<float> &labels) const {
-            switch( loss_type ) {
-            case kLinearSquare:
-                return SquareLoss(preds,labels);
-            case kLogisticNeglik:
-            case kLogisticClassify:
-                return NegLoglikelihoodLoss(preds,labels);
-            default:
-                utils::Error("unknown loss_type");
-                return 0.0f;
-            }
-        }
-
-        /*!
-         * \brief calculating the square loss, given the predictions and labels
-         * \param preds the given predictions
-         * \param labels the given labels
-         * \return the summation of square loss
-         */
-        inline float SquareLoss(const std::vector<float> &preds, const std::vector<float> &labels) const {
-            float ans = 0.0;
-            for(size_t i = 0; i < preds.size(); i++) {
-                float dif = preds[i] - labels[i];
-                ans += dif * dif;
-            }
-            return ans;
-        }
-
-        /*!
-         * \brief calculating the square loss, given the predictions and labels
-         * \param preds the given predictions
-         * \param labels the given labels
-         * \return the summation of square loss
-         */
-        inline float NegLoglikelihoodLoss(const std::vector<float> &preds, const std::vector<float> &labels) const {
-            float ans = 0.0;
-            for(size_t i = 0; i < preds.size(); i++)
-                ans -= labels[i] * logf(preds[i]) + ( 1 - labels[i] ) * logf(1 - preds[i]);
-            return ans;
-        }
     };
 private:
     int silent;
     RankEvalSet evaluator_;
+    sample::PairSamplerWrapper sampler;
     booster::GBMBase base_gbm;
     ModelParam   mparam;
     const RMatrix *train_;