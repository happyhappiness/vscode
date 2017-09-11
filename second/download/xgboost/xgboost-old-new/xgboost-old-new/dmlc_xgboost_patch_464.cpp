@@ -19,16 +19,18 @@ namespace xgboost{
              * \param name name of the parameter
              * \param val  value of the parameter
              */
-            virtual void SetParam(const char *name, const char *val) = 0;            
+            virtual void SetParam(const char *name, const char *val) = 0;
             /*! 
              * \brief get gradient over each of predictions, given existing information
-             * \param preds prediction of current round
+             * \param preds prediction of current round             
              * \param info information about labels, weights, groups in rank
+             * \param iter current iteration number 
              * \param grad gradient over each preds
              * \param hess second order gradient over each preds
              */
             virtual void GetGradient(const std::vector<float>& preds,  
                                      const DMatrix::Info &info,
+                                     int iter,
                                      std::vector<float> &grad, 
                                      std::vector<float> &hess ) = 0;
             /*! \return the default evaluation metric for the problem */
@@ -104,6 +106,7 @@ namespace xgboost{
     namespace regrank{        
         IObjFunction* CreateObjFunction( const char *name ){
             if( !strcmp("reg", name ) ) return new RegressionObj();
+            if( !strcmp("rank", name ) ) return new PairwiseRankObj();
             utils::Error("unknown objective function type");
             return NULL;
         }