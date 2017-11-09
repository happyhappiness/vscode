static int column_config(const char *var, const char *value,
			 const char *key, unsigned int *colopts)
{
	if (!value)
		return config_error_nonbool(var);
	if (parse_config(colopts, value))
		return error("invalid column.%s mode %s", key, value);
	return 0;
}