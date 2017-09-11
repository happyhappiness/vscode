    XGBoosterSaveModel(R_ExternalPtrAddr(handle), CHAR(asChar(fname)));
  }
  void XGBoosterDumpModel_R(SEXP handle, SEXP fname, SEXP fmap) {
    uint64_t olen;
    const char **res = XGBoosterDumpModel(R_ExternalPtrAddr(handle),
                                          CHAR(asChar(fmap)),
                                          &olen);
    FILE *fo = utils::FopenCheck(CHAR(asChar(fname)), "w");
    for (size_t i = 0; i < olen; ++i) {
      fprintf(fo, "booster[%lu]:\n", i);
      fprintf(fo, "%s", res[i]);
    }
    fclose(fo);
