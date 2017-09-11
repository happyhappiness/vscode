@@ -17,26 +17,26 @@ namespace utils {
  * \tparam IndexType type of index used to store the index position, usually unsigned or size_t
  * \tparam whether enabling the usage of aclist, this option must be enabled manually
  */
-template<typename IndexType, bool UseAcList = false>
+template<typename IndexType, bool UseAcList = false, typename SizeType = size_t>
 struct SparseCSRMBuilder {
  private:
   /*! \brief dummy variable used in the indicator matrix construction */
   std::vector<size_t> dummy_aclist;
   /*! \brief pointer to each of the row */
-  std::vector<size_t> &rptr;
+  std::vector<SizeType> &rptr;
   /*! \brief index of nonzero entries in each row */
   std::vector<IndexType> &findex;
   /*! \brief a list of active rows, used when many rows are empty */
   std::vector<size_t> &aclist;
 
  public:
-  SparseCSRMBuilder(std::vector<size_t> &p_rptr,
+  SparseCSRMBuilder(std::vector<SizeType> &p_rptr,
                     std::vector<IndexType> &p_findex)
       :rptr(p_rptr), findex(p_findex), aclist(dummy_aclist) {
     Assert(!UseAcList, "enabling bug");
   }
   /*! \brief use with caution! rptr must be cleaned before use */
-  SparseCSRMBuilder(std::vector<size_t> &p_rptr,
+  SparseCSRMBuilder(std::vector<SizeType> &p_rptr,
                     std::vector<IndexType> &p_findex,
                     std::vector<size_t> &p_aclist)
       :rptr(p_rptr), findex(p_findex), aclist(p_aclist) {
@@ -62,7 +62,7 @@ struct SparseCSRMBuilder {
    * \param row_id the id of the row
    * \param nelem  number of element budget add to this row
    */
-  inline void AddBudget(size_t row_id, size_t nelem = 1) {
+  inline void AddBudget(size_t row_id, SizeType nelem = 1) {
     if (rptr.size() < row_id + 2) {
       rptr.resize(row_id + 2, 0);
     }
@@ -101,7 +101,7 @@ struct SparseCSRMBuilder {
    * element to each row, the number of calls shall be exactly same as add_budget
    */
   inline void PushElem(size_t row_id, IndexType col_id) {
-    size_t &rp = rptr[row_id + 1];
+    SizeType &rp = rptr[row_id + 1];
     findex[rp++] = col_id;
   }
   /*!