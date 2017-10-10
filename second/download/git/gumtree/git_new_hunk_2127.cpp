		printf("Diag: url=%s\n", url ? url : "NULL");
		printf("Diag: protocol=%s\n", prot_name(protocol));
		printf("Diag: hostandport=%s\n", hostandport ? hostandport : "NULL");
		printf("Diag: path=%s\n", path ? path : "NULL");
		conn = NULL;
	} else if (protocol == PROTO_GIT) {
		/*
		 * Set up virtual host information based on where we will
		 * connect, unless the user has overridden us in
		 * the environment.
		 */
		char *target_host = getenv("GIT_OVERRIDE_VIRTUAL_HOST");
		if (target_host)
			target_host = xstrdup(target_host);
		else
			target_host = xstrdup(hostandport);

		/* These underlying connection commands die() if they
		 * cannot connect.
		 */
		if (git_use_proxy(hostandport))
			conn = git_proxy_connect(fd, hostandport);
		else
			git_tcp_connect(fd, hostandport, flags);
		/*
		 * Separate original protocol components prog and path
