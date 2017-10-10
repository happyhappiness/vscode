				fprintf(stderr, "IMAP error: LOGIN failed\n");
				goto bail;
			}
		}
	} /* !preauth */

	ctx->prefix = "";
	return ctx;

bail:
	imap_close_store(ctx);
	return NULL;
}

/*
 * Insert CR characters as necessary in *msg to ensure that every LF
