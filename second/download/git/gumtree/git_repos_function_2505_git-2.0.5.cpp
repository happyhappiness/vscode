int run_column_filter(int colopts, const struct column_options *opts)
{
	const char *av[10];
	int ret, ac = 0;
	struct strbuf sb_colopt  = STRBUF_INIT;
	struct strbuf sb_width   = STRBUF_INIT;
	struct strbuf sb_padding = STRBUF_INIT;

	if (fd_out != -1)
		return -1;

	av[ac++] = "column";
	strbuf_addf(&sb_colopt, "--raw-mode=%d", colopts);
	av[ac++] = sb_colopt.buf;
	if (opts && opts->width) {
		strbuf_addf(&sb_width, "--width=%d", opts->width);
		av[ac++] = sb_width.buf;
	}
	if (opts && opts->indent) {
		av[ac++] = "--indent";
		av[ac++] = opts->indent;
	}
	if (opts && opts->padding) {
		strbuf_addf(&sb_padding, "--padding=%d", opts->padding);
		av[ac++] = sb_padding.buf;
	}
	av[ac] = NULL;

	fflush(stdout);
	memset(&column_process, 0, sizeof(column_process));
	column_process.in = -1;
	column_process.out = dup(1);
	column_process.git_cmd = 1;
	column_process.argv = av;

	ret = start_command(&column_process);

	strbuf_release(&sb_colopt);
	strbuf_release(&sb_width);
	strbuf_release(&sb_padding);

	if (ret)
		return -2;

	fd_out = dup(1);
	close(1);
	dup2(column_process.in, 1);
	close(column_process.in);
	return 0;
}