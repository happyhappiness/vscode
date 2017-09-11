}

void SaveDataMatrix(const DataMatrix &dmat, const char *fname, bool silent) {
  if (dmat.magic == DMatrixSimple::kMagic) {
    const DMatrixSimple *p_dmat = static_cast<const DMatrixSimple*>(&dmat);
    p_dmat->SaveBinary(fname, silent);
  } else {
    utils::Error("not implemented");
  }
}

