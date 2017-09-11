@@ -6,6 +6,8 @@
 * \author Kailong Chen: chenkl198812@gmail.com, Tianqi Chen: tianqi.tchen@gmail.com
 */
 #include <cmath>
+#include <cstdlib>
+#include <cstring>
 #include "xgboost_regdata.h"
 #include "../booster/xgboost_gbmbase.h"
 #include "../utils/xgboost_utils.h"
@@ -16,22 +18,18 @@ namespace xgboost{
         /*! \brief class for gradient boosted regression */
         class RegBoostLearner{            
         public:
-
-            RegBoostLearner(bool silent = false){
-                this->silent = silent;
-            }
-
+            /*! \brief constructor */
+            RegBoostLearner( void ){}
             /*! 
             * \brief a regression booter associated with training and evaluating data 
             * \param train pointer to the training data
             * \param evals array of evaluating data
             * \param evname name of evaluation data, used print statistics
             */
             RegBoostLearner( const DMatrix *train,
-                std::vector<const DMatrix *> evals,
-                std::vector<std::string> evname, bool silent = false ){
-                    this->silent = silent;
-                    SetData(train,evals,evname);
+                             const std::vector<DMatrix *> &evals,
+                             const std::vector<std::string> &evname ){
+                this->SetData(train,evals,evname);
             }
 
             /*! 
@@ -40,23 +38,22 @@ namespace xgboost{
             * \param evals array of evaluating data
             * \param evname name of evaluation data, used print statistics
             */
-            inline void SetData(const DMatrix *train,
-                std::vector<const DMatrix *> evals,
-                std::vector<std::string> evname){
-                    this->train_ = train;
-                    this->evals_ = evals;
-                    this->evname_ = evname; 
-                    //assign buffer index
-                    int buffer_size = (*train).size();
-                    for(int i = 0; i < evals.size(); i++){
-                        buffer_size += (*evals[i]).size();
-                    }
-                    char str[25];
-                    _itoa(buffer_size,str,10);
-                    base_model.SetParam("num_pbuffer",str);
-                    base_model.SetParam("num_pbuffer",str);
+            inline void SetData( const DMatrix *train,
+                                 const std::vector<DMatrix *> &evals,
+                                 const std::vector<std::string> &evname ){
+                this->train_ = train;
+                this->evals_ = evals;
+                this->evname_ = evname; 
+                //assign buffer index
+                unsigned buffer_size = static_cast<unsigned>( train->Size() );
+                
+                for( size_t i = 0; i < evals.size(); ++ i ){
+                    buffer_size += static_cast<unsigned>( evals[i]->Size() );
+                }
+                char snum_pbuffer[25];
+                printf( snum_pbuffer, "%u", buffer_size );
+                base_model.SetParam( "num_pbuffer",snum_pbuffer );
             }
-
             /*! 
             * \brief set parameters from outside 
             * \param name name of the parameter
@@ -72,17 +69,14 @@ namespace xgboost{
             */
             inline void InitTrainer( void ){
                 base_model.InitTrainer();
-                InitModel();
-                mparam.AdjustBase();
             } 
-
             /*!
             * \brief initialize the current data storage for model, if the model is used first time, call this function
             */
             inline void InitModel( void ){
                 base_model.InitModel();
-            } 
-
+                mparam.AdjustBase();
+            }
             /*! 
             * \brief load model from stream
             * \param fi input stream
@@ -99,57 +93,78 @@ namespace xgboost{
                 fo.Write( &mparam, sizeof(ModelParam) );
                 base_model.SaveModel( fo );	
             } 
-
             /*! 
-            * \brief update the model for one iteration
-            * \param iteration the number of updating iteration 
-            */           
-            inline void UpdateOneIter( int iteration ){
-                std::vector<float> grad,hess,preds;
+             * \brief update the model for one iteration
+             * \param iteration iteration number
+             */
+            inline void UpdateOneIter( int iter ){
+                std::vector<float> grad, hess, preds;
+                this->Predict( preds, *train_, 0 );
+                this->GetGradient( preds, train_->labels, grad, hess );
+
                 std::vector<unsigned> root_index;
-                booster::FMatrixS::Image train_image((*train_).data);
-                Predict(preds,*train_,0);
-                Gradient(preds,(*train_).labels,grad,hess);
-                base_model.DoBoost(grad,hess,train_image,root_index);
-                int buffer_index_offset = (*train_).size();
-                float loss = 0.0;
-                for(int i = 0; i < evals_.size();i++){
-                    Predict(preds, *evals_[i], buffer_index_offset);
-                    loss = mparam.Loss(preds,(*evals_[i]).labels);
-                    if(!silent){
-                        printf("The loss of %s data set in %d the \
-                               iteration is %f",evname_[i].c_str(),&iteration,&loss);
-                    }
-                    buffer_index_offset += (*evals_[i]).size();
-                }
+                booster::FMatrixS::Image train_image( train_->data );                
+                base_model.DoBoost(grad,hess,train_image,root_index);                
+            }
+            /*! 
+             * \brief evaluate the model for specific iteration
+             * \param iter iteration number
+             * \param fo file to output log
+             */            
+            inline void EvalOneIter( int iter, FILE *fo = stderr ){
+                std::vector<float> preds;
+                fprintf( fo, "[%d]", iter );
+                int buffer_offset = static_cast<int>( train_->Size() );
 
+                for(size_t i = 0; i < evals_.size();i++){
+                    this->Predict(preds, *evals_[i], buffer_offset);
+                    this->Eval( fo, evname_[i].c_str(), preds, (*evals_[i]).labels );
+                    buffer_offset += static_cast<int>( evals_[i]->Size() );
+                }
+                fprintf( fo,"\n" );
             }
 
+            /*! \brief get prediction, without buffering */
+            inline void Predict( std::vector<float> &preds, const DMatrix &data ){
+                preds.resize( data.Size() );
+                for( size_t j = 0; j < data.Size(); j++ ){
+                    preds[j] = mparam.PredTransform
+                        ( mparam.base_score + base_model.Predict( data.data[j], -1 ) );
+                }
+            }
+        private:
+            /*! \brief print evaluation results */
+            inline void Eval( FILE *fo, const char *evname,
+                              const std::vector<float> &preds, 
+                              const std::vector<float> &labels ){
+                const float loss = mparam.Loss( preds, labels );
+                fprintf( fo, "\t%s:%f", evname, loss );
+            }
             /*! \brief get the transformed predictions, given data */
-            inline void Predict( std::vector<float> &preds, const DMatrix &data,int buffer_index_offset = 0 ){
-                int data_size = data.size();
-                preds.resize(data_size);
-                for(int j = 0; j < data_size; j++){
-                    preds[j] = mparam.PredTransform(mparam.base_score + 
-                        base_model.Predict(data.data[j],buffer_index_offset + j));
+            inline void Predict( std::vector<float> &preds, const DMatrix &data, unsigned buffer_offset ){
+                preds.resize( data.Size() );
+                for( size_t j = 0; j < data.Size(); j++ ){
+                    preds[j] = mparam.PredTransform
+                        ( mparam.base_score + base_model.Predict( data.data[j], buffer_offset + j ) );
                 }
             }
 
-        private:
-            /*! \brief get the first order and second order gradient, given the transformed predictions and labels*/
-            inline void Gradient(const std::vector<float> &preds, const std::vector<float> &labels, std::vector<float> &grad,
-                std::vector<float> &hess){
-                    grad.clear(); 
-                    hess.clear();
-                    for(int j = 0; j < preds.size(); j++){
-                        grad.push_back(mparam.FirstOrderGradient(preds[j],labels[j]));
-                        hess.push_back(mparam.SecondOrderGradient(preds[j],labels[j]));
-                    }
+            /*! \brief get the first order and second order gradient, given the transformed predictions and labels */
+            inline void GetGradient( const std::vector<float> &preds, 
+                                     const std::vector<float> &labels, 
+                                     std::vector<float> &grad,
+                                     std::vector<float> &hess ){
+                grad.clear(); hess.clear();
+                for( size_t j = 0; j < preds.size(); j++ ){
+                    grad.push_back( mparam.FirstOrderGradient (preds[j],labels[j]) );
+                    hess.push_back( mparam.SecondOrderGradient(preds[j],labels[j]) );
+                }
             }
 
-            enum LOSS_TYPE_LIST{
-                LINEAR_SQUARE,
-                LOGISTIC_NEGLOGLIKELIHOOD,
+        private:
+            enum LossType{
+                kLinearSquare = 0,
+                kLogisticNeglik = 1,
             };
 
             /*! \brief training parameter for regression */
@@ -181,6 +196,20 @@ namespace xgboost{
                         base_score = - logf( 1.0f / base_score - 1.0f );
                     }
                 }
+
+                /*! 
+                * \brief transform the linear sum to prediction 
+                * \param x linear sum of boosting ensemble
+                * \return transformed prediction
+                */
+                inline float PredTransform( float x ){
+                    switch( loss_type ){                        
+                    case kLinearSquare: return x;
+                    case kLogisticNeglik: return 1.0f/(1.0f + expf(-x));
+                    default: utils::Error("unknown loss_type"); return 0.0f;
+                    }
+                }
+
                 /*! 
                 * \brief calculate first order gradient of loss, given transformed prediction
                 * \param predt transformed prediction
@@ -189,7 +218,7 @@ namespace xgboost{
                 */
                 inline float FirstOrderGradient( float predt, float label ) const{
                     switch( loss_type ){                        
-                    case LINEAR_SQUARE: return predt - label;
+                    case kLinearSquare: return predt - label;
                     case 1: return predt - label;
                     default: utils::Error("unknown loss_type"); return 0.0f;
                     }
@@ -202,8 +231,8 @@ namespace xgboost{
                 */
                 inline float SecondOrderGradient( float predt, float label ) const{
                     switch( loss_type ){                        
-                    case LINEAR_SQUARE: return 1.0f;
-                    case LOGISTIC_NEGLOGLIKELIHOOD: return predt * ( 1 - predt );
+                    case kLinearSquare: return 1.0f;
+                    case kLogisticNeglik: return predt * ( 1 - predt );
                     default: utils::Error("unknown loss_type"); return 0.0f;
                     }
                 }
@@ -216,8 +245,8 @@ namespace xgboost{
                 */
                 inline float Loss(const std::vector<float> &preds, const std::vector<float> &labels) const{
                     switch( loss_type ){
-                    case LINEAR_SQUARE: return SquareLoss(preds,labels);
-                    case LOGISTIC_NEGLOGLIKELIHOOD: return NegLoglikelihoodLoss(preds,labels);
+                    case kLinearSquare: return SquareLoss(preds,labels);
+                    case kLogisticNeglik: return NegLoglikelihoodLoss(preds,labels);
                     default: utils::Error("unknown loss_type"); return 0.0f;
                     }
                 }
@@ -230,8 +259,10 @@ namespace xgboost{
                 */
                 inline float SquareLoss(const std::vector<float> &preds, const std::vector<float> &labels) const{
                     float ans = 0.0;
-                    for(int i = 0; i < preds.size(); i++)
-                        ans += pow(preds[i] - labels[i], 2);
+                    for(size_t i = 0; i < preds.size(); i++){
+                        float dif = preds[i] - labels[i];
+                        ans += dif * dif;
+                    }
                     return ans;
                 }
 
@@ -243,34 +274,18 @@ namespace xgboost{
                 */
                 inline float NegLoglikelihoodLoss(const std::vector<float> &preds, const std::vector<float> &labels) const{
                     float ans = 0.0;
-                    for(int i = 0; i < preds.size(); i++)
-                        ans -= labels[i] * log(preds[i]) + ( 1 - labels[i] ) * log(1 - preds[i]);
+                    for(size_t i = 0; i < preds.size(); i++)
+                        ans -= labels[i] * logf(preds[i]) + ( 1 - labels[i] ) * logf(1 - preds[i]);
                     return ans;
                 }
-
-
-                /*! 
-                * \brief transform the linear sum to prediction 
-                * \param x linear sum of boosting ensemble
-                * \return transformed prediction
-                */
-                inline float PredTransform( float x ){
-                    switch( loss_type ){                        
-                    case LINEAR_SQUARE: return x;
-                    case LOGISTIC_NEGLOGLIKELIHOOD: return 1.0f/(1.0f + expf(-x));
-                    default: utils::Error("unknown loss_type"); return 0.0f;
-                    }
-                }
-
-
-            };            
+            };
         private:            
             booster::GBMBaseModel base_model;
             ModelParam   mparam;
             const DMatrix *train_;
-            std::vector<const DMatrix *> evals_;
+            std::vector<DMatrix *> evals_;
             std::vector<std::string> evname_;
-            bool silent;
+            std::vector<unsigned> buffer_index_;
         };
     }
 };