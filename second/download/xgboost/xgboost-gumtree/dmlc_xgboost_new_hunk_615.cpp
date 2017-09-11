    utils::Check(this->HaveColAccess(), "NumCol:need column access");
    return col_ptr_.size() - 1;
  }
  /*! \brief get number of buffered rows */  
  inline const std::vector<bst_uint> buffered_rowset(void) const {
    return buffered_rowset_;
  }
  /*! \brief get col sorted iterator */
  inline ColIter GetSortedCol(size_t cidx) const {
    utils::Assert(cidx < this->NumCol(), "col id exceed bound");
    return ColIter(&col_data_[0] + col_ptr_[cidx] - 1,
                   &col_data_[0] + col_ptr_[cidx + 1] - 1);
  }
  /*!
   * \brief get reversed col iterator,
   *   this function will be deprecated at some point
   */
  inline ColBackIter GetReverseSortedCol(size_t cidx) const {
    utils::Assert(cidx < this->NumCol(), "col id exceed bound");
    return ColBackIter(&col_data_[0] + col_ptr_[cidx + 1],
                       &col_data_[0] + col_ptr_[cidx]);
  }
  /*! \brief get col size */
  inline size_t GetColSize(size_t cidx) const {
    return col_ptr_[cidx+1] - col_ptr_[cidx];
  }
  /*! \brief get column density */
  inline float GetColDensity(size_t cidx) const {
    size_t nmiss = buffered_rowset_.size() - (col_ptr_[cidx+1] - col_ptr_[cidx]);
    return 1.0f - (static_cast<float>(nmiss)) / buffered_rowset_.size();
  }
  inline void InitColAccess(float pkeep = 1.0f) {
    if (this->HaveColAccess()) return;
    this->InitColData(pkeep);
  }
  /*!
   * \brief get the row iterator associated with FMatrix
