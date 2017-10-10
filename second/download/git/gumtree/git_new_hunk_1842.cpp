	} /* !preauth */

	if (cred.username)
		credential_approve(&cred);
	credential_clear(&cred);

	/* check the target mailbox exists */
	ctx->name = folder;
	switch (imap_exec(ctx, NULL, "EXAMINE \"%s\"", ctx->name)) {
	case RESP_OK:
		/* ok */
		break;
	case RESP_BAD:
		fprintf(stderr, "IMAP error: could not check mailbox\n");
		goto out;
	case RESP_NO:
		if (imap_exec(ctx, NULL, "CREATE \"%s\"", ctx->name) == RESP_OK) {
			imap_info("Created missing mailbox\n");
		} else {
			fprintf(stderr, "IMAP error: could not create missing mailbox\n");
			goto out;
		}
		break;
	}

	ctx->prefix = "";
	return ctx;

bail:
	if (cred.username)
		credential_reject(&cred);
	credential_clear(&cred);

 out:
	imap_close_store(ctx);
	return NULL;
}

/*
 * Insert CR characters as necessary in *msg to ensure that every LF
