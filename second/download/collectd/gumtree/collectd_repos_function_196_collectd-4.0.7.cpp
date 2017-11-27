static int interface_init (void)
{
#if HAVE_LIBKSTAT
	kstat_t *ksp_chain;
	unsigned long long val;

	numif = 0;

	if (kc == NULL)
		return (-1);

	for (numif = 0, ksp_chain = kc->kc_chain;
			(numif < MAX_NUMIF) && (ksp_chain != NULL);
			ksp_chain = ksp_chain->ks_next)
	{
		if (strncmp (ksp_chain->ks_class, "net", 3))
			continue;
		if (ksp_chain->ks_type != KSTAT_TYPE_NAMED)
			continue;
		if (kstat_read (kc, ksp_chain, NULL) == -1)
			continue;
		if ((val = get_kstat_value (ksp_chain, "obytes")) == -1LL)
			continue;
		ksp[numif++] = ksp_chain;
	}
#endif /* HAVE_LIBKSTAT */

	return (0);
}