    /*! \brief the maximum error of the summary */
    inline RType MaxError(void) const {
      RType res = 0;
      for (size_t i = 1; i < size; ++i) {
        res = std::max(data[i].rmax - data[i-1].rmin, res);
      }
      return res;
