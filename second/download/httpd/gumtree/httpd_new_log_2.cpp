fprintf(stderr,
		"Error:\tApache has not been designed to serve pages while\n"
		"\trunning as root.  There are known race conditions that\n"
		"\twill allow any local user to read any file on the system.\n"
		"\tShould you still desire to serve pages as root then\n"
		"\tadd -DBIG_SECURITY_HOLE to the EXTRA_CFLAGS line in your\n"
		"\tsrc/Configuration file and rebuild the server.  It is\n"
		"\tstrongly suggested that you instead modify the User\n"
		"\tdirective in your httpd.conf file to list a non-root\n"
		"\tuser.\n");