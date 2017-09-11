    /*! \brief the value of data */
    DType value;
    // constructor
    Entry(void) {
      rmin = rmax = wmin = 0.0;
    }
    // constructor
    Entry(RType rmin, RType rmax, RType wmin, DType value)
        : rmin(rmin), rmax(rmax), wmin(wmin), value(value) {
      if (!(this->rmax - this->rmin - this->wmin > -0.1)) {
        rmax = rmin + wmin;
        printf("correct\n");
        printf("rmax=%f, rmin=%f, wmin=%f, plus=%f, v=%f\n", 
               rmax, rmin, wmin, rmin+wmin, value);
      }
    }
    /*! \brief debug function,  check Valid */
    inline void CheckValid(RType eps = 0) const {
      utils::Assert(rmin >= 0 && rmax >= 0 && wmin >= 0, "nonneg constraint");
      if (!(rmax - rmin - wmin > -eps)) {
        printf("rmax=%f, rmin=%f, wmin=%f, plus=%f, v=%f\n", 
               rmax, rmin, wmin, rmin+wmin, value);
      }
      utils::Assert(rmax- rmin - wmin > -eps  , "relation constraint: min/max");
    }
    /*! \return rmin estimation for v strictly bigger than value */
    inline RType rmin_next(void) const {
