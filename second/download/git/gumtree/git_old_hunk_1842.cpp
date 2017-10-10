	} /* !preauth */

	if (cred.username)
		credential_approve(&cred);
	credential_clear(&cred);

	ctx->prefix = "";
	return ctx;

bail:
	if (cred.username)
		credential_reject(&cred);
	credential_clear(&cred);

	imap_close_store(ctx);
	return NULL;
}

/*
 * Insert CR characters as necessary in *msg to ensure that every LF
