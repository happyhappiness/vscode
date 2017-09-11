@@ -13,8 +13,6 @@
 #include "../utils/xgboost_omp.h"
 #include "../utils/xgboost_random.h"
 #include "xgboost_regrank_data.h"
-#include <functional>
-#include <tuple>
 
 namespace xgboost{
     namespace regrank{
@@ -36,14 +34,17 @@ namespace xgboost{
         inline static bool CmpFirst(const std::pair<float, unsigned> &a, const std::pair<float, unsigned> &b){
             return a.first > b.first;
         }
+        inline static bool CmpSecond(const std::pair<float, unsigned> &a, const std::pair<float, unsigned> &b){
+            return a.second > b.second;
+        }
 
         /*! \brief RMSE */
         struct EvalRMSE : public IEvaluator{
             virtual float Eval(const std::vector<float> &preds,
-            const DMatrix::Info &info) const {
+                               const DMatrix::Info &info) const {
                 const unsigned ndata = static_cast<unsigned>(preds.size());
                 float sum = 0.0, wsum = 0.0;
-#pragma omp parallel for reduction(+:sum,wsum) schedule( static )
+                #pragma omp parallel for reduction(+:sum,wsum) schedule( static )
                 for (unsigned i = 0; i < ndata; ++i){
                     const float wt = info.GetWeight(i);
                     const float diff = info.labels[i] - preds[i];
@@ -60,10 +61,10 @@ namespace xgboost{
         /*! \brief Error */
         struct EvalLogLoss : public IEvaluator{
             virtual float Eval(const std::vector<float> &preds,
-            const DMatrix::Info &info) const {
+                               const DMatrix::Info &info) const {
                 const unsigned ndata = static_cast<unsigned>(preds.size());
                 float sum = 0.0f, wsum = 0.0f;
-#pragma omp parallel for reduction(+:sum,wsum) schedule( static )
+                #pragma omp parallel for reduction(+:sum,wsum) schedule( static )
                 for (unsigned i = 0; i < ndata; ++i){
                     const float y = info.labels[i];
                     const float py = preds[i];
@@ -81,10 +82,10 @@ namespace xgboost{
         /*! \brief Error */
         struct EvalError : public IEvaluator{
             virtual float Eval(const std::vector<float> &preds,
-            const DMatrix::Info &info) const {
+                               const DMatrix::Info &info) const {
                 const unsigned ndata = static_cast<unsigned>(preds.size());
                 float sum = 0.0f, wsum = 0.0f;
-#pragma omp parallel for reduction(+:sum,wsum) schedule( static )
+                #pragma omp parallel for reduction(+:sum,wsum) schedule( static )
                 for (unsigned i = 0; i < ndata; ++i){
                     const float wt = info.GetWeight(i);
                     if (preds[i] > 0.5f){
@@ -112,11 +113,11 @@ namespace xgboost{
                 const unsigned ngroup = static_cast<unsigned>(gptr.size() - 1);
 
                 double sum_auc = 0.0f;
-#pragma omp parallel reduction(+:sum_auc) 
+                #pragma omp parallel reduction(+:sum_auc) 
                 {
                     // each thread takes a local rec
                     std::vector< std::pair<float, unsigned> > rec;
-#pragma omp for schedule(static) 
+                    #pragma omp for schedule(static) 
                     for (unsigned k = 0; k < ngroup; ++k){
                         rec.clear();
                         for (unsigned j = gptr[k]; j < gptr[k + 1]; ++j){
@@ -153,142 +154,109 @@ namespace xgboost{
             }
         };
 
-        /*! \brief Precison at N, for both classification and rank */
-        struct EvalPrecision : public IEvaluator{
-            unsigned topn_;
-            std::string name_;
-            EvalPrecision(const char *name){
-                name_ = name;
-                utils::Assert(sscanf(name, "pre@%u", &topn_));
-            }
+        /*! \brief Evaluate rank list */          
+        struct EvalRankList : public IEvaluator{
+        public:
             virtual float Eval(const std::vector<float> &preds,
-                const DMatrix::Info &info) const {
+                               const DMatrix::Info &info) const {
                 const std::vector<unsigned> &gptr = info.group_ptr;
                 utils::Assert(gptr.size() != 0 && gptr.back() == preds.size(), "EvalAuc: group structure must match number of prediction");
                 const unsigned ngroup = static_cast<unsigned>(gptr.size() - 1);
 
-                double sum_pre = 0.0f;
-#pragma omp parallel reduction(+:sum_pre) 
+                double sum_metric = 0.0f;
+                #pragma omp parallel reduction(+:sum_metric) 
                 {
                     // each thread takes a local rec
                     std::vector< std::pair<float, unsigned> > rec;
-#pragma omp for schedule(static) 
+                    #pragma omp for schedule(static) 
                     for (unsigned k = 0; k < ngroup; ++k){
                         rec.clear();
                         for (unsigned j = gptr[k]; j < gptr[k + 1]; ++j){
                             rec.push_back(std::make_pair(preds[j], (int)info.labels[j]));
                         }
-                        std::sort(rec.begin(), rec.end(), CmpFirst);
-                        // calculate Preicsion
-                        unsigned nhit = 0;
-                        for (size_t j = 0; j < rec.size() && j < topn_; ++j){
-                            nhit += rec[j].second;
-                        }
-                        sum_pre += ((float)nhit) / topn_;
+                        sum_metric += this->EvalMetric( rec );                        
                     }
                 }
-                return static_cast<float>(sum_pre) / ngroup;
+                return static_cast<float>(sum_metric) / ngroup;
             }
             virtual const char *Name(void) const{
                 return name_.c_str();
             }
-        };
-
-        /*! \brief Normalized DCG */
-        class EvalNDCG : public IEvaluator {
-        public:
-            virtual float Eval(const std::vector<float> &preds,
-                const DMatrix::Info &info) const{
-                if (info.group_ptr.size() <= 1) return 0;
-                float acc = 0;
-                std::vector< std::pair<float, float> > pairs_sort;
-                for (int i = 0; i < info.group_ptr.size() - 1; i++){
-                    for (int j = info.group_ptr[i]; j < info.group_ptr[i + 1]; j++){
-                        pairs_sort.push_back(std::make_pair(preds[j], info.labels[j]));
-                    }
-                    acc += NDCG(pairs_sort);
-                }
-                return acc / (info.group_ptr.size() - 1);
-            }
-
-            static float DCG(const std::vector<float> &labels){
-                float ans = 0.0;
-                for (int i = 0; i < labels.size(); i++){
-                    ans += (pow(2, labels[i]) - 1) / log(i + 2);
+        protected:
+            EvalRankList(const char *name){
+                name_ = name;
+                if( sscanf(name, "%*[^@]@%u", &topn_) != 1 ){
+                    topn_ = UINT_MAX;
                 }
-                return ans;
-            }
-
-            virtual const char *Name(void) const {
-                return "NDCG";
-            }
-
-        private:
-            /*\brief Obtain NDCG given the list of labels and predictions
-            * \param pairs_sort the first field is prediction and the second is label
-            */
-            float NDCG(std::vector< std::pair<float, float> > pairs_sort) const{
-                std::sort(pairs_sort.begin(), pairs_sort.end(), [](std::pair<float, float> a, std::pair<float, float> b){
-                    return std::get<0>(a) > std::get<0>(b);
-                });
-                float dcg = DCG(pairs_sort);
-                std::sort(pairs_sort.begin(), pairs_sort.end(), [](std::pair<float, float> a, std::pair<float, float> b){
-                    return std::get<1>(a) > std::get<1>(b);
-                });
-                float IDCG = DCG(pairs_sort);
-                if (IDCG == 0) return 0;
-                return dcg / IDCG;
             }
-
-            float DCG(std::vector< std::pair<float, float> > pairs_sort) const{
-                std::vector<float> labels;
-                for (int i = 1; i < pairs_sort.size(); i++){
-                    labels.push_back(std::get<1>(pairs_sort[i]));
+            /*! \return evaluation metric, given the pair_sort record, (pred,label) */
+            virtual float EvalMetric( std::vector< std::pair<float, unsigned> > &pair_sort ) const = 0;
+        protected:
+            unsigned topn_;
+            std::string name_;
+        };
+        
+        /*! \brief Precison at N, for both classification and rank */
+        struct EvalPrecision : public EvalRankList{
+        public:
+            EvalPrecision(const char *name):EvalRankList(name){}
+        protected:
+            virtual float EvalMetric( std::vector< std::pair<float, unsigned> > &rec ) const {
+                // calculate Preicsion
+                std::sort(rec.begin(), rec.end(), CmpFirst);
+                unsigned nhit = 0;
+                for (size_t j = 0; j < rec.size() && j < this->topn_; ++j){
+                    nhit += (rec[j].second != 0 );
                 }
-                return DCG(labels);
+                return static_cast<float>( nhit ) / topn_;
             }
         };
 
 
-        /*! \brief Mean Average Precision */
-        class EvalMAP : public IEvaluator {
+        /*! \brief NDCG */
+        struct EvalNDCG : public EvalRankList{
         public:
-            virtual float Eval(const std::vector<float> &preds,
-                const DMatrix::Info &info) const{
-                if (info.group_ptr.size() <= 1) return 0;
-                float acc = 0;
-                std::vector<std::pair<float,float>> pairs_sort;
-                for (int i = 0; i < info.group_ptr.size() - 1; i++){
-                    for (int j = info.group_ptr[i]; j < info.group_ptr[i + 1]; j++){
-                        pairs_sort.push_back(std::make_pair(preds[j], info.labels[j]));
+            EvalNDCG(const char *name):EvalRankList(name){}
+        protected:
+            inline float CalcDCG( const std::vector< std::pair<float,unsigned> > &rec ) const {
+                double sumdcg = 0.0;
+                for( size_t i = 0; i < rec.size() && i < this->topn_; i ++ ){
+                    const unsigned rel = rec[i].second;
+                    if( rel != 0 ){ 
+                        sumdcg += logf( 2.0f ) *((1<<rel)-1) / logf( i + 1 );
                     }
-                    acc += average_precision(pairs_sort);
                 }
-                return acc / (info.group_ptr.size() - 1);
+                return static_cast<float>(sumdcg);
             }
-
-            virtual const char *Name(void) const {
-                return "MAP";
+            virtual float EvalMetric( std::vector< std::pair<float, unsigned> > &rec ) const {
+                std::sort(rec.begin(), rec.end(), CmpFirst);
+                float idcg = this->CalcDCG(rec);
+                std::sort(rec.begin(), rec.end(), CmpSecond);
+                float dcg = this->CalcDCG(rec);
+                if( idcg == 0.0f ) return 0.0f;
+                else return dcg/idcg;
             }
+        };
 
-        private:
-            /*\brief Obtain average precision given the list of labels and predictions
-            * \param pairs_sort the first field is prediction and the second is label
-            */
-            float average_precision(std::vector< std::pair<float,float> > pairs_sort) const{
-                std::sort(pairs_sort.begin(), pairs_sort.end(), [](std::pair<float, float> a, std::pair<float, float> b){
-                    return std::get<0>(a) > std::get<0>(b);
-                });
-                float hits = 0;
-                float average_precision = 0;
-                for (int j = 0; j < pairs_sort.size(); j++){
-                    if (std::get<1>(pairs_sort[j]) == 1){
-                        hits++;
-                        average_precision += hits / (j + 1);
+        /*! \brief Precison at N, for both classification and rank */
+        struct EvalMAP : public EvalRankList{
+        public:
+            EvalMAP(const char *name):EvalRankList(name){}
+        protected:
+            virtual float EvalMetric( std::vector< std::pair<float, unsigned> > &rec ) const {
+                std::sort(rec.begin(), rec.end(), CmpFirst);
+                unsigned nhits = 0;
+                double sumap = 0.0;
+                for( size_t i = 0; i < rec.size(); ++i){
+                    if( rec[i].second != 0 ){
+                        nhits += 1;
+                        if( i < this->topn_ ){
+                            sumap += static_cast<float>(nhits) / (i+1);
+                        }
                     }
                 }
-                if (hits != 0) average_precision /= hits;
-                return average_precision;
+                if (nhits != 0) sumap /= nhits;
+                return static_cast<float>(sumap);                
             }
         };
     };
@@ -306,6 +274,8 @@ namespace xgboost{
                 if (!strcmp(name, "logloss")) evals_.push_back(new EvalLogLoss());
                 if (!strcmp(name, "auc"))    evals_.push_back(new EvalAuc());
                 if (!strncmp(name, "pre@", 4)) evals_.push_back(new EvalPrecision(name));
+                if (!strncmp(name, "map", 3))   evals_.push_back(new EvalMAP(name));
+                if (!strncmp(name, "ndcg", 3))  evals_.push_back(new EvalNDCG(name));
             }
             ~EvalSet(){
                 for (size_t i = 0; i < evals_.size(); ++i){