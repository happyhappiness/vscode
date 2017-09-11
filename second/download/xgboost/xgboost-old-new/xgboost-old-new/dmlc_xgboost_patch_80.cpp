@@ -1,25 +1,28 @@
-#ifndef XGBOOST_LEARNER_OBJECTIVE_H_
-#define XGBOOST_LEARNER_OBJECTIVE_H_
 /*!
+ * Copyright 2014 by Contributors
  * \file objective.h
  * \brief interface of objective function used for gradient boosting
  * \author Tianqi Chen, Kailong Chen
  */
-#include "dmatrix.h"
+#ifndef XGBOOST_LEARNER_OBJECTIVE_H_
+#define XGBOOST_LEARNER_OBJECTIVE_H_
+
+#include <vector>
+#include "./dmatrix.h"
 
 namespace xgboost {
 namespace learner {
 /*! \brief interface of objective function */
 class IObjFunction{
  public:
   /*! \brief virtual destructor */
-  virtual ~IObjFunction(void){}
+  virtual ~IObjFunction(void) {}
   /*!
    * \brief set parameters from outside
    * \param name name of the parameter
    * \param val value of the parameter
    */
-  virtual void SetParam(const char *name, const char *val) = 0;  
+  virtual void SetParam(const char *name, const char *val) = 0;
   /*!
    * \brief get gradient over each of predictions, given existing information
    * \param preds prediction of current round
@@ -38,9 +41,9 @@ class IObjFunction{
    * \brief transform prediction values, this is only called when Prediction is called
    * \param io_preds prediction values, saves to this vector as well
    */
-  virtual void PredTransform(std::vector<float> *io_preds){}
+  virtual void PredTransform(std::vector<float> *io_preds) {}
   /*!
-   * \brief transform prediction values, this is only called when Eval is called, 
+   * \brief transform prediction values, this is only called when Eval is called,
    *  usually it redirect to PredTransform
    * \param io_preds prediction values, saves to this vector as well
    */
@@ -49,7 +52,7 @@ class IObjFunction{
   }
   /*!
    * \brief transform probability value back to margin
-   * this is used to transform user-set base_score back to margin 
+   * this is used to transform user-set base_score back to margin
    * used by gradient boosting
    * \return transformed value
    */
@@ -77,7 +80,7 @@ inline IObjFunction* CreateObjFunction(const char *name) {
   if (!strcmp("multi:softprob", name)) return new SoftmaxMultiClassObj(1);
   if (!strcmp("rank:pairwise", name )) return new PairwiseRankObj();
   if (!strcmp("rank:ndcg", name)) return new LambdaRankObjNDCG();
-  if (!strcmp("rank:map", name)) return new LambdaRankObjMAP();  
+  if (!strcmp("rank:map", name)) return new LambdaRankObjMAP();
   utils::Error("unknown objective function type: %s", name);
   return NULL;
 }