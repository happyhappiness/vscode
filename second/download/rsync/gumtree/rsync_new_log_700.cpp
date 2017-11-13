fprintf(stderr, "\tcon %p os %p nextCharArg \"%s\" nextArg \"%s\" argv[%d] \"%s\"\n",
	con, con->os,
	(con->os->nextCharArg ? con->os->nextCharArg : ""),
	(con->os->nextArg ? con->os->nextArg : ""),
	con->os->next,
	(con->os->argv && con->os->argv[con->os->next]
		? con->os->argv[con->os->next] : ""));