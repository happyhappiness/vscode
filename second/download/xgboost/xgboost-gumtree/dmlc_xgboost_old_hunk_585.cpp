    iter->BeforeFirst();
    utils::Assert(iter->Next(), "slice");
    const SparseBatch &batch = iter->Value();
    for (size_t i = 0; i < len; ++i) {
      const int ridx = idxset[i];
      SparseBatch::Inst inst = batch[ridx];
      utils::Check(static_cast<size_t>(ridx) < batch.size, "slice index exceed number of rows");
      ret.row_data_.resize(ret.row_data_.size() + inst.length);
      memcpy(&ret.row_data_[ret.row_ptr_.back()], inst.data,
             sizeof(SparseBatch::Entry) * inst.length);
