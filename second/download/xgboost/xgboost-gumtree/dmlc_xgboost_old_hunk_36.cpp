     * \param eps the tolerate level for violating the relation
     */
    inline void CheckValid(RType eps = 0) const {
      utils::Assert(rmin >= 0 && rmax >= 0 && wmin >= 0, "nonneg constraint");
      utils::Assert(rmax- rmin - wmin > -eps, "relation constraint: min/max");
    }
    /*! \return rmin estimation for v strictly bigger than value */
    inline RType rmin_next(void) const {
      return rmin + wmin;
    }
    /*! \return rmax estimation for v strictly smaller than value */
    inline RType rmax_prev(void) const {
      return rmax - wmin;
    }
  };
