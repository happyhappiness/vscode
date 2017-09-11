                                SEXP indices,
                                SEXP data) {
    _WrapperBegin();
    const int *p_indptr = INTEGER(indptr);
    const int *p_indices = INTEGER(indices);
    const double *p_data = REAL(data);
    int nindptr = length(indptr);
    int ndata = length(data);
    std::vector<bst_ulong> col_ptr_(nindptr);
    std::vector<unsigned> indices_(ndata);
    std::vector<float> data_(ndata);

    for (int i = 0; i < nindptr; ++i) {
      col_ptr_[i] = static_cast<bst_ulong>(p_indptr[i]);
    }
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < ndata; ++i) {
      indices_[i] = static_cast<unsigned>(p_indices[i]);
      data_[i] = static_cast<float>(p_data[i]);
    }
    void *handle = XGDMatrixCreateFromCSC(BeginPtr(col_ptr_), BeginPtr(indices_),
                                          BeginPtr(data_), nindptr, ndata);
    SEXP ret = PROTECT(R_MakeExternalPtr(handle, R_NilValue, R_NilValue));
    R_RegisterCFinalizerEx(ret, _DMatrixFinalizer, TRUE);
    UNPROTECT(1);
