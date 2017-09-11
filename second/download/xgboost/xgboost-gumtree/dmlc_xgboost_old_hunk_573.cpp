    utils::Check(src.info.group_ptr.size() == 0,
                 "slice does not support group structure");
    ret.Clear();
    ret.info.num_row = len;
    ret.info.num_col = src.info.num_col;

    utils::IIterator<SparseBatch> *iter = src.fmat.RowIterator();
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
