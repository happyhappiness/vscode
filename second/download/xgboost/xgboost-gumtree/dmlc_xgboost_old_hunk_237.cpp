
using namespace xgboost::wrapper;

void* XGDMatrixCreateFromFile(const char *fname, int silent) {
  return LoadDataMatrix(fname, silent != 0, false, false);
}
void* XGDMatrixCreateFromCSR(const bst_ulong *indptr,
                             const unsigned *indices,
                             const float *data,
                             bst_ulong nindptr,
                             bst_ulong nelem) {
  DMatrixSimple *p_mat = new DMatrixSimple();
  DMatrixSimple &mat = *p_mat;
  mat.row_ptr_.resize(nindptr);
  for (bst_ulong i = 0; i < nindptr; ++i) {
