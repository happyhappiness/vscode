#include "collectd.h"
#include "common.h"
#include "plugin.h"

#include "utils_cmd_listval.h"
#include "utils_cache.h"

#define print_to_socket(fh, ...) \
  if (fprintf (fh, __VA_ARGS__) < 0) { \
    char errbuf[1024]; \
    WARNING ("handle_listval: failed to write to socket #%i: %s", \
	fileno (fh), sstrerror (errno, errbuf, sizeof (errbuf))); \
    return -1; \
  }

int handle_listval (FILE *fh, char **fields, int fields_num)
{
  char **names = NULL;
  time_t *times = NULL;
  size_t number = 0;
  size_t i;
  int status;

  if (fields_num != 1)
  {
    DEBUG ("command listval: us_handle_listval: Wrong number of fields: %i",
	fields_num);
    print_to_socket (fh, "-1 Wrong number of fields: Got %i, expected 1.\n",
	fields_num);
    return (-1);
  }

  status = uc_get_names (&names, &times, &number);
  if (status != 0)
  {
