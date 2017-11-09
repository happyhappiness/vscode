static void set_reflog_message(int argc, const char **argv)
{
	int i;
	struct strbuf msg = STRBUF_INIT;

	for (i = 0; i < argc; i++) {
		if (i)
			strbuf_addch(&msg, ' ');
		strbuf_addstr(&msg, argv[i]);
	}

	setenv("GIT_REFLOG_ACTION", msg.buf, 0);

	strbuf_release(&msg);
}