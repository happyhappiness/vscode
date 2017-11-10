int config_error_nonbool(const char *var)
{
	return error("missing value for '%s'", var);
}