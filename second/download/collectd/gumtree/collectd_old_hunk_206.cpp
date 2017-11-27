 **/

#include "collectd.h"
#include "common.h"
#include "plugin.h"

static int parse_value (const data_set_t *ds, value_list_t *vl,
		const char *type,
	       	FILE *fh, char *buffer)
{
	char *dummy;
	char *ptr;
