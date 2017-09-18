apr_file_printf(errfile,
		    "%s: cannot modify file %s; use '-c' to create it\n",
		    argv[0], pwfilename);