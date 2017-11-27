static int config_query_callback (udb_query_t *q, oconfig_item_t *ci)
{
	if (0 == strcasecmp ("Param", ci->key))
		return config_query_param_add (q, ci);

	log_err ("Option not allowed within a Query block: `%s'", ci->key);

	return (-1);
}