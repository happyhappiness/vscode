			if (cmdp->cb.cont || cmdp->cb.data)
				imap->literal_pending = 0;
			arg = next_arg(&cmd);
			if (!strcmp("OK", arg))
				resp = DRV_OK;
			else {
				if (!strcmp("NO", arg))
					resp = RESP_NO;
				else /*if (!strcmp("BAD", arg))*/
					resp = RESP_BAD;
				fprintf(stderr, "IMAP command '%s' returned response (%s) - %s\n",
					!starts_with(cmdp->cmd, "LOGIN") ?
							cmdp->cmd : "LOGIN <user> <pass>",
							arg, cmd ? cmd : "");
			}
			if ((resp2 = parse_response_code(ctx, &cmdp->cb, cmd)) > resp)
				resp = resp2;
			if (cmdp->cb.done)
				cmdp->cb.done(ctx, cmdp, resp);
			free(cmdp->cb.data);
			free(cmdp->cmd);
			free(cmdp);
			if (!tcmd || tcmd == cmdp)
