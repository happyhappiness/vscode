  /*! \brief number of elements in the summary */
  size_t size;
  GKSummary(Entry *data, size_t size)
      : data(data), size(size) {} 
  /*! \brief the maximum error of the summary */
  inline RType MaxError(void) const {
    RType res = 0;
