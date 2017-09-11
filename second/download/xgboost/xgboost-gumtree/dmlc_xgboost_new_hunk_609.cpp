                                         asInteger(iter),
                                         &vec_dmats[0], &vec_sptr[0], len)); 
  }
  SEXP XGBoosterPredict_R(SEXP handle, SEXP dmat, SEXP output_margin) {
    size_t olen;
    const float *res = XGBoosterPredict(R_ExternalPtrAddr(handle),
                                        R_ExternalPtrAddr(dmat),
                                        asInteger(output_margin),
                                        &olen);
    SEXP ret = PROTECT(allocVector(REALSXP, olen));
    for (size_t i = 0; i < olen; ++i) {
      REAL(ret)[i] = res[i];
    }
    UNPROTECT(1);
    return ret;
  }
  void XGBoosterLoadModel_R(SEXP handle, SEXP fname) {
    XGBoosterLoadModel(R_ExternalPtrAddr(handle), CHAR(asChar(fname)));
  }
  void XGBoosterSaveModel_R(SEXP handle, SEXP fname) {
    XGBoosterSaveModel(R_ExternalPtrAddr(handle), CHAR(asChar(fname)));
  }
  void XGBoosterDumpModel_R(SEXP handle, SEXP fname, SEXP fmap) {
    size_t olen;
    const char **res = XGBoosterDumpModel(R_ExternalPtrAddr(handle),
                                          CHAR(asChar(fmap)),
                                          &olen);
    FILE *fo = utils::FopenCheck(CHAR(asChar(fname)), "w");
    for (size_t i = 0; i < olen; ++i) {
      fprintf(fo, "booster[%lu]:\n", i);
      fprintf(fo, "%s\n", res[i]);
    }
    fclose(fo);
  }
}
