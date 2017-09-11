     */
    inline RType MaxError(void) const {
      RType res = data[0].rmax - data[0].rmin - data[0].wmin;
      for (size_t i = 1; i < size; ++i) {
        res = std::max(data[i].rmax_prev() - data[i - 1].rmin_next(), res);
        res = std::max(data[i].rmax - data[i].rmin - data[i].wmin, res);
      }
      return res;
    }
    /*! 
     * \brief debug function, validate whether the summary 
     *  run consistency check to check if it is a valid summary
     * \param eps the tolerate error level, used when RType is floating point and 
     *        some inconsistency could occur due to rounding error
     */
    inline void CheckValid(RType eps) const {
      for (size_t i = 0; i < size; ++i) {
        data[i].CheckValid(eps);
        if (i != 0) {
          utils::Assert(data[i].rmin >= data[i - 1].rmin + data[i - 1].wmin, "rmin range constraint");
          utils::Assert(data[i].rmax >= data[i - 1].rmax + data[i].wmin, "rmax range constraint");
