fprintf(stderr, "%s: cannot open file %s for read access\n"
		    "%s: existing auth data would be lost on "
		    "password mismatch",
		    argv[0], pwfilename, argv[0]);