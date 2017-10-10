		printf("Diag: url=%s\n", url ? url : "NULL");
		printf("Diag: protocol=%s\n", prot_name(protocol));
		printf("Diag: hostandport=%s\n", hostandport ? hostandport : "NULL");
		printf("Diag: path=%s\n", path ? path : "NULL");
		conn = NULL;
	} else if (protocol == PROTO_GIT) {
		/* These underlying connection commands die() if they
		 * cannot connect.
		 */
		char *target_host = xstrdup(hostandport);
		if (git_use_proxy(hostandport))
			conn = git_proxy_connect(fd, hostandport);
		else
			git_tcp_connect(fd, hostandport, flags);
		/*
		 * Separate original protocol components prog and path
