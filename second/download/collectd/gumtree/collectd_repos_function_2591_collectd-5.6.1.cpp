static int plugin_mark_loaded (char const *name)
{
	char *name_copy;
	int status;

	name_copy = strdup (name);
	if (name_copy == NULL)
		return (ENOMEM);

	status = c_avl_insert (plugins_loaded,
			/* key = */ name_copy, /* value = */ NULL);
	return (status);
}