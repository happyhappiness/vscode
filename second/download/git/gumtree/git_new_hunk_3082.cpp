		argv_array_pushf(&cld.env_array, "REMOTE_ADDR=[%s]", buf);
		argv_array_pushf(&cld.env_array, "REMOTE_PORT=%d",
				 ntohs(sin6_addr->sin6_port));
#endif
	}

	cld.argv = cld_argv.argv;
	cld.in = incoming;
	cld.out = dup(incoming);

	if (start_command(&cld))
		logerror("unable to fork");
	else
