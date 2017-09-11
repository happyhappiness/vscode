@@ -96,8 +96,6 @@ struct SparseBatch {
   };
   /*! \brief batch size */
   size_t size;
-  /*! \brief the offset of rowid of this batch */
-  size_t base_rowid;
   /*! \brief array[size+1], row pointer of each of the elements */
   const size_t *row_ptr;
   /*! \brief array[row_ptr.back()], content of the sparse element */
@@ -107,7 +105,19 @@ struct SparseBatch {
     return Inst(data_ptr + row_ptr[i], static_cast<bst_uint>(row_ptr[i+1] - row_ptr[i]));
   }
 };
-
+/*! \brief read-only row batch, used to access row continuously */
+struct RowBatch : public SparseBatch {
+  /*! \brief the offset of rowid of this batch */
+  size_t base_rowid;
+};
+/*! 
+ * \brief read-only column batch, used to access columns,
+ * the columns are not required to be continuous
+ */
+struct ColBatch : public RowBatch {
+  /*! \brief column index of each columns in the data */
+  bst_uint *col_index;
+};
 /**
  * \brief This is a interface convention via template, defining the way to access features,
  *        column access rule is defined by template, for efficiency purpose,
@@ -168,15 +178,15 @@ class FMatrixInterface {
    */
   inline float GetColDensity(size_t cidx) const;
   /*! \brief get the row iterator associated with FMatrix */
-  inline utils::IIterator<SparseBatch>* RowIterator(void) const;
+  inline utils::IIterator<RowBatch>* RowIterator(void) const;
 };
 
 /*!
  * \brief sparse matrix that support column access, CSC
  */
 class FMatrixS : public FMatrixInterface<FMatrixS>{
  public:
-  typedef SparseBatch::Entry Entry;
+  typedef RowBatch::Entry Entry;
   /*! \brief row iterator */
   struct ColIter{
     const Entry *dptr_, *end_;
@@ -261,12 +271,12 @@ class FMatrixS : public FMatrixInterface<FMatrixS>{
    * \brief get the row iterator associated with FMatrix
    *  this function is not threadsafe, returns iterator stored in FMatrixS
    */
-  inline utils::IIterator<SparseBatch>* RowIterator(void) const {
+  inline utils::IIterator<RowBatch>* RowIterator(void) const {
     iter_->BeforeFirst();
     return iter_;
   }
   /*! \brief set iterator */
-  inline void set_iter(utils::IIterator<SparseBatch> *iter) {
+  inline void set_iter(utils::IIterator<RowBatch> *iter) {
     this->iter_ = iter;
   }
   /*!
@@ -297,12 +307,12 @@ class FMatrixS : public FMatrixInterface<FMatrixS>{
    */
   inline static void SaveBinary(utils::IStream &fo,
                                 const std::vector<size_t> &ptr,
-                                const std::vector<SparseBatch::Entry> &data) {
+                                const std::vector<RowBatch::Entry> &data) {
     size_t nrow = ptr.size() - 1;
     fo.Write(&nrow, sizeof(size_t));
     fo.Write(&ptr[0], ptr.size() * sizeof(size_t));
     if (data.size() != 0) {
-      fo.Write(&data[0], data.size() * sizeof(SparseBatch::Entry));
+      fo.Write(&data[0], data.size() * sizeof(RowBatch::Entry));
     }
   }
   /*!
@@ -313,15 +323,15 @@ class FMatrixS : public FMatrixInterface<FMatrixS>{
    */
   inline static void LoadBinary(utils::IStream &fi,
                                 std::vector<size_t> *out_ptr,
-                                std::vector<SparseBatch::Entry> *out_data) {
+                                std::vector<RowBatch::Entry> *out_data) {
     size_t nrow;
     utils::Check(fi.Read(&nrow, sizeof(size_t)) != 0, "invalid input file format");
     out_ptr->resize(nrow + 1);
     utils::Check(fi.Read(&(*out_ptr)[0], out_ptr->size() * sizeof(size_t)) != 0,
                   "invalid input file format");
     out_data->resize(out_ptr->back());
     if (out_data->size() != 0) {
-      utils::Assert(fi.Read(&(*out_data)[0], out_data->size() * sizeof(SparseBatch::Entry)) != 0,
+      utils::Assert(fi.Read(&(*out_data)[0], out_data->size() * sizeof(RowBatch::Entry)) != 0,
                     "invalid input file format");
     }
   }
@@ -334,16 +344,16 @@ class FMatrixS : public FMatrixInterface<FMatrixS>{
   inline void InitColData(float pkeep) {
     buffered_rowset_.clear();
     // note: this part of code is serial, todo, parallelize this transformer
-    utils::SparseCSRMBuilder<SparseBatch::Entry> builder(col_ptr_, col_data_);
+    utils::SparseCSRMBuilder<RowBatch::Entry> builder(col_ptr_, col_data_);
     builder.InitBudget(0);
     // start working
     iter_->BeforeFirst();
     while (iter_->Next()) {
-      const SparseBatch &batch = iter_->Value();
+      const RowBatch &batch = iter_->Value();
       for (size_t i = 0; i < batch.size; ++i) {
         if (pkeep == 1.0f || random::SampleBinary(pkeep)) {
           buffered_rowset_.push_back(static_cast<bst_uint>(batch.base_rowid+i));
-          SparseBatch::Inst inst = batch[i];
+          RowBatch::Inst inst = batch[i];
           for (bst_uint j = 0; j < inst.length; ++j) {
             builder.AddBudget(inst[j].index);
           }
@@ -355,12 +365,12 @@ class FMatrixS : public FMatrixInterface<FMatrixS>{
     iter_->BeforeFirst();
     size_t ktop = 0;
     while (iter_->Next()) {
-      const SparseBatch &batch = iter_->Value();
+      const RowBatch &batch = iter_->Value();
       for (size_t i = 0; i < batch.size; ++i) {
         if (ktop < buffered_rowset_.size() &&
             buffered_rowset_[ktop] == batch.base_rowid+i) {
           ++ktop;
-          SparseBatch::Inst inst = batch[i];
+          RowBatch::Inst inst = batch[i];
           for (bst_uint j = 0; j < inst.length; ++j) {
             builder.PushElem(inst[j].index,
                              Entry((bst_uint)(batch.base_rowid+i),
@@ -381,13 +391,13 @@ class FMatrixS : public FMatrixInterface<FMatrixS>{
 
  private:
   // --- data structure used to support InitColAccess --
-  utils::IIterator<SparseBatch> *iter_;
+  utils::IIterator<RowBatch> *iter_;
   /*! \brief list of row index that are buffered */
   std::vector<bst_uint> buffered_rowset_;
   /*! \brief column pointer of CSC format */
   std::vector<size_t> col_ptr_;
   /*! \brief column datas in CSC format */
-  std::vector<SparseBatch::Entry> col_data_;
+  std::vector<RowBatch::Entry> col_data_;
 };
 }  // namespace xgboost
 #endif  // XGBOOST_DATA_H