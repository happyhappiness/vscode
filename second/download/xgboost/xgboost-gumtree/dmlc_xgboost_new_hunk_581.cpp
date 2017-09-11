    iter->BeforeFirst();
    utils::Assert(iter->Next(), "slice");
    const SparseBatch &batch = iter->Value();
    for (bst_ulong i = 0; i < len; ++i) {
      const int ridx = idxset[i];
      SparseBatch::Inst inst = batch[ridx];
      utils::Check(static_cast<bst_ulong>(ridx) < batch.size, "slice index exceed number of rows");
      ret.row_data_.resize(ret.row_data_.size() + inst.length);
      memcpy(&ret.row_data_[ret.row_ptr_.back()], inst.data,
             sizeof(SparseBatch::Entry) * inst.length);
