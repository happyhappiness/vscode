static int pplugin_register_data_set (pTHX_ char *name, AV *dataset)
{
	int ret = 0;

	data_set_t ds;

	if ((NULL == name) || (NULL == dataset))
		return -1;

	if (0 != av2data_set (aTHX_ dataset, name, &ds))
		return -1;

	ret = plugin_register_data_set (&ds);

	free (ds.ds);
	return ret;
}