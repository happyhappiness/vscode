		 (loader_vtable && loader_vtable->name) ? loader_vtable->name : "(null)",
		 filename ? filename : "(null)");
#endif
	handle->module = (*loader_vtable->module_open) (loader_vtable->dlloader_data,
							filename, advise);
#ifdef LT_DEBUG_LOADERS
	if (!handle->module) {
		char *error;
		LT__GETERROR(error);
		fprintf (stderr, "  Result: Failed\n"
				"  Error message << %s >>\n",
				error ? error : "(null)");
	} else {
		fprintf (stderr, "  Result: Success\n");
	}
#endif

	if (handle->module != 0)
	  {
	    if (advise)
	      {
