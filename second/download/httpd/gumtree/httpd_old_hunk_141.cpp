    }

    if (apr_file_gets(argsbuffer, HUGE_STRING_LEN, script_err) == APR_SUCCESS) {
	apr_file_puts("%stderr\n", f);
	apr_file_puts(argsbuffer, f);
	while (apr_file_gets(argsbuffer, HUGE_STRING_LEN,
	                     script_err) == APR_SUCCESS)
	    apr_file_puts(argsbuffer, f);
	apr_file_puts("\n", f);
    }

    apr_brigade_destroy(bb);
    apr_file_close(script_err);

