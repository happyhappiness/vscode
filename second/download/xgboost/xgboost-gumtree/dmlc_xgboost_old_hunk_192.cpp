#else
// crippled implementation for solaris case
// exception handling is not needed for R, so it is OK.
#define API_BEGIN() 
#define API_END_FINALIZE(Finalize) return 0
#define API_END() return 0

const char *XGBSetGetLastError_(const char *str_set) {
  return NULL;
}
#endif

/*! \brief return str message of the last error */
const char *XGBGetLastError() {
