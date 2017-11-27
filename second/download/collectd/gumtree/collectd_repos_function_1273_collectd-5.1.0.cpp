static int do_init (void)
{
#if HAVE_LIBKSTAT
	kc = NULL;
	update_kstat ();
#endif

#if HAVE_LIBSTATGRAB
	if (sg_init ())
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