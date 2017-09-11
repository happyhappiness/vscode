void XGDMatrixSaveBinary_R(SEXP handle, SEXP fname, SEXP silent) {
    XGDMatrixSaveBinary(R_ExternalPtrAddr(handle),
                        CHAR(asChar(fname)), asInteger(silent));
  }