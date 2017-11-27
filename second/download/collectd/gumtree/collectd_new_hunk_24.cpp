
long long get_kstat_value (kstat_t *ksp, char *name)
{
	kstat_named_t *kn;
	long long retval = -1LL;

#ifdef assert
	assert (ksp != NULL);
	assert (ksp->ks_type == KSTAT_TYPE_NAMED);
#else
	if (ksp == NULL)
	{
		fprintf (stderr, "ERROR: %s:%i: ksp == NULL\n", __FILE__, __LINE__);
		return (-1LL);
	}
	else if (ksp->ks_type != KSTAT_TYPE_NAMED)
	{
		fprintf (stderr, "ERROR: %s:%i: ksp->ks_type != KSTAT_TYPE_NAMED\n", __FILE__, __LINE__);
		return (-1LL);
	}
#endif

	if ((kn = (kstat_named_t *) kstat_data_lookup (ksp, name)) == NULL)
		return (retval);

	if (kn->data_type == KSTAT_DATA_INT32)
		retval = (long long) kn->value.i32;
	else if (kn->data_type == KSTAT_DATA_UINT32)
