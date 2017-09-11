 * \tparam RType type of rank
 */
template<typename DType, typename RType=unsigned>
class WQuantileSketch {
 public:
  /*! \brief an entry in the sketch summary */
  struct Entry {
    /*! \brief minimum rank */
    RType rmin;
    /*! \brief maximum rank */
    RType rmax;
    /*! \brief maximum weight */
    RType wmin;
    /*! \brief the value of data */
    DType value;
    // constructor
    Entry(void) {}
    // constructor
    Entry(RType rmin, RType rmax, RType wmin, DType value)
        : rmin(rmin), rmax(rmax), wmin(wmin), value(value) {}
    /*! \brief debug function,  */
    inline void CheckValid(void) const {
      utils::Assert(rmin >= 0 && rmax >= 0 && wmin >= 0, "nonneg constraint");
      utils::Assert(rmax >= rmin + wmin, "relation constraint");
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
  /*! 
   * \brief this is data structure presenting one summary
