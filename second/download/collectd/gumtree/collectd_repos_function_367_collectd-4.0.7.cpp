static int tape_init (void)
{
#ifdef HAVE_LIBKSTAT
	kstat_t *ksp_chain;

	numtape = 0;

	if (kc == NULL)
		return (-1);

	for (numtape = 0, ksp_chain = kc->kc_chain;
			(numtape < MAX_NUMTAPE) && (ksp_chain != NULL);
			ksp_chain = ksp_chain->ks_next)
	{
		if (strncmp (ksp_chain->ks_class, "tape", 4) )
			continue;
		if (ksp_chain->ks_type != KSTAT_TYPE_IO)
			continue;
		ksp[numtape++] = ksp_chain;
	}
#endif

	return (0);
}