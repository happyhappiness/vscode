	    cmd->server->server_uid = ap_user_id;
	    fprintf(stderr,
		    "Warning: User directive in <VirtualHost> "
		    "requires SUEXEC wrapper.\n");
	}
    }
#if !defined (BIG_SECURITY_HOLE) && !defined (__EMX__)
    if (cmd->server->server_uid == 0) {
	fprintf(stderr,
		"Error:\tApache has not been designed to serve pages while\n"
		"\trunning as root.  There are known race conditions that\n"
		"\twill allow any local user to read any file on the system.\n"
		"\tShould you still desire to serve pages as root then\n"
