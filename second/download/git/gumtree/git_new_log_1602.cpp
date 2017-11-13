fprintf(stderr, "IMAP command '%s' returned response (%s) - %s\n",
					!starts_with(cmdp->cmd, "LOGIN") ?
							cmdp->cmd : "LOGIN <user> <pass>",
							arg, cmd ? cmd : "");