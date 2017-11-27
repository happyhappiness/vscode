		lt_dladvise_destroy(&advise);
	} else {
        	dlh = lt_dlopen (file);
	}
#else /* if LIBTOOL_VERSION == 1 */
	if (flags & PLUGIN_FLAGS_GLOBAL)
		ERROR ("plugin_load_file: The global flag is not supported, "
				"libtool 2 is required for this.");
	dlh = lt_dlopen (file);
#endif

	if (dlh == NULL)
	{
		const char *error = lt_dlerror ();

		ERROR ("lt_dlopen (%s) failed: %s", file, error);
		fprintf (stderr, "lt_dlopen (%s) failed: %s\n", file, error);
		return (1);
	}

	if ((reg_handle = (void (*) (void)) lt_dlsym (dlh, "module_register")) == NULL)
	{
		WARNING ("Couldn't find symbol `module_register' in `%s': %s\n",
				file, lt_dlerror ());
		lt_dlclose (dlh);
		return (-1);
	}

	(*reg_handle) ();
