		if (!strcmp(*paths, "-"))
			in = stdin;
		else
			in = fopen(*paths, "r");

		if (!in)
			return error_errno(_("could not open '%s' for reading"),
					   *paths);

		mail = mkpath("%s/%0*d", state->dir, state->prec, i + 1);

		out = fopen(mail, "w");
		if (!out)
			return error_errno(_("could not open '%s' for writing"),
					   mail);

		ret = fn(out, in, keep_cr);

		fclose(out);
		fclose(in);

