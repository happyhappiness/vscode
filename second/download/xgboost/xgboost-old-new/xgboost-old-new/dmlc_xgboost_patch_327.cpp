@@ -89,7 +89,7 @@ extern "C"{
     }
     mat.row_data_.resize(nelem);
     for (bst_ulong i = 0; i < nelem; ++i) {
-      mat.row_data_[i] = SparseBatch::Entry(indices[i], data[i]);
+      mat.row_data_[i] = RowBatch::Entry(indices[i], data[i]);
       mat.info.info.num_col = std::max(mat.info.info.num_col,
                                        static_cast<size_t>(indices[i]+1));
     }
@@ -108,7 +108,7 @@ extern "C"{
       bst_ulong nelem = 0;
       for (bst_ulong j = 0; j < ncol; ++j) {
         if (data[j] != missing) {
-          mat.row_data_.push_back(SparseBatch::Entry(j, data[j]));
+          mat.row_data_.push_back(RowBatch::Entry(j, data[j]));
           ++nelem;
         }
       }
@@ -135,17 +135,17 @@ extern "C"{
     ret.info.info.num_row = len;
     ret.info.info.num_col = src.info.num_col();
 
-    utils::IIterator<SparseBatch> *iter = src.fmat.RowIterator();
+    utils::IIterator<RowBatch> *iter = src.fmat.RowIterator();
     iter->BeforeFirst();
     utils::Assert(iter->Next(), "slice");
-    const SparseBatch &batch = iter->Value();
+    const RowBatch &batch = iter->Value();
     for (bst_ulong i = 0; i < len; ++i) {
       const int ridx = idxset[i];
-      SparseBatch::Inst inst = batch[ridx];
+      RowBatch::Inst inst = batch[ridx];
       utils::Check(static_cast<bst_ulong>(ridx) < batch.size, "slice index exceed number of rows");
       ret.row_data_.resize(ret.row_data_.size() + inst.length);
       memcpy(&ret.row_data_[ret.row_ptr_.back()], inst.data,
-             sizeof(SparseBatch::Entry) * inst.length);
+             sizeof(RowBatch::Entry) * inst.length);
       ret.row_ptr_.push_back(ret.row_ptr_.back() + inst.length);
       if (src.info.labels.size() != 0) {
         ret.info.labels.push_back(src.info.labels[ridx]);