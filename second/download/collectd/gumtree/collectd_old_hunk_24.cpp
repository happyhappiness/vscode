
long long get_kstat_value (kstat_t *ksp, char *name)
{
	kstat_named_t *kn;
	long long retval = -1LL;

	if ((kn = (kstat_named_t *) kstat_data_lookup (ksp, name)) == NULL)
		return (retval);

	if (kn->data_type == KSTAT_DATA_INT32)
		retval = (long long) kn->value.i32;
	else if (kn->data_type == KSTAT_DATA_UINT32)
