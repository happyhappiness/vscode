@@ -27,6 +27,8 @@ namespace xgboost{
                                const DMatrix::Info &info ) const = 0;
             /*! \return name of metric */
             virtual const char *Name(void) const = 0;
+            /*! \brief virtual destructor */
+            virtual ~IEvaluator(void){}
         };
 
         /*! \brief RMSE */
@@ -104,8 +106,8 @@ namespace xgboost{
                 std::vector<unsigned> tgptr(2,0); tgptr[1] = preds.size();
                 const std::vector<unsigned> &gptr = info.group_ptr.size() == 0 ? tgptr : info.group_ptr;
                 utils::Assert( gptr.back() == preds.size(), "EvalAuc: group structure must match number of prediction" );
-                const unsigned ngroup = static_cast<unsigned>( gptr.size() );
-            
+                const unsigned ngroup = static_cast<unsigned>( gptr.size() - 1 );
+
                 double sum_auc = 0.0f;
                 #pragma omp parallel reduction(+:sum_auc) 
                 {                   