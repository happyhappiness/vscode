@@ -14,6 +14,7 @@
 #include "utils/io.h"
 #include "utils/utils.h"
 #include "utils/iterator.h"
+#include "utils/random.h"
 #include "utils/matrix_csr.h"
 
 namespace xgboost {
@@ -184,7 +185,6 @@ class FMatrixS : public FMatrixInterface<FMatrixS>{
   /*! \brief constructor */
   FMatrixS(void) {
     iter_ = NULL;
-    num_buffered_row_ = 0;
   }
   // destructor
   ~FMatrixS(void) {
@@ -199,33 +199,37 @@ class FMatrixS : public FMatrixInterface<FMatrixS>{
     utils::Check(this->HaveColAccess(), "NumCol:need column access");
     return col_ptr_.size() - 1;
   }
+  /*! \brief get number of buffered rows */  
+  inline const std::vector<bst_uint> buffered_rowset(void) const {
+    return buffered_rowset_;
+  }
   /*! \brief get col sorted iterator */
   inline ColIter GetSortedCol(size_t cidx) const {
     utils::Assert(cidx < this->NumCol(), "col id exceed bound");
-    return ColIter(&col_data_[col_ptr_[cidx]] - 1,
-                   &col_data_[col_ptr_[cidx + 1]] - 1);
+    return ColIter(&col_data_[0] + col_ptr_[cidx] - 1,
+                   &col_data_[0] + col_ptr_[cidx + 1] - 1);
   }
   /*!
    * \brief get reversed col iterator,
    *   this function will be deprecated at some point
    */
   inline ColBackIter GetReverseSortedCol(size_t cidx) const {
     utils::Assert(cidx < this->NumCol(), "col id exceed bound");
-    return ColBackIter(&col_data_[col_ptr_[cidx + 1]],
-                       &col_data_[col_ptr_[cidx]]);
+    return ColBackIter(&col_data_[0] + col_ptr_[cidx + 1],
+                       &col_data_[0] + col_ptr_[cidx]);
   }
   /*! \brief get col size */
   inline size_t GetColSize(size_t cidx) const {
     return col_ptr_[cidx+1] - col_ptr_[cidx];
   }
   /*! \brief get column density */
   inline float GetColDensity(size_t cidx) const {
-    size_t nmiss = num_buffered_row_ - (col_ptr_[cidx+1] - col_ptr_[cidx]);
-    return 1.0f - (static_cast<float>(nmiss)) / num_buffered_row_;
+    size_t nmiss = buffered_rowset_.size() - (col_ptr_[cidx+1] - col_ptr_[cidx]);
+    return 1.0f - (static_cast<float>(nmiss)) / buffered_rowset_.size();
   }
-  inline void InitColAccess(size_t max_nrow = ULONG_MAX) {
+  inline void InitColAccess(float pkeep = 1.0f) {
     if (this->HaveColAccess()) return;
-    this->InitColData(max_nrow);
+    this->InitColData(pkeep);
   }
   /*!
    * \brief get the row iterator associated with FMatrix
@@ -244,8 +248,8 @@ class FMatrixS : public FMatrixInterface<FMatrixS>{
    * \param fo output stream to save to
    */
   inline void SaveColAccess(utils::IStream &fo) const {
-    fo.Write(&num_buffered_row_, sizeof(num_buffered_row_));
-    if (num_buffered_row_ != 0) {
+    fo.Write(buffered_rowset_);
+    if (buffered_rowset_.size() != 0) {
       SaveBinary(fo, col_ptr_, col_data_);
     }
   }
@@ -254,9 +258,8 @@ class FMatrixS : public FMatrixInterface<FMatrixS>{
    * \param fo output stream to load from
    */
   inline void LoadColAccess(utils::IStream &fi) {
-    utils::Check(fi.Read(&num_buffered_row_, sizeof(num_buffered_row_)) != 0,
-                 "invalid input file format");
-    if (num_buffered_row_ != 0) {
+    utils::Check(fi.Read(&buffered_rowset_), "invalid input file format");
+    if (buffered_rowset_.size() != 0) {
       LoadBinary(fi, &col_ptr_, &col_data_);
     }
   }
@@ -300,39 +303,43 @@ class FMatrixS : public FMatrixInterface<FMatrixS>{
  protected:
   /*!
    * \brief intialize column data
-   * \param max_nrow maximum number of rows supported
+   * \param pkeep probability to keep a row
    */
-  inline void InitColData(size_t max_nrow) {
+  inline void InitColData(float pkeep) {
+    buffered_rowset_.clear();
     // note: this part of code is serial, todo, parallelize this transformer
     utils::SparseCSRMBuilder<SparseBatch::Entry> builder(col_ptr_, col_data_);
     builder.InitBudget(0);
     // start working
     iter_->BeforeFirst();
-    num_buffered_row_ = 0;
     while (iter_->Next()) {
       const SparseBatch &batch = iter_->Value();
-      if (batch.base_rowid >= max_nrow) break;
-      const size_t nbatch = std::min(batch.size, max_nrow - batch.base_rowid);
-      for (size_t i = 0; i < nbatch; ++i, ++num_buffered_row_) {
-        SparseBatch::Inst inst = batch[i];
-        for (bst_uint j = 0; j < inst.length; ++j) {
-          builder.AddBudget(inst[j].findex);
+      for (size_t i = 0; i < batch.size; ++i) {
+        if (pkeep==1.0f || random::SampleBinary(pkeep)) {
+          buffered_rowset_.push_back(batch.base_rowid+i);
+          SparseBatch::Inst inst = batch[i];
+          for (bst_uint j = 0; j < inst.length; ++j) {
+            builder.AddBudget(inst[j].findex);
+          }
         }
       }
     }
     builder.InitStorage();
 
     iter_->BeforeFirst();
+    size_t ktop = 0;
     while (iter_->Next()) {
       const SparseBatch &batch = iter_->Value();
-      if (batch.base_rowid >= max_nrow) break;
-      const size_t nbatch = std::min(batch.size, max_nrow - batch.base_rowid);
-      for (size_t i = 0; i < nbatch; ++i) {
-        SparseBatch::Inst inst = batch[i];
-        for (bst_uint j = 0; j < inst.length; ++j) {
-          builder.PushElem(inst[j].findex,
-                           Entry((bst_uint)(batch.base_rowid+i),
-                                 inst[j].fvalue));
+      for (size_t i = 0; i < batch.size; ++i) {
+        if (ktop < buffered_rowset_.size() && 
+            buffered_rowset_[ktop] == batch.base_rowid+i) {
+          ++ ktop;
+          SparseBatch::Inst inst = batch[i];
+          for (bst_uint j = 0; j < inst.length; ++j) {
+            builder.PushElem(inst[j].findex,
+                             Entry((bst_uint)(batch.base_rowid+i),
+                                   inst[j].fvalue));
+          }
         }
       }
     }
@@ -349,8 +356,8 @@ class FMatrixS : public FMatrixInterface<FMatrixS>{
  private:
   // --- data structure used to support InitColAccess --
   utils::IIterator<SparseBatch> *iter_;
-  /*! \brief number */
-  size_t num_buffered_row_;
+  /*! \brief list of row index that are buffered */
+  std::vector<bst_uint> buffered_rowset_;
   /*! \brief column pointer of CSC format */
   std::vector<size_t> col_ptr_;
   /*! \brief column datas in CSC format */