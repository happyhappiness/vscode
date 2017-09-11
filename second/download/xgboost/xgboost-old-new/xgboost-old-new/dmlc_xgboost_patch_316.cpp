@@ -16,7 +16,7 @@ using namespace xgboost::io;
 namespace xgboost {
 namespace wrapper {
 // booster wrapper class
-class Booster: public learner::BoostLearner<FMatrixS> {
+class Booster: public learner::BoostLearner {
  public:
   explicit Booster(const std::vector<DataMatrix*>& mats) {
     this->silent = 1;
@@ -37,15 +37,15 @@ class Booster: public learner::BoostLearner<FMatrixS> {
     for (bst_omp_uint j = 0; j < ndata; ++j) {
       gpair_[j] = bst_gpair(grad[j], hess[j]);
     }
-    gbm_->DoBoost(train.fmat, train.info.info, &gpair_);
+    gbm_->DoBoost(train.fmat(), train.info.info, &gpair_);
   }
   inline void CheckInitModel(void) {
     if (!init_model) {
       this->InitModel(); init_model = true;
     }
   }
   inline void LoadModel(const char *fname) {
-    learner::BoostLearner<FMatrixS>::LoadModel(fname);
+    learner::BoostLearner::LoadModel(fname);
     this->init_model = true;
   }
   inline const char** GetModelDump(const utils::FeatMap& fmap, bool with_stats, bst_ulong *len) {
@@ -135,7 +135,7 @@ extern "C"{
     ret.info.info.num_row = len;
     ret.info.info.num_col = src.info.num_col();
 
-    utils::IIterator<RowBatch> *iter = src.fmat.RowIterator();
+    utils::IIterator<RowBatch> *iter = src.fmat()->RowIterator();
     iter->BeforeFirst();
     utils::Assert(iter->Next(), "slice");
     const RowBatch &batch = iter->Value();