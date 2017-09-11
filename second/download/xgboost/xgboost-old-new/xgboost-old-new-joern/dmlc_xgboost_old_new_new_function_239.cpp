SEXP XGBoosterDumpModel_R(SEXP handle, SEXP fmap, SEXP with_stats) {
    _WrapperBegin();
    bst_ulong olen;
    const char **res = XGBoosterDumpModel(R_ExternalPtrAddr(handle),
    CHAR(asChar(fmap)),
    asInteger(with_stats),
    &olen);
    SEXP out = PROTECT(allocVector(STRSXP, olen));    
    for (size_t i = 0; i < olen; ++i) {     
      stringstream stream;
      stream <<  "booster["<<i<<"]\n" << res[i];
      SET_STRING_ELT(out, i, mkChar(stream.str().c_str()));
    }
    _WrapperEnd();
    UNPROTECT(1);
    return out;
  }