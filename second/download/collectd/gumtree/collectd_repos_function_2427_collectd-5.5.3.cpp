static _Bool plugin_is_loaded (char const *name)
{
	int status;

	if (plugins_loaded == NULL)
		plugins_loaded = c_avl_create ((void *) strcasecmp);
	assert (plugins_loaded != NULL);

	status = c_avl_get (plugins_loaded, name, /* ret_value = */ NULL);
	return (status == 0);
}