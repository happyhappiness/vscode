fprintf(stderr, "IMAP command '%s' returned response (%s) - %s\n",
					 memcmp(cmdp->cmd, "LOGIN", 5) ?
							cmdp->cmd : "LOGIN <user> <pass>",
							arg, cmd ? cmd : "");