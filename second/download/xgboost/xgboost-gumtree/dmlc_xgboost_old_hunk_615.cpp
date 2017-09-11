    utils::Check(this->HaveColAccess(), "NumCol:need column access");
    return col_ptr_.size() - 1;
  }
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
    return col_ptr_[cidx+1] - col_ptr_[cidx];
  }
  /*! \brief get column density */
  inline float GetColDensity(size_t cidx) const {
    size_t nmiss = num_buffered_row_ - (col_ptr_[cidx+1] - col_ptr_[cidx]);
    return 1.0f - (static_cast<float>(nmiss)) / num_buffered_row_;
  }
  inline void InitColAccess(size_t max_nrow = ULONG_MAX) {
    if (this->HaveColAccess()) return;
    this->InitColData(max_nrow);
  }
  /*!
   * \brief get the row iterator associated with FMatrix
