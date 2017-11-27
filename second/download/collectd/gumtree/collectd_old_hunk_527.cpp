 * Authors:
 *   Florian octo Forster <octo at collectd.org>
 */

#include "plugin.h"

void plugin_log (int level, char const *format, ...)
{
  char buffer[1024];
  va_list ap;

  va_start (ap, format);
  vsnprintf (buffer, sizeof (buffer), format, ap);
  va_end (ap);

  printf ("plugin_log (%i, \"%s\");\n", level, buffer);
}

/* vim: set sw=2 sts=2 et : */
