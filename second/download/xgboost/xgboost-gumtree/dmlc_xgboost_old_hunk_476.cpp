    /*! \brief data field */
    Entry *data;
    /*! \brief number of elements in the summary */
    RType size;
    /*! \brief the maximum error of the summary */
    inline RType MaxError(void) const {
      RType res = 0;
      for (RType i = 1; i < size; ++i) {
        res = std::max(data[i].rmax - data[i-1].rmin, res);
      }
      return res;
    }
    /*! \return maximum rank in the summary */
    inline RType MaxRank(void) const {
      return data[size - 1].rmax;
