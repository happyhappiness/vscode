		 (loader_vtable && loader_vtable->name) ? loader_vtable->name : "(null)",
		 filename ? filename : "(null)");
#endif
	handle->module = (*loader_vtable->module_open) (loader_vtable->dlloader_data,
							filename, advise);
#ifdef LT_DEBUG_LOADERS
	fprintf (stderr, "  Result: %s\n",
		 handle->module ? "Success" : "Failed");
#endif

	if (handle->module != 0)
	  {
	    if (advise)
	      {
