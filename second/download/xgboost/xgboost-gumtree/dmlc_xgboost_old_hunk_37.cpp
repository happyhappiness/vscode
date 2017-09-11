  /*!
   * \return the maximum error of the Summary
   */
  inline RType MaxError(void) const {
    RType res = data[0].rmax - data[0].rmin - data[0].wmin;
    for (size_t i = 1; i < size; ++i) {
      res = std::max(data[i].rmax_prev() - data[i - 1].rmin_next(), res);
