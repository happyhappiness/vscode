static int get_cmd_result(struct imap_store *ctx, struct imap_cmd *tcmd)
{
	struct imap *imap = ctx->imap;
	struct imap_cmd *cmdp, **pcmdp, *ncmdp;
	char *cmd, *arg, *arg1, *p;
	int n, resp, resp2, tag;

	for (;;) {
		if (buffer_gets(&imap->buf, &cmd))
			return RESP_BAD;

		arg = next_arg(&cmd);
		if (*arg == '*') {
			arg = next_arg(&cmd);
			if (!arg) {
				fprintf(stderr, "IMAP error: unable to parse untagged response\n");
				return RESP_BAD;
			}

			if (!strcmp("NAMESPACE", arg)) {
				/* rfc2342 NAMESPACE response. */
				skip_list(&cmd); /* Personal mailboxes */
				skip_list(&cmd); /* Others' mailboxes */
				skip_list(&cmd); /* Shared mailboxes */
			} else if (!strcmp("OK", arg) || !strcmp("BAD", arg) ||
				   !strcmp("NO", arg) || !strcmp("BYE", arg)) {
				if ((resp = parse_response_code(ctx, NULL, cmd)) != RESP_OK)
					return resp;
			} else if (!strcmp("CAPABILITY", arg)) {
				parse_capability(imap, cmd);
			} else if ((arg1 = next_arg(&cmd))) {
				; /*
				   * Unhandled response-data with at least two words.
				   * Ignore it.
				   *
				   * NEEDSWORK: Previously this case handled '<num> EXISTS'
				   * and '<num> RECENT' but as a probably-unintended side
				   * effect it ignores other unrecognized two-word
				   * responses.  imap-send doesn't ever try to read
				   * messages or mailboxes these days, so consider
				   * eliminating this case.
				   */
			} else {
				fprintf(stderr, "IMAP error: unable to parse untagged response\n");
				return RESP_BAD;
			}
		} else if (!imap->in_progress) {
			fprintf(stderr, "IMAP error: unexpected reply: %s %s\n", arg, cmd ? cmd : "");
			return RESP_BAD;
		} else if (*arg == '+') {
			/* This can happen only with the last command underway, as
			   it enforces a round-trip. */
			cmdp = (struct imap_cmd *)((char *)imap->in_progress_append -
			       offsetof(struct imap_cmd, next));
			if (cmdp->cb.data) {
				n = socket_write(&imap->buf.sock, cmdp->cb.data, cmdp->cb.dlen);
				free(cmdp->cb.data);
				cmdp->cb.data = NULL;
				if (n != (int)cmdp->cb.dlen)
					return RESP_BAD;
			} else if (cmdp->cb.cont) {
				if (cmdp->cb.cont(ctx, cmdp, cmd))
					return RESP_BAD;
			} else {
				fprintf(stderr, "IMAP error: unexpected command continuation request\n");
				return RESP_BAD;
			}
			if (socket_write(&imap->buf.sock, "\r\n", 2) != 2)
				return RESP_BAD;
			if (!cmdp->cb.cont)
				imap->literal_pending = 0;
			if (!tcmd)
				return DRV_OK;
		} else {
			tag = atoi(arg);
			for (pcmdp = &imap->in_progress; (cmdp = *pcmdp); pcmdp = &cmdp->next)
				if (cmdp->tag == tag)
					goto gottag;
			fprintf(stderr, "IMAP error: unexpected tag %s\n", arg);
			return RESP_BAD;
		gottag:
			if (!(*pcmdp = cmdp->next))
				imap->in_progress_append = pcmdp;
			imap->num_in_progress--;
			if (cmdp->cb.cont || cmdp->cb.data)
				imap->literal_pending = 0;
			arg = next_arg(&cmd);
			if (!strcmp("OK", arg))
				resp = DRV_OK;
			else {
				if (!strcmp("NO", arg)) {
					if (cmdp->cb.create && cmd && (cmdp->cb.trycreate || !memcmp(cmd, "[TRYCREATE]", 11))) { /* SELECT, APPEND or UID COPY */
						p = strchr(cmdp->cmd, '"');
						if (!issue_imap_cmd(ctx, NULL, "CREATE \"%.*s\"", (int)(strchr(p + 1, '"') - p + 1), p)) {
							resp = RESP_BAD;
							goto normal;
						}
						/* not waiting here violates the spec, but a server that does not
						   grok this nonetheless violates it too. */
						cmdp->cb.create = 0;
						if (!(ncmdp = issue_imap_cmd(ctx, &cmdp->cb, "%s", cmdp->cmd))) {
							resp = RESP_BAD;
							goto normal;
						}
						free(cmdp->cmd);
						free(cmdp);
						if (!tcmd)
							return 0;	/* ignored */
						if (cmdp == tcmd)
							tcmd = ncmdp;
						continue;
					}
					resp = RESP_NO;
				} else /*if (!strcmp("BAD", arg))*/
					resp = RESP_BAD;
				fprintf(stderr, "IMAP command '%s' returned response (%s) - %s\n",
					 memcmp(cmdp->cmd, "LOGIN", 5) ?
							cmdp->cmd : "LOGIN <user> <pass>",
							arg, cmd ? cmd : "");
			}
			if ((resp2 = parse_response_code(ctx, &cmdp->cb, cmd)) > resp)
				resp = resp2;
		normal:
			if (cmdp->cb.done)
				cmdp->cb.done(ctx, cmdp, resp);
			free(cmdp->cb.data);
			free(cmdp->cmd);
			free(cmdp);
			if (!tcmd || tcmd == cmdp)
				return resp;
		}
	}
	/* not reached */
}