 * \tparam IndexType type of index used to store the index position, usually unsigned or size_t
 * \tparam whether enabling the usage of aclist, this option must be enabled manually
 */
template<typename IndexType, bool UseAcList = false>
struct SparseCSRMBuilder {
 private:
  /*! \brief dummy variable used in the indicator matrix construction */
  std::vector<size_t> dummy_aclist;
  /*! \brief pointer to each of the row */
  std::vector<size_t> &rptr;
  /*! \brief index of nonzero entries in each row */
  std::vector<IndexType> &findex;
  /*! \brief a list of active rows, used when many rows are empty */
  std::vector<size_t> &aclist;

 public:
  SparseCSRMBuilder(std::vector<size_t> &p_rptr,
                    std::vector<IndexType> &p_findex)
      :rptr(p_rptr), findex(p_findex), aclist(dummy_aclist) {
    Assert(!UseAcList, "enabling bug");
  }
  /*! \brief use with caution! rptr must be cleaned before use */
  SparseCSRMBuilder(std::vector<size_t> &p_rptr,
                    std::vector<IndexType> &p_findex,
                    std::vector<size_t> &p_aclist)
      :rptr(p_rptr), findex(p_findex), aclist(p_aclist) {
