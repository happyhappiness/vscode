 **/

#include "collectd.h"
#include "common.h"
#include "plugin.h"

static int parse_option_severity (notification_t *n, char *value)
{
  if (strcasecmp (value, "Failure") == 0)
    n->severity = NOTIF_FAILURE;
  else if (strcasecmp (value, "Warning") == 0)
    n->severity = NOTIF_WARNING;
