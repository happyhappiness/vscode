/*! \brief report error message, same as check */
inline void Error(const char *fmt, ...) {
  {
    std::string msg(kErrorBuffer, '\0');
    va_list args;
    va_start(args, fmt);
    vsnprintf(&msg[0], kErrorBuffer, fmt, args);
    va_end(args);
    HandleCheckError(msg.c_str());
  }
}

/*! \brief replace fopen, report error when the file open fails */
inline FILE *FopenCheck(const char *fname, const char *flag) {
  FILE *fp = fopen64(fname, flag);
  Check(fp != NULL, "can not open file \"%s\"\n", fname);
  return fp;
}

}  // namespace utils
}  // namespace xgboost
#endif  // XGBOOST_UTILS_UTILS_H_
