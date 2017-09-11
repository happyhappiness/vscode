@@ -16,72 +16,73 @@ namespace xgboost{
     namespace regression{
         /*! \brief evaluator that evaluates the loss metrics */
         struct IEvaluator{
-            /*! 
-             * \brief evaluate a specific metric 
+            /*!
+             * \brief evaluate a specific metric
              * \param preds prediction
              * \param labels label
              */
-            virtual float Eval( const std::vector<float> &preds, 
-                                const std::vector<float> &labels ) const= 0;
+            virtual float Eval(const std::vector<float> &preds,
+            const std::vector<float> &labels) const = 0;
             /*! \return name of metric */
-            virtual const char *Name( void ) const= 0;
+            virtual const char *Name(void) const = 0;
         };
 
         /*! \brief RMSE */
-        struct EvalRMSE : public IEvaluator{            
-            virtual float Eval( const std::vector<float> &preds, 
-                                const std::vector<float> &labels ) const{
-                const unsigned ndata = static_cast<unsigned>( preds.size() );
+        struct EvalRMSE : public IEvaluator{
+            virtual float Eval(const std::vector<float> &preds,
+            const std::vector<float> &labels) const{
+                const unsigned ndata = static_cast<unsigned>(preds.size());
                 float sum = 0.0;
-                #pragma omp parallel for reduction(+:sum) schedule( static )
-                for( unsigned i = 0; i < ndata; ++ i ){
+#pragma omp parallel for reduction(+:sum) schedule( static )
+                for (unsigned i = 0; i < ndata; ++i){
                     float diff = preds[i] - labels[i];
                     sum += diff * diff;
-                } 
-                return sqrtf( sum / ndata );
+                }
+                return sqrtf(sum / ndata);
             }
-            virtual const char *Name( void ) const{
+            virtual const char *Name(void) const{
                 return "rmse";
             }
         };
 
         /*! \brief Error */
-        struct EvalError : public IEvaluator{            
-            virtual float Eval( const std::vector<float> &preds, 
-                                const std::vector<float> &labels ) const{
-                const unsigned ndata = static_cast<unsigned>( preds.size() );
+        struct EvalError : public IEvaluator{
+            virtual float Eval(const std::vector<float> &preds,
+            const std::vector<float> &labels) const{
+                const unsigned ndata = static_cast<unsigned>(preds.size());
                 unsigned nerr = 0;
-                #pragma omp parallel for reduction(+:nerr) schedule( static )
-                for( unsigned i = 0; i < ndata; ++ i ){
-                    if( preds[i] > 0.5f ){
-                        if( labels[i] < 0.5f ) nerr += 1;
-                    }else{
-                        if( labels[i] > 0.5f ) nerr += 1;
+#pragma omp parallel for reduction(+:nerr) schedule( static )
+                for (unsigned i = 0; i < ndata; ++i){
+                    if (preds[i] > 0.5f){
+                        if (labels[i] < 0.5f) nerr += 1;
                     }
-                } 
+                    else{
+                        if (labels[i] > 0.5f) nerr += 1;
+                    }
+                }
                 return static_cast<float>(nerr) / ndata;
             }
-            virtual const char *Name( void ) const{
+            virtual const char *Name(void) const{
                 return "error";
             }
         };
 
 
         /*! \brief Error */
-        struct EvalLogLoss : public IEvaluator{            
-            virtual float Eval( const std::vector<float> &preds, 
-                                const std::vector<float> &labels ) const{
-                const unsigned ndata = static_cast<unsigned>( preds.size() );
+        struct EvalLogLoss : public IEvaluator{
+            virtual float Eval(const std::vector<float> &preds,
+            const std::vector<float> &labels) const{
+                const unsigned ndata = static_cast<unsigned>(preds.size());
                 unsigned nerr = 0;
-                #pragma omp parallel for reduction(+:nerr) schedule( static )
-                for( unsigned i = 0; i < ndata; ++ i ){
+#pragma omp parallel for reduction(+:nerr) schedule( static )
+                for (unsigned i = 0; i < ndata; ++i){
                     const float y = labels[i];
                     const float py = preds[i];
-                    nerr -= y * std::log(py) + (1.0f-y)*std::log(1-py);
-                } 
+                    nerr -= y * std::log(py) + (1.0f - y)*std::log(1 - py);
+                }
                 return static_cast<float>(nerr) / ndata;
             }
-            virtual const char *Name( void ) const{
+            virtual const char *Name(void) const{
                 return "negllik";
             }
         };
@@ -91,28 +92,28 @@ namespace xgboost{
         /*! \brief a set of evaluators */
         struct EvalSet{
         public:
-            inline void AddEval( const char *name ){                
-                if( !strcmp( name, "rmse") ) evals_.push_back( &rmse_ );
-                if( !strcmp( name, "error") ) evals_.push_back( &error_ );
-                if( !strcmp( name, "logloss") ) evals_.push_back( &logloss_ );
+            inline void AddEval(const char *name){
+                if (!strcmp(name, "rmse")) evals_.push_back(&rmse_);
+                if (!strcmp(name, "error")) evals_.push_back(&error_);
+                if (!strcmp(name, "logloss")) evals_.push_back(&logloss_);
             }
-            inline void Init( void ){
-                std::sort( evals_.begin(), evals_.end() );
-                evals_.resize( std::unique( evals_.begin(), evals_.end() ) - evals_.begin() );
+            inline void Init(void){
+                std::sort(evals_.begin(), evals_.end());
+                evals_.resize(std::unique(evals_.begin(), evals_.end()) - evals_.begin());
             }
-            inline void Eval( FILE *fo, const char *evname,
-                              const std::vector<float> &preds, 
-                              const std::vector<float> &labels ) const{
-                for( size_t i = 0; i < evals_.size(); ++ i ){
-                    float res = evals_[i]->Eval( preds, labels );
-                    fprintf( fo, "\t%s-%s:%f", evname, evals_[i]->Name(), res ); 
-                } 
+            inline void Eval(FILE *fo, const char *evname,
+                const std::vector<float> &preds,
+                const std::vector<float> &labels) const{
+                for (size_t i = 0; i < evals_.size(); ++i){
+                    float res = evals_[i]->Eval(preds, labels);
+                    fprintf(fo, "\t%s-%s:%f", evname, evals_[i]->Name(), res);
+                }
             }
         private:
             EvalRMSE  rmse_;
             EvalError error_;
             EvalLogLoss logloss_;
-            std::vector<const IEvaluator*> evals_;  
+            std::vector<const IEvaluator*> evals_;
         };
     };
 };