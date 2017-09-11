    ret.info.info.num_row = len;
    ret.info.info.num_col = src.info.num_col();

    utils::IIterator<RowBatch> *iter = src.fmat.RowIterator();
    iter->BeforeFirst();
    utils::Assert(iter->Next(), "slice");
    const RowBatch &batch = iter->Value();
    for (bst_ulong i = 0; i < len; ++i) {
      const int ridx = idxset[i];
      RowBatch::Inst inst = batch[ridx];
      utils::Check(static_cast<bst_ulong>(ridx) < batch.size, "slice index exceed number of rows");
      ret.row_data_.resize(ret.row_data_.size() + inst.length);
      memcpy(&ret.row_data_[ret.row_ptr_.back()], inst.data,
             sizeof(RowBatch::Entry) * inst.length);
      ret.row_ptr_.push_back(ret.row_ptr_.back() + inst.length);
      if (src.info.labels.size() != 0) {
        ret.info.labels.push_back(src.info.labels[ridx]);
