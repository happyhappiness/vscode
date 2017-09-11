@@ -8,19 +8,21 @@
 #include <cmath>
 #include <cstdlib>
 #include <cstring>
+#include <omp.h>
 #include "xgboost_regdata.h"
+#include "xgboost_regeval.h"
 #include "../booster/xgboost_gbmbase.h"
 #include "../utils/xgboost_utils.h"
 #include "../utils/xgboost_stream.h"
 
 namespace xgboost{
     namespace regression{
         /*! \brief class for gradient boosted regression */
-        class RegBoostLearner{            
+        class RegBoostLearner{
         public:
             /*! \brief constructor */
             RegBoostLearner( void ){
-                silent = 0;            
+                silent = 0; 
             }
             /*! 
             * \brief a regression booter associated with training and evaluating data 
@@ -59,14 +61,17 @@ namespace xgboost{
                     printf( "buffer_size=%u\n", buffer_size );
                 }
                 base_model.SetParam( "num_pbuffer",snum_pbuffer );
+                
+                this->eval_preds_.resize( evals.size(), std::vector<float>() );
             }
             /*! 
             * \brief set parameters from outside 
             * \param name name of the parameter
             * \param val  value of the parameter
             */
             inline void SetParam( const char *name, const char *val ){
-                if( !strcmp( name, "silent") ) silent = atoi( val );
+                if( !strcmp( name, "silent") )  silent = atoi( val );
+                if( !strcmp( name, "eval_metric") )  evaluator_.AddEval( val );
                 mparam.SetParam( name, val );
                 base_model.SetParam( name, val );
             }
@@ -76,6 +81,12 @@ namespace xgboost{
             */
             inline void InitTrainer( void ){
                 base_model.InitTrainer();
+                if( mparam.loss_type == kLogisticClassify ){
+                    evaluator_.AddEval( "error" );
+                }else{
+                    evaluator_.AddEval( "rmse" );
+                }
+                evaluator_.Init();
             } 
             /*!
             * \brief initialize the current data storage for model, if the model is used first time, call this function
@@ -120,26 +131,24 @@ namespace xgboost{
              * \param iteration iteration number
              */
             inline void UpdateOneIter( int iter ){
-                std::vector<float> grad, hess, preds;
-                this->Predict( preds, *train_, 0 );
-                this->GetGradient( preds, train_->labels, grad, hess );
-
+                this->PredictBuffer( preds_, *train_, 0 );
+                this->GetGradient( preds_, train_->labels, grad_, hess_ );
                 std::vector<unsigned> root_index;
-                base_model.DoBoost(grad,hess,train_->data,root_index);                
+                base_model.DoBoost( grad_, hess_, train_->data, root_index );                
             }
             /*! 
              * \brief evaluate the model for specific iteration
              * \param iter iteration number
              * \param fo file to output log
              */            
             inline void EvalOneIter( int iter, FILE *fo = stderr ){
-                std::vector<float> preds;
                 fprintf( fo, "[%d]", iter );
                 int buffer_offset = static_cast<int>( train_->Size() );
-
-                for(size_t i = 0; i < evals_.size();i++){
-                    this->Predict(preds, *evals_[i], buffer_offset);
-                    this->Eval( fo, evname_[i].c_str(), preds, (*evals_[i]).labels );
+                
+                for( size_t i = 0; i < evals_.size(); ++i ){
+                    std::vector<float> &preds = this->eval_preds_[ i ];                    
+                    this->PredictBuffer( preds, *evals_[i], buffer_offset);
+                    evaluator_.Eval( fo, evname_[i].c_str(), preds, (*evals_[i]).labels );
                     buffer_offset += static_cast<int>( evals_[i]->Size() );
                 }
                 fprintf( fo,"\n" );
@@ -148,23 +157,22 @@ namespace xgboost{
             /*! \brief get prediction, without buffering */
             inline void Predict( std::vector<float> &preds, const DMatrix &data ){
                 preds.resize( data.Size() );
-                for( size_t j = 0; j < data.Size(); j++ ){
+
+                const unsigned ndata = static_cast<unsigned>( data.Size() );
+                #pragma omp parallel for schedule( static )
+                for( unsigned j = 0; j < ndata; ++ j ){
                     preds[j] = mparam.PredTransform
                         ( mparam.base_score + base_model.Predict( data.data[j], -1 ) );
                 }
             }
         private:
-            /*! \brief print evaluation results */
-            inline void Eval( FILE *fo, const char *evname,
-                              const std::vector<float> &preds, 
-                              const std::vector<float> &labels ){
-                const float loss = mparam.Loss( preds, labels );
-                fprintf( fo, "\t%s:%f", evname, loss );
-            }
             /*! \brief get the transformed predictions, given data */
-            inline void Predict( std::vector<float> &preds, const DMatrix &data, unsigned buffer_offset ){
+            inline void PredictBuffer( std::vector<float> &preds, const DMatrix &data, unsigned buffer_offset ){
                 preds.resize( data.Size() );
-                for( size_t j = 0; j < data.Size(); j++ ){
+
+                const unsigned ndata = static_cast<unsigned>( data.Size() );
+                #pragma omp parallel for schedule( static )
+                for( unsigned j = 0; j < ndata; ++ j ){                
                     preds[j] = mparam.PredTransform
                         ( mparam.base_score + base_model.Predict( data.data[j], buffer_offset + j ) );
                 }
@@ -175,13 +183,16 @@ namespace xgboost{
                                      const std::vector<float> &labels, 
                                      std::vector<float> &grad,
                                      std::vector<float> &hess ){
-                grad.clear(); hess.clear();
-                for( size_t j = 0; j < preds.size(); j++ ){
-                    grad.push_back( mparam.FirstOrderGradient (preds[j],labels[j]) );
-                    hess.push_back( mparam.SecondOrderGradient(preds[j],labels[j]) );
+                grad.resize( preds.size() ); hess.resize( preds.size() );
+
+                const unsigned ndata = static_cast<unsigned>( preds.size() );
+                #pragma omp parallel for schedule( static )
+                for( unsigned j = 0; j < ndata; ++ j ){
+                    grad[j] = mparam.FirstOrderGradient( preds[j], labels[j] );
+                    hess[j] = mparam.SecondOrderGradient( preds[j], labels[j] );
                 }
             }
-
+            
         private:
             enum LossType{
                 kLinearSquare = 0,
@@ -262,26 +273,26 @@ namespace xgboost{
                 }
 
                 /*!
-                * \brief calculating the loss, given the predictions, labels and the loss type
-                * \param preds the given predictions
-                * \param labels the given labels
-                * \return the specified loss
-                */
+                 * \brief calculating the loss, given the predictions, labels and the loss type
+                 * \param preds the given predictions
+                 * \param labels the given labels
+                 * \return the specified loss
+                 */
                 inline float Loss(const std::vector<float> &preds, const std::vector<float> &labels) const{
                     switch( loss_type ){
                     case kLinearSquare: return SquareLoss(preds,labels);
-                    case kLogisticNeglik: return NegLoglikelihoodLoss(preds,labels);
-                    case kLogisticClassify: return ClassificationError(preds, labels);
+                    case kLogisticNeglik: 
+                    case kLogisticClassify: return NegLoglikelihoodLoss(preds,labels);
                     default: utils::Error("unknown loss_type"); return 0.0f;
                     }
                 }
 
                 /*!
-                * \brief calculating the square loss, given the predictions and labels
-                * \param preds the given predictions
-                * \param labels the given labels
-                * \return the summation of square loss
-                */
+                 * \brief calculating the square loss, given the predictions and labels
+                 * \param preds the given predictions
+                 * \param labels the given labels
+                 * \return the summation of square loss
+                 */
                 inline float SquareLoss(const std::vector<float> &preds, const std::vector<float> &labels) const{
                     float ans = 0.0;
                     for(size_t i = 0; i < preds.size(); i++){
@@ -292,44 +303,30 @@ namespace xgboost{
                 }
 
                 /*!
-                * \brief calculating the square loss, given the predictions and labels
-                * \param preds the given predictions
-                * \param labels the given labels
-                * \return the summation of square loss
-                */
+                 * \brief calculating the square loss, given the predictions and labels
+                 * \param preds the given predictions
+                 * \param labels the given labels
+                 * \return the summation of square loss
+                 */
                 inline float NegLoglikelihoodLoss(const std::vector<float> &preds, const std::vector<float> &labels) const{
                     float ans = 0.0;
                     for(size_t i = 0; i < preds.size(); i++)
                         ans -= labels[i] * logf(preds[i]) + ( 1 - labels[i] ) * logf(1 - preds[i]);
                     return ans;
                 }
-
-                /*!
-                * \brief calculating the ClassificationError  loss, given the predictions and labels
-                * \param preds the given predictions
-                * \param labels the given labels
-                * \return the summation of square loss
-                */
-                inline float ClassificationError(const std::vector<float> &preds, const std::vector<float> &labels) const{
-                    int nerr = 0;
-                    for(size_t i = 0; i < preds.size(); i++){
-                        if( preds[i] > 0.5f ){
-                            if( labels[i] < 0.5f ) nerr ++;
-                        }else{
-                            if( labels[i] > 0.5f ) nerr ++;
-                        }
-                    }
-                    return (float)nerr/preds.size();
-                }                
             };
         private:
             int silent;
+            EvalSet evaluator_;
             booster::GBMBaseModel base_model;
             ModelParam   mparam;
             const DMatrix *train_;
             std::vector<DMatrix *> evals_;
             std::vector<std::string> evname_;
             std::vector<unsigned> buffer_index_;
+        private:
+            std::vector<float> grad_, hess_, preds_;
+            std::vector< std::vector<float> > eval_preds_;
         };
     }
 };