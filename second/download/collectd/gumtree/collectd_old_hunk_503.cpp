 **/

#include "collectd.h"
#include "common.h"
#include "plugin.h"
#include "utils_parse_option.h"

#define print_to_socket(fh, ...) \
	do { \
		if (fprintf (fh, __VA_ARGS__) < 0) { \
			char errbuf[1024]; \
			WARNING ("handle_flush: failed to write to socket #%i: %s", \
					fileno (fh), sstrerror (errno, errbuf, sizeof (errbuf))); \
			return -1; \
		} \
		fflush(fh); \
	} while (0)

static int add_to_array (char ***array, int *array_num, char *value)
{
	char **temp;

	temp = (char **) realloc (*array, sizeof (char *) * (*array_num + 1));
	if (temp == NULL)
		return (-1);

	*array = temp;
	(*array)[*array_num] = value;
	(*array_num)++;

	return (0);
} /* int add_to_array */

int handle_flush (FILE *fh, char *buffer)
{
	int success = 0;
	int error   = 0;

	double timeout = 0.0;
	char **plugins = NULL;
	int plugins_num = 0;
	char **identifiers = NULL;
	int identifiers_num = 0;

	int i;

	if ((fh == NULL) || (buffer == NULL))
		return (-1);

	DEBUG ("utils_cmd_flush: handle_flush (fh = %p, buffer = %s);",
			(void *) fh, buffer);

	if (strncasecmp ("FLUSH", buffer, strlen ("FLUSH")) != 0)
	{
		print_to_socket (fh, "-1 Cannot parse command.\n");
		return (-1);
	}
	buffer += strlen ("FLUSH");

	while (*buffer != 0)
	{
