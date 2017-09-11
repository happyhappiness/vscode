
using namespace xgboost::wrapper;

/*! \brief  macro to guard beginning and end section of all functions */
#define API_BEGIN() try {
/*!
 * \brief every function starts with API_BEGIN(); and finishes with API_END();
 * \param Finalize optionally put in a finalizer
 */
#define API_END(Finalize) } catch(std::exception &e) {  \
    Finalize; return XGBHandleException(e);             \
  } return 0;

// do not use threadlocal on OSX since it is not always available
#ifndef DISABLE_THREAD_LOCAL
#ifdef __GNUC__
  #define XGB_TREAD_LOCAL __thread
#elif __STDC_VERSION__ >= 201112L
  #define XGB_TREAD_LOCAL _Thread_local
#elif defined(_MSC_VER)
  #define XGB_TREAD_LOCAL __declspec(thread)
#endif
#endif

#ifndef XGB_TREAD_LOCAL
#pragma message("Warning: Threadlocal not enabled, used single thread error handling")
#define XGB_TREAD_LOCAL
#endif

/*!
 * \brief a helper function for error handling
 *  will set the last error to be str_set when it is not NULL
 * \param str_set the error to set
 * \return a pointer message to last error
 */
const char *XGBSetGetLastError_(const char *str_set) {
  // use last_error to record last error
  static XGB_TREAD_LOCAL std::string last_error;
  if (str_set != NULL) {
    last_error = str_set;
  }
  return last_error.c_str();
}

/*! \brief return str message of the last error */
const char *XGBGetLastError() {
  return XGBSetGetLastError_(NULL);
}

/*!
 * \brief handle exception throwed out
 * \param e the exception
 * \return the return value of API after exception is handled
 */
int XGBHandleException(const std::exception &e) {
  XGBSetGetLastError_(e.what());
  return -1;
}

int XGDMatrixCreateFromFile(const char *fname,
                            int silent,
                            DMatrixHandle *out) {
  API_BEGIN();
  *out = LoadDataMatrix(fname, silent != 0, false, false);
  API_END();
}

int XGDMatrixCreateFromCSR(const bst_ulong *indptr,
                           const unsigned *indices,
                           const float *data,
                           bst_ulong nindptr,
                           bst_ulong nelem,
                           DMatrixHandle *out) {
  DMatrixSimple *p_mat = NULL;
  API_BEGIN();
  p_mat = new DMatrixSimple();
  DMatrixSimple &mat = *p_mat;
  mat.row_ptr_.resize(nindptr);
  for (bst_ulong i = 0; i < nindptr; ++i) {
