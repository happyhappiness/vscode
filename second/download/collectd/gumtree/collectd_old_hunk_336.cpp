
/*
 * (Try to) load the shared object `file'. Won't complain if it isn't a shared
 * object, but it will bitch about a shared object not having a
 * ``module_register'' symbol..
 */
static int plugin_load_file (char *file)
{
	lt_dlhandle dlh;
	void (*reg_handle) (void);

	DEBUG ("file = %s", file);

	lt_dlinit ();
	lt_dlerror (); /* clear errors */

	if ((dlh = lt_dlopen (file)) == NULL)
	{
		const char *error = lt_dlerror ();

		ERROR ("lt_dlopen (%s) failed: %s", file, error);
		fprintf (stderr, "lt_dlopen (%s) failed: %s\n", file, error);
		return (1);
