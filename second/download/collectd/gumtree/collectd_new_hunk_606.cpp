 * Authors:
 *   Håkon J Dugstad Johnsen <hakon-dugstad.johnsen at telenor.com>
 *   Sebastian "tokkee" Harl <sh@tokkee.org>
 **/

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#include <assert.h>
#include <errno.h>

#if NAN_STATIC_DEFAULT
#include <math.h>
/* #endif NAN_STATIC_DEFAULT*/
#elif NAN_STATIC_ISOC
#ifndef __USE_ISOC99
#define DISABLE_ISOC99 1
#define __USE_ISOC99 1
#endif /* !defined(__USE_ISOC99) */
#include <math.h>
#if DISABLE_ISOC99
#undef DISABLE_ISOC99
#undef __USE_ISOC99
#endif /* DISABLE_ISOC99 */
/* #endif NAN_STATIC_ISOC */
#elif NAN_ZERO_ZERO
#include <math.h>
#ifdef NAN
#undef NAN
#endif
#define NAN (0.0 / 0.0)
#ifndef isnan
#define isnan(f) ((f) != (f))
#endif /* !defined(isnan) */
#ifndef isfinite
#define isfinite(f) (((f) - (f)) == 0.0)
#endif
#ifndef isinf
#define isinf(f) (!isfinite(f) && !isnan(f))
#endif
#endif /* NAN_ZERO_ZERO */

#include "libcollectdclient/collectd/client.h"

#ifndef PREFIX
#define PREFIX "/opt/" PACKAGE_NAME
#endif

#ifndef LOCALSTATEDIR
#define LOCALSTATEDIR PREFIX "/var"
#endif

#define DEFAULT_SOCK LOCALSTATEDIR "/run/" PACKAGE_NAME "-unixsock"

extern char *optarg;
extern int optind;

__attribute__((noreturn)) static void exit_usage(const char *name, int status) {
  fprintf(
      (status == 0) ? stdout : stderr,
      "Usage: %s [options] <command> [cmd options]\n\n"

      "Available options:\n"
      "  -s       Path to collectd's UNIX socket.\n"
      "           Default: " DEFAULT_SOCK "\n"

      "\n  -h       Display this help and exit.\n"

      "\nAvailable commands:\n\n"

      " * getval <identifier>\n"
