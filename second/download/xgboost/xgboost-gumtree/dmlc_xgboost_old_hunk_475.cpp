 * \tparam RType type of rank
 */
template<typename DType, typename RType=unsigned>
class QuantileSketch {
 public:
  /*! \brief an entry in the sketch summary */
  struct Entry {
    /*! \brief minimum rank */
    RType rmin;
    /*! \brief maximum rank */
    RType rmax;
    /*! \brief the value of data */
    DType value;
    // constructor
    Entry(void) {}
    // constructor
    Entry(RType rmin, RType rmax, DType value)
        : rmin(rmin), rmax(rmax), value(value) {}
  };
  /*! 
   * \brief this is data structure presenting one summary
