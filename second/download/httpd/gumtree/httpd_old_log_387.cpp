fprintf(stderr, "Could not open passwd file %s for writing: %s\n",
		    argv[2],
                    apr_strerror(rv, errmsg, sizeof errmsg));