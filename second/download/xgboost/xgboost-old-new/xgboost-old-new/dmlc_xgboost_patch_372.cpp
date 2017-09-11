@@ -9,16 +9,17 @@
 #include <vector>
 #include <limits>
 #include <climits>
+#include <cstring>
 #include <algorithm>
 #include "utils/io.h"
 #include "utils/utils.h"
 #include "utils/iterator.h"
 #include "utils/matrix_csr.h"
 
 namespace xgboost {
-/*! 
- * \brief unsigned interger type used in boost, 
- *        used for feature index and row index 
+/*!
+ * \brief unsigned interger type used in boost,
+ *        used for feature index and row index
  */
 typedef unsigned bst_uint;
 /*! \brief float type, used for storing statistics */
@@ -82,7 +83,7 @@ struct SparseBatch {
 
 /**
  * \brief This is a interface convention via template, defining the way to access features,
- *        column access rule is defined by template, for efficiency purpose, 
+ *        column access rule is defined by template, for efficiency purpose,
  *        row access is defined by iterator of sparse batches
  * \tparam Derived type of actual implementation
  */
@@ -122,9 +123,9 @@ class FMatrixInterface {
    * \return number of columns
    */
   inline size_t NumCol(void) const;
-  /*! 
-   * \brief check if column access is supported, if not, initialize column access 
-   * \param max_rows maximum number of rows allowed in constructor 
+  /*!
+   * \brief check if column access is supported, if not, initialize column access
+   * \param max_rows maximum number of rows allowed in constructor
    */
   inline void InitColAccess(void);
   /*! \return whether column access is enabled */
@@ -133,8 +134,8 @@ class FMatrixInterface {
   inline size_t GetColSize(size_t cidx) const;
   /*!
    * \breif return #entries-in-col / #rows
-   * \param cidx column index 
-   *   this function is used to help speedup, 
+   * \param cidx column index
+   *   this function is used to help speedup,
    *   doese not necessarily implement it if not sure, return 0.0;
    * \return column density
    */
@@ -204,9 +205,9 @@ class FMatrixS : public FMatrixInterface<FMatrixS>{
     return ColIter(&col_data_[col_ptr_[cidx]] - 1,
                    &col_data_[col_ptr_[cidx + 1]] - 1);
   }
-  /*! 
-   * \brief get reversed col iterator, 
-   *   this function will be deprecated at some point 
+  /*!
+   * \brief get reversed col iterator,
+   *   this function will be deprecated at some point
    */
   inline ColBackIter GetReverseSortedCol(size_t cidx) const {
     utils::Assert(cidx < this->NumCol(), "col id exceed bound");
@@ -226,8 +227,8 @@ class FMatrixS : public FMatrixInterface<FMatrixS>{
     if (this->HaveColAccess()) return;
     this->InitColData(max_nrow);
   }
-  /*! 
-   * \brief get the row iterator associated with FMatrix 
+  /*!
+   * \brief get the row iterator associated with FMatrix
    *  this function is not threadsafe, returns iterator stored in FMatrixS
    */
   inline utils::IIterator<SparseBatch>* RowIterator(void) const {
@@ -287,19 +288,19 @@ class FMatrixS : public FMatrixInterface<FMatrixS>{
     size_t nrow;
     utils::Check(fi.Read(&nrow, sizeof(size_t)) != 0, "invalid input file format");
     out_ptr->resize(nrow + 1);
-    utils::Check(fi.Read(&(*out_ptr)[0], out_ptr->size() * sizeof(size_t)) != 0, 
+    utils::Check(fi.Read(&(*out_ptr)[0], out_ptr->size() * sizeof(size_t)) != 0,
                   "invalid input file format");
     out_data->resize(out_ptr->back());
     if (out_data->size() != 0) {
-      utils::Assert(fi.Read(&(*out_data)[0], out_data->size() * sizeof(SparseBatch::Entry)) != 0, 
+      utils::Assert(fi.Read(&(*out_data)[0], out_data->size() * sizeof(SparseBatch::Entry)) != 0,
                     "invalid input file format");
     }
   }
 
  protected:
   /*!
-   * \brief intialize column data 
-   * \param max_nrow maximum number of rows supported 
+   * \brief intialize column data
+   * \param max_nrow maximum number of rows supported
    */
   inline void InitColData(size_t max_nrow) {
     // note: this part of code is serial, todo, parallelize this transformer