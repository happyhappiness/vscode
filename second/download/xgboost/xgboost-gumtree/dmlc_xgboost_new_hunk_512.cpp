        data[i * ncol +j] = din[i + nrow * j];
      }
    }
    void *handle = XGDMatrixCreateFromMat(BeginPtr(data), nrow, ncol, asReal(missing));
    SEXP ret = PROTECT(R_MakeExternalPtr(handle, R_NilValue, R_NilValue));
    R_RegisterCFinalizerEx(ret, _DMatrixFinalizer, TRUE);
    UNPROTECT(1);
    _WrapperEnd();
    return ret;    
  }
  SEXP XGDMatrixCreateFromCSC_R(SEXP indptr,
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
    _WrapperEnd();
    return ret;
  }
  SEXP XGDMatrixSliceDMatrix_R(SEXP handle, SEXP idxset) {
    _WrapperBegin();
    int len = length(idxset);
    std::vector<int> idxvec(len);
    for (int i = 0; i < len; ++i) {
      idxvec[i] = INTEGER(idxset)[i] - 1;
    }
    void *res = XGDMatrixSliceDMatrix(R_ExternalPtrAddr(handle), BeginPtr(idxvec), len);
    SEXP ret = PROTECT(R_MakeExternalPtr(res, R_NilValue, R_NilValue));
    R_RegisterCFinalizerEx(ret, _DMatrixFinalizer, TRUE);
    UNPROTECT(1);
    _WrapperEnd();
    return ret;        
  }
  void XGDMatrixSaveBinary_R(SEXP handle, SEXP fname, SEXP silent) {
    _WrapperBegin();
    XGDMatrixSaveBinary(R_ExternalPtrAddr(handle),
                        CHAR(asChar(fname)), asInteger(silent));
    _WrapperEnd();
  }
  void XGDMatrixSetInfo_R(SEXP handle, SEXP field, SEXP array) {
    _WrapperBegin();
    int len = length(array);
    const char *name = CHAR(asChar(field));
    if (!strcmp("group", name)) {
