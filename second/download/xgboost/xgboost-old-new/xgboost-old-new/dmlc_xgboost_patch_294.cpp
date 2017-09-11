@@ -9,6 +9,7 @@
 #include <algorithm>
 #include "./io.h"
 #include "./utils.h"
+#include "./omp.h"
 
 namespace xgboost {
 namespace utils {
@@ -155,9 +156,9 @@ struct SparseCSRFileBuilder {
     for (size_t i = 1; i < rptr.size(); i++) {
       nelem += rptr[i];
       rptr[i] = nelem;
-    }
-    SizeType begin_meta = sizeof(SizeType) + nelem * sizeof(IndexType);
-    fo->Seek(0);
+    }    
+    begin_data = static_cast<SizeType>(fo->Tell()) + sizeof(SizeType);
+    SizeType begin_meta = begin_data + nelem * sizeof(IndexType);
     fo->Write(&begin_meta, sizeof(begin_meta));
     fo->Seek(begin_meta);
     fo->Write(rptr);
@@ -184,7 +185,28 @@ struct SparseCSRFileBuilder {
       utils::Assert(saved_offset[i] == rptr[i+1], "some block not write out");
     }
   }
-  
+  /*! \brief content must be in wb+ */
+  template<typename Comparator>
+  inline void SortRows(Comparator comp, size_t step) {
+    for (size_t i = 0; i < rptr.size() - 1; i += step) {
+      bst_omp_uint begin = static_cast<bst_omp_uint>(i);
+      bst_omp_uint end = static_cast<bst_omp_uint>(std::min(rptr.size(), i + step));
+      if (rptr[end] != rptr[begin]) {
+        fo->Seek(begin_data + rptr[begin] * sizeof(IndexType));
+        buffer_data.resize(rptr[end] - rptr[begin]);
+        fo->Read(BeginPtr(buffer_data), (rptr[end] - rptr[begin]) * sizeof(IndexType));
+        // do parallel sorting
+        #pragma omp parallel for schedule(static)
+        for (bst_omp_uint j = begin; j < end; ++j){
+          std::sort(&buffer_data[0] + rptr[j] - rptr[begin],
+                    &buffer_data[0] + rptr[j+1] - rptr[begin],
+                    comp);
+        }
+        fo->Seek(begin_data + rptr[begin] * sizeof(IndexType));
+        fo->Write(BeginPtr(buffer_data), (rptr[end] - rptr[begin]) * sizeof(IndexType));
+      }
+    }
+  }
  protected:
   inline void WriteBuffer(void) {
     SizeType start = 0;
@@ -202,7 +224,7 @@ struct SparseCSRFileBuilder {
       size_t nelem = buffer_rptr[i+1] - buffer_rptr[i];
       if (nelem != 0) {
         utils::Assert(saved_offset[i] < rptr[i+1], "data exceed bound");
-        fo->Seek((rptr[i] + saved_offset[i]) * sizeof(IndexType) + sizeof(SizeType));
+        fo->Seek((rptr[i] + saved_offset[i]) * sizeof(IndexType) + begin_data);
         fo->Write(&buffer_data[0] + buffer_rptr[i], nelem * sizeof(IndexType));
         saved_offset[i] += nelem;
       }
@@ -219,6 +241,8 @@ struct SparseCSRFileBuilder {
   std::vector<SizeType> rptr;
   /*! \brief saved top space of each item */
   std::vector<SizeType> saved_offset;
+  /*! \brief beginning position of data */
+  size_t begin_data;
   // ----- the following are buffer space
   /*! \brief maximum size of content buffer*/
   size_t buffer_size;