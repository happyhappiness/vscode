#  define isinf(f) (!isfinite(f) && !isnan(f))
# endif
#endif /* NAN_ZERO_ZERO */

#include "libcollectdclient/collectd/client.h"

#ifndef PREFIX
# define PREFIX "/opt/" PACKAGE_NAME
#endif

#ifndef LOCALSTATEDIR
# define LOCALSTATEDIR PREFIX "/var"
#endif

#define DEFAULT_SOCK LOCALSTATEDIR"/run/"PACKAGE_NAME"-unixsock"

extern char *optarg;
extern int   optind;

__attribute__((noreturn))
static void exit_usage (const char *name, int status) {
  fprintf ((status == 0) ? stdout : stderr,
      "Usage: %s [options] <command> [cmd options]\n\n"

      "Available options:\n"
      "  -s       Path to collectd's UNIX socket.\n"
