@@ -1,5 +1,5 @@
-#ifndef XGBOOST_UNITY_DATA_H
-#define XGBOOST_UNITY_DATA_H
+#ifndef XGBOOST_DATA_H
+#define XGBOOST_DATA_H
 /*!
  * \file data.h
  * \brief the input data structure for gradient boosting
@@ -8,6 +8,7 @@
 #include <cstdio>
 #include <vector>
 #include <limits>
+#include <climits>
 #include <algorithm>
 #include "utils/io.h"
 #include "utils/utils.h"
@@ -27,7 +28,7 @@ const float rt_eps = 1e-5f;
 const float rt_2eps = rt_eps * 2.0f;
 
 /*! \brief gradient statistics pair usually needed in gradient boosting */
-struct bst_gpair{
+struct bst_gpair {
   /*! \brief gradient statistics */
   bst_float grad;
   /*! \brief second order gradient statistics */
@@ -139,7 +140,7 @@ class FMatrixInterface {
    */
   inline float GetColDensity(size_t cidx) const;
   /*! \brief get the row iterator associated with FMatrix */
-  virtual utils::IIterator<SparseBatch>* RowIterator(void) const = 0;
+  inline utils::IIterator<SparseBatch>* RowIterator(void) const;
 };
 
 /*!
@@ -180,11 +181,13 @@ class FMatrixS : public FMatrixInterface<FMatrixS>{
     }
   };
   /*! \brief constructor */
-  explicit FMatrixS(utils::IIterator<SparseBatch> *base_iter)
-      : iter_(base_iter) {}
+  FMatrixS(void) {
+    iter_ = NULL;
+    num_buffered_row_ = 0;
+  }
   // destructor
-  virtual ~FMatrixS(void) {
-    delete iter_;
+  ~FMatrixS(void) {
+    if (iter_ != NULL) delete iter_;
   }
   /*! \return whether column access is enabled */
   inline bool HaveColAccess(void) const {
@@ -219,15 +222,75 @@ class FMatrixS : public FMatrixInterface<FMatrixS>{
     size_t nmiss = num_buffered_row_ - (col_ptr_[cidx+1] - col_ptr_[cidx]);
     return 1.0f - (static_cast<float>(nmiss)) / num_buffered_row_;
   }
-  virtual void InitColAccess(void) {
+  inline void InitColAccess(size_t max_nrow = ULONG_MAX) {
     if (this->HaveColAccess()) return;
-    const size_t max_nrow = std::numeric_limits<bst_uint>::max();
     this->InitColData(max_nrow);
   }
   /*! \brief get the row iterator associated with FMatrix */
-  virtual utils::IIterator<SparseBatch>* RowIterator(void) const {
+  inline utils::IIterator<SparseBatch>* RowIterator(void) const {
     return iter_;
   }
+  /*! \brief set iterator */
+  inline void set_iter(utils::IIterator<SparseBatch> *iter) {
+    this->iter_ = iter;
+  }
+  /*!
+   * \brief save column access data into stream
+   * \param fo output stream to save to
+   */
+  inline void SaveColAccess(utils::IStream &fo) {
+    fo.Write(&num_buffered_row_, sizeof(num_buffered_row_));
+    if (num_buffered_row_ != 0) {
+      SaveBinary(fo, col_ptr_, col_data_);
+    }
+  }
+  /*!
+   * \brief load column access data from stream
+   * \param fo output stream to load from
+   */
+  inline void LoadColAccess(utils::IStream &fi) {
+    utils::Check(fi.Read(&num_buffered_row_, sizeof(num_buffered_row_)) != 0,
+                 "invalid input file format");
+    if (num_buffered_row_ != 0) {
+      LoadBinary(fi, &col_ptr_, &col_data_);
+    }
+  }
+  /*!
+   * \brief save data to binary stream
+   * \param fo output stream
+   * \param ptr pointer data
+   * \param data data content
+   */
+  inline static void SaveBinary(utils::IStream &fo,
+                                const std::vector<size_t> &ptr,
+                                const std::vector<SparseBatch::Entry> &data) {
+    size_t nrow = ptr.size() - 1;
+    fo.Write(&nrow, sizeof(size_t));
+    fo.Write(&ptr[0], ptr.size() * sizeof(size_t));
+    if (data.size() != 0) {
+      fo.Write(&data[0], data.size() * sizeof(SparseBatch::Entry));
+    }
+  }
+  /*!
+   * \brief load data from binary stream
+   * \param fi input stream
+   * \param out_ptr pointer data
+   * \param out_data data content
+   */
+  inline static void LoadBinary(utils::IStream &fi,
+                                std::vector<size_t> *out_ptr,
+                                std::vector<SparseBatch::Entry> *out_data) {
+    size_t nrow;
+    utils::Check(fi.Read(&nrow, sizeof(size_t)) != 0, "invalid input file format");
+    out_ptr->resize(nrow + 1);
+    utils::Check(fi.Read(&(*out_ptr)[0], out_ptr->size() * sizeof(size_t)) != 0, 
+                  "invalid input file format");
+    out_data->resize(out_ptr->back());
+    if (out_data->size() != 0) {
+      utils::Assert(fi.Read(&(*out_data)[0], out_data->size() * sizeof(SparseBatch::Entry)) != 0, 
+                    "invalid input file format");
+    }
+  }
 
  protected:
   /*!
@@ -278,16 +341,15 @@ class FMatrixS : public FMatrixInterface<FMatrixS>{
                 &col_data_[col_ptr_[i + 1]], Entry::CmpValue);
     }
   }
-
  private:
   // --- data structure used to support InitColAccess --
   utils::IIterator<SparseBatch> *iter_;
   /*! \brief number */
   size_t num_buffered_row_;
   /*! \brief column pointer of CSC format */
-  std::vector<size_t>  col_ptr_;
+  std::vector<size_t> col_ptr_;
   /*! \brief column datas in CSC format */
-  std::vector<SparseBatch::Entry>  col_data_;
+  std::vector<SparseBatch::Entry> col_data_;
 };
 }  // namespace xgboost
-#endif
+#endif  // XGBOOST_DATA_H