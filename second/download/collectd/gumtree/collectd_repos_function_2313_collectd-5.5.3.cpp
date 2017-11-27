static int do_init (void)
{
#if HAVE_SETLOCALE
	if (setlocale (LC_NUMERIC, COLLECTD_LOCALE) == NULL)
		WARNING ("setlocale (\"%s\") failed.", COLLECTD_LOCALE);

	/* Update the environment, so that libraries that are calling
	 * setlocale(LC_NUMERIC, "") don't accidentally revert these changes. */
	unsetenv ("LC_ALL");
	setenv ("LC_NUMERIC", COLLECTD_LOCALE, /* overwrite = */ 1);
#endif

#if HAVE_LIBKSTAT
	kc = NULL;
	update_kstat ();
#endif

#if HAVE_LIBSTATGRAB
	if (sg_init (
# if HAVE_LIBSTATGRAB_0_90
		    0
# endif
		    ))
	{
		ERROR ("sg_init: %s", sg_str_error (sg_get_error ()));
		return (-1);
	}

	if (sg_drop_privileges ())
	{
		ERROR ("sg_drop_privileges: %s", sg_str_error (sg_get_error ()));
		return (-1);
	}
#endif

	plugin_init_all ();

	return (0);
}