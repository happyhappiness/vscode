    return ColIter(&col_data_[col_ptr_[cidx]] - 1,
                   &col_data_[col_ptr_[cidx + 1]] - 1);
  }
  /*! 
   * \brief get reversed col iterator, 
   *   this function will be deprecated at some point 
   */
  inline ColBackIter GetReverseSortedCol(size_t cidx) const {
    utils::Assert(cidx < this->NumCol(), "col id exceed bound");
