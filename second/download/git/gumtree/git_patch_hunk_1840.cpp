 			if (cmdp->cb.cont || cmdp->cb.data)
 				imap->literal_pending = 0;
 			arg = next_arg(&cmd);
 			if (!strcmp("OK", arg))
 				resp = DRV_OK;
 			else {
-				if (!strcmp("NO", arg)) {
-					if (cmdp->cb.create && cmd && (cmdp->cb.trycreate || !memcmp(cmd, "[TRYCREATE]", 11))) { /* SELECT, APPEND or UID COPY */
-						p = strchr(cmdp->cmd, '"');
-						if (!issue_imap_cmd(ctx, NULL, "CREATE \"%.*s\"", (int)(strchr(p + 1, '"') - p + 1), p)) {
-							resp = RESP_BAD;
-							goto normal;
-						}
-						/* not waiting here violates the spec, but a server that does not
-						   grok this nonetheless violates it too. */
-						cmdp->cb.create = 0;
-						if (!(ncmdp = issue_imap_cmd(ctx, &cmdp->cb, "%s", cmdp->cmd))) {
-							resp = RESP_BAD;
-							goto normal;
-						}
-						free(cmdp->cmd);
-						free(cmdp);
-						if (!tcmd)
-							return 0;	/* ignored */
-						if (cmdp == tcmd)
-							tcmd = ncmdp;
-						continue;
-					}
+				if (!strcmp("NO", arg))
 					resp = RESP_NO;
-				} else /*if (!strcmp("BAD", arg))*/
+				else /*if (!strcmp("BAD", arg))*/
 					resp = RESP_BAD;
 				fprintf(stderr, "IMAP command '%s' returned response (%s) - %s\n",
-					 memcmp(cmdp->cmd, "LOGIN", 5) ?
+					!starts_with(cmdp->cmd, "LOGIN") ?
 							cmdp->cmd : "LOGIN <user> <pass>",
 							arg, cmd ? cmd : "");
 			}
 			if ((resp2 = parse_response_code(ctx, &cmdp->cb, cmd)) > resp)
 				resp = resp2;
-		normal:
 			if (cmdp->cb.done)
 				cmdp->cb.done(ctx, cmdp, resp);
 			free(cmdp->cb.data);
 			free(cmdp->cmd);
 			free(cmdp);
 			if (!tcmd || tcmd == cmdp)
