#include "common.h"
#include "plugin.h"

#include "utils_parse_option.h"

#define print_to_socket(fh, ...) \
        if (fprintf (fh, __VA_ARGS__) < 0) { \
		char errbuf[1024]; \
		WARNING ("handle_putval: failed to write to socket #%i: %s", \
				fileno (fh), sstrerror (errno, errbuf, sizeof (errbuf))); \
		return -1; \
	}

static int dispatch_values (const data_set_t *ds, value_list_t *vl,
	       	FILE *fh, char *buffer)
{
	int status;

