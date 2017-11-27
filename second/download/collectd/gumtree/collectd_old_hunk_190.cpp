	lt_dlerror (); /* clear errors */

	if ((dlh = lt_dlopen (file)) == NULL)
	{
		const char *error = lt_dlerror ();

		ERROR ("lt_dlopen failed: %s", error);
		fprintf (stderr, "lt_dlopen failed: %s\n", error);
		return (1);
	}

	if ((reg_handle = (void (*) (void)) lt_dlsym (dlh, "module_register")) == NULL)
	{
		WARNING ("Couldn't find symbol ``module_register'' in ``%s'': %s\n",
				file, lt_dlerror ());
		lt_dlclose (dlh);
		return (-1);
	}

	(*reg_handle) ();
