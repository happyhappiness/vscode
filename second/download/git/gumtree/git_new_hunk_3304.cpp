				}
			} else {
				fprintf(stderr, "Unknown authentication method:%s\n", srvc->host);
				goto bail;
			}
		} else {
			if (CAP(NOLOGIN)) {
				fprintf(stderr, "Skipping account %s@%s, server forbids LOGIN\n",
					srvc->user, srvc->host);
				goto bail;
			}
			if (!imap->buf.sock.ssl)
				imap_warn("*** IMAP Warning *** Password is being "
					  "sent in the clear\n");
			if (imap_exec(ctx, NULL, "LOGIN \"%s\" \"%s\"", srvc->user, srvc->pass) != RESP_OK) {
				fprintf(stderr, "IMAP error: LOGIN failed\n");
				goto bail;
