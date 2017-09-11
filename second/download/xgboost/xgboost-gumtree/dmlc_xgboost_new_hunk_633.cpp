    size_t nmiss = num_buffered_row_ - (col_ptr_[cidx+1] - col_ptr_[cidx]);
    return 1.0f - (static_cast<float>(nmiss)) / num_buffered_row_;
  }
  inline void InitColAccess(size_t max_nrow = ULONG_MAX) {
    if (this->HaveColAccess()) return;
    this->InitColData(max_nrow);
  }
  /*! \brief get the row iterator associated with FMatrix */
  inline utils::IIterator<SparseBatch>* RowIterator(void) const {
    return iter_;
  }
  /*! \brief set iterator */
  inline void set_iter(utils::IIterator<SparseBatch> *iter) {
    this->iter_ = iter;
  }
  /*!
   * \brief save column access data into stream
   * \param fo output stream to save to
   */
  inline void SaveColAccess(utils::IStream &fo) {
    fo.Write(&num_buffered_row_, sizeof(num_buffered_row_));
    if (num_buffered_row_ != 0) {
      SaveBinary(fo, col_ptr_, col_data_);
    }
  }
  /*!
   * \brief load column access data from stream
   * \param fo output stream to load from
   */
  inline void LoadColAccess(utils::IStream &fi) {
    utils::Check(fi.Read(&num_buffered_row_, sizeof(num_buffered_row_)) != 0,
                 "invalid input file format");
    if (num_buffered_row_ != 0) {
      LoadBinary(fi, &col_ptr_, &col_data_);
    }
  }
  /*!
   * \brief save data to binary stream
   * \param fo output stream
   * \param ptr pointer data
   * \param data data content
   */
  inline static void SaveBinary(utils::IStream &fo,
                                const std::vector<size_t> &ptr,
                                const std::vector<SparseBatch::Entry> &data) {
    size_t nrow = ptr.size() - 1;
    fo.Write(&nrow, sizeof(size_t));
    fo.Write(&ptr[0], ptr.size() * sizeof(size_t));
    if (data.size() != 0) {
      fo.Write(&data[0], data.size() * sizeof(SparseBatch::Entry));
    }
  }
  /*!
   * \brief load data from binary stream
   * \param fi input stream
   * \param out_ptr pointer data
   * \param out_data data content
   */
  inline static void LoadBinary(utils::IStream &fi,
                                std::vector<size_t> *out_ptr,
                                std::vector<SparseBatch::Entry> *out_data) {
    size_t nrow;
    utils::Check(fi.Read(&nrow, sizeof(size_t)) != 0, "invalid input file format");
    out_ptr->resize(nrow + 1);
    utils::Check(fi.Read(&(*out_ptr)[0], out_ptr->size() * sizeof(size_t)) != 0, 
                  "invalid input file format");
    out_data->resize(out_ptr->back());
    if (out_data->size() != 0) {
      utils::Assert(fi.Read(&(*out_data)[0], out_data->size() * sizeof(SparseBatch::Entry)) != 0, 
                    "invalid input file format");
    }
  }

 protected:
  /*!
