  };
  /*! \brief batch size */
  size_t size;
};
/*! \brief read-only row batch, used to access row continuously */
struct RowBatch : public SparseBatch {
  /*! \brief the offset of rowid of this batch */
  size_t base_rowid;
  /*! \brief array[size+1], row pointer of each of the elements */
  const size_t *ind_ptr;
  /*! \brief array[ind_ptr.back()], content of the sparse element */
  const Entry *data_ptr;
  /*! \brief get i-th row from the batch */
  inline Inst operator[](size_t i) const {
    return Inst(data_ptr + ind_ptr[i], static_cast<bst_uint>(ind_ptr[i+1] - ind_ptr[i]));
  }
};
/*! 
 * \brief read-only column batch, used to access columns,
 * the columns are not required to be continuous
 */
struct ColBatch : public SparseBatch {
  /*! \brief column index of each columns in the data */
  const bst_uint *col_index;
  /*! \brief pointer to the column data */
  const Inst *col_data;
  /*! \brief get i-th row from the batch */
  inline Inst operator[](size_t i) const {
    return col_data[i];
  }
};
/**
 * \brief interface of feature matrix, needed for tree construction
 *  this interface defines two way to access features,
 *  row access is defined by iterator of RowBatch
 *  col access is optional, checked by HaveColAccess, and defined by iterator of ColBatch
 */
class IFMatrix {
 public:
  // the interface only need to ganrantee row iter
  // column iter is active, when ColIterator is called, row_iter can be disabled
  /*! \brief get the row iterator associated with FMatrix */
  virtual utils::IIterator<RowBatch> *RowIterator(void) = 0;
  /*!\brief get column iterator */
  virtual utils::IIterator<ColBatch> *ColIterator(void) = 0;
  /*!
   * \brief get the column iterator associated with FMatrix with subset of column features 
   * \param fset is the list of column index set that must be contained in the returning Column iterator
   * \return the column iterator, initialized so that it reads the elements in fset
   */
  virtual utils::IIterator<ColBatch> *ColIterator(const std::vector<bst_uint> &fset) = 0;
  /*!
   * \brief check if column access is supported, if not, initialize column access
   * \param subsample subsample ratio when generating column access
   */
  virtual void InitColAccess(float subsample) = 0;
  // the following are column meta data, should be able to answer them fast
  /*! \return whether column access is enabled */
  virtual bool HaveColAccess(void) const = 0;
  /*! \return number of columns in the FMatrix */
  virtual size_t NumCol(void) const = 0;
  /*! \brief get number of non-missing entries in column */
  virtual size_t GetColSize(size_t cidx) const = 0;
  /*! \brief get column density */  
  virtual float GetColDensity(size_t cidx) const = 0;  
  /*! \brief reference of buffered rowset */
  virtual const std::vector<bst_uint> &buffered_rowset(void) const = 0;
  // virtual destructor
  virtual ~IFMatrix(void){}
};
}  // namespace xgboost
#endif  // XGBOOST_DATA_H
