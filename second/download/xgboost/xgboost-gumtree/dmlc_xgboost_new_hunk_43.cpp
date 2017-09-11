  GKSummary(Entry *data, size_t size)
      : data(data), size(size) {}
  /*! \brief the maximum error of the summary */
  inline RType MaxError() const {
    RType res = 0;
    for (size_t i = 1; i < size; ++i) {
      res = std::max(data[i].rmax - data[i-1].rmin, res);
    }
    return res;
  }
  /*! \return maximum rank in the summary */
  inline RType MaxRank() const {
    return data[size - 1].rmax;
  }
  /*!
