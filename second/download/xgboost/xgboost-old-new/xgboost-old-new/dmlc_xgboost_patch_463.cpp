@@ -31,6 +31,10 @@ namespace xgboost{
             virtual ~IEvaluator(void){}
         };
 
+      inline static bool CmpFirst( const std::pair<float,unsigned> &a, const std::pair<float,unsigned> &b ){
+        return a.first > b.first;
+      }
+
         /*! \brief RMSE */
         struct EvalRMSE : public IEvaluator{
             virtual float Eval(const std::vector<float> &preds,
@@ -98,9 +102,6 @@ namespace xgboost{
 
         /*! \brief Area under curve, for both classification and rank */
         struct EvalAuc : public IEvaluator{         
-            inline static bool CmpFirst( const std::pair<float,unsigned> &a, const std::pair<float,unsigned> &b ){
-                return a.first > b.first;
-            }
             virtual float Eval( const std::vector<float> &preds, 
                                 const DMatrix::Info &info ) const {
                 std::vector<unsigned> tgptr(2,0); tgptr[1] = preds.size();
@@ -149,6 +150,47 @@ namespace xgboost{
                 return "auc";
             }
         };
+
+        /*! \brief Precison at N, for both classification and rank */
+        struct EvalPrecision : public IEvaluator{         
+            unsigned topn_;
+            std::string name_;
+            EvalPrecision( const char *name ){
+                name_ = name;
+                utils::Assert( sscanf( name, "pre@%u", &topn_ ) );
+            }
+            virtual float Eval( const std::vector<float> &preds, 
+                                const DMatrix::Info &info ) const {
+                const std::vector<unsigned> &gptr = info.group_ptr;
+                utils::Assert( gptr.size()!=0 && gptr.back() == preds.size(), "EvalAuc: group structure must match number of prediction" );
+                const unsigned ngroup = static_cast<unsigned>( gptr.size() - 1 );
+
+                double sum_pre = 0.0f;
+                #pragma omp parallel reduction(+:sum_pre) 
+                {                   
+                    // each thread takes a local rec
+                    std::vector< std::pair<float,unsigned> > rec;
+                    #pragma omp for schedule(static) 
+                    for( unsigned k = 0; k < ngroup; ++ k ){
+                        rec.clear();
+                        for( unsigned j = gptr[k]; j < gptr[k+1]; ++ j ){                        
+                            rec.push_back( std::make_pair( preds[j], (int)info.labels[j] ) );
+                        }
+                        std::sort( rec.begin(), rec.end(), CmpFirst );                    
+                        // calculate Preicsion
+                        unsigned nhit = 0;
+                        for( size_t j = 0; j < rec.size() && j < topn_; ++ j ){
+                            nhit += rec[j].second;
+                        }
+                        sum_pre += ((float)nhit) / topn_;
+                    }
+                }
+                return static_cast<float>(sum_pre) / ngroup;
+            }
+            virtual const char *Name( void ) const{
+                return name_.c_str();
+            }          
+        };
     };
 
     namespace regrank{
@@ -163,6 +205,7 @@ namespace xgboost{
                 if (!strcmp(name, "error"))   evals_.push_back( new EvalError() );
                 if (!strcmp(name, "logloss")) evals_.push_back( new EvalLogLoss() );
                 if (!strcmp( name, "auc"))    evals_.push_back( new EvalAuc() );
+                if (!strncmp( name, "pre@",4)) evals_.push_back( new EvalPrecision(name) );
             }
             ~EvalSet(){
                 for( size_t i = 0; i < evals_.size(); ++ i ){