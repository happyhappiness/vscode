static int c_psql_config_writer (oconfig_item_t *ci)
{
	c_psql_writer_t *writer;
	c_psql_writer_t *tmp;

	int status = 0;
	int i;

	if ((ci->values_num != 1)
			|| (ci->values[0].type != OCONFIG_TYPE_STRING)) {
		log_err ("<Writer> expects a single string argument.");
		return 1;
	}

	tmp = (c_psql_writer_t *)realloc (writers,
			sizeof (*writers) * (writers_num + 1));
	if (tmp == NULL) {
		log_err ("Out of memory.");
		return -1;
	}

	writers = tmp;
	writer  = writers + writers_num;
	memset (writer, 0, sizeof (*writer));

	writer->name = sstrdup (ci->values[0].value.string);
	writer->statement = NULL;
	writer->store_rates = 1;

	for (i = 0; i < ci->children_num; ++i) {
		oconfig_item_t *c = ci->children + i;

		if (strcasecmp ("Statement", c->key) == 0)
			status = cf_util_get_string (c, &writer->statement);
		else if (strcasecmp ("StoreRates", c->key) == 0)
			status = cf_util_get_boolean (c, &writer->store_rates);
		else
			log_warn ("Ignoring unknown config key \"%s\".", c->key);
	}

	if (status != 0) {
		sfree (writer->statement);
		sfree (writer->name);
		return status;
	}

	++writers_num;
	return 0;
}