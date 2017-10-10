			/* capabilities may have changed, so get the new capabilities */
			if (imap_exec(ctx, NULL, "CAPABILITY") != RESP_OK)
				goto bail;
		}
#endif
		imap_info("Logging in...\n");
		if (!srvc->user || !srvc->pass) {
			cred.protocol = xstrdup(srvc->use_ssl ? "imaps" : "imap");
			cred.host = xstrdup(srvc->host);

			if (srvc->user)
				cred.username = xstrdup(srvc->user);
			if (srvc->pass)
				cred.password = xstrdup(srvc->pass);

			credential_fill(&cred);

			if (!srvc->user)
				srvc->user = xstrdup(cred.username);
			if (!srvc->pass)
				srvc->pass = xstrdup(cred.password);
		}

		if (CAP(NOLOGIN)) {
			fprintf(stderr, "Skipping account %s@%s, server forbids LOGIN\n", srvc->user, srvc->host);
			goto bail;
		}

		if (srvc->auth_method) {
