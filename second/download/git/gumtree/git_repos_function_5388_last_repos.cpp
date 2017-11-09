static int parse_expire_cfg_value(const char *var, const char *value, timestamp_t *expire)
{
	if (!value)
		return config_error_nonbool(var);
	if (parse_expiry_date(value, expire))
		return error(_("'%s' for '%s' is not a valid timestamp"),
			     value, var);
	return 0;
}