    size_t nmiss = num_buffered_row_ - (col_ptr_[cidx+1] - col_ptr_[cidx]);
    return 1.0f - (static_cast<float>(nmiss)) / num_buffered_row_;
  }
  virtual void InitColAccess(void) {
    if (this->HaveColAccess()) return;
    const size_t max_nrow = std::numeric_limits<bst_uint>::max();
    this->InitColData(max_nrow);
  }
  /*! \brief get the row iterator associated with FMatrix */
  virtual utils::IIterator<SparseBatch>* RowIterator(void) const {
    return iter_;
  }

 protected:
  /*!
