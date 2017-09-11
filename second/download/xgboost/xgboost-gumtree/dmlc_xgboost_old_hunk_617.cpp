  /*! \brief get col sorted iterator */
  inline ColIter GetSortedCol(size_t cidx) const {
    utils::Assert(cidx < this->NumCol(), "col id exceed bound");
    return ColIter(&col_data_[col_ptr_[cidx]] - 1,
                   &col_data_[col_ptr_[cidx + 1]] - 1);
  }
  /*!
   * \brief get reversed col iterator,
   *   this function will be deprecated at some point
   */
  inline ColBackIter GetReverseSortedCol(size_t cidx) const {
    utils::Assert(cidx < this->NumCol(), "col id exceed bound");
    return ColBackIter(&col_data_[col_ptr_[cidx + 1]],
                       &col_data_[col_ptr_[cidx]]);
  }
  /*! \brief get col size */
  inline size_t GetColSize(size_t cidx) const {
