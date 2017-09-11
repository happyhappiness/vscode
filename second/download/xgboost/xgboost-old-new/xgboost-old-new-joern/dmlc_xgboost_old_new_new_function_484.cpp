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