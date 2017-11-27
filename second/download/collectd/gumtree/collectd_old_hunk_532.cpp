#define print_to_socket(fh, ...) \
    do { \
        if (fprintf (fh, __VA_ARGS__) < 0) { \
            char errbuf[1024]; \
            WARNING ("handle_putval: failed to write to socket #%i: %s", \
                    fileno (fh), sstrerror (errno, errbuf, sizeof (errbuf))); \
            return -1; \
        } \
        fflush(fh); \
    } while (0)

static int dispatch_values (const data_set_t *ds, value_list_t *vl,
	       	FILE *fh, char *buffer)
{
	int status;

	status = parse_values (buffer, vl, ds);
	if (status != 0)
	{
		print_to_socket (fh, "-1 Parsing the values string failed.\n");
		return (-1);
	}

	plugin_dispatch_values (vl);
	return (0);
} /* int dispatch_values */

static int set_option (value_list_t *vl, const char *key, const char *value)
{
	if ((vl == NULL) || (key == NULL) || (value == NULL))
		return (-1);

	if (strcasecmp ("interval", key) == 0)
