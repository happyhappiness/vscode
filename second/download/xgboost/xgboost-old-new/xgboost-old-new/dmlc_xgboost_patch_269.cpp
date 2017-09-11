@@ -7,16 +7,8 @@
  */
 #include <cstdio>
 #include <vector>
-#include <limits>
-#include <climits>
-#include <cstring>
-#include <algorithm>
-#include "utils/io.h"
-#include "utils/omp.h"
 #include "utils/utils.h"
 #include "utils/iterator.h"
-#include "utils/random.h"
-#include "utils/matrix_csr.h"
 
 namespace xgboost {
 /*!
@@ -70,12 +62,12 @@ struct SparseBatch {
   /*! \brief an entry of sparse vector */
   struct Entry {
     /*! \brief feature index */
-    bst_uint findex;
+    bst_uint index;
     /*! \brief feature value */
     bst_float fvalue;
     // default constructor
     Entry(void) {}
-    Entry(bst_uint findex, bst_float fvalue) : findex(findex), fvalue(fvalue) {}
+    Entry(bst_uint index, bst_float fvalue) : index(index), fvalue(fvalue) {}
     /*! \brief reversely compare feature values */
     inline static bool CmpValue(const Entry &a, const Entry &b) {
       return a.fvalue < b.fvalue;
@@ -86,7 +78,7 @@ struct SparseBatch {
     /*! \brief pointer to the elements*/
     const Entry *data;
     /*! \brief length of the instance */
-    const bst_uint length;
+    bst_uint length;
     /*! \brief constructor */
     Inst(const Entry *data, bst_uint length) : data(data), length(length) {}
     /*! \brief get i-th pair in the sparse vector*/
@@ -96,298 +88,72 @@ struct SparseBatch {
   };
   /*! \brief batch size */
   size_t size;
+};
+/*! \brief read-only row batch, used to access row continuously */
+struct RowBatch : public SparseBatch {
   /*! \brief the offset of rowid of this batch */
   size_t base_rowid;
   /*! \brief array[size+1], row pointer of each of the elements */
-  const size_t *row_ptr;
-  /*! \brief array[row_ptr.back()], content of the sparse element */
+  const size_t *ind_ptr;
+  /*! \brief array[ind_ptr.back()], content of the sparse element */
   const Entry *data_ptr;
   /*! \brief get i-th row from the batch */
   inline Inst operator[](size_t i) const {
-    return Inst(data_ptr + row_ptr[i], static_cast<bst_uint>(row_ptr[i+1] - row_ptr[i]));
+    return Inst(data_ptr + ind_ptr[i], static_cast<bst_uint>(ind_ptr[i+1] - ind_ptr[i]));
+  }
+};
+/*! 
+ * \brief read-only column batch, used to access columns,
+ * the columns are not required to be continuous
+ */
+struct ColBatch : public SparseBatch {
+  /*! \brief column index of each columns in the data */
+  const bst_uint *col_index;
+  /*! \brief pointer to the column data */
+  const Inst *col_data;
+  /*! \brief get i-th row from the batch */
+  inline Inst operator[](size_t i) const {
+    return col_data[i];
   }
 };
-
 /**
- * \brief This is a interface convention via template, defining the way to access features,
- *        column access rule is defined by template, for efficiency purpose,
- *        row access is defined by iterator of sparse batches
- * \tparam Derived type of actual implementation
+ * \brief interface of feature matrix, needed for tree construction
+ *  this interface defines two way to access features,
+ *  row access is defined by iterator of RowBatch
+ *  col access is optional, checked by HaveColAccess, and defined by iterator of ColBatch
  */
-template<typename Derived>
-class FMatrixInterface {
- public:
-  /*! \brief example iterator over one column */
-  struct ColIter{
-    /*!
-     * \brief move to next position
-     * \return whether there is element in next position
-     */
-    inline bool Next(void);
-    /*! \return row index of current position  */
-    inline bst_uint rindex(void) const;
-    /*! \return feature value in current position */
-    inline bst_float fvalue(void) const;
-  };
-  /*! \brief backward iterator over column */
-  struct ColBackIter : public ColIter {};
+class IFMatrix {
  public:
-  // column access is needed by some of tree construction algorithms
-  /*!
-   * \brief get column iterator, the columns must be sorted by feature value
-   * \param cidx column index
-   * \return column iterator
-   */
-  inline ColIter GetSortedCol(size_t cidx) const;
-  /*!
-   * \brief get column backward iterator, starts from biggest fvalue, and iterator back
-   * \param cidx column index
-   * \return reverse column iterator
-   */
-  inline ColBackIter GetReverseSortedCol(size_t cidx) const;
+  // the interface only need to ganrantee row iter
+  // column iter is active, when ColIterator is called, row_iter can be disabled
+  /*! \brief get the row iterator associated with FMatrix */
+  virtual utils::IIterator<RowBatch> *RowIterator(void) = 0;
+  /*!\brief get column iterator */
+  virtual utils::IIterator<ColBatch> *ColIterator(void) = 0;
   /*!
-   * \brief get number of columns
-   * \return number of columns
+   * \brief get the column iterator associated with FMatrix with subset of column features 
+   * \param fset is the list of column index set that must be contained in the returning Column iterator
+   * \return the column iterator, initialized so that it reads the elements in fset
    */
-  inline size_t NumCol(void) const;
+  virtual utils::IIterator<ColBatch> *ColIterator(const std::vector<bst_uint> &fset) = 0;
   /*!
    * \brief check if column access is supported, if not, initialize column access
-   * \param max_rows maximum number of rows allowed in constructor
-   */
-  inline void InitColAccess(void);
-  /*! \return whether column access is enabled */
-  inline bool HaveColAccess(void) const;
-  /*! \breif return #entries-in-col */
-  inline size_t GetColSize(size_t cidx) const;
-  /*!
-   * \breif return #entries-in-col / #rows
-   * \param cidx column index
-   *   this function is used to help speedup,
-   *   doese not necessarily implement it if not sure, return 0.0;
-   * \return column density
+   * \param subsample subsample ratio when generating column access
    */
-  inline float GetColDensity(size_t cidx) const;
-  /*! \brief get the row iterator associated with FMatrix */
-  inline utils::IIterator<SparseBatch>* RowIterator(void) const;
-};
-
-/*!
- * \brief sparse matrix that support column access, CSC
- */
-class FMatrixS : public FMatrixInterface<FMatrixS>{
- public:
-  typedef SparseBatch::Entry Entry;
-  /*! \brief row iterator */
-  struct ColIter{
-    const Entry *dptr_, *end_;
-    ColIter(const Entry* begin, const Entry* end)
-        :dptr_(begin), end_(end) {}
-    inline bool Next(void) {
-      if (dptr_ == end_) {
-        return false;
-      } else {
-        ++dptr_; return true;
-      }
-    }
-    inline bst_uint rindex(void) const {
-      return dptr_->findex;
-    }
-    inline bst_float fvalue(void) const {
-      return dptr_->fvalue;
-    }
-  };
-  /*! \brief reverse column iterator */
-  struct ColBackIter : public ColIter {
-    ColBackIter(const Entry* dptr, const Entry* end) : ColIter(dptr, end) {}
-    // shadows ColIter::Next
-    inline bool Next(void) {
-      if (dptr_ == end_) {
-        return false;
-      } else {
-        --dptr_; return true;
-      }
-    }
-  };
-  /*! \brief constructor */
-  FMatrixS(void) {
-    iter_ = NULL;
-  }
-  // destructor
-  ~FMatrixS(void) {
-    if (iter_ != NULL) delete iter_;
-  }
+  virtual void InitColAccess(float subsample) = 0;
+  // the following are column meta data, should be able to answer them fast
   /*! \return whether column access is enabled */
-  inline bool HaveColAccess(void) const {
-    return col_ptr_.size() != 0;
-  }
-  /*! \brief get number of colmuns */
-  inline size_t NumCol(void) const {
-    utils::Check(this->HaveColAccess(), "NumCol:need column access");
-    return col_ptr_.size() - 1;
-  }
-  /*! \brief get number of buffered rows */
-  inline const std::vector<bst_uint> buffered_rowset(void) const {
-    return buffered_rowset_;
-  }
-  /*! \brief get col sorted iterator */
-  inline ColIter GetSortedCol(size_t cidx) const {
-    utils::Assert(cidx < this->NumCol(), "col id exceed bound");
-    return ColIter(&col_data_[0] + col_ptr_[cidx] - 1,
-                   &col_data_[0] + col_ptr_[cidx + 1] - 1);
-  }
-  /*!
-   * \brief get reversed col iterator,
-   *   this function will be deprecated at some point
-   */
-  inline ColBackIter GetReverseSortedCol(size_t cidx) const {
-    utils::Assert(cidx < this->NumCol(), "col id exceed bound");
-    return ColBackIter(&col_data_[0] + col_ptr_[cidx + 1],
-                       &col_data_[0] + col_ptr_[cidx]);
-  }
-  /*! \brief get col size */
-  inline size_t GetColSize(size_t cidx) const {
-    return col_ptr_[cidx+1] - col_ptr_[cidx];
-  }
-  /*! \brief get column density */
-  inline float GetColDensity(size_t cidx) const {
-    size_t nmiss = buffered_rowset_.size() - (col_ptr_[cidx+1] - col_ptr_[cidx]);
-    return 1.0f - (static_cast<float>(nmiss)) / buffered_rowset_.size();
-  }
-  inline void InitColAccess(float pkeep = 1.0f) {
-    if (this->HaveColAccess()) return;
-    this->InitColData(pkeep);
-  }
-  /*!
-   * \brief get the row iterator associated with FMatrix
-   *  this function is not threadsafe, returns iterator stored in FMatrixS
-   */
-  inline utils::IIterator<SparseBatch>* RowIterator(void) const {
-    iter_->BeforeFirst();
-    return iter_;
-  }
-  /*! \brief set iterator */
-  inline void set_iter(utils::IIterator<SparseBatch> *iter) {
-    this->iter_ = iter;
-  }
-  /*!
-   * \brief save column access data into stream
-   * \param fo output stream to save to
-   */
-  inline void SaveColAccess(utils::IStream &fo) const {
-    fo.Write(buffered_rowset_);
-    if (buffered_rowset_.size() != 0) {
-      SaveBinary(fo, col_ptr_, col_data_);
-    }
-  }
-  /*!
-   * \brief load column access data from stream
-   * \param fo output stream to load from
-   */
-  inline void LoadColAccess(utils::IStream &fi) {
-    utils::Check(fi.Read(&buffered_rowset_), "invalid input file format");
-    if (buffered_rowset_.size() != 0) {
-      LoadBinary(fi, &col_ptr_, &col_data_);
-    }
-  }
-  /*!
-   * \brief save data to binary stream
-   * \param fo output stream
-   * \param ptr pointer data
-   * \param data data content
-   */
-  inline static void SaveBinary(utils::IStream &fo,
-                                const std::vector<size_t> &ptr,
-                                const std::vector<SparseBatch::Entry> &data) {
-    size_t nrow = ptr.size() - 1;
-    fo.Write(&nrow, sizeof(size_t));
-    fo.Write(&ptr[0], ptr.size() * sizeof(size_t));
-    if (data.size() != 0) {
-      fo.Write(&data[0], data.size() * sizeof(SparseBatch::Entry));
-    }
-  }
-  /*!
-   * \brief load data from binary stream
-   * \param fi input stream
-   * \param out_ptr pointer data
-   * \param out_data data content
-   */
-  inline static void LoadBinary(utils::IStream &fi,
-                                std::vector<size_t> *out_ptr,
-                                std::vector<SparseBatch::Entry> *out_data) {
-    size_t nrow;
-    utils::Check(fi.Read(&nrow, sizeof(size_t)) != 0, "invalid input file format");
-    out_ptr->resize(nrow + 1);
-    utils::Check(fi.Read(&(*out_ptr)[0], out_ptr->size() * sizeof(size_t)) != 0,
-                  "invalid input file format");
-    out_data->resize(out_ptr->back());
-    if (out_data->size() != 0) {
-      utils::Assert(fi.Read(&(*out_data)[0], out_data->size() * sizeof(SparseBatch::Entry)) != 0,
-                    "invalid input file format");
-    }
-  }
-
- protected:
-  /*!
-   * \brief intialize column data
-   * \param pkeep probability to keep a row
-   */
-  inline void InitColData(float pkeep) {
-    buffered_rowset_.clear();
-    // note: this part of code is serial, todo, parallelize this transformer
-    utils::SparseCSRMBuilder<SparseBatch::Entry> builder(col_ptr_, col_data_);
-    builder.InitBudget(0);
-    // start working
-    iter_->BeforeFirst();
-    while (iter_->Next()) {
-      const SparseBatch &batch = iter_->Value();
-      for (size_t i = 0; i < batch.size; ++i) {
-        if (pkeep == 1.0f || random::SampleBinary(pkeep)) {
-          buffered_rowset_.push_back(static_cast<bst_uint>(batch.base_rowid+i));
-          SparseBatch::Inst inst = batch[i];
-          for (bst_uint j = 0; j < inst.length; ++j) {
-            builder.AddBudget(inst[j].findex);
-          }
-        }
-      }
-    }
-    builder.InitStorage();
-
-    iter_->BeforeFirst();
-    size_t ktop = 0;
-    while (iter_->Next()) {
-      const SparseBatch &batch = iter_->Value();
-      for (size_t i = 0; i < batch.size; ++i) {
-        if (ktop < buffered_rowset_.size() &&
-            buffered_rowset_[ktop] == batch.base_rowid+i) {
-          ++ktop;
-          SparseBatch::Inst inst = batch[i];
-          for (bst_uint j = 0; j < inst.length; ++j) {
-            builder.PushElem(inst[j].findex,
-                             Entry((bst_uint)(batch.base_rowid+i),
-                                   inst[j].fvalue));
-          }
-        }
-      }
-    }
-
-    // sort columns
-    bst_omp_uint ncol = static_cast<bst_omp_uint>(this->NumCol());
-    #pragma omp parallel for schedule(static)
-    for (bst_omp_uint i = 0; i < ncol; ++i) {
-      std::sort(&col_data_[0] + col_ptr_[i],
-                &col_data_[0] + col_ptr_[i + 1], Entry::CmpValue);
-    }
-  }
-
- private:
-  // --- data structure used to support InitColAccess --
-  utils::IIterator<SparseBatch> *iter_;
-  /*! \brief list of row index that are buffered */
-  std::vector<bst_uint> buffered_rowset_;
-  /*! \brief column pointer of CSC format */
-  std::vector<size_t> col_ptr_;
-  /*! \brief column datas in CSC format */
-  std::vector<SparseBatch::Entry> col_data_;
+  virtual bool HaveColAccess(void) const = 0;
+  /*! \return number of columns in the FMatrix */
+  virtual size_t NumCol(void) const = 0;
+  /*! \brief get number of non-missing entries in column */
+  virtual size_t GetColSize(size_t cidx) const = 0;
+  /*! \brief get column density */  
+  virtual float GetColDensity(size_t cidx) const = 0;  
+  /*! \brief reference of buffered rowset */
+  virtual const std::vector<bst_uint> &buffered_rowset(void) const = 0;
+  // virtual destructor
+  virtual ~IFMatrix(void){}
 };
 }  // namespace xgboost
 #endif  // XGBOOST_DATA_H