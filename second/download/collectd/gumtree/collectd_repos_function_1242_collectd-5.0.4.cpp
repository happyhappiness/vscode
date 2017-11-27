static int pidfile_remove (void)
{
	const char *file = global_option_get ("PIDFile");

	DEBUG ("unlink (%s)", (file != NULL) ? file : "<null>");
	return (unlink (file));
}