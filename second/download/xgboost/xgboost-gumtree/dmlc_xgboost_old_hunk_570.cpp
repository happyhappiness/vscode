#include <inttypes.h>
#endif


#include <cstdio>
#include <cstdarg>
#include <cstdlib>

namespace xgboost {
/*! \brief namespace for helper utils of the project */
namespace utils {

/*! \brief assert an condition is true, use this to handle debug information */
inline void Assert(bool exp, const char *fmt, ...) {
  if (!exp) {
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "AssertError:");
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");
    exit(-1);
  }
}

/*!\brief same as assert, but this is intended to be used as message for user*/
inline void Check(bool exp, const char *fmt, ...) {
  if (!exp) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");
    exit(-1);
  }
}

/*! \brief report error message, same as check */
inline void Error(const char *fmt, ...) {
  {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");
    exit(-1);
  }
}

