@@ -6,6 +6,7 @@
  * \author Tianqi Chen
  */
 #include <vector>
+#include <utility>
 #include <algorithm>
 #include "./io.h"
 #include "./utils.h"
@@ -156,7 +157,7 @@ struct SparseCSRFileBuilder {
     for (size_t i = 1; i < rptr.size(); i++) {
       nelem += rptr[i];
       rptr[i] = nelem;
-    }    
+    }
     begin_data = static_cast<SizeType>(fo->Tell()) + sizeof(SizeType);
     SizeType begin_meta = begin_data + nelem * sizeof(IndexType);
     fo->Write(&begin_meta, sizeof(begin_meta));
@@ -166,8 +167,8 @@ struct SparseCSRFileBuilder {
     buffer_rptr.resize(rptr.size());
     buffer_temp.reserve(buffer_size);
     buffer_data.resize(buffer_size);
-    saved_offset.clear();
-    saved_offset.resize(rptr.size() - 1, 0);
+    saved_offset = rptr;
+    saved_offset.resize(rptr.size() - 1);
     this->ClearBuffer();
   }
   /*! \brief step 4: push element into buffer */
@@ -176,7 +177,8 @@ struct SparseCSRFileBuilder {
       this->WriteBuffer();
       this->ClearBuffer();
     }
-    buffer_temp.push_back(std::make_pair(row_id, col_id));    
+    buffer_rptr[row_id + 1] += 1;
+    buffer_temp.push_back(std::make_pair(row_id, col_id));
   }
   /*! \brief finalize the construction */
   inline void Finalize(void) {
@@ -190,14 +192,14 @@ struct SparseCSRFileBuilder {
   inline void SortRows(Comparator comp, size_t step) {
     for (size_t i = 0; i < rptr.size() - 1; i += step) {
       bst_omp_uint begin = static_cast<bst_omp_uint>(i);
-      bst_omp_uint end = static_cast<bst_omp_uint>(std::min(rptr.size(), i + step));
+      bst_omp_uint end = static_cast<bst_omp_uint>(std::min(rptr.size() - 1, i + step));
       if (rptr[end] != rptr[begin]) {
         fo->Seek(begin_data + rptr[begin] * sizeof(IndexType));
         buffer_data.resize(rptr[end] - rptr[begin]);
         fo->Read(BeginPtr(buffer_data), (rptr[end] - rptr[begin]) * sizeof(IndexType));
         // do parallel sorting
         #pragma omp parallel for schedule(static)
-        for (bst_omp_uint j = begin; j < end; ++j){
+        for (bst_omp_uint j = begin; j < end; ++j) {
           std::sort(&buffer_data[0] + rptr[j] - rptr[begin],
                     &buffer_data[0] + rptr[j+1] - rptr[begin],
                     comp);
@@ -206,6 +208,7 @@ struct SparseCSRFileBuilder {
         fo->Write(BeginPtr(buffer_data), (rptr[end] - rptr[begin]) * sizeof(IndexType));
       }
     }
+    printf("CSV::begin_dat=%lu\n", begin_data);
   }
  protected:
   inline void WriteBuffer(void) {
@@ -220,11 +223,11 @@ struct SparseCSRFileBuilder {
       buffer_data[rp++] = buffer_temp[i].second;
     }
     // write out
-    for (size_t i = 0; i < buffer_rptr.size(); ++i) {
+    for (size_t i = 0; i < buffer_rptr.size() - 1; ++i) {
       size_t nelem = buffer_rptr[i+1] - buffer_rptr[i];
       if (nelem != 0) {
-        utils::Assert(saved_offset[i] < rptr[i+1], "data exceed bound");
-        fo->Seek((rptr[i] + saved_offset[i]) * sizeof(IndexType) + begin_data);
+        utils::Assert(saved_offset[i] + nelem <= rptr[i+1], "data exceed bound");
+        fo->Seek(saved_offset[i] * sizeof(IndexType) + begin_data);
         fo->Write(&buffer_data[0] + buffer_rptr[i], nelem * sizeof(IndexType));
         saved_offset[i] += nelem;
       }