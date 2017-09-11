    XGBoosterSaveModel(R_ExternalPtrAddr(handle), CHAR(asChar(fname)));
    _WrapperEnd();
  }
  SEXP XGBoosterDumpModel_R(SEXP handle, SEXP fmap, SEXP with_stats) {
    _WrapperBegin();
    bst_ulong olen;
    const char **res = XGBoosterDumpModel(R_ExternalPtrAddr(handle),
    CHAR(asChar(fmap)),
    asInteger(with_stats),
    &olen);
    SEXP out = PROTECT(allocVector(STRSXP, olen));    
    char buffer [2000];
    for (size_t i = 0; i < olen; ++i) {     
      memset(buffer, 0, sizeof buffer);
      sprintf (buffer, "booster[%u]:\n%s", static_cast<unsigned>(i), res[i]);
      SET_STRING_ELT(out, i, mkChar(buffer));
    }
    _WrapperEnd();
    UNPROTECT(1);
    return out;
  }
}
 No newline at end of file
