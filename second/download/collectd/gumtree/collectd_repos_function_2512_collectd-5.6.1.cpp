int cf_util_get_service (const oconfig_item_t *ci, char **ret_string) /* {{{ */
{
	int port;
	char *service;
	int status;

	if (ci->values_num != 1)
	{
		ERROR ("cf_util_get_service: The %s option requires exactly "
				"one argument.", ci->key);
		return (-1);
	}

	if (ci->values[0].type == OCONFIG_TYPE_STRING)
		return (cf_util_get_string (ci, ret_string));
	if (ci->values[0].type != OCONFIG_TYPE_NUMBER)
	{
		ERROR ("cf_util_get_service: The %s option requires "
				"exactly one string or numeric argument.",
				ci->key);
	}

	port = 0;
	status = cf_util_get_int (ci, &port);
	if (status != 0)
		return (status);
	else if ((port < 1) || (port > 65535))
	{
		ERROR ("cf_util_get_service: The port number given "
				"for the %s option is out of "
				"range (%i).", ci->key, port);
		return (-1);
	}

	service = malloc (6);
	if (service == NULL)
	{
		ERROR ("cf_util_get_service: Out of memory.");
		return (-1);
	}
	ssnprintf (service, 6, "%i", port);

	sfree (*ret_string);
	*ret_string = service;

	return (0);
}