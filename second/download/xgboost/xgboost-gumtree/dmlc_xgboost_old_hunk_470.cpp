     */
    inline RType MaxError(void) const {
      RType res = data[0].rmax - data[0].rmin - data[0].wmin;
      for (RType i = 1; i < size; ++i) {
        res = std::max(data[i].rmax_prev() - data[i - 1].rmax_next(), res);
        res = std::max(data[i].rmax - data[i].rmin - data[i].wmin, res);
      }
      return res;
    }
    /*! 
     * \brief debug function, validate whether the summary 
     *  run consistency check to check if it is a valid summary
     */
    inline void CheckValid(void) const {
      for (RType i = 0; i < size; ++i) {
        data[i].CheckValid();
        if (i != 0) {
          utils::Assert(data[i].rmin >= data[i - 1].rmin + data[i - 1].wmin, "rmin range constraint");
          utils::Assert(data[i].rmax >= data[i - 1].rmax + data[i].wmin, "rmax range constraint");
