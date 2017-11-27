static int set_timeout (oconfig_item_t *ci, int *timeout)
{
	if ((0 != ci->children_num) || (1 != ci->values_num)
			|| (OCONFIG_TYPE_NUMBER != ci->values[0].type)) {
		log_err ("%s expects a single number argument.", ci->key);
		return 1;
	}

	*timeout = (int)ci->values[0].value.number;
	if (0 > *timeout)
		*timeout = DEFAULT_TIMEOUT;
	return 0;
}