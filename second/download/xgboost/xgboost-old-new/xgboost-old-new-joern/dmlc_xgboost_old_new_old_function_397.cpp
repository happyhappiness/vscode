SEXP XGDMatrixCreateFromCSC_R(SEXP indptr,
                                SEXP indices,
                                SEXP data) {
    const int *col_ptr = INTEGER(indptr);
    const int *row_index = INTEGER(indices);
    const double *col_data = REAL(data);
    int ncol = length(indptr) - 1;
    int ndata = length(data);
    // transform into CSR format
    std::vector<bst_ulong> row_ptr;
    std::vector< std::pair<unsigned, float> > csr_data;
    utils::SparseCSRMBuilder<std::pair<unsigned,float>, false, bst_ulong> builder(row_ptr, csr_data);
    builder.InitBudget();
    for (int i = 0; i < ncol; ++i) {
      for (int j = col_ptr[i]; j < col_ptr[i+1]; ++j) {
        builder.AddBudget(row_index[j]);
      }
    }
    builder.InitStorage();
    for (int i = 0; i < ncol; ++i) {
      for (int j = col_ptr[i]; j < col_ptr[i+1]; ++j) {
        builder.PushElem(row_index[j], std::make_pair(i, col_data[j]));
      }
    }
    utils::Assert(csr_data.size() == static_cast<size_t>(ndata), "BUG CreateFromCSC");
    std::vector<float> row_data(ndata);
    std::vector<unsigned> col_index(ndata);
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < ndata; ++i) {
      col_index[i] = csr_data[i].first;
      row_data[i] = csr_data[i].second;      
    }
    void *handle = XGDMatrixCreateFromCSR(&row_ptr[0], &col_index[0], &row_data[0], row_ptr.size(), ndata );
    SEXP ret = PROTECT(R_MakeExternalPtr(handle, R_NilValue, R_NilValue));
    R_RegisterCFinalizerEx(ret, _DMatrixFinalizer, TRUE);
    UNPROTECT(1);
    return ret;
  }