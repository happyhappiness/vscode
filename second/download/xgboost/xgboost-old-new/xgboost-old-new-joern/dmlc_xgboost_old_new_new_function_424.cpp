void SaveDataMatrix(const DataMatrix &dmat, const char *fname, bool silent) {
  if (!strcmp(fname + strlen(fname) - 5, ".page")) {    
    DMatrixPage::Save(fname, dmat, silent);
    return;
  }
  if (dmat.magic == DMatrixSimple::kMagic) {
    const DMatrixSimple *p_dmat = static_cast<const DMatrixSimple*>(&dmat);
    p_dmat->SaveBinary(fname, silent);
  } else {
    DMatrixSimple smat;
    smat.CopyFrom(dmat);
    smat.SaveBinary(fname, silent);
  }
}