static int cna_init (void) /* {{{ */
{
	char err[256] = { 0 };

	if (!na_startup(err, sizeof(err))) {
		err[sizeof (err) - 1] = 0;
		ERROR("netapp plugin: Error initializing netapp API: %s", err);
		return 1;
	}

	return (0);
}