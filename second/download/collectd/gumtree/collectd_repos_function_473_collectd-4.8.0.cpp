int get_kstat (kstat_t **ksp_ptr, char *module, int instance, char *name)
{
	char ident[128];

	*ksp_ptr = NULL;
	
	if (kc == NULL)
		return (-1);

	ssnprintf (ident, sizeof (ident), "%s,%i,%s", module, instance, name);

	*ksp_ptr = kstat_lookup (kc, module, instance, name);
	if (*ksp_ptr == NULL)
	{
		ERROR ("get_kstat: Cound not find kstat %s", ident);
		return (-1);
	}

	if ((*ksp_ptr)->ks_type != KSTAT_TYPE_NAMED)
	{
		ERROR ("get_kstat: kstat %s has wrong type", ident);
		*ksp_ptr = NULL;
		return (-1);
	}

#ifdef assert
	assert (*ksp_ptr != NULL);
	assert ((*ksp_ptr)->ks_type == KSTAT_TYPE_NAMED);
#endif

	if (kstat_read (kc, *ksp_ptr, NULL) == -1)
	{
		ERROR ("get_kstat: kstat %s could not be read", ident);
		return (-1);
	}

	if ((*ksp_ptr)->ks_type != KSTAT_TYPE_NAMED)
	{
		ERROR ("get_kstat: kstat %s has wrong type", ident);
		return (-1);
	}

	return (0);
}