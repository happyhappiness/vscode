#include <regex.h>

#include "common.h"
#include "utils_vl_lookup.h"
#include "utils_avltree.h"

#if HAVE_LIBKSTAT
kstat_ctl_t *kc;
#endif /* HAVE_LIBKSTAT */

#if BUILD_TEST
# define sstrncpy strncpy
# define plugin_log(s, ...) do { \
  printf ("[severity %i] ", s); \
  printf (__VA_ARGS__); \
  printf ("\n"); \
