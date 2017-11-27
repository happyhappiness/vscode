fprintf (stderr, "Calling %s->module_open (%s)\n",
		 (loader_vtable && loader_vtable->name) ? loader_vtable->name : "(null)",
		 filename ? filename : "(null)");