@@ -7,6 +7,7 @@
  */
 #include <vector>
 #include <algorithm>
+#include "./io.h"
 #include "./utils.h"
 
 namespace xgboost {
@@ -118,6 +119,117 @@ struct SparseCSRMBuilder {
   }
 };
 
+/*!
+ * \brief a class used to help construct CSR format matrix file
+ * \tparam IndexType type of index used to store the index position
+ * \tparam SizeType type of size used in row pointer
+ */
+template<typename IndexType, typename SizeType = size_t>
+struct SparseCSRFileBuilder {
+ public:
+  explicit SparseCSRFileBuilder(utils::ISeekStream *fo, size_t buffer_size) 
+      : fo(fo), buffer_size(buffer_size) {
+  }
+  /*!
+   * \brief step 1: initialize the number of rows in the data, not necessary exact
+   * \nrows number of rows in the matrix, can be smaller than expected
+   */
+  inline void InitBudget(size_t nrows = 0) {
+    rptr.clear();
+    rptr.resize(nrows + 1, 0);
+  }
+  /*!
+   * \brief step 2: add budget to each rows
+   * \param row_id the id of the row
+   * \param nelem  number of element budget add to this row
+   */
+  inline void AddBudget(size_t row_id, SizeType nelem = 1) {
+    if (rptr.size() < row_id + 2) {
+      rptr.resize(row_id + 2, 0);
+    }
+    rptr[row_id + 1] += nelem;
+  }
+  /*! \brief step 3: initialize the necessary storage */
+  inline void InitStorage(void) {
+    SizeType nelem = 0;
+    for (size_t i = 1; i < rptr.size(); i++) {
+      nelem += rptr[i];
+      rptr[i] = nelem;
+    }
+    SizeType begin_meta = sizeof(SizeType) + nelem * sizeof(IndexType);
+    fo->Seek(0);
+    fo->Write(&begin_meta, sizeof(begin_meta));
+    fo->Seek(begin_meta);
+    fo->Write(rptr);
+    // setup buffer space
+    buffer_rptr.resize(rptr.size());
+    buffer.reserve(buffer_size);
+    buffer_data.resize(buffer_size);
+    saved_offset.clear();
+    saved_offset.resize(rptr.size() - 1, 0);
+    this->ClearBuffer();
+  }
+  /*! \brief step 4: push element into buffer */
+  inline void PushElem(SizeType row_id, IndexType col_id) {
+    if (buffer_temp.size() == buffer_size) {
+      this->WriteBuffer();
+      this->ClearBuffer();
+    }
+    buffer_temp.push_back(std::make_pair(row_id, col_id));    
+  }
+  /*! \brief finalize the construction */
+  inline void Finalize(void) {
+    this->WriteBuffer();
+    for (size_t i = 0; i < saved_offset.size(); ++i) {
+      utils::Assert(saved_offset[i] == rptr[i+1], "some block not write out");
+    }
+  }
+  
+ protected:
+  inline void WriteBuffer(void) {
+    SizeType start = 0;
+    for (size_t i = 1; i < buffer_rptr.size(); ++i) {
+      size_t rlen = buffer_rptr[i];
+      buffer_rptr[i] = start;
+      start += rlen;
+    }
+    for (size_t i = 0; i < buffer_temp.size(); ++i) {
+      SizeType &rp = buffer_rptr[buffer_temp[i].first + 1];
+      buffer_data[rp++] = buffer_temp[i].second;
+    }
+    // write out
+    for (size_t i = 0; i < buffer_rptr.size(); ++i) {
+      size_t nelem = buffer_rptr[i+1] - buffer_rptr[i];
+      if (nelem != 0) {
+        utils::Assert(saved_offset[i] < rptr[i+1], "data exceed bound");
+        fo->Seek((rptr[i] + saved_offset[i]) * sizeof(IndexType) + sizeof(SizeType));
+        fo->Write(&buffer_data[0] + buffer_rptr[i], nelem * sizeof(IndexType));
+        saved_offset[i] += nelem;
+      }
+    }
+  }
+  inline void ClearBuffer(void) {
+    buffer_temp.clear();
+    std::fill(buffer_rptr.begin(), buffer_rptr.end(), 0);
+  }
+ private:
+  /*! \brief output file pointer the data */
+  utils::ISeekStream *fo;
+  /*! \brief pointer to each of the row */
+  std::vector<SizeType> rptr;
+  /*! \brief saved top space of each item */
+  std::vector<SizeType> saved_offset;
+  // ----- the following are buffer space
+  /*! \brief maximum size of content buffer*/
+  size_t buffer_size;
+  /*! \brief store the data content */
+  std::vector< std::pair<SizeType, IndexType> > buffer_temp;
+  /*! \brief saved top space of each item */
+  std::vector<SizeType> buffer_rptr;
+  /*! \brief saved top space of each item */
+  std::vector<IndexType> buffer_data;
+};
+
 }  // namespace utils
 }  // namespace xgboost
 #endif