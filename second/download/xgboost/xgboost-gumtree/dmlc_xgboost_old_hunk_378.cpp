    XGBoosterSaveModel(R_ExternalPtrAddr(handle), CHAR(asChar(fname)));
    _WrapperEnd();
  }
  void XGBoosterDumpModel_R(SEXP handle, SEXP fname,
                            SEXP fmap, SEXP with_stats) {
    _WrapperBegin();
    bst_ulong olen;
    const char **res = XGBoosterDumpModel(R_ExternalPtrAddr(handle),
                                          CHAR(asChar(fmap)),
                                          asInteger(with_stats),
                                          &olen);
    FILE *fo = utils::FopenCheck(CHAR(asChar(fname)), "w");
    for (size_t i = 0; i < olen; ++i) {
      fprintf(fo, "booster[%u]:\n", static_cast<unsigned>(i));
      fprintf(fo, "%s", res[i]);
    }
    fclose(fo);
    _WrapperEnd();
  }
}
 No newline at end of file
