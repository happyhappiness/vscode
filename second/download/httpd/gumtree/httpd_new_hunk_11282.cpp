	return FORBIDDEN;

    /* Load the module */

    if (!(isapi_handle = LoadLibraryEx(r->filename, NULL,
				       LOAD_WITH_ALTERED_SEARCH_PATH))) {
	ap_log_rerror(APLOG_MARK, APLOG_ALERT, r,
		    "Could not load DLL: %s", r->filename);
	return SERVER_ERROR;
    }

    if (!(isapi_version =
	  (void *)(GetProcAddress(isapi_handle, "GetExtensionVersion")))) {
	ap_log_rerror(APLOG_MARK, APLOG_ALERT, r,
		    "DLL could not load GetExtensionVersion(): %s", r->filename);
	FreeLibrary(isapi_handle);
	return SERVER_ERROR;
    }

    if (!(isapi_entry =
	  (void *)(GetProcAddress(isapi_handle, "HttpExtensionProc")))) {
	ap_log_rerror(APLOG_MARK, APLOG_ALERT, r,
		    "DLL could not load HttpExtensionProc(): %s", r->filename);
	FreeLibrary(isapi_handle);
	return SERVER_ERROR;
    }

    isapi_term = (void *)(GetProcAddress(isapi_handle, "TerminateExtension"));

    /* Run GetExtensionVersion() */

    if ((*isapi_version)(pVer) != TRUE) {
	ap_log_rerror(APLOG_MARK, APLOG_ALERT, r,
		    "ISAPI GetExtensionVersion() failed: %s", r->filename);
	FreeLibrary(isapi_handle);
	return SERVER_ERROR;
    }

    /* Set up variables */
