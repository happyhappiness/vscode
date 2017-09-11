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
   * \brief intialize column data
   * \param max_nrow maximum number of rows supported
   */
  inline void InitColData(size_t max_nrow) {
    // note: this part of code is serial, todo, parallelize this transformer
