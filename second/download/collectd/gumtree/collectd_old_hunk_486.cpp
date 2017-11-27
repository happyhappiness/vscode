#include "common.h"
#include "plugin.h"

#include "utils_parse_option.h"

#define print_to_socket(fh, ...) \
  do { \
    if (fprintf (fh, __VA_ARGS__) < 0) { \
      char errbuf[1024]; \
      WARNING ("handle_putnotif: failed to write to socket #%i: %s", \
          fileno (fh), sstrerror (errno, errbuf, sizeof (errbuf))); \
      return -1; \
    } \
    fflush(fh); \
  } while (0)

static int set_option_severity (notification_t *n, const char *value)
{
  if (strcasecmp (value, "Failure") == 0)
    n->severity = NOTIF_FAILURE;
  else if (strcasecmp (value, "Warning") == 0)
