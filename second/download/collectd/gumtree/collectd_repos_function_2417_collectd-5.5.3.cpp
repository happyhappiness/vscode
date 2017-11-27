static int plugin_load_file (char *file, uint32_t flags)
{
	lt_dlhandle dlh;
	void (*reg_handle) (void);

	lt_dlinit ();
	lt_dlerror (); /* clear errors */

#if LIBTOOL_VERSION == 2
	if (flags & PLUGIN_FLAGS_GLOBAL) {
		lt_dladvise advise;
		lt_dladvise_init(&advise);
		lt_dladvise_global(&advise);
		dlh = lt_dlopenadvise(file, advise);
		lt_dladvise_destroy(&advise);
	} else {
		dlh = lt_dlopen (file);
	}
#else /* if LIBTOOL_VERSION == 1 */
	if (flags & PLUGIN_FLAGS_GLOBAL)
		WARNING ("plugin_load_file: The global flag is not supported, "
				"libtool 2 is required for this.");
	dlh = lt_dlopen (file);
#endif

	if (dlh == NULL)
	{
		char errbuf[1024] = "";

		ssnprintf (errbuf, sizeof (errbuf),
				"lt_dlopen (\"%s\") failed: %s. "
				"The most common cause for this problem is "
				"missing dependencies. Use ldd(1) to check "
				"the dependencies of the plugin "
				"/ shared object.",
				file, lt_dlerror ());

		ERROR ("%s", errbuf);
		/* Make sure this is printed to STDERR in any case, but also
		 * make sure it's printed only once. */
		if (list_log != NULL)
			fprintf (stderr, "ERROR: %s\n", errbuf);

		return (1);
	}

	if ((reg_handle = (void (*) (void)) lt_dlsym (dlh, "module_register")) == NULL)
	{
		WARNING ("Couldn't find symbol \"module_register\" in \"%s\": %s\n",
				file, lt_dlerror ());
		lt_dlclose (dlh);
		return (-1);
	}

	(*reg_handle) ();

	return (0);
}