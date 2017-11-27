#include "collectd.h"
#include "common.h"
#include "plugin.h"

#include "utils_cmd_listval.h"
#include "utils_cache.h"
#include "utils_parse_option.h"

#define print_to_socket(fh, ...) \
  if (fprintf (fh, __VA_ARGS__) < 0) { \
    char errbuf[1024]; \
    WARNING ("handle_listval: failed to write to socket #%i: %s", \
	fileno (fh), sstrerror (errno, errbuf, sizeof (errbuf))); \
    return -1; \
  }

int handle_listval (FILE *fh, char *buffer)
{
  char *command;
  char **names = NULL;
  time_t *times = NULL;
  size_t number = 0;
  size_t i;
  int status;

  DEBUG ("utils_cmd_listval: handle_listval (fh = %p, buffer = %s);",
      (void *) fh, buffer);

  command = NULL;
  status = parse_string (&buffer, &command);
  if (status != 0)
  {
    print_to_socket (fh, "-1 Cannot parse command.\n");
    return (-1);
  }
  assert (command != NULL);

  if (strcasecmp ("LISTVAL", command) != 0)
  {
    print_to_socket (fh, "-1 Unexpected command: `%s'.\n", command);
    return (-1);
  }

  if (*buffer != 0)
  {
    print_to_socket (fh, "-1 Garbage after end of command: %s\n", buffer);
    return (-1);
  }

  status = uc_get_names (&names, &times, &number);
  if (status != 0)
  {
