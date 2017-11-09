static int archive_zip_config(const char *var, const char *value, void *data)
{
	return userdiff_config(var, value);
}