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
}