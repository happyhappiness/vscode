		if (!starts_with(buf, arg_cmd))
			die("'argument' token or flush expected");
		argv_array_push(&sent_argv, buf + strlen(arg_cmd));
	}

	/* parse all options sent by the client */
	return write_archive(sent_argv.argc, sent_argv.argv, prefix, 0, NULL, 1);
}

__attribute__((format (printf, 1, 2)))
static void error_clnt(const char *fmt, ...)
{
	struct strbuf buf = STRBUF_INIT;
