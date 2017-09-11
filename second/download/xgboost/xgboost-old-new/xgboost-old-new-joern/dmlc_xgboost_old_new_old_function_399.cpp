inline ColBackIter GetReverseSortedCol(size_t cidx) const {
    utils::Assert(cidx < this->NumCol(), "col id exceed bound");
    return ColBackIter(&col_data_[0] + col_ptr_[cidx + 1],
                       &col_data_[0] + col_ptr_[cidx]);
  }