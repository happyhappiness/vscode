static int config_set_callback(const char *key, const char *value, void *cb)
{
	struct config_set *cs = cb;
	configset_add_value(cs, key, value);
	return 0;
}