void HandleCheckError(const char *msg) {
  error("%s", msg);
}
void HandlePrint(const char *msg) {
  Rprintf("%s", msg);
}
}  // namespace utils
}  // namespace xgboost

