int parse_value (const char *value, value_t *ret_value, const data_source_t ds)
{
	char *endptr = NULL;

	if (DS_TYPE_COUNTER == ds.type)
		ret_value->counter = (counter_t)strtoll (value, &endptr, 0);
	else if (DS_TYPE_GAUGE == ds.type)
		ret_value->gauge = (gauge_t)strtod (value, &endptr);
	else {
		ERROR ("parse_value: Invalid data source \"%s\" "
				"(type = %i).", ds.name, ds.type);
		return -1;
	}

	if (value == endptr) {
		ERROR ("parse_value: Failed to parse string as number: %s.", value);
		return -1;
	}
	else if ((NULL != endptr) && ('\0' != *endptr))
		WARNING ("parse_value: Ignoring trailing garbage after number: %s.",
				endptr);
	return 0;
}