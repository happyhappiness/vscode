  dmat->CacheLoad(fname, silent, savebuffer);
  return dmat;
}

void SaveDataMatrix(const DataMatrix &dmat, const char *fname, bool silent) {
  utils::Error("not implemented");
}

}  // namespace io
}  // namespace xgboost
