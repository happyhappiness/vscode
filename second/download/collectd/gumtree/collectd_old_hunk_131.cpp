
	if ((dlh = lt_dlopen (file)) == NULL)
	{
		const char *error = lt_dlerror ();

		ERROR ("lt_dlopen failed: %s", error);
		return (1);
	}

	if ((reg_handle = (void (*) (void)) lt_dlsym (dlh, "module_register")) == NULL)
	{
		WARNING ("Couldn't find symbol ``module_register'' in ``%s'': %s\n",
