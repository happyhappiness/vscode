static int pidfile_remove (void)
{
	const char *file = global_option_get ("PIDFile");
	if (file == NULL)
		return 0;

	return (unlink (file));
}