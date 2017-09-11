    /*! \brief the value of data */
    DType value;
    // constructor
    Entry(void) {}
    // constructor
    Entry(RType rmin, RType rmax, RType wmin, DType value)
        : rmin(rmin), rmax(rmax), wmin(wmin), value(value) {}
    /*! 
     * \brief debug function,  check Valid 
     * \param eps the tolerate level for violating the relation
     */
    inline void CheckValid(RType eps = 0) const {
      utils::Assert(rmin >= 0 && rmax >= 0 && wmin >= 0, "nonneg constraint");
      utils::Assert(rmax- rmin - wmin > -eps, "relation constraint: min/max");
    }
    /*! \return rmin estimation for v strictly bigger than value */
    inline RType rmin_next(void) const {
