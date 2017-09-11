@@ -46,6 +46,14 @@ bool PairValueComparer(const Pair &a, const Pair &b){
     return a.value_ < b.value_;
 }
 
+struct EvalPair : public IRankEvaluator{
+    virtual float Eval( const std::vector<float> &preds,
+                        const std::vector<float> &labels,
+                        const std::vector<int> &group_index  ) const {
+	return 0;
+    }  
+};
+
 /*! \brief Mean Average Precision */
 struct EvalMAP : public IRankEvaluator {
     virtual float Eval( const std::vector<float> &preds,
@@ -130,6 +138,7 @@ namespace rank {
 struct RankEvalSet {
 public:
     inline void AddEval( const char *name ) {
+        if( !strcmp( name, "PAIR" )) evals_.push_back( &pair_);
         if( !strcmp( name, "MAP") ) evals_.push_back( &map_ );
         if( !strcmp( name, "NDCG") ) evals_.push_back( &ndcg_ );
     }
@@ -144,12 +153,13 @@ struct RankEvalSet {
                       const std::vector<float> &labels,
                       const std::vector<int> &group_index ) const {
         for( size_t i = 0; i < evals_.size(); ++ i ) {
-            float res = evals_[i]->Eval( preds, labels );
+            float res = evals_[i]->Eval( preds, labels,group_index );
             fprintf( fo, "\t%s-%s:%f", evname, evals_[i]->Name(), res );
         }
     }
     
 private:
+    EvalPair pair_;
     EvalMAP map_;
     EvalNDCG ndcg_;
     std::vector<const IRankEvaluator*> evals_;