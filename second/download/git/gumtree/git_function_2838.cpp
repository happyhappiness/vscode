static int split_mail_conv(mail_conv_fn fn, struct am_state *state,
			const char **paths, int keep_cr)
{
	static const char *stdin_only[] = {"-", NULL};
	int i;

	if (!*paths)
		paths = stdin_only;

	for (i = 0; *paths; paths++, i++) {
		FILE *in, *out;
		const char *mail;
		int ret;

		if (!strcmp(*paths, "-"))
			in = stdin;
		else
			in = fopen(*paths, "r");

		if (!in)
			return error(_("could not open '%s' for reading: %s"),
					*paths, strerror(errno));

		mail = mkpath("%s/%0*d", state->dir, state->prec, i + 1);

		out = fopen(mail, "w");
		if (!out)
			return error(_("could not open '%s' for writing: %s"),
					mail, strerror(errno));

		ret = fn(out, in, keep_cr);

		fclose(out);
		fclose(in);

		if (ret)
			return error(_("could not parse patch '%s'"), *paths);
	}

	state->cur = 1;
	state->last = i;
	return 0;
}