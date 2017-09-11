  printf("%s", msg);
}
#else
#ifndef XGBOOST_STRICT_CXX98__
// include declarations, some one must implement this
void HandleAssertError(const char *msg);
void HandleCheckError(const char *msg);
