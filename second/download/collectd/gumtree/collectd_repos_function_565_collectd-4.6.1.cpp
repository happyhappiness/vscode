static int pplugin_dispatch_values (pTHX_ HV *values)
{
	value_list_t vl = VALUE_LIST_INIT;

	int ret = 0;

	if (NULL == values)
		return -1;

	if (0 != hv2value_list (aTHX_ values, &vl))
		return -1;

	ret = plugin_dispatch_values (&vl);

	sfree (vl.values);
	return ret;
}