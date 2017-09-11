    utils::Check(this->HaveColAccess(), "NumCol:need column access");
    return col_ptr_.size() - 1;
  }
  /*! \brief get col sorted iterator */
  inline ColIter GetSortedCol(size_t cidx) const {
    utils::Assert(cidx < this->NumCol(), "col id exceed bound");
